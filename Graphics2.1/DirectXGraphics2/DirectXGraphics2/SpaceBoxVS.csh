#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer SHADER_VARS
// {
//
//   row_major float4x4 worldMatrix;    // Offset:    0 Size:    64
//   row_major float4x4 viewMatrix;     // Offset:   64 Size:    64
//   row_major float4x4 projectionMatrix;// Offset:  128 Size:    64
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// SHADER_VARS                       cbuffer      NA          NA            cb0      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// POSITION                 0   xyz         0     NONE   float   xyz 
// NORMAL                   0   xyz         1     NONE   float   xyz 
// TEXCOORD                 0   xy          2     NONE   float   xy  
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Position              0   xyzw        0      POS   float   xyzw
// ONORMAL                  0   xyz         1     NONE   float   xyz 
// OTEXCOORD                0   xy          2     NONE   float   xy  
// OTEXCOORD                2   xyz         3     NONE   float   xyz 
//
//
// Constant buffer to DX9 shader constant mappings:
//
// Target Reg Buffer  Start Reg # of Regs        Data Conversion
// ---------- ------- --------- --------- ----------------------
// c1         cb0             0        12  ( FLT, FLT, FLT, FLT)
//
//
// Runtime generated constant mappings:
//
// Target Reg                               Constant Description
// ---------- --------------------------------------------------
// c0                              Vertex Shader position offset
//
//
// Level9 shader bytecode:
//
    vs_2_x
    dcl_texcoord v0
    dcl_texcoord1 v1
    dcl_texcoord2 v2
    mul r0, v0.y, c2
    mad r0, v0.x, c1, r0
    mad r0, v0.z, c3, r0
    add r0, r0, c4
    mul r1, r0.y, c6
    mad r1, r0.x, c5, r1
    mad r1, r0.z, c7, r1
    mad r0, r0.w, c8, r1
    mul r1, r0.y, c10
    mad r1, r0.x, c9, r1
    mad r1, r0.z, c11, r1
    mad r0, r0.w, c12, r1
    mad oPos.xy, r0.w, c0, r0
    mov oPos.zw, r0
    mov oT0.xyz, v1
    mov oT1.xy, v2
    mov oT2.xyz, v0

// approximately 17 instruction slots used
vs_4_0
dcl_constantbuffer CB0[12], immediateIndexed
dcl_input v0.xyz
dcl_input v1.xyz
dcl_input v2.xy
dcl_output_siv o0.xyzw, position
dcl_output o1.xyz
dcl_output o2.xy
dcl_output o3.xyz
dcl_temps 2
mul r0.xyzw, v0.yyyy, cb0[1].xyzw
mad r0.xyzw, v0.xxxx, cb0[0].xyzw, r0.xyzw
mad r0.xyzw, v0.zzzz, cb0[2].xyzw, r0.xyzw
add r0.xyzw, r0.xyzw, cb0[3].xyzw
mul r1.xyzw, r0.yyyy, cb0[5].xyzw
mad r1.xyzw, r0.xxxx, cb0[4].xyzw, r1.xyzw
mad r1.xyzw, r0.zzzz, cb0[6].xyzw, r1.xyzw
mad r0.xyzw, r0.wwww, cb0[7].xyzw, r1.xyzw
mul r1.xyzw, r0.yyyy, cb0[9].xyzw
mad r1.xyzw, r0.xxxx, cb0[8].xyzw, r1.xyzw
mad r1.xyzw, r0.zzzz, cb0[10].xyzw, r1.xyzw
mad o0.xyzw, r0.wwww, cb0[11].xyzw, r1.xyzw
mov o1.xyz, v1.xyzx
mov o2.xy, v2.xyxx
mov o3.xyz, v0.xyzx
ret 
// Approximately 16 instruction slots used
#endif

