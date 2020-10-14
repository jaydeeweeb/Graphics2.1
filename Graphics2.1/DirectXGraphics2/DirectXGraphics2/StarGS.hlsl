
struct MyVertex
{
	float4 xyzw : SV_POSITION;
	float4 rgba : COLOR;
};

struct GSOutput
{
	float4 pos : SV_POSITION;
	float4 rgba : OCOLOR;
};

[maxvertexcount(3)]

void main(
	point MyVertex input[1],
	inout TriangleStream< GSOutput > output
)
{

	for (uint i = 0; i < 3; i++)
	{
		GSOutput element;
		element.pos = input[0].xyzw;
		element.rgba = input[0].rgba;
		output.Append(element);
	}
}