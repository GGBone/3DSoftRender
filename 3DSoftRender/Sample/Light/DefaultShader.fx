
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

float4 VS( float4 Pos : POSITION ) : SV_POSITION
{
	float4 OPOS;
	OPOS = mul(Pos, model);
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