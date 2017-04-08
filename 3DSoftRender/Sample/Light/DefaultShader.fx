
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
    float4 normal :NORMAL0;
    float3 color : COLOR0;
};

float4 VS( VS_Input IN) : SV_POSITION
{
	float4 OPOS;
	OPOS = mul(IN.pos, model);
    OPOS = mul(OPOS,view);
    OPOS = mul(OPOS,project);
    return OPOS;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( float4 Pos : SV_POSITION ) : SV_Target
{
	return float4(1.0f,1.0f,0.0f,1.0f);
}