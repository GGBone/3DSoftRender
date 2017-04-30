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

/*
Nodes Pool
Read - Write
*/

RWStructuredBuffer<Node> nodesPool;
RWBuffer<int> brickIndex;
RWBuffer<int> numNode;
RWBuffer<int> nodeIndex;

[numthreads(1,1,1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    
}