#include "..\..\stdafx.h"
#include "..\headers\D3DInitializer.h"

namespace DRenderer
{
	D3DInitializer * D3DInitializer::_instance = nullptr;

	D3DInitializer * D3DInitializer::GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new D3DInitializer();
		}
		return _instance;
	}

	void D3DInitializer::DeleteInstance()
	{
		if (_instance != nullptr)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

	void D3DInitializer::Initialize(HWND hWnd)
	{
		HRESULT hr = S_OK;

		RECT rc;
		GetClientRect(hWnd, &rc);
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;

		UINT createDeviceFlags = 0;

#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};
		UINT numDriverTypes = ARRAYSIZE(driverTypes);

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(scd));
		scd.BufferCount = 1;
		scd.BufferDesc.Width = width;
		scd.BufferDesc.Height = height;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = hWnd;
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.Windowed = TRUE;

		D3D_DRIVER_TYPE _driverType = D3D_DRIVER_TYPE_NULL;
		for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
		{
			_driverType = driverTypes[driverTypeIndex];
			hr = D3D11CreateDeviceAndSwapChain(
				NULL,
				_driverType,
				NULL,
				createDeviceFlags,
				featureLevels,
				numFeatureLevels,
				D3D11_SDK_VERSION,
				&scd,
				&_swap_chain,
				&_theDevice,
				&_featureLevel,
				&_theDeviceContext
				);

			if (SUCCEEDED(hr))
				break;
		}

		if (FAILED(hr))
			return;

		ID3D11Texture2D* pBackBuffer = NULL;
		hr = _swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		if (FAILED(hr))
			return;

		hr = _theDevice->CreateRenderTargetView(pBackBuffer, NULL, &_rtv);
		pBackBuffer->Release();
		if (FAILED(hr))
			return;

		_theDeviceContext->OMSetRenderTargets(1, &_rtv, NULL);

		// Setup the view port
		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)width;
		vp.Height = (FLOAT)height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		_theDeviceContext->RSSetViewports(1, &vp);
	}

	D3DInitializer::D3DInitializer()
	{
		std::cout << "Initializing directx" << std::endl;

		_theDevice = nullptr;
		_theDeviceContext = nullptr;
		_swap_chain = nullptr;
		_rtv = nullptr;
	}


	D3DInitializer::~D3DInitializer()
	{
		if (_theDeviceContext != nullptr)
		{
			_theDeviceContext->ClearState();
			_theDeviceContext->Release();
			_theDeviceContext = nullptr;
		}
		if (_rtv != nullptr)
		{
			_rtv->Release();
			_rtv = nullptr;
		}		
		if (_swap_chain != nullptr)
		{
			_swap_chain->Release();
			_swap_chain = nullptr;
		}				
		if (_theDevice != nullptr)
		{
			_theDevice->Release();
			_theDevice = nullptr;
		}
	}
}
