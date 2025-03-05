#include "Global.fx"
#include "Light.fx"

struct VS_OUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VS_OUT VS(VertexTextureNormalTangent input)
{
    VS_OUT output;
    
    //float4 worldPos = mul(input.position, W);
    float4 viewPos = mul(float4(input.position.xyz,0), V);// 회전만 적용하고 싶다.
    
    float4 clipPos = mul(viewPos, P);
    
    output.position = clipPos.xyzw;
    output.position.z = output.position.w*0.999999f;
    
    output.uv = input.uv;
    //rs: x/w y/w z/w 1
    // 클립스페이스(xy -1~1) z(0~1)인데 강제조작해서 1나오게
    
    

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


};
