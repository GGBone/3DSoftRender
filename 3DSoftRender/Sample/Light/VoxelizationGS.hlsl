//0 z is dominate
//1 x is dominate
//2 y is dominate
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
    float3 n = normalize(gin[0].normalW + gin[1].normalW + gin[2].normalW);
    static float3 axis[3] =
    {
        float3(0, 0, 1),
        float3(1, 0, 0),
        float3(0, 1, 0)
    };
    uint maxAix = 0;
    for (int i = 0; i < 3;++i)
    {
        int t = abs(dot(n, axis[i]));
        if(t>0)
        {
            t = 0;
            maxAix = i;
        }
    }
    GeometryOut g;
    for (uint v = 0; v < 3; ++ v)
    {
        g.posH = mul(float4(gin[v].posW, 1.0f), vproj[maxAix]);
        g.posH.w = 1.0f;
        g.posW = gin[v].posW;
        g.normalW = float3(maxAix, maxAix, maxAix);
        g.tex = gin[v].tex;
        gout.Append(g);
    }
    gout.RestartStrip();
}
