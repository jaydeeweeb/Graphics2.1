Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);


struct OutputVertex
{
    //float4 xyzw : SV_Position;
    float4 rgba : OCOLOR;
   // float3 uvw : OTEXCOORD;
    //float3 nrm : ONORMAL;


};

float4 main(OutputVertex inputPixel) : SV_TARGET
{
    //return txDiffuse.Sample(samLinear, inputPixel.uvw.xy);
    return inputPixel.rgba;
}