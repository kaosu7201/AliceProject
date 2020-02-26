SamplerState samLinear : register(s0);

Texture2D Diffuse : register(t0);

cbuffer ConstBuff : register(b0)
{
  matrix mtxWorld;
  matrix mtxProj;
  float uv_left;
  float uv_top;
  float uv_width;
  float uv_height;
  float alpha;
  float r;
  float g;
  float b;
}

struct VS_INPUT
{
  float3 Pos : POSITION;
  float4 Col : COLOR;
  float2 Tex : TEXCOORD;
};

struct PS_INPUT
{
  float4 Pos : SV_POSITION;
  float4 Col : COLOR0;
  float2 Tex : TEXCOORD;
};

PS_INPUT vsMain(VS_INPUT pos)
{
  PS_INPUT o = (PS_INPUT)0;
  o.Pos = mul(float4(pos.Pos, 1.0f), mtxWorld);
  o.Pos = mul(float4(o.Pos), mtxProj);
  o.Col = pos.Col * alpha;
  o.Col.r = r;
  o.Col.g = g;
  o.Col.b = b;
  o.Tex = pos.Tex * float2(uv_width, uv_height) + float2(uv_left, uv_top);
  return o;
}

float4 psMain(PS_INPUT input) : SV_TARGET
{
  float4 result = 0;
  result = Diffuse.Sample(samLinear, input.Tex) * input.Col;
  return result;
}