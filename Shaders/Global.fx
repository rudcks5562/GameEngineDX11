#ifndef _GLOBAL_FX_
#define _GLOBAL_FX_

cbuffer GlobalBuffer
{
    matrix V;
    matrix P;
    matrix VP;
    matrix VInv;
};
cbuffer TransformBuffer
{
    matrix W;
};

struct Vertex
{
    float4 position : POSITION;
};
struct VertexTexture
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};
struct VertexColor
{
    float4 position : POSITION;
    float4 color : COLOR;
};
struct VertexTextureNormal
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    
    
};
struct VertexTextureNormalTangent
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    
};

// vsout
struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    
};
struct MeshOutput
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION1;   
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT; 
    
};
//samplerstate
SamplerState LinearSampler
{
    filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};
SamplerState PointSampler
{
    filter = MIN_MAG_MIP_POINT;
    AddressU = Wrap;
    AddressV = Wrap;
};

RasterizerState FillModeWireFrame
{
    FillMode = WireFrame;
};
// macro 
#define PASS_VP(name,vs,ps)                             \
pass name {                                             \
        SetVertexShader(CompileShader(vs_5_0, vs()));   \
        SetPixelShader(CompileShader(ps_5_0, ps()));    \
} 

#define PASS_RS_VP(name, rs, vs, ps)				\
pass name											\
{													\
    SetRasterizerState(rs);							\
    SetVertexShader(CompileShader(vs_5_0, vs()));	\
    SetPixelShader(CompileShader(ps_5_0, ps()));	\
}
//function ?
float3 CameraPosition()
{
    return -V._41_42_43;
    
}



#endif
