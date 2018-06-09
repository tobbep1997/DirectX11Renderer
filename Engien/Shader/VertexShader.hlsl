cbuffer WORLD_BUFFER : register (b0)
{
    float4x4 worldMatrix;
    float4x4 viewProjection;
};

struct VS_INPUT
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 worldPos : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
};
VS_OUTPUT main( VS_INPUT input )
{
    VS_OUTPUT o;
    o.pos = mul(input.pos, mul(worldMatrix, viewProjection));
    o.worldPos = mul(input.pos, worldMatrix);
    o.normal = mul(float4(input.normal, 0), worldMatrix).xyz;
    o.texCoord = input.texCoord;
    return o;
}