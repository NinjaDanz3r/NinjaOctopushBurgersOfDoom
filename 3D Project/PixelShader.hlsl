Texture2D txDiffuse : register(t0);
SamplerState sampAni
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 8;
};

//Output from VS is input in PS
struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};
float4 PS_main(VS_OUT input) : SV_Target
{
	float3 result = txDiffuse.Sample(sampAni, input.Tex).xyz;
	return float4(result, 1.0);
}