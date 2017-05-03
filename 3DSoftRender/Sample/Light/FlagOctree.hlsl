cbuffer cbInfo
{
    uint curLevel;
    uint totalLevel;
    uint sumVoxels;
    uint curNode;
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

struct Voxel
{
    float3 pos;
    uint normal;
    uint color;
};

StructuredBuffer<Voxel> FragmentList;

RWStructuredBuffer<Node> nodesPool;

uint extralPos(uint childPtr)
{
    return childPtr & 0x3FFFFFFF;
}

[numthreads(16,16,1)]
void main(uint3 DTid:SV_DispatchThreadID)
{
    uint voxelIndex = DTid.x + DTid.y * groupSize.x * 16;
    if(voxelIndex >= sumVoxels)
        return;
    Voxel voxel = FragmentList[voxelIndex];
    uint curIndex = 0;
    for (uint level = 0; level < curLevel;++level)
    {
        int tt = pow(2.0f, level);
        uint xx = uint(frac(voxel.pos.x * tt) * 2.0f);
        uint yy = uint(frac(voxel.pos.y * tt) * 2.0f);
        uint zz = uint(frac(voxel.pos.z * tt) * 2.0f);
        curIndex = extralPos(nodesPool[curIndex].childPtr) + xx + yy * 2 + zz * 4;
    }

    if(curLevel == totalLevel - 1)
    {
        //leaf node
        InterlockedOr(nodesPool[curIndex].childPtr, 0x40000000);
        return;
    }
    InterlockedOr(nodesPool[curIndex].childPtr, 0x80000000);

}