Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);


struct OutputVertex //float4
{
    float4 xyzw : SV_Position;
    float3 nrm : ONORMAL;
    float2 tex : OTEXCOORD;
};

float4 main(OutputVertex inputPixel) : SV_TARGET
{
    return txDiffuse.Sample(samLinear, inputPixel.tex.xy);
}