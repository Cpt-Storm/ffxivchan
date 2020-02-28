#include "_Resources\resource.h"
#include "LuaVM/Scripts.h"
#include "user.h"

VOID WINAPI ModuleEntry(HMODULE hInstance) {
	game = new MemorySystem("ffxiv_dx11.exe"); xiv = new FFXIV();
	// Load Resource Files
	HRSRC hRes = FindResource(hInstance, MAKEINTRESOURCE(IDR_FONT1), MAKEINTRESOURCE(TEXTFILE));
	sys.font_data = LockResource(LoadResource(hInstance, hRes));
	sys.font_size = SizeofResource(hInstance, hRes);
	// Init Game Systems
	Sleep(9750); sys.prevProc = (WNDPROC) SetWindowLongPtr(sys.hWindow, 
		GWLP_WNDPROC, (LONG_PTR) WndProc); ifstream 
	ifs("../game/lua/data/tradecraft.json"); ifs 
		>> xiv->tradecraft; ifs.close();
	DebugActiveProcessStop(GetProcessId(0));
	//auto chat_pb = game->ScanPattern(Offsets::CHAT, 3);
	//auto chat = chat_pb[0x2C10][0x16D8 + 0x48].Cast<ChatLog>();
	//printf("chat_pb, chats: %p, %p\n", chat_pb, chat);
	while (!sys.Stop) {
		sys.ResizeTarget();
		Sleep(1000);
	}; sys.~Interface();
FreeLibrary:
	FreeLibraryAndExitThread(hInstance, 1);
}

#define EXPORT comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)
EXTERN_C HRESULT WINAPI CreateDXGIFactory(REFIID riid, void** ppFactory)
{
#pragma EXPORT
	decltype(&CreateDXGIFactory) original = DynLib
		{ "C:\\Windows\\System32\\dxgi.dll" }["CreateDXGIFactory"];
	auto value = original(riid, ppFactory); VMT::Factory = new VMT(*ppFactory);
	printf("CreateDXGIFactory() -> ptr: %p, v: %x\n", ppFactory, *ppFactory);
	VMT::Factory->HookVM(Hooks::CreateSwapChain, 10); 
	VMT::Factory->ApplyVMT(); return value;
}

EXTERN_C HRESULT WINAPI CreateDXGIFactory1(REFIID riid, void** ppFactory)
{
#pragma EXPORT
	decltype(&CreateDXGIFactory1) original = DynLib
	{ "C:\\Windows\\System32\\dxgi.dll" }["CreateDXGIFactory1"];
		printf("should Never Be called {CreateDXGIFactory1}"); 
	return original(riid, ppFactory);
}

PVOID oIsDebuggerPresent;
BOOL _stdcall hkIsDebuggerPresent() {
	return false;
};

BOOL APIENTRY DllMain(
	HMODULE hInstance,
	DWORD fdwReason,
	LPVOID lpvReserved
) {
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		Utils::EnableConsole();
		DisableThreadLibraryCalls(hInstance);
		// Testing
		DetourRestoreAfterWith(); DetourTransactionBegin(); DetourUpdateThread(GetCurrentThread());
		oIsDebuggerPresent = GetProcAddress(GetModuleHandle("kernel32.dll"), "IsDebuggerPresent");
		DetourAttach(&oIsDebuggerPresent, hkIsDebuggerPresent); DetourTransactionCommit();
		// Meh
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)
			ModuleEntry, hInstance, 0, 0); break;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == nullptr)
			Utils::DisableConsole();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	default:
		break;
	};  return TRUE;
}