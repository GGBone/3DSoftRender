cbuffer cbAttri
{
    float4 extent;
    float4 origin;
};
struct Voxel
{
    float3 pos;
    float4 normal;
    uint color;
};


struct GeometryOut
{
    float4 posH : SV_POSITION;
    float3 posW : POSITION;
    float3 normalW : NORMAL;
    float2 tex : TEXCOORD;
};

SamplerState sam;
AppendStructuredBuffer<Voxel> FragmentList;
RWBuffer<int> voxelIndex;

Texture2D diffuseMap;

uint rgba2u32(float r, float g, float b, float a)
{
    uint R = uint(r * 255.f);
    uint G = uint(g * 255.f);
    uint B = uint(b * 255.f);
    uint A = uint(a * 255.f);
    return (0 << 24) | (R << 16) | (G << 8) | B;
}

void main(GeometryOut pin)
{
    Voxel v;
    v.pos.x = (pin.posW.x - origin.x) / extent.x;
    v.pos.y = (pin.posW.x - origin.y) / extent.y;
    v.pos.z = (pin.posW.x - origin.z) / extent.z;
    float4 color = diffuseMap.Sample(sam, pin.tex);
    v.color = rgba2u32(color.r, color.g, color.b, color.a);
    v.normal = 1;
    FragmentList.Append(v);
    InterlockedAdd(voxelIndex[0], 1);
}