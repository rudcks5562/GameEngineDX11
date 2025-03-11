#include "Global.fx"
#include "Light.fx"
struct VS_IN
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    // instancing
    matrix world : INST;
    
};


struct VS_OUT
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION1;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

VS_OUT VS(VS_IN input)
{
    VS_OUT output;

    output.position = mul(input.position, input.world);//W
    output.worldPosition = output.position;
    output.position = mul(output.position,VP);
    output.uv = input.uv;
    output.normal = input.normal;
    
    

    return output;
}

float4 PS(VS_OUT input) : SV_TARGET
{
	//ComputeNormalMapping(input.normal, input.tangent, input.uv);
	//float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);

    return color;
}

float4 PS_RED(MeshOutput input) : SV_TARGET
{
    return float4(1, 0, 0, 1);
}

technique11 T0
{
    pass p0
    {
        SetRasterizerState(FrontCounterClockwiseTrue);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));

    }
    PASS_VP(P0, VS, PS)
};
