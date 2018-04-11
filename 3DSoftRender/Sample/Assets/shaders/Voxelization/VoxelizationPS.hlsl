cbuffer cbAttri
{
    float4 extent;
    float4 origin;
};
struct Voxel
{
    float3 pos;
    uint normal;
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

//RWTexture3D texture;

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
    v.pos.y = (-pin.posW.y + origin.y) / extent.y;
    v.pos.z = (pin.posW.z - origin.z) / extent.z;
    float4 color = diffuseMap.Sample(sam, pin.tex);
    v.color = rgba2u32(color.r, color.g, color.b, color.a);
    v.normal = 1;
    FragmentList.Append(v);
    InterlockedAdd(voxelIndex[0], 1);
}

//float3 scaleAndBias(float3 p)
//{
//    return 0.5f * p + float3(0.5f);
//}

//bool isInsideCube(float3 p,float e)
//{
//    return abs(p.x) < 1 + e && abs(p.y) < 1 + e && abs(p.z) < 1 + e;
//}
//void main(GeometryOut pin)
//{
//    float3 color = float3(0.0f);
//    if (!isInsideCube(pin.posW, 0))
//        return;
//    float alpha = 0.5f;
//    float3 vox = scaleAndBias(pin.posW);
//    float3 dim;
//    texture.GetDimensions(dim.x, dim.y, dim.z);
//    texture[dim * vox] = 1.0f;
//}