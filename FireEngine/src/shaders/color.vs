
cbuffer perspBuf
{
  float4x4 perspective;
};

cbuffer viewBuf
{
  float4x4 view;
};

cbuffer modelBuf
{
  float4x4 model;
};


struct VertexInput
{
  float4 position : POSITION;
};

struct PixelInputType
{
  float4 position : SV_POSITION;
  float4 color : COLOR;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType main(VertexInput input)
{
  PixelInputType output;
  output.position = mul(model, input.position);
  output.position = mul(view, output.position);
  output.position = mul(perspective, output.position);
  output.color = float4(1.0,0.0,0.0,1.0);
  return output;
}
