SamplerState sampState : register(s0);
Texture2D txDiffuse : register(t0);
Texture2D txShadow : register(t1);

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

cbuffer LIGHT_MATRIX : register(b2)
{
    float4x4 lightViewProjection;
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
    float specmult = 0;
    float distanceToLight = 0;
    float attenuation = 0;
    for (int i = 0; i < info[0].x; i++)
    {
        posToLight = position[i] - input.worldPos;

        distanceToLight = length(posToLight);
        attenuation = 1.0 / (1.0 + 0.1 * pow(distanceToLight, 2));

        dif += (saturate(l_color[i] * color) * max(dot(input.normal, normalize(posToLight.xyz)), 0.0));

        specmult = dot(input.normal, normalize(posToCam.xyz + posToLight.xyz));
        if (specmult > 0)
        {
            spec += attenuation * l_color[i] * max(pow(abs(specmult), 64), 0.0);
        }
 
    }


    float4 lightView = mul(input.worldPos, lightViewProjection); // Translate the world position into the view space of the light
    lightView.xy /= lightView.w; // Get the texture coords of the "object" in the shadow map


    float2 smTex = float2(0.5f * lightView.x + 0.5f, -0.5f * lightView.y + 0.5f); // Texcoords are not [-1, 1], change the coords to [0, 1]
	
    float depth = lightView.z / lightView.w;
    
    if (abs(lightView.x) > 1.0f)							    
        return min(ambient + spec + dif, float4(1, 1, 1, 1));
        
    if (abs(lightView.y) > 1.0f)							    
        return min(ambient + spec + dif, float4(1, 1, 1, 1));


    float shadowCoeff = (txShadow.Sample(sampState, smTex).r + 0.001 < depth) ? 0.2f : 1.0f; // If the depth from camera is larger than depth from light,


    return min((ambient + spec + dif) * shadowCoeff, float4(1, 1, 1, 1));
}