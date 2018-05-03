#include "..\CommonInclude.hlsl"

//My Implementation
//struct NodeStructure
//{
//    float4 color;
//    float2 deepthAndPrev;
//};
//RWBuffer<int> HeaderPointer;
//AppendStructuredBuffer<NodeStructure> nodeBuffer;
//RWBuffer<int> nodeCount;
//cbuffer ScreenSize : register(b5)
//{
//    uint width;
//    uint height;
//}
//PS_Output PS_Main(VS_Output vs_output)
//{
//    uint index = pos.y * width + pos.x;
//    uint oldValue;
//    InterlockedExchange(HeaderPointer[index], nodeCount, oldValue);
//    NodeStructure currNode;
//    currNode.color = mColor;
//    currNode.depthAndPrev = float2(depth, oldValue);
//    nodeBuffer.Addend(currNode);
//    InterIockedAdd(nodeCount[0], 1);
//}
cbuffer ScreenSize
{
    float width;
    float height;
}
struct FragmentData_STRUCT
{
    float4 color;
    float depth;
};

struct FragmentAndLinkBuffer_STRUCT
{
    FragmentData_STRUCT FragmentData;
    uint nNext;
};
RWStructuredBuffer<FragmentAndLinkBuffer_STRUCT> FLBuffer;

//Screen-sized (width * height * sizeof(UINT32)) Declaration:
RWByteAddressBuffer StartOffsetBuffer;
/*
Linked ListCreation *No ColorRender 
                    *Depth bufferbound if needed(OIT need it in a few slieds).
                    *UAVs bounds as input/output StartOffsetBuffer(R/W) FragmentAndLinkBuffer(W)
*/
void CreateLinkList(VertexShaderOutput IN)
{
    float2 screenPos = IN.position.xy / IN.position.z;
    float depth = IN.position.z/IN.position.w;
    float4 color = Mat.DiffuseColor;
    FragmentData_STRUCT data;
    data.color = color;
    data.depth = depth;
    uint uPixelCount = FLBuffer.IncrementCounter();
    uint uStartOffsetAddress = 4 * screenPos.y * width + screenPos.x;
    uint uOldStartOffset;
    StartOffsetBuffer.InterlockedExchange(uStartOffsetAddress, uPixelCount, uOldStartOffset);
    FragmentAndLinkBuffer_STRUCT Element;
    Element.FragmentData = data;
    Element.nNext = uOldStartOffset;
    FLBuffer[uPixelCount] = Element;
}

void ProcessPixel(FragmentAndLinkBuffer_STRUCT element, inout float4 color)
{
    //blend
    color += element.FragmentData.color;
}

float4 RenderLinkList(float x,float y)
{
    uint uStartOffsetAddress = 4 * (y * width + x);
    uint uNodePos = StartOffsetBuffer.Load(uStartOffsetAddress);
    float4 color = 0.0f;
    while (uNodePos != -1)
    {
        FragmentAndLinkBuffer_STRUCT element = FLBuffer[uNodePos];
        //Process Pixel 
        ProcessPixel(element, color);
        uNodePos = element.nNext; 
        
    } 
    return color; 
}


float4 PS_main(VertexShaderOutput IN) : SV_TARGET
{
    float2 screenPos = IN.position.xy / IN.position.z;
    CreateLinkList(IN);
    return RenderLinkList(screenPos.x, screenPos.y);
}