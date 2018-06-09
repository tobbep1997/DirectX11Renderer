SamplerState sampState : register(s0);
Texture2D txDiffuse : register(t0);

cbuffer LIGHT_BUFFER : register(b0)
{
    int4    info[256];
    float4  position[256];
    float4  direction[256];
    float4  l_color[256];
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
    float4 color = txDiffuse.Sample(sampState, input.uv);
    float4 ambient = float4(0.1, 0.1, 0.1, 0.1) * color;

    float4 posToCam = cameraPosition - input.worldPos;
    float4 posToLight;
    float4 dif;
    float4 spec = 0;
    for (int i = 0; i < info[0].x; i++)
    {
        posToLight = position[i] - input.worldPos;
        dif += l_color[i] * color * max(dot(input.normal, normalize(posToLight.xyz)), 0.0);
        spec += l_color[i] * max(pow(dot(input.normal, normalize(posToCam.xyz + posToLight.xyz)), 32), 0);
    }


    return saturate(ambient + spec + dif);
}