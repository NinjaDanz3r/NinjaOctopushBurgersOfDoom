#include <windows.h>
#include "D3DClass.h"

HWND InitWindow(HINSTANCE hInstance);
LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) //Win Main
{

	MSG msg = {0};
	D3DClass D3DHandler;
	HWND wndHandle = InitWindow(hInstance);
	if(wndHandle)
	{
		D3DHandler.initD3D(wndHandle); //init d3d and link wndhandle to d3d.
		ShowWindow(wndHandle, nCmdShow);
		while(WM_QUIT != msg.message)
		{
			if(PeekMessage(&msg, nullptr, 0,0,PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else //Render/update
			{
				D3DHandler.Update();
				D3DHandler.Render();
			}
		}
		D3DHandler.release();
		

		DestroyWindow(wndHandle);
	}
	return (int) msg.wParam;
}

//Initialize Window
HWND InitWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wcex				= {0};
	wcex.cbSize					= sizeof(WNDCLASSEX);
	wcex.style					= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc			= wndProc;
	wcex.hInstance				= hInstance;
	wcex.lpszClassName			= "3DProj";
	if(!RegisterClassEx(&wcex))
		return false;
	RECT rc = {0,0,640,480};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND handle = CreateWindow(
	"3DProj",								//Name of window class
	"TestWindow",							//Window Title
	WS_OVERLAPPEDWINDOW,					//Window style, 
	CW_USEDEFAULT,							//Window initial x pos.
	CW_USEDEFAULT,							//Window initial y pos.
	rc.right-rc.left,						//Window width (Compensating for rendering)
	rc.bottom-rc.top,						//Window height -::-
	nullptr,								//Parent window
	nullptr,								//Menu handle
	hInstance,								//Handle instance.
	nullptr									//"A pointer to a value to be passed to the window through the CREATESTRUCT structure (lpCreateParams member) pointed to by the lParam param of the WM_CREATE message. This message is sent to the created window by this function before it returns."
	);
	return handle;
}

//Message Handler
LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}