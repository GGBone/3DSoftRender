#include "CommonInclude.hlsl"

struct GeometryPassOutput
{
    float4 position : SV_Target0;
    float4 normal : SV_Target1;
    float4 albedo : SV_Target2;
    float4 specular : SV_Target3;
};
GeometryPassOutput PS_GeometryPass(VertexShaderOutput IN)
{
    GeometryPassOutput output;
    return output;
}



float4 PS_GBuffer_Lighting_Pass()
{

}