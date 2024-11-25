#include "Drawing.h"
#include "../labtool/hooks/Hook.h"

// Static member definitions
BOOL Drawing::bInit = FALSE;
bool Drawing::bDisplay = false;
bool Drawing::bSetPos = true;
ImVec2 Drawing::vWindowPos = ImVec2(0.0f, 0.0f);
ImVec2 Drawing::vWindowSize = ImVec2(0.0f, 0.0f);

/**
    @brief : Hook of the EndScene function.
    @param  D3D9Device : Current Direct3D9 Device Object.
    @retval : Result of the original EndScene function.
**/


void Drawing::RenderWindow() {
    ImGui::Begin("Window Title", &bDisplay);
    {
        ImGui::SetWindowSize({ 500, 300 }, ImGuiCond_Once);

        // Handle window position and size persistence
        if (vWindowPos.x != 0.0f && vWindowPos.y != 0.0f && 
            vWindowSize.x != 0.0f && vWindowSize.y != 0.0f && bSetPos)
        {
            ImGui::SetWindowPos(vWindowPos);
            ImGui::SetWindowSize(vWindowSize);
            bSetPos = false;
        }

        if (bSetPos == false)
        {
            vWindowPos = ImGui::GetWindowPos();
            vWindowSize = ImGui::GetWindowSize();
        }

        ImGui::Text("back on my bullshit :^)");
    }
    ImGui::End();
}
HRESULT Drawing::hkEndScene(const LPDIRECT3DDEVICE9 D3D9Device)
{
	if (!Hook::pDevice)
		Hook::pDevice = D3D9Device;

	if (!bInit)
		InitImGui(D3D9Device);

	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDisplay = !bDisplay;

	if (GetAsyncKeyState(VK_END) & 1)
	{
		Hook::UnHookDirectX();
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, Hook::hDDLModule, 0, nullptr);
		return Hook::oEndScene(D3D9Device);
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (bDisplay)
	{
		RenderWindow();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return Hook::oEndScene(D3D9Device);
}

/**
    @brief : function that init ImGui for rendering.
    @param pDevice : Current Direct3D9 Device Object given by the hooked function.
**/
void Drawing::InitImGui(const LPDIRECT3DDEVICE9 pDevice)
{
	D3DDEVICE_CREATION_PARAMETERS CP;
	pDevice->GetCreationParameters(&CP);
	Hook::window = CP.hFocusWindow;
	Hook::HookWindow();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = nullptr;
	io.Fonts->AddFontDefault();

	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(Hook::window);
	ImGui_ImplDX9_Init(pDevice);

	bInit = TRUE;
}
