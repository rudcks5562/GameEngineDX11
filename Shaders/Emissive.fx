#include "Global.fx"


float4 MaterialEmissive;



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

    
    float3 cameraPosition = -V._41_42_43;
    float3 E = cameraPosition - input.worldPosition;
    float value = saturate(dot(E, input.normal));
    float emissive = 1.0f - value;  
    
    emissive = smoothstep(0.0f, 1.0f,emissive);
    emissive = pow(emissive, 2);
    float4 color = MaterialEmissive * emissive;
    return color;
}



technique11 T0
{
    PASS_VP(P0, VS, PS)
};
