#pragma once

namespace DRenderer
{
	class D3DInitializer
	{
	public:
		static D3DInitializer * GetInstance();
		static void DeleteInstance();

		void Initialize(HWND hWnd);


		ID3D11Device *			GetDevice() { return _theDevice; }
		ID3D11DeviceContext *	GetDeviceContext() { return _theDeviceContext; }
		IDXGISwapChain *		GetSwapChain() { return _swap_chain; }
		D3D_FEATURE_LEVEL		GetFeatureLevel() { return _featureLevel; }
		ID3D11RenderTargetView * GetRenderTargetView() { return _rtv; }
	private:
		D3DInitializer();
		~D3DInitializer();

		static D3DInitializer *	_instance;

		// Direct X Variables
		ID3D11Device *			_theDevice;
		ID3D11DeviceContext *	_theDeviceContext;
		IDXGISwapChain *		_swap_chain;
		D3D_FEATURE_LEVEL		_featureLevel;
		ID3D11RenderTargetView * _rtv;
	}; // D3DInitializer
} // DRenderer
