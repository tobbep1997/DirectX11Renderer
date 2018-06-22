cbuffer WORLD_BUFFER : register (b0)
{
    float4x4 worldMatrix;       //rotation * scale * translation
    float4x4 viewProjection;    //view * projection
};

struct VS_INPUT
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float3 tangent : TANGENT;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 worldPos : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float3 tangent : TANGENT;
};
VS_OUTPUT main( VS_INPUT input )
{
    VS_OUTPUT o;
    
    
    //  Here we multiply the position to world and projection space
    o.pos = mul(input.pos, mul(worldMatrix, viewProjection));
    o.worldPos = mul(input.pos, worldMatrix);
    //  The normal must also be moved to worldspace 
    o.normal = normalize(mul(float4(input.normal, 0), worldMatrix).xyz);
    o.tangent = normalize(mul(float4(input.tangent, 0), worldMatrix).xyz);
    //  We just pass the texCoods 
    o.texCoord = input.texCoord;
    return o;
}