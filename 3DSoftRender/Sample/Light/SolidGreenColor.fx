
cbuffer PerObject : register(b0)
{
	matrix model;
};

cbuffer PerView : register(b1)
{
	matrix view;
};

cbuffer PerProjection : register(b2)
{
	 matrix projection;
};
struct VS_Input
{
    float4 pos  : POSITION;
    float2 tex0 : TEXCOORD0;
};

struct PS_Input
{
    float4 pos  : SV_POSITION;
    float2 tex0 : TEXCOORD0;
};


PS_Input VS_Main( VS_Input vertex )
{
    PS_Input vsOut = ( PS_Input )0;
    vsOut.pos = vertex.pos;
    vsOut.tex0 = vertex.tex0;

    return vsOut;
}

float4 PS_Main(PS_Input frag ):SV_Target
{  
    //return colorMap_.Sample( colorSampler_, frag.tex0 ); 
    return float4(1.0f,1.0f,0.0f,1.0f);
}  

float4 VS( float4 Pos : POSITION ) : SV_POSITION
{
	float4 OPOS;
	OPOS = mul(Pos, model);
	OPOS = mul(OPOS, view);
	OPOS = mul(OPOS, projection);
    return OPOS;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( float4 Pos : SV_POSITION ) : SV_Target
{
	return float4(1.0f,0.0f,1.0f,1.0f);
}