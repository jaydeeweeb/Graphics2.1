Texture2D txDiffuse : register(t0);
Texture2D specMap : register(t1);

SamplerState samLinear : register(s0);


struct OutputVertex //Matches with output of vertex shader
{
    float4 xyzw : SV_Position;
    float3 nrm : ONORMAL;
    float2 tex : OTEXCOORD;
    float3 worldPos : POSITION;
};

cbuffer SHADER_VARS : register(b0) //Register assigns to variable name, b = buffer, t = textures, s = samplers
{
    //spot
    float4 spotLightPosition;
    float4 spotLightColor;
    float4 spotLightDir;
    //point
    float4 pointLightPosition;
    float4 pointLightColor;
    //directional
    float4 dirLightDirection;
    float4 dirLightColor;

    float4 camPos;
    float2 padding;
    float innerConeAngle;
    float outerConeAngle;

};

float4 directionalLight(OutputVertex inputPixel);
float4 pointLight(OutputVertex inputPixel);
float4 spotLight(OutputVertex inputPixel);

float4 main(OutputVertex inputPixel) : SV_TARGET
{
    inputPixel.nrm = normalize(inputPixel.nrm);
    //float4 surfaceColor = txDiffuse.Sample(samLinear, inputPixel.tex.xy);
    //float4 lightColor = { 1,1,1,1 };
    //float3 lightDir = { 0.5f, -0.5f, 0.0 };
    //lightDir = normalize(lightDir);
    ////dot(-lightDir, inputPixel.nrm) Is Angular Attenuation (returns 0 - 1) 0 = Perpendicular, 1 = parallel
    //float attenuation = saturate(dot(-dirLightDirection, inputPixel.nrm));
    //float4 finalDirLightColor = dirLightColor * surfaceColor * attenuation;
    //return finalDirLightColor;

    return directionalLight(inputPixel) + pointLight(inputPixel) + spotLight(inputPixel);
}

float4 directionalLight(OutputVertex inputPixel)
{
    float4 normLightDir = normalize(dirLightDirection);
    float4 surfaceColor = txDiffuse.Sample(samLinear, inputPixel.tex.xy);
    float attenuation = saturate(dot(-normLightDir.xyz, inputPixel.nrm.xyz));
    float4 specColor = specMap.Sample(samLinear, inputPixel.tex.xy);


    //Specular lighting
    //Add a sample to get spec texture color 
    float3 reflectVec = reflect(normLightDir.xyz, inputPixel.nrm.xyz);
    float3 toCamera = normalize(camPos.xyz - inputPixel.worldPos.xyz);
    float specAllignment = saturate(dot(reflectVec, toCamera));
    specAllignment = pow(specAllignment, 32);
    float4 finalSpecColor = specColor * float4(1, 1, 1, 1) * specAllignment;  //vSurfaceSpecColor (usually white, could come from SpecMap texture) * vLightSpecColor (white, or light color) * specAllignment;

    float4 finalDirLightColor = dirLightColor * surfaceColor * attenuation;
    return finalDirLightColor + finalSpecColor;
    //LIGHTRATIO = CLAMP(DOT(-LIGHTDIR, SURFACENORMAL))
    //RESULT = LIGHTRATIO * LIGHTCOLOR * SURFACECOLOR
}

float4 pointLight(OutputVertex inputPixel)
{
    float3 lightDir = pointLightPosition.xyz - inputPixel.worldPos;  
    float lightDistance = length(lightDir);
    lightDir /= lightDistance; //normalizes lightDir if you want to add specular to Point Light, it's the same as DirLight, just use this lightDir variable the same way light direction was used above (negate it before reflecting it though, it points the opposite way)
    float4 surfaceColor = txDiffuse.Sample(samLinear, inputPixel.tex.xy);
    float lightRatio = saturate(dot(lightDir, inputPixel.nrm));
    float rangeAttenuation = 1.0 - saturate(lightDistance /500.0);
    float4 specColor = specMap.Sample(samLinear, inputPixel.tex.xy);


    float3 reflectVec = reflect(-lightDir, inputPixel.nrm);
    float3 toCamera = normalize(camPos.xyz - inputPixel.worldPos.xyz);
    float specAllignment = saturate(dot(reflectVec, toCamera));
    specAllignment = pow(specAllignment, 32);
    float4 finalSpecColor =specColor * float4(1, 1, 1, 1) * specAllignment;  //vSurfaceSpecColor (usually white, could come from SpecMap texture) * vLightSpecColor (white, or light color) * specAllignment;

    rangeAttenuation *= rangeAttenuation;
    float4 finalPointLight = (lightRatio * pointLightColor * surfaceColor * rangeAttenuation);
    return finalPointLight + finalSpecColor;
//LIGHTDIR = NORMALIZE(LIGHTPOS � SURFACEPOS)
//LIGHTRATIO = CLAMP(DOT(LIGHTDIR, SURFACENORMAL))
//RESULT = LIGHTRATIO * LIGHTCOLOR * SURFACECOLOR
}

float4 spotLight(OutputVertex inputPixel)
{
    float3 lightDir = spotLightPosition.xyz - inputPixel.worldPos;
    float lightDistance = length(lightDir);
    lightDir /= lightDistance; //normalizes lightDir if you want to add specular to Light, it's the same as DirLight, just use this lightDir variable the same way light direction was used above (negate it before reflecting it though, it points the opposite way)
    float4 surfaceColor = txDiffuse.Sample(samLinear, inputPixel.tex.xy);
    float coneRatio  = saturate(dot(-lightDir.xyz, spotLightDir.xyz));
    //float spotFactor = (coneRatio > coneAngle) ? 1 : 0;
    float spotFactor = saturate((coneRatio - outerConeAngle) / (innerConeAngle - outerConeAngle));
    float lightRatio = saturate(dot(lightDir, inputPixel.nrm));
    float4 specColor = specMap.Sample(samLinear, inputPixel.tex.xy);


    float rangeAttenuation = 1.0 - saturate(lightDistance / 200.0);
    float3 reflectVec = reflect(-lightDir, inputPixel.nrm);
    float3 toCamera = normalize(camPos - inputPixel.worldPos);
    float specAllignment = saturate(dot(reflectVec, toCamera));
    specAllignment = pow(specAllignment, 32);
    float4 finalSpecColor = specColor * float4(1, 1, 1, 1) * specAllignment; //vSurfaceSpecColor (usually white, could come from SpecMap texture) * vLightSpecColor (white, or light color) * specAllignment;
    rangeAttenuation *= rangeAttenuation;

    float4 finalSpotLight = (spotFactor * lightRatio * spotLightColor * surfaceColor * rangeAttenuation);
    return finalSpotLight + finalSpecColor;

    //LIGHTDIR = NORMALIZE(LIGHTPOS � SURFACEPOS) )
    //SURFACERATIO = CLAMP(DOT(-LIGHTDIR, CONEDIR))
    //    SPOTFACTOR = (SURFACERATIO > CONERATIO) ? 1 : 0
    //    LIGHTRATIO = CLAMP(DOT(LIGHTDIR, SURFACENORMAL))
    //    RESULT = SPOTFACTOR * LIGHTRATIO * LIGHTCOLOR * SURFACECOLOR

}
