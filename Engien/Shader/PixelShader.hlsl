SamplerState sampState : register(s0);
Texture2D txDiffuse : register(t0);
Texture2D txNormal : register(t1);
Texture2D txShadow : register(t2);

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

cbuffer TEX_INFO : register(b3)
{
    bool useTex;
    bool useNormal;
    bool pad0;
    bool pad1;
}

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 worldPos : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float3 tangent : TANGENT;
};

float4 main(VS_OUTPUT input) : SV_TARGET
{
    float4 color = float4(1, 0, 1, 1);
    if (useTex)
        color = txDiffuse.Sample(sampState, input.texCoord);

    float4 ambient = float4(0.1, 0.1, 0.1, 1) * color;

    //return float4(input.normal, 1);

    if (useNormal)
    {
        float3 n = txNormal.Sample(sampState, input.texCoord).xyz;
        n = (2.0f * n) - 1.0f;
        float3 biTangent = cross(input.normal, input.tangent);

        float3x3 texSpace = float3x3(input.tangent, biTangent, input.normal);

        input.normal = normalize(mul(n, texSpace));
    }
    
    

    float4 posToCam = cameraPosition - input.worldPos;
    float4 posToLight = float4(0, 0, 0, 0);
    float4 dif = float4(0, 0, 0, 1);
    float4 spec = float4(0, 0, 0, 1);
    float specmult = 0;
    float distanceToLight = 0;
    float attenuation = 0;
    float difMult = 0;

    for (int i = 0; i < info[0].x; i++)
    {


        if (info[i].y == 0)
        {
            posToLight = position[i] - input.worldPos;

            distanceToLight = length(posToLight);
            attenuation = 1.0 / (1.0 + 0.01 * pow(distanceToLight, 2));

            difMult = max(dot(input.normal, normalize(posToLight.xyz)), 0.0);
            if (difMult > 0)
                dif += attenuation * (saturate(l_color[i] * color) * difMult);

            //specmult = dot(input.normal, normalize(posToCam.xyz + posToLight.xyz));
            //if (specmult > 0)
                //spec += attenuation * l_color[i] * max(pow(abs(specmult), 32), 0.0);
            
        }
        else if (info[i].y == 1)
        {
            distanceToLight = length(posToLight);
            attenuation = 1.0 / (1.0 + 0.01 * pow(distanceToLight, 2));

            difMult = max(dot(input.normal, -direction[i].xyz), 0.0);
            if (difMult > 0)
                dif += (saturate(l_color[i] * color) * difMult);

            specmult = dot(input.normal, normalize(posToCam.xyz - direction[i].xyz));
            if (specmult > 0)
                spec += attenuation * l_color[i] * max(pow(abs(specmult), 32), 0.0);
        }
        else if (info[i].y == 2)
        {
            posToLight = position[i] - input.worldPos;

            float cone = max(dot(normalize(posToLight), -direction[i]), 0);

            difMult = max(dot(input.normal, normalize(posToLight.xyz)), 0.0);
            if (difMult > 0 && cone > .5)
                dif += (saturate(l_color[i] * color) * difMult);
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