
cbuffer Model : register(b0)
{
    matrix world;
};

cbuffer View : register(b1)
{
 
    matrix view;

};

cbuffer Project : register(b2)
{

    matrix project;
};


cbuffer LightBuffer : register(b3)
{
    int g_NumLights;
    float3 vLightDir[1];
    float4 vLightColor[1];
    float4 vOutputColor;
    float g_fTime;
};

struct VS_Input
{
    float4 pos_model  : POSITION;
    float3 normal_model :NORMAL0;
    float2 TexUV : TEXCOORD0;
    //float3 color : COLOR0;
};


struct VS_Output
{
    float4 position : SV_POSITION;
    float4 Diffuse : COLOR0;
    float2 TexUV : TEXCOORD0;
};

VS_Output VS( VS_Input IN)
{
    VS_Output output;
    float3 vNormalWorldSpace;
    //Transform position
    output.position = mul(IN.pos_model, world);
    output.position = mul(output.position,view);
    output.position = mul(output.position,project);

    //Transform the normal
    vNormalWorldSpace = normalize(mul(IN.normal_model,(float3x3)world));

    //Conpute simple directional lighting equation
    float vTotalDiffuseColor = float3(0,0,0);
	for (int i = 0; i < g_NumLights; i++)
	{
		vTotalDiffuseColor += g_LightDiffuse * max(0, dot(vNormalWorldSpace, g_LightDir));
	}

    output.Diffuse.rgb = g_MaterialDiffuseColor * vTotalDiffuseColor +
    g_MaterialAmbientColor * g_LightAmbient;

    output.Diffuse.a = 1.0f;

    output.TexUV = IN.TexUV;

    return output;
}



//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_Output psIn) : SV_Target
{
    return psIn.Diffuse;
}

struct PSOutput
{
      float3 normal_viewspace;
      float3 normal_worldspace;
      float3 vertex_viewspace;
      float3 vertex_worldspace;
};
PSOutput PhongPS(VS_Output psIn)
{
    
}