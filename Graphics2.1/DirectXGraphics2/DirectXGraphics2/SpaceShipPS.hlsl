Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);


struct OutputVertex //Matches with output of vertex shader
{
    float4 xyzw : SV_Position;
    float3 nrm : ONORMAL;
    float2 tex : OTEXCOORD;
};

cbuffer SHADER_VARS : register(b0) //Register assigns to variable name, b = buffer, t = textures, s = samplers
{
    float4 dirLightDirection;
    float4 dirLightColor;
    float4 camPos;
    float4 padding;
};

float4 main(OutputVertex inputPixel) : SV_TARGET
{    

    float4 surfaceColor = txDiffuse.Sample(samLinear, inputPixel.tex.xy);
    float4 lightColor = { 1,1,1,1 };
    float3 lightDir = { 0.5f, -0.5f, 0.0 };
    lightDir = normalize(lightDir);
    //dot(-lightDir, inputPixel.nrm) Is Angular Attenuation (returns 0 - 1) 0 = Perpendicular, 1 = parallel
    float attenuation = saturate(dot(-dirLightDirection, inputPixel.nrm));
    float4 finalDirLightColor = dirLightColor * surfaceColor * attenuation;
    return finalDirLightColor;
}



//DIRECTIONAL LIGHT
//float4 surfaceColor = txDiffuse.Sample(samLinear, inputPixel.tex.xy);
//float4 lightColor = { 1,1,1,1 };
//float3 lightDir = { 0.5f, -0.5f, 0.0 };
//lightDir = normalize(lightDir);
////dot(-lightDir, inputPixel.nrm) Is Angular Attenuation (returns 0 - 1) 0 = Perpendicular, 1 = parallel
//float attenuation = saturate(dot(-lightDir, inputPixel.nrm));
//float4 finalDirLightColor = lightColor * surfaceColor * attenuation;
//return finalDirLightColor;