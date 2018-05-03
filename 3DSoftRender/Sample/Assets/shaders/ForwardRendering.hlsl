#include "CommonInclude.hlsl"

VertexShaderOutput VS_main(AppData IN)
{
	VertexShaderOutput OUT;

	OUT.position = mul(ModelViewProjection, float4(IN.position, 1.0f));

	OUT.positionVS = mul(ModelView, float4(IN.position, 1.0f)).xyz;
    OUT.tangentVS = mul(IN.tangent, (float3x3) ModelView);
    OUT.binormalVS = mul(IN.binormal, (float3x3) ModelView);
    OUT.normalVS = mul(IN.normal, (float3x3) ModelView);

	OUT.texCoord = IN.texCoord;

	return OUT;
}


[earlydepthstencil]
float4 PS_main(VertexShaderOutput IN) : SV_TARGET
{
	float4 eyePos = { 0, 0, 0, 1 };
Material mat = Mat;
float4 diffuse = mat.DiffuseColor;
if (mat.HasDiffuseTexture)
{
	float4 diffuseTex = DiffuseTexture.Sample(LinearRepeatSampler, IN.texCoord);
	if (any(diffuse.rgb))
	{
		diffuse *= diffuseTex;
	}
	else
	{
		diffuse = diffuseTex;
	}
}

// By default, use the alpha from the diffuse component.
float alpha = diffuse.a;
if (mat.HasOpacityTexture)
{
	// If the material has an opacity texture, use that to override the diffuse alpha.
	alpha = OpacityTexture.Sample(LinearRepeatSampler, IN.texCoord).r;
}

float4 ambient = mat.AmbientColor;
if (mat.HasAmbientTexture)
{
	float4 ambientTex = AmbientTexture.Sample(LinearRepeatSampler, IN.texCoord);
	if (any(ambient.rgb))
	{
		ambient *= ambientTex;
	}
	else
	{
		ambient = ambientTex;
	}
}
// Combine the global ambient term.
ambient *= mat.GlobalAmbient;

float4 emissive = mat.EmissiveColor;
if (mat.HasEmissiveTexture)
{
	float4 emissiveTex = EmissiveTexture.Sample(LinearRepeatSampler, IN.texCoord);
	if (any(emissive.rgb))
	{
		emissive *= emissiveTex;
	}
	else
	{
		emissive = emissiveTex;
	}
}

if (mat.HasSpecularPowerTexture)
{
	mat.SpecularPower = SpecularPowerTexture.Sample(LinearRepeatSampler, IN.texCoord).r * mat.SpecularScale;
}

float4 N;

// Normal mapping
if (mat.HasNormalTexture)
{
	// For scense with normal mapping, I don't have to invert the binormal.
	float3x3 TBN = float3x3(normalize(IN.tangentVS),
		normalize(IN.binormalVS),
		normalize(IN.normalVS));

	N = DoNormalMapping(TBN, NormalTexture, LinearRepeatSampler, IN.texCoord);
}
// Bump mapping
else if (mat.HasBumpTexture)
{
	// For most scenes using bump mapping, I have to invert the binormal.
	float3x3 TBN = float3x3(normalize(IN.tangentVS),
		normalize(-IN.binormalVS),
		normalize(IN.normalVS));

	N = DoBumpMapping(TBN, BumpTexture, LinearRepeatSampler, IN.texCoord, mat.BumpIntensity);
}
// Just use the normal from the model.
else
{
	N = normalize(float4(IN.normalVS, 0));
}

float4 P = float4(IN.positionVS, 1);

LightingResult lit = DoLighting(Lights, mat, eyePos, P, N);

diffuse *= float4(lit.Diffuse.rgb, 1.0f); // Discard the alpha value from the lighting calculations.

float4 specular = 0;
if (mat.SpecularPower > 1.0f) // If specular power is too low, don't use it.
{
	specular = mat.SpecularColor;
	if (mat.HasSpecularTexture)
	{
		float4 specularTex = SpecularTexture.Sample(LinearRepeatSampler, IN.texCoord);
		if (any(specular.rgb))
		{
			specular *= specularTex;
		}
		else
		{
			specular = specularTex;
		}
	}
	specular *= lit.Specular;
}
    return lit.Specular;
    return float4((ambient + emissive + diffuse + specular).rgb, alpha * mat.Opacity);

}