const BYTE SpaceBoxVS[] =
{
     68,  88,  66,  67,  66, 234, 
    161, 109,  74, 157, 114, 169, 
    207, 242, 239, 253,  85, 105, 
    149, 171,   1,   0,   0,   0, 
    212,   6,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
    196,   1,   0,   0,  68,   4, 
      0,   0, 192,   4,   0,   0, 
    208,   5,   0,   0,  68,   6, 
      0,   0,  65, 111, 110,  57, 
    132,   1,   0,   0, 132,   1, 
      0,   0,   0,   2, 254, 255, 
     80,   1,   0,   0,  52,   0, 
      0,   0,   1,   0,  36,   0, 
      0,   0,  48,   0,   0,   0, 
     48,   0,   0,   0,  36,   0, 
      1,   0,  48,   0,   0,   0, 
      0,   0,  12,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   2, 254, 255, 
     31,   0,   0,   2,   5,   0, 
      0, 128,   0,   0,  15, 144, 
     31,   0,   0,   2,   5,   0, 
      1, 128,   1,   0,  15, 144, 
     31,   0,   0,   2,   5,   0, 
      2, 128,   2,   0,  15, 144, 
      5,   0,   0,   3,   0,   0, 
     15, 128,   0,   0,  85, 144, 
      2,   0, 228, 160,   4,   0, 
      0,   4,   0,   0,  15, 128, 
      0,   0,   0, 144,   1,   0, 
    228, 160,   0,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   0,   0, 170, 144, 
      3,   0, 228, 160,   0,   0, 
    228, 128,   2,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   4,   0, 228, 160, 
      5,   0,   0,   3,   1,   0, 
     15, 128,   0,   0,  85, 128, 
      6,   0, 228, 160,   4,   0, 
      0,   4,   1,   0,  15, 128, 
      0,   0,   0, 128,   5,   0, 
    228, 160,   1,   0, 228, 128, 
      4,   0,   0,   4,   1,   0, 
     15, 128,   0,   0, 170, 128, 
      7,   0, 228, 160,   1,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,  15, 128,   0,   0, 
    255, 128,   8,   0, 228, 160, 
      1,   0, 228, 128,   5,   0, 
      0,   3,   1,   0,  15, 128, 
      0,   0,  85, 128,  10,   0, 
    228, 160,   4,   0,   0,   4, 
      1,   0,  15, 128,   0,   0, 
      0, 128,   9,   0, 228, 160, 
      1,   0, 228, 128,   4,   0, 
      0,   4,   1,   0,  15, 128, 
      0,   0, 170, 128,  11,   0, 
    228, 160,   1,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   0,   0, 255, 128, 
     12,   0, 228, 160,   1,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,   3, 192,   0,   0, 
    255, 128,   0,   0, 228, 160, 
      0,   0, 228, 128,   1,   0, 
      0,   2,   0,   0,  12, 192, 
      0,   0, 228, 128,   1,   0, 
      0,   2,   0,   0,   7, 224, 
      1,   0, 228, 144,   1,   0, 
      0,   2,   1,   0,   3, 224, 
      2,   0, 228, 144,   1,   0, 
      0,   2,   2,   0,   7, 224, 
      0,   0, 228, 144, 255, 255, 
      0,   0,  83,  72,  68,  82, 
    120,   2,   0,   0,  64,   0, 
      1,   0, 158,   0,   0,   0, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   0,   0,   0,   0, 
     12,   0,   0,   0,  95,   0, 
      0,   3, 114,  16,  16,   0, 
      0,   0,   0,   0,  95,   0, 
      0,   3, 114,  16,  16,   0, 
      1,   0,   0,   0,  95,   0, 
      0,   3,  50,  16,  16,   0, 
      2,   0,   0,   0, 103,   0, 
      0,   4, 242,  32,  16,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0, 101,   0,   0,   3, 
    114,  32,  16,   0,   1,   0, 
      0,   0, 101,   0,   0,   3, 
     50,  32,  16,   0,   2,   0, 
      0,   0, 101,   0,   0,   3, 
    114,  32,  16,   0,   3,   0, 
      0,   0, 104,   0,   0,   2, 
      2,   0,   0,   0,  56,   0, 
      0,   8, 242,   0,  16,   0, 
      0,   0,   0,   0,  86,  21, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   0,   0,   0,   0, 
      6,  16,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      0,   0,   0,   0, 166,  26, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   8, 
    242,   0,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  56,   0, 
      0,   8, 242,   0,  16,   0, 
      1,   0,   0,   0,  86,   5, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   5,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   1,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0, 166,  10, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   6,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   0,   0, 
      0,   0, 246,  15,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      7,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   8, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     86,   5,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   9,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0,   6,   0,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   1,   0,   0,   0, 
    166,  10,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,  10,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,  32,  16,   0, 
      0,   0,   0,   0, 246,  15, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,  11,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  54,   0,   0,   5, 
    114,  32,  16,   0,   1,   0, 
      0,   0,  70,  18,  16,   0, 
      1,   0,   0,   0,  54,   0, 
      0,   5,  50,  32,  16,   0, 
      2,   0,   0,   0,  70,  16, 
     16,   0,   2,   0,   0,   0, 
     54,   0,   0,   5, 114,  32, 
     16,   0,   3,   0,   0,   0, 
     70,  18,  16,   0,   0,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 116,   0, 
      0,   0,  16,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   7,   0,   0,   0, 
     12,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  82,  68, 
     69,  70,   8,   1,   0,   0, 
      1,   0,   0,   0,  72,   0, 
      0,   0,   1,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    254, 255,   0,   1,   0,   0, 
    224,   0,   0,   0,  60,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     83,  72,  65,  68,  69,  82, 
     95,  86,  65,  82,  83,   0, 
     60,   0,   0,   0,   3,   0, 
      0,   0,  96,   0,   0,   0, 
    192,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    168,   0,   0,   0,   0,   0, 
      0,   0,  64,   0,   0,   0, 
      2,   0,   0,   0, 180,   0, 
      0,   0,   0,   0,   0,   0, 
    196,   0,   0,   0,  64,   0, 
      0,   0,  64,   0,   0,   0, 
      2,   0,   0,   0, 180,   0, 
      0,   0,   0,   0,   0,   0, 
    207,   0,   0,   0, 128,   0, 
      0,   0,  64,   0,   0,   0, 
      2,   0,   0,   0, 180,   0, 
      0,   0,   0,   0,   0,   0, 
    119, 111, 114, 108, 100,  77, 
     97, 116, 114, 105, 120,   0, 
      2,   0,   3,   0,   4,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 118, 105, 
    101, 119,  77,  97, 116, 114, 
    105, 120,   0, 112, 114, 111, 
    106, 101,  99, 116, 105, 111, 
    110,  77,  97, 116, 114, 105, 
    120,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  49,  48,  46,  49,   0, 
     73,  83,  71,  78, 108,   0, 
      0,   0,   3,   0,   0,   0, 
      8,   0,   0,   0,  80,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      7,   7,   0,   0,  89,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
      7,   7,   0,   0,  96,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      3,   3,   0,   0,  80,  79, 
     83,  73,  84,  73,  79,  78, 
      0,  78,  79,  82,  77,  65, 
     76,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0, 171, 
    171, 171,  79,  83,  71,  78, 
    136,   0,   0,   0,   4,   0, 
      0,   0,   8,   0,   0,   0, 
    104,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  15,   0,   0,   0, 
    116,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   7,   8,   0,   0, 
    124,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   3,  12,   0,   0, 
    124,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   3,   0, 
      0,   0,   7,   8,   0,   0, 
     83,  86,  95,  80, 111, 115, 
    105, 116, 105, 111, 110,   0, 
     79,  78,  79,  82,  77,  65, 
     76,   0,  79,  84,  69,  88, 
     67,  79,  79,  82,  68,   0, 
    171, 171
};
