cbuffer cbPerObject
{
	float4x4 World;
	float4x4 CamViewProj;
};

struct GS_IN
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

struct GS_OUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

[maxvertexcount(6)]
void GS_main(triangle GS_IN tris[3], inout TriangleStream<GS_OUT> Tstream)
{
	GS_OUT v1, v2, v3;
	//Set v1,v2,v3 equal to triangle vertices. 
	v1 = (GS_OUT)tris[0];
	v2 = (GS_OUT)tris[1];
	v3 = (GS_OUT)tris[2];
	//Multiply current postion with WVP (mul(World,CamViewProj) )
	v1.Pos = mul(v1.Pos, mul(World,CamViewProj));
	v2.Pos = mul(v2.Pos, mul(World, CamViewProj));
	v3.Pos = mul(v3.Pos, mul(World, CamViewProj));
	//Append vertices to pipeline.
	Tstream.Append(v1);
	Tstream.Append(v2);
	Tstream.Append(v3);

	//Copy
	Tstream.RestartStrip();
	v1 = (GS_OUT)tris[0];
	v2 = (GS_OUT)tris[1];
	v3 = (GS_OUT)tris[2];
	//Calculate triangle normal and normalize
	float4 Normal = normalize(float4(cross((v2.Pos - v1.Pos), (v3.Pos - v1.Pos)), 0.0f));
	v1.Pos = v1.Pos + Normal;
	v2.Pos = v2.Pos + Normal;
	v3.Pos = v3.Pos + Normal;

	v1.Pos = mul(v1.Pos, mul(World, CamViewProj));
	v2.Pos = mul(v2.Pos, mul(World, CamViewProj));
	v3.Pos = mul(v3.Pos, mul(World, CamViewProj));

	Tstream.Append(v1);
	Tstream.Append(v2);
	Tstream.Append(v3);
	Tstream.RestartStrip();
}