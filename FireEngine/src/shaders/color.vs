
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
  output.position = input.position;
  output.color = float4(1.0,0.0,0.0,1.0);
  return output;
}
