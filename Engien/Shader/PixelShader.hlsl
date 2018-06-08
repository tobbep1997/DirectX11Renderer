cbuffer LIGHT_BUFFER : register(b0)
{
    int4    info[256];
    float4  position[256];
    float4  direction[256];
    float4  color[256];
}

cbuffer CAMERA_BUFFER : register(b1)
{
    float4 cameraPosition;
}

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 worldPos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

float4 main(VS_OUTPUT input) : SV_TARGET
{
    float4 color = float4(1, 0, 0, 1);
    float4 ambient = float4(0.1, 0.1, 0.1, 0.1) * color;

    float4 posToLight = position[0] - input.worldPos;
    float4 posToCam = cameraPosition - input.worldPos;

    float dif = max(dot(input.normal, normalize(posToLight.xyz)), 0.0);

    float spec = max(pow(dot(input.normal, normalize(posToCam.xyz + posToLight.xyz)), 512), 0);


    return min(ambient + spec + (color * dif), float4(1,1,1,1));
}