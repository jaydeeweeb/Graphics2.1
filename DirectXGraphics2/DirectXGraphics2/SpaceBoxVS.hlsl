#pragma pack_matrix(row_major) // treats all matricies to row major

struct InputVertex //Matches inputlayout
{
    float3 pos : POSITION;
    float3 nrm : NORMAL;
    float2 tex : TEXCOORD;
};

struct OutputVertex //float4 Must match Pshader Input
{
    float4 xyzw : SV_Position;
    float3 nrm : ONORMAL;
    float2 tex : OTEXCOORD;
    float3 tex3d : OTEXCOORD2;
};


cbuffer SHADER_VARS : register(b0) //Register assigns to variable name, b = buffer, t = textures, s = samplers
{
    float4x4 worldMatrix;
    float4x4 viewMatrix;
    float4x4 projectionMatrix;
};

OutputVertex main(InputVertex Input)
{
    OutputVertex output = (OutputVertex)0;
    output.tex = Input.tex;
    output.tex3d = Input.pos;
    output.nrm = Input.nrm;
    output.xyzw = float4(Input.pos, 1.0f);

    //Math (shader intrinsics)
    output.xyzw = mul(output.xyzw, worldMatrix);
    output.xyzw = mul(output.xyzw, viewMatrix);
    output.xyzw = mul(output.xyzw, projectionMatrix);
    //Don't do perspectve divide, rasterizer will do that for us

    return output;
}