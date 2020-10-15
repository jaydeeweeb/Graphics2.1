

struct MyVertex
{
	float4 xyzw : SV_POSITION;
	float4 rgba : COLOR;
};

cbuffer SHADER_VARS : register(b0) //Register assigns to variable name, b = buffer, t = textures, s = samplers
{
	float4x4 worldMatrix;
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
};

cbuffer SHADER_STARS : register(b1) //Register assigns to variable name, b = buffer, t = textures, s = samplers
{
	MyVertex starsArray[1000];
};

struct GSOutput
{
	float4 rgba : OCOLOR;
	float4 pos : SV_POSITION;
};

[maxvertexcount(3)]

void main(
	point MyVertex input[1],
	inout PointStream< GSOutput > output
)
{

	for (uint i = 0; i < 1000; i++)
	{
		GSOutput element;
		element.pos = starsArray[i].xyzw;
		element.rgba = starsArray[i].rgba;
		element.pos = mul(element.pos, viewMatrix);
		element.pos = mul(element.pos, projectionMatrix);
		//element.pos = float4(0, 0, 1, 1);
		//element.rgba = float4(1, 1, 1, 1);
		output.Append(element);
	}
}