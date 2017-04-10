
cbuffer Model : register(b0)
{
	matrix model;
};

cbuffer View : register(b1)
{
 
    matrix view;

};

cbuffer Project : register(b2)
{
    matrix project;
};

struct VS_Input
{
    float4 pos  : POSITION;
    float3 normal :NORMAL0;
    float2 Tex : TEXCOORD0;
    //float3 color : COLOR0;
};

struct VS_Output
{
	float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

VS_Output VS( VS_Input IN)
{
	VS_Output output;
	output.Pos = mul(IN.pos, model);
    output.Pos = mul(output.Pos,view);
    output.Pos = mul(output.Pos,project);
    output.Tex = IN.Tex;
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_Output psIn) : SV_Target
{
	return float4(1.0f,1.0f,0.0f,1.0f);
}