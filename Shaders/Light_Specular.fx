#include "Global.fx"

float3 LightDir;// 태양방향?
float4 LightSpecular;
float4 MaterialSpecular;



Texture2D DiffuseMap;



MeshOutput VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, W);
    output.position = mul(output.position, VP);
    output.worldPosition = input.position;//???

    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) W);

    return output;
}



float4 PS(MeshOutput input) : SV_TARGET
{
    //float3 R = reflect(LightDir, input.normal);// 내장함수
    float3 R = LightDir - (2 * input.normal * dot(LightDir, input.normal));
    //내적의 결과는 스칼라이기 때문에 다시 방향벡터를 곱해줘야함.
    float3 cameraPosition = -V._41_42_43;
    float3 E = normalize(cameraPosition - input.worldPosition); // 상대 - 나 
    
    float value = saturate(dot(R, E));// clamp (0~1)
    
    float specular = pow(value, 10);// 보정   
    
    float4 color = LightSpecular * MaterialSpecular * specular;
    

    return color;
    
}



technique11 T0
{
    PASS_VP(P0, VS, PS)
};
