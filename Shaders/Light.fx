#ifndef _LIGHT_FX_
#define _LIGHT_FX_

#include "Global.fx"

// struct 
// color로 정리..

struct LightDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emmisive;
    float3 direction;
    float padding;// 16바이트를 지키기 위해
};

struct MaterialDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emmisive;
};

//const buffer

cbuffer LightBuffer
{
    LightDesc GlobalLight;
};
cbuffer MaterialBuffer
{
    MaterialDesc Material;
};// 분할의 이유: 전역 선언시 결국에는 하나의 글로벌 constantbuff로 취급되는데 매번 취급되는것과 1회성이 같이 들어있으면 낭비.

//SRV


Texture2D DiffuseMap;
Texture2D SpecularMap;
Texture2D NormalMap;

// fucntion
float4 ComputeLight(float3 normal, float2 uv, float3 worldPosition)
{
    
    float4 ambientColor = 0;
    float4 diffuseColor = 0;
    float4 specularColor = 0;
    float4 emissiveColor = 0;
    
    //ambient
    
    //diffuse
    
    //specular
    
    //emissive
}


#endif
