#pragma once
#include "vmt.h"
extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}; using namespace std;
// SDK Namespace
class LuaVM {
public:
	void Connect(); lua_State* L;
	void DoFile(const char* fname, 
		const char* prefix = "../game/lua/");
	void DoString(const char* fn_str);
	// REPL State
	struct line {
		char std; string str;
	}; deque <struct line> Items;
	void Output(char x, string ins) {
		Items.push_back({ x, ins });
	}; void Output(char x, char* ins) {
		Items.push_back({ x, ins});
	}; // Imgui Shit
}; inline LuaVM vm;
// Hooks Namespace
namespace Hooks {
	HRESULT _fastcall Present(IDXGISwapChain *pChain, UINT SyncInterval, UINT Flags);
	HRESULT _fastcall CreateSwapChain(IDXGIFactory* pFactory, ID3D11Device *pDevice,
		DXGI_SWAP_CHAIN_DESC *pDesc, IDXGISwapChain **ppSwapChain);
};