cbuffer cbTrans
{
    float4x4 vp;
};

struct VisualPackage
{
    float4x4 world;
    float4 normal;
    float4 color;
};

struct VertexIn
{
    float3 posL : POSITION;
    uint index : INDEX;
};

struct VertexOut
{
    float4 posH : SV_Position;
    float3 normalW : NORMAL;
    float3 color : COLOR;
};

StructuredBuffer<VisualPackage> visualPool;

VertexOut main(VertexIn vin)
{
    VertexOut vout;
    VisualPackage visual = visualPool[vin.index];
    vout.posH = mul(float4(vin.posL, 1.f), mul(visual.world, vp));

    vout.color = float3(saturate(-vout.posH.r*vin.index/1000.0f), saturate(vout.posH.g*vin.index / 1000.0f), saturate(vout.posH.b*vin.index / 500.0f));
    return vout;
}