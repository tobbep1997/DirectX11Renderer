cbuffer WORLD_BUFFER : register (b0)
{
    float4x4 worldMatrix;
    float4x4 viewProjection;
};

struct VS_INPUT
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 worldPos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};
float4 main( VS_INPUT input ) : SV_POSITION
{
    return mul(input.pos, mul(worldMatrix, viewProjection));
}