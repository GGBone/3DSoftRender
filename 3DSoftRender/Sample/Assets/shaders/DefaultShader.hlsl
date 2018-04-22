struct VertexShaderOutput
{
    float3 positionVS   : TEXCOORD0;    // View space position.
    float2 texCoord     : TEXCOORD1;    // Texture coordinate
    float3 tangentVS    : TANGENT;      // View space tangent.
    float3 binormalVS   : BINORMAL;     // View space binormal.
    float3 normalVS     : NORMAL;       // View space normal.
    float4 position     : SV_POSITION;  // Clip space position.
};

struct AppData
{
    float3 position : POSITION;
    float3 tangent  : TANGENT;
    float3 binormal : BINORMAL;
    float3 normal   : NORMAL;
    float2 texCoord : TEXCOORD0;
};
struct Material
{
    float4  GlobalAmbient;
    //-------------------------- ( 16 bytes )
    float4  AmbientColor;
    //-------------------------- ( 16 bytes )
    float4  EmissiveColor;
    //-------------------------- ( 16 bytes )
    float4  DiffuseColor;
    //-------------------------- ( 16 bytes )
    float4  SpecularColor;
    //-------------------------- ( 16 bytes )
    // Reflective value.
    float4  Reflectance;
    //-------------------------- ( 16 bytes )
    float   Opacity;
    float   SpecularPower;
    // For transparent materials, IOR > 0.
    float   IndexOfRefraction;
    bool    HasAmbientTexture;
    //-------------------------- ( 16 bytes )
    bool    HasEmissiveTexture;
    bool    HasDiffuseTexture;
    bool    HasSpecularTexture;
    bool    HasSpecularPowerTexture;
    //-------------------------- ( 16 bytes )
    bool    HasNormalTexture;
    bool    HasBumpTexture;
    bool    HasOpacityTexture;
    float   BumpIntensity;
    //-------------------------- ( 16 bytes )
    float   SpecularScale;
    float   AlphaThreshold;
    float2  Padding;
    //--------------------------- ( 16 bytes )
};  //--------------------------- ( 16 * 10 = 160 bytes )

cbuffer PerObject : register( b0 )
{
    float4x4 ModelViewProjection;
    float4x4 ModelView;
}

cbuffer Material : register( b2 )
{
    Material Mat;
};
VertexShaderOutput VS_main(AppData IN)
{
	VertexShaderOutput OUT;

	OUT.position = mul(ModelViewProjection, float4(IN.position, 1.0f));

	OUT.positionVS = mul(ModelView, float4(IN.position, 1.0f)).xyz;
	OUT.tangentVS = mul((float3x3)ModelView, IN.tangent);
	OUT.binormalVS = mul((float3x3)ModelView, IN.binormal);
	OUT.normalVS = mul((float3x3)ModelView, IN.normal);

	OUT.texCoord = IN.texCoord;

	return OUT;
}

[earlydepthstencil]
float4 PS_main(VertexShaderOutput IN):SV_TARGET
{
    Material mat = Mat;
    float4 diffuse = mat.DiffuseColor;
 

    return diffuse;
   
}