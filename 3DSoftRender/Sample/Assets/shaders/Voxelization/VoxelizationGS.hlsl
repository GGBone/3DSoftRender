
// 0 proj from z
// 1 proj from x
// 2 proj form y
cbuffer cbProj
{
    float4x4 vproj[3];

};

struct VertexOut
{
    float3 posW : POSITION;
    float3 normalW : NORMAL;
    float2 tex : TEXCOORD;
};

struct GeometryOut
{
    float4 posH : SV_POSITION;
    float3 posW : POSITION;
    float3 normalW : NORMAL;
    float2 tex : TEXCOORD;
};




[maxvertexcount(3)]
void main(
	triangle VertexOut gin[3],
	inout TriangleStream<GeometryOut> gout
)
{
    float3 n = normalize((gin[0].normalW + gin[1].normalW + gin[2].normalW) / 3);
    static float3 axis[3] = { float3(0, 0, 1), float3(1, 0, 0), float3(0, 1, 0) };



    uint maxAxis = 0;
    int l = 0;
    for (uint i = 0; i < 3; ++i)
    {
        int t = abs(dot(n, axis[i]));
        if (t > l)
        {
            t = l;
            maxAxis = i;
        }
    }
    GeometryOut g;
    for (uint v = 0; v < 3; ++v)
    {
        g.posH = mul(float4(gin[v].posW, 1.f), vproj[maxAxis]);
        g.posH.w = 1.f;
        g.posW = gin[v].posW;
        g.normalW = float3(maxAxis, maxAxis, maxAxis);
        g.tex = gin[v].tex;
        gout.Append(g);
    }
	
}


//[maxvertexcount(3)]
//void main(
//	triangle VertexOut gin[3],
//	inout TriangleStream<GeometryOut> gout
//)
//{
//    GeometryOut g;
//    float3 p1 = gin[1].posW - gin[0].posW;
//    float3 p2 = gin[2].posW - gin[0].posW;
//    float3 p = abs(cross(p1, p2));
//    for (
//    uint i = 0; i < 3; ++i)
//    {
//        g.posW = gin[i].posW;
//        g.normalW = gin[i].normalW;
//        if (p.z > p.x && p.z > p.y)
//        {
//            g.posH = float4(g.posW.x, g.posW.y, 0, 1);
//        }
//        else if (p.x > p.y && p.x > p.z)
//        {
//            g.posH = float4(g.posW.y, g.posW.z, 0, 1);
//        }
//        else
//        {
//            g.posH = float4(g.posW.x, g.posW.z, 0, 1);
//        }
//        g.tex = gin[i].tex;
//        gout.Append(g);
//    }
//    gout.RestartStrip();
//}