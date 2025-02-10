matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;
float3 LightDir;


struct VertexInput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;

};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);

    output.uv = input.uv;
    
    output.normal = mul(input.normal, (float3x3) World);// 단위벡터이므로 회전만 적용하려함? 

    return output;
}

SamplerState Sampler0;

float4 PS(VertexOutput input) : SV_TARGET
{
    float3 normal = normalize(input.normal);
    float3 light = -LightDir;
    
    //return float4(1, 1, 1, 1)*dot(light, normal); // 내적인데 단위벡터이므로 코사인사잇각만 남음.
    
    
    return Texture0.Sample(Sampler0, input.uv) * dot(light, normal);// 원래 색상 * 내적-> 결과 광원 비?
}

RasterizerState FillModeWireFrame
{
    FillMode = Wireframe;
};

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P1
    {
        SetRasterizerState(FillModeWireFrame);

        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
};
