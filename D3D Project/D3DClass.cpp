#include "D3DClass.h"
#include "bth_image.h"
#include <string>

void D3DClass::CreateShaders()
{
	//create vertex shader
	ID3DBlob* pVS = nullptr;
	ID3DBlob* pPS = nullptr;
	ID3DBlob* pGS = nullptr;
	ID3DBlob* errorblob = nullptr;
	HRESULT res;
	D3DCompileFromFile(L"VertexShader.hlsl",nullptr,nullptr, "VS_main", "vs_4_0",0,NULL,&pVS, nullptr);
	res = D3DCompileFromFile(L"PixelShader.hlsl",nullptr,nullptr, "PS_main", "ps_4_0",0,NULL,&pPS, &errorblob);
	D3DCompileFromFile(L"GeometryShader.hlsl", nullptr, nullptr, "GS_main", "gs_4_0", 0, NULL, &pGS, nullptr);
	if (FAILED(res))
	{
		std::string error = (char*)errorblob->GetBufferPointer();
		OutputDebugStringA(error.c_str());
	}
	res = Device->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &VertexShader);

	D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
	{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0}, 
	{"TEXCOORD",0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA,0}
	,};

	Device->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &VertexLayout);
	pVS->Release();

	Device->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), nullptr, &PixelShader);
	pPS->Release();

	Device->CreateGeometryShader(pGS->GetBufferPointer(), pGS->GetBufferSize(), nullptr, &GeometryShader);
	pGS->Release();
};

void D3DClass::initD3D(HWND& hwnd)
{
	winHandle			= &hwnd;
	SwapChain			= nullptr;
	Device				= nullptr;
	DeviceContext		= nullptr;
	BackBufferRTV		= nullptr;
	VertexBuffer		= nullptr;
	VertexLayout		= nullptr;
	VertexShader		= nullptr;
	PixelShader			= nullptr;
	DepthStencilBuffer	= nullptr;
	
	CurrRot = 0.0f;

	CreateD3DContext();
	setRasterizerState();
	setViewport();
	CreateShaders();
	CreateTriangleData();
	CreateTexture();
	CreateCB();
	CreateCamera();
};

void D3DClass::CreateCB()
{
	D3D11_BUFFER_DESC CBDesc;
	ZeroMemory(&CBDesc, sizeof(D3D11_BUFFER_DESC));
	CBDesc.Usage			= D3D11_USAGE_DEFAULT;
	CBDesc.ByteWidth		= sizeof(cbPerObject);
	CBDesc.BindFlags		= D3D11_BIND_CONSTANT_BUFFER;
	CBDesc.CPUAccessFlags	= 0;
	CBDesc.MiscFlags		= 0;
	Device->CreateBuffer(&CBDesc,nullptr,&PerObjectBuffer);
};

void D3DClass::CreateTexture()
{
	ID3D11Texture2D* BTH_Texture;
	D3D11_TEXTURE2D_DESC TexDesc;
	ZeroMemory(&TexDesc, sizeof(TexDesc));
	//Create 2D texture description.
	TexDesc.Width					= BTH_IMAGE_WIDTH;
	TexDesc.Height					= BTH_IMAGE_HEIGHT;
	TexDesc.ArraySize				= 1;
	TexDesc.MipLevels				= 1;
	TexDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
	TexDesc.SampleDesc.Count		= 1;
	TexDesc.SampleDesc.Quality		= 0;
	TexDesc.Usage					= D3D11_USAGE_DEFAULT;
	TexDesc.BindFlags				= D3D11_BIND_SHADER_RESOURCE;
	TexDesc.MiscFlags				= 0;
	TexDesc.CPUAccessFlags			= 0;

	//create texture from data
	BTH_Texture = nullptr;
	ZeroMemory(&BTH_Data, sizeof(BTH_Data));
	BTH_Data.pSysMem = (void*)BTH_IMAGE_DATA;
	BTH_Data.SysMemPitch = BTH_IMAGE_WIDTH*4*sizeof(char);
	Device->CreateTexture2D(&TexDesc, &BTH_Data, &BTH_Texture);
	//resource view desc
	D3D11_SHADER_RESOURCE_VIEW_DESC rvDesc;
	ZeroMemory(&rvDesc, sizeof(rvDesc));
	rvDesc.Format = TexDesc.Format;
	rvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	rvDesc.Texture2D.MipLevels = TexDesc.MipLevels;
	rvDesc.Texture2D.MostDetailedMip = 0;
	Device->CreateShaderResourceView(BTH_Texture, &rvDesc, &TextureView);
	BTH_Texture->Release();
}

void D3DClass::CreateTriangleData()
{
	TriangleVertex triangleVertices[6] = 
	{
		0.5f, 0.5f, 0.0f,	//Vertex 0 point
		1.0f, 0.0f,			//Vertex 0 texcoords

		0.5f, -0.5f, 0.0f,
		1.0f, 1.0f,
		
		-0.5f, -0.5f, 0.0f,
		0.0f, 1.0f,

		-0.5f, -0.5f, 0.0f,	
		0.0f, 1.0f,

		-0.5f, 0.5f, 0.0f,
		0.0f, 0.0f,

		0.5f, 0.5f, 0.0f,
		1.0f, 0.0f
	};


	D3D11_BUFFER_DESC bufferDesc;
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	bufferDesc.ByteWidth = sizeof(triangleVertices);
	data.pSysMem = triangleVertices;
	Device->CreateBuffer(&bufferDesc, &data, &VertexBuffer);
};

