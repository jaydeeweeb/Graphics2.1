//RULE OF THREE
//THREE THINGS MUST MATCH (DATA)
//1. C++ VERTEX STRUCT
//2. INPUT LAYOUT
//3. HLSL VERTEX STRUCT

#pragma pack_matrix(row_major) // treats all matricies to row major

struct InputVertex //Where 2 lines meet
{
    float4 xyzw :POSITION;
    float4 rgba :COLOR;
};

struct OutputVertex //float4
{
    float4 xyzw :SV_Position;
    float4 rgba : OCOLOR;

};


cbuffer SHADER_VARS : register(b0) //Register assigns to variable name, b = buffer, t = textures, s = samplers
{
    float4x4 worldMatrix;
    float4x4 viewMatrix;
    float4x4 projectionMatrix;
};

OutputVertex main(InputVertex Input)
{
    OutputVertex output = (OutputVertex) 0;
    output.xyzw = float4(Input.xyzw.xyz, 1.0f);
    output.rgba = Input.rgba;
    
    //Math (shader intrinsics
    output.xyzw = mul(output.xyzw, worldMatrix);
    output.xyzw = mul(output.xyzw, viewMatrix);
    output.xyzw = mul(output.xyzw, projectionMatrix);
    //Don't do perspectve divide, rasterizer will do that for us
    
    
    return output;
}