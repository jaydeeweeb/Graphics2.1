#pragma pack_matrix(row_major) // treats all matricies to row major

struct MyVertex
{
	float4 xyzw : SV_POSITION;
	float4 rgba : OCOLOR;
	int vertID : ID;

};

cbuffer SHADER_VARS : register(b0) //Register assigns to variable name, b = buffer, t = textures, s = samplers
{
	float4x4 worldMatrix;
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
	int toggleStar[16 * 63];
};

//cbuffer SHADER_STARS : register(b1) //Register assigns to variable name, b = buffer, t = textures, s = samplers
//{
//	int starsArray[1000];
//};

struct GSOutput
{
	float4 pos : SV_POSITION;
	float4 rgba : OCOLOR;
};

[maxvertexcount(3)]

void main(
	point MyVertex input[1],
	inout PointStream< GSOutput > output
)
{
	GSOutput element;
	element.pos = input[0].xyzw;
	element.rgba = input[0].rgba;


	element.pos = mul(element.pos, viewMatrix);
	element.pos = mul(element.pos, projectionMatrix);


	if(toggleStar[input[0].vertID] == 0)
	output.Append(element); //Sends to rasterizer

}