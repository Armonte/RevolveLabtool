#ifndef DRAWING_H
#define DRAWING_H

#include "../labtool/hooks/pch.h"

class Drawing
{
public:
	static BOOL bInit;
	static bool bDisplay;
	static bool bSetPos;
	static ImVec2 vWindowPos;
	static ImVec2 vWindowSize;

	static HRESULT APIENTRY hkEndScene(const LPDIRECT3DDEVICE9 D3D9Device);

private:
	static void RenderWindow();
	static void InitImGui(const LPDIRECT3DDEVICE9 pDevice);
};

#endif