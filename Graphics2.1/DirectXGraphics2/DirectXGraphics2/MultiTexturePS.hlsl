texture2D baseTex : register(t0);
texture2D detailTex : register(t1);
SamplerState filters[2] : register (s0);

float4 main(float2 baseUV: TEXCOORD0, float2 detailUV : TEXCOORD1, float4 modulate : COLOR) : SV_TARGET
{
	float4 baseColor = baseTex.Sample(filters[0], baseUV) * modulate; //base color
	float4 detailColor = detailTex.Sample(filters[1], detailUV); //get details
	float4 finalColor = float4(lerp(baseColor.rgb, detailColor.rgb, detailColor.a), baseColor.a);
	return finalColor;
}