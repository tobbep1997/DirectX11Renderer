cbuffer WORLD_BUFFER : register (b0)
{
    float4x4 worldMatrix;       //rotation * scale * translation
    float4x4 viewProjection;    //view * projection
};

struct VS_INPUT
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD;
};

float4 main( VS_INPUT input ) : SV_Position
{
    return mul(input.pos, mul(worldMatrix, viewProjection));
    //return mul(input.pos, worldMatrix);
}