void D3DClass::CreateDepthStencilBuffer()
{
	D3D11_TEXTURE2D_DESC depthStencilBufferDesc;

	depthStencilBufferDesc.ArraySize = 1;
	depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilBufferDesc.CPUAccessFlags = 0;
	depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilBufferDesc.Width = 640;
	depthStencilBufferDesc.Height = 480;
	depthStencilBufferDesc.MiscFlags = 0;
	depthStencilBufferDesc.MipLevels = 1;
	depthStencilBufferDesc.SampleDesc.Count = 4;
	depthStencilBufferDesc.SampleDesc.Quality = 0;
	depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	HRESULT hr = Device->CreateTexture2D(&depthStencilBufferDesc, nullptr, &DepthStencilBuffer);

	Device->CreateDepthStencilView(DepthStencilBuffer, nullptr, &DepthStencilView );
};

void D3DClass::setViewport()
{
	D3D11_VIEWPORT vp;
	vp.Width = (float)640;
	vp.Height = (float)480;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	DeviceContext->RSSetViewports(1,&vp);
};

void D3DClass::setRasterizerState()
{
	D3D11_RASTERIZER_DESC desc;
	desc.AntialiasedLineEnable = false;
	desc.CullMode = D3D11_CULL_BACK;
	desc.DepthBias = 0;
	desc.DepthBiasClamp = 0.0f;
	desc.DepthClipEnable = true;
	desc.FillMode = D3D11_FILL_SOLID;
	desc.FrontCounterClockwise = false;
	desc.MultisampleEnable = false;
	desc.ScissorEnable = false;
	desc.SlopeScaledDepthBias = 0.0f;

	Device->CreateRasterizerState(&desc, &RasterState);
	DeviceContext->RSSetState(RasterState);
}

void D3DClass::Update()
{
	CurrRot +=0.00005;
	if (CurrRot > XM_2PI) //If rotation excedes 2pi radians, reset rotation
		CurrRot = 0;
	RectWorld			= XMMatrixIdentity();						//Set world matrix to identity
	RectTrans			= XMMatrixTranslation(0.0f,0.0f,2.0f);		//Translate (x,y,z)
	RectRot				= XMMatrixRotationY(CurrRot);				//Rotate	(Rotate around RotAxis (y) by CurrRot radians
	RectScale			= XMMatrixScaling(1.0f,1.0f,1.0f);			//Scale		(x,y,z)
	RectWorld			= RectRot * RectScale;						//Multiply
}

void D3DClass::Render()
{
	float clearColor[] = {0,0,0,1};
	UINT32 vertexSize = sizeof(float)*5;
	UINT32 offset = 0;
	DeviceContext->ClearRenderTargetView(BackBufferRTV, clearColor);
	DeviceContext->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	
	DeviceContext->GSSetConstantBuffers(0, 1, &PerObjectBuffer);
	DeviceContext->VSSetShader(VertexShader, nullptr, 0);
	DeviceContext->HSSetShader(nullptr, nullptr, 0);
	DeviceContext->DSSetShader(nullptr, nullptr, 0);
	DeviceContext->GSSetShader(GeometryShader, nullptr, 0);
	DeviceContext->PSSetShader(PixelShader, nullptr, 0);
	DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &vertexSize, &offset);
	DeviceContext->PSSetShaderResources(0,1,&TextureView);

	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->IASetInputLayout(VertexLayout);
	
	cbPerObject.World = XMMatrixTranspose(RectWorld);
	cbPerObject.CamViewProj = XMMatrixTranspose((CamView * CamProj));
	DeviceContext->UpdateSubresource(PerObjectBuffer,0,nullptr,&cbPerObject,0,0);
	//draws x amount of vertices, (x,startvertexloc)
	DeviceContext->Draw(6,0);
	SwapChain->Present(0,0);
};

void D3DClass::CreateCamera()
{
	CamPos			= XMVectorSet(0.0f, 0.0f, -3.0f, 1.0f);
	CamTarget		= XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	CamUp			= XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	CamView			= XMMatrixLookAtLH(CamPos, CamTarget, CamUp);
	//View angle, Aspect ratio, Near distance, far distance.
	CamProj			= XMMatrixPerspectiveFovLH(0.45*XM_PI, 640.0f/480.0f, 0.5f, 500.0f);
}

HRESULT D3DClass::CreateD3DContext()
{
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = *winHandle;
	scd.SampleDesc.Count = 4;
	scd.Windowed = true;

	HRESULT hr =  D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&SwapChain,
		&Device,
		NULL,
		&DeviceContext);

		if(SUCCEEDED(hr))
		{
			ID3D11Texture2D* pBackBuffer = nullptr;
			SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

			Device->CreateRenderTargetView(pBackBuffer, nullptr, &BackBufferRTV);
			pBackBuffer->Release();
			
			CreateDepthStencilBuffer();
			DeviceContext->OMSetRenderTargets(1, &BackBufferRTV, DepthStencilView);

		}
		return hr;
};

void D3DClass::release()
{
	VertexBuffer->Release();
	VertexLayout->Release();
	VertexShader->Release();
	PixelShader->Release();
	BackBufferRTV->Release();
	SwapChain->Release();
	Device->Release();
	DeviceContext->Release();
	PerObjectBuffer->Release();
};

//Texture2D txDiffuse : register(t0);
//SamplerState sampAni
//{
//	Filter = ANISOTROPIC;
//	MaxAnisotropy = 8;
//};
//
////Output from VS is input in PS
//struct VS_OUT
//{
//	float4 Pos : SV_POSITION;
//	float2 Tex : TEXCOORD;
//};
//float4 PS_main(VS_OUT input) : SV_Target
//{
//	float3 result = txDiffuse.Sample(sampAni, input.Tex).xyz;
//	return float4(result, 1.0);
//}