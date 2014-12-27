#ifndef D3DClass_H
#define D3DClass_H
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

class D3DClass
{
public:
	void CreateShaders();
	void CreateTriangleData();
	void initD3D(HWND&);
	void setViewport();
	void setRasterizerState();
	void Render();
	void Update();
	HRESULT CreateD3DContext();
	void release();
	void CreateDepthStencilBuffer();
	void CreateTexture();
	void CreateCB();
	void CreateCamera();
private:
	//Structs
	struct cbPerObjectData
	{
		XMMATRIX World;
		XMMATRIX CamViewProj;
	};
	//System
	HWND*						winHandle;
	IDXGISwapChain*				SwapChain;
	ID3D11Device*				Device;
	ID3D11DeviceContext*		DeviceContext;
	//Buffers
	ID3D11RenderTargetView*		BackBufferRTV;
	ID3D11Buffer*				VertexBuffer;
	ID3D11Texture2D*			DepthStencilBuffer;
	ID3D11DepthStencilView*		DepthStencilView;
	ID3D11Buffer*				PerObjectBuffer;
	//Shaders
	ID3D11VertexShader*			VertexShader;
	ID3D11PixelShader*			PixelShader;
	ID3D11GeometryShader*		GeometryShader;
	//misc
	D3D11_SUBRESOURCE_DATA		BTH_Data;
	ID3D11RasterizerState*		RasterState;
	ID3D11InputLayout*			VertexLayout;
	ID3D11ShaderResourceView*	TextureView;
	cbPerObjectData				cbPerObject;
	//Space matricies
	XMMATRIX					WVP;				//World*View*Projection
	XMMATRIX					CamView;
	XMMATRIX					CamProj;
	//Rectangle properties
	XMMATRIX					RectWorld;			//Rectangle world matrix
	XMMATRIX					RectRot;			//Rectangle rotation matrix
	XMMATRIX					RectTrans;			//Rectangle translation matrix
	XMMATRIX					RectScale;
	float						CurrRot;
	//Camera properties
	XMVECTOR					CamPos;				//Camera position
	XMVECTOR					CamTarget;			//Position the camera looks at
	XMVECTOR					CamUp;				//Cameras up direction
};

struct TriangleVertex
{
	float x,y,z;
	float u,v;
};
#endif