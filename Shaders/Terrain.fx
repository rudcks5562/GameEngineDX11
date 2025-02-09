matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;



struct VertexInput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    output.uv = input.uv;

    return output;
}
SamplerState Sampler0;
SamplerState SamplerAddressWrap
{
    AddressU=Wrap;
    AddressV = Wrap;
};
SamplerState SamplerAddressMirror
{
    AddressU = Mirror;
    AddressV = Mirror;
};
SamplerState SamplerAddressClamp
{
    AddressU = Clamp;
    AddressV = Clamp;
};
SamplerState SamplerAddressBorder
{
    AddressU = Border;
    AddressV = Border;
    BorderColor = float4(1, 0, 0, 1);
};
float4 PS(VertexOutput input) : SV_TARGET
{

    
    
    return Texture0.Sample(Sampler0, input.uv);
    
}


//filter 확대축소 일어났을경우 중간값 처리방식


//address uv가 1보다 큰 경우(그리드 테스트 경우)





technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
};
