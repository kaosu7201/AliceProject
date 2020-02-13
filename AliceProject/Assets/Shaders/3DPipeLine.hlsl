SamplerState samLinear : register(s0);

Texture2D Diffuse : register(t0);

struct VS_INPUT
{
  float3 Pos : POSITION;
  float3 Nor : NORMAL;
  float4 Col : COLOR;
  float2 Tex : TEXCOORD;
};

struct PS_INPUT
{
  float4 Pos : SV_POSITION;
  float4 Col : COLOR;
  float2 Tex : TEXCOORD;
};

cbuffer ConstantBuffer
{
  float4x4 World;         //ワールド変換行列
  float4x4 View;          //ビュー変換行列
  float4x4 Projection;    //透視射影変換行列
}

PS_INPUT vsMain(VS_INPUT pos)
{
  PS_INPUT o = (PS_INPUT)0;

  o.pos = mul(pos.pos, World);
  o.pos = mul(o.pos, View);
  o.pos = mul(o.pos, Projection);
  o.col = pos.col;

  o.tex = pos.tex;

  return output;
}

float4 psMain(PS_INPUT input) : SV_TARGET
{
  float4 result = 0;
  result = Diffuse.Sample(samLinear, input.Tex) * input.Col;
  return result;
}