// Pixel shader for rendering lights (debug) for forward renderer.
float4 PS_light(VertexShaderOutput IN) : SV_TARGET
{
    Material mat = Mat;
    float4 diffuse = mat.DiffuseColor;
    if (mat.HasDiffuseTexture)
    {
        float4 diffuseTexColor = DiffuseTexture.Sample(LinearRepeatSampler, IN.texCoord);
        if (any(diffuseTexColor))
        {
            diffuse *= diffuseTexColor;
        }
        else
            diffuse = diffuseTexColor;
    }
    float alpha = diffuse.a;

    float3 N = normalize(IN.normalVS);
    float4 DiffuseColor = 0.0f;
    float4 LightDirectionVS = float4(mul(Lights[0].DirectionWS, ModelView).xyz, 0.0f);

    float3 L = 0.0f;
    float4 spec = 0.0f;
    if (Lights[0].Type == 0)
    {
    //0 point
        L = Lights[0].PositionVS.xyz - IN.positionVS;
        float distance = length(L);
        L = L / distance;

        float attenuation = DoAttenuation(Lights[0], distance);
        float NdotL = max(dot(N, L), 0);
        DiffuseColor = (Lights[0].Color * NdotL) * attenuation;
    }
    else if (Lights[0].Type == 1)
    {
    //1 spot
        
    }
    else if (Lights[0].Type == 2)
    {
        //2 directional

        L = -normalize(LightDirectionVS);
        float NdotL = min(max(dot(N, L), 0.0f), 1.0f);
        if (NdotL > .000000f)
            DiffuseColor = (Lights[0].Color * NdotL);

         //Light Spec
        float3 R = normalize(reflect(-L, N));
        float RDov = max(dot(R, normalize(-IN.positionVS)), 0.0f);
        spec = (Lights[0].Color) * pow(RDov, mat.SpecularPower) * Lights[0].Intensity;
    }


    float4 specColor = 0;
    if (mat.SpecularPower > 1.0f)
    {
        specColor = mat.SpecularColor;
        specColor *= spec;
    }
    return diffuse * DiffuseColor + specColor;
}

// Used for rendering unlit materials.
float4 PS_unlit(VertexShaderOutput IN) : SV_Target
{
	float4 diffuse = Mat.DiffuseColor;
	if (Mat.HasDiffuseTexture)
	{
		float4 diffuseTex = DiffuseTexture.Sample(LinearRepeatSampler, IN.texCoord);
		if (any(diffuse.rgb))
		{
			diffuse *= diffuseTex;
		}
		else
		{
			diffuse = diffuseTex;
		}
	}

	// By default, use the alpha from the diffuse component.
	float alpha = diffuse.a;
	if (Mat.HasOpacityTexture)
	{
		// If the material has an opacity texture, use that to override the diffuse alpha.
		alpha = OpacityTexture.Sample(LinearRepeatSampler, IN.texCoord).a;
	}

	if (alpha * Mat.Opacity < Mat.AlphaThreshold)
	{
		discard;
	}

	float4 ambient = Mat.AmbientColor;
	if (Mat.HasAmbientTexture)
	{
		float4 ambientTex = AmbientTexture.Sample(LinearRepeatSampler, IN.texCoord);
		if (any(ambient.rgb))
		{
			ambient *= ambientTex;
		}
		else
		{
			ambient = ambientTex;
		}
	}
	// Combine the global ambient term.
	ambient *= Mat.GlobalAmbient;

	float4 emissive = Mat.EmissiveColor;
	if (Mat.HasEmissiveTexture)
	{
		float4 emissiveTex = EmissiveTexture.Sample(LinearRepeatSampler, IN.texCoord);
		if (any(emissive.rgb))
		{
			emissive *= emissiveTex;
		}
		else
		{
			emissive = emissiveTex;
		}
	}

	// Do view space lighting based on normal.
	float4 N = normalize(float4(IN.normalVS, 0));

	return float4((ambient + emissive + (diffuse * N.z)).rgb, alpha * Mat.Opacity);

}