cbuffer cbInfo
{
    uint curLevel;
    uint totalLevels;
    uint subVoxels;
    uint curNodes;
};

cbuffer cbBrickInfo
{
    uint3 brickExtent;
};

cbuffer cbGroupInfo
{
    uint3 groupSize;
};

struct Node
{
    uint brickPtr;
    uint childPtr;
};

StructuredBuffer<Node> nodesPool;
RWBuffer<int> numNode;

RWTexture3D<uint> bricksPool_color;
RWTexture3D<uint> bricksPool_normal;
RWTexture3D<uint> bricksPool_irrandiance;

float3 u32tofloat3(uint value)
{
    uint r = (value & 0x00FF0000) >> 16;
    uint g = (value & 0x0000FF00) >> 8;
    uint b = (value & 0x000000FF);
    return float3(float(r) / 255.0f, float(g) / 255.f, float(b) / 255.f);
}

uint rgba2u32(float r,float g,float b,float a)
{
    uint R = uint(r * 255.0f);
    uint G = uint(g * 255.0f);
    uint B = uint(b * 255.0f);
    uint A = uint(a * 255.0f);
    return (0 << 24) + (R << 16) + G << 8 + B;
}

uint3 brickPtr2Index(uint brickIndex)
{
    uint bz = brickIndex / (brickExtent.x * brickExtent.y);
    brickIndex %= (brickExtent.x * brickExtent.y);
    uint by = brickIndex / brickExtent.x;
    uint bx = brickIndex % brickExtent.x;
    return uint3(bx, by, bz);
}

[numthreads(1,1,1)]
void main(uint3 DTid:SV_DispatchThreadID)
{
    uint index = DTid.x + DTid.y * groupSize.x;
    if (index >= curNodes)
        return;
    uint offset = 0;
    for (uint level = 0; level < curLevel; ++level)
    {
        offset += numNode[level];
    }
    index += offset;

    if (!nodesPool[index].childPtr & 0x80000000)
        return;
    
    uint childPos = (nodesPool[index].childPtr & 0x3FFFFFFF);
    uint3 fb = brickPtr2Index(nodesPool[index].brickPtr);
    fb *= 2;
    uint3 loopindex[] =
    {
        uint3(0, 0, 0), uint3(1, 0, 0),
        uint3(0, 1, 0), uint3(0, 0, 1),
        uint3(1, 1, 0), uint3(1, 0, 1),
        uint3(0, 1, 0), uint3(1, 1, 1)
    };

    for (uint i = 0; i < 8;++i)
    {
        uint3 bi = brickPtr2Index(nodesPool[childPos++].brickPtr);
        bi *= 2;
        float weight = 0.f;
        float3 c = float3(0.0f,0.0f,0.0f);
        float3 n = float3(0.f,0.f,0.f);
        
        for (int j = 0; j < 8;j++)
        {
            uint ic = bricksPool_color[bi + loopindex[j]];
            uint inn = bricksPool_normal[bi + loopindex[j]];
            if(!ic)
                continue;
            weight += 1.f;
            c += u32tofloat3(ic);
            n += u32tofloat3(inn);
        }
        if(weight <0.01f)
            weight = 1.f;

        c /= weight;
        n /= weight;
        n = normalize(n);

        bricksPool_color[fb + loopindex[i]] = rgba2u32(c.x, c.y, c.z, 0.f);
        bricksPool_normal[fb + loopindex[i]] = rgba2u32(n.x, n.y, n.z, 0.f);
        bricksPool_irrandiance[fb + loopindex[i]] = 0;

    }

}
