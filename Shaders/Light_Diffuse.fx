#include "Global.fx"

float3 LightDir;// 태양방향?
float4 LightDiffuse;// 색상
float4 MaterialDiffuse;// 물체 
Texture2D DiffuseMap;



VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
    output.position = mul(input.position, W);
    output.position = mul(output.position, VP);
   

    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) W);

    return output;
}



float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    
    float value = dot(-LightDir, normalize(input.normal));
    color = color * value* LightDiffuse * MaterialDiffuse;
    return color;
    
}



technique11 T0
{
    PASS_VP(P0, VS, PS)
};
