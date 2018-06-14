SamplerState sampState : register(s0);
Texture2D txDiffuse : register(t0);

cbuffer LIGHT_BUFFER : register(b0)
{
    int4    info[64];
    float4  position[64];
    float4  direction[64];
    float4  l_color[64];
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
    float2 texCoord : TEXCOORD;
};

float4 main(VS_OUTPUT input) : SV_TARGET
{
    float4 color = txDiffuse.Sample(sampState, input.texCoord);
    float4 ambient = float4(0.1, 0.1, 0.1, 0.1) * color;

    float4 posToCam = cameraPosition - input.worldPos;
    float4 posToLight = float4(0, 0, 0, 0);
    float4 dif = float4(0, 0, 0, 1);
    float4 spec = float4(0, 0, 0, 1);
    float specmult;

    for (int i = 0; i < info[0].x; i++)
    {
        posToLight = position[i] - input.worldPos;

        dif +=  (saturate(l_color[i] * color) * max(dot(input.normal, normalize(posToLight.xyz)), 0.0));

        specmult = dot(input.normal, normalize(posToCam.xyz + posToLight.xyz));
        if (specmult >= 0)
        {
            spec += l_color[i] * max(pow(specmult, 32), 0.0);
        }
 
    }
    return min(ambient + spec + dif, float4(1, 1, 1, 1));
}