#pragma once

#include "stdafx.h"

#include <string>
#include "WindowClass.h"
#include "Window.h"

namespace xexperimente
{
	namespace WinUI
	{
		WindowClassName WindowClass::getClassName() {
			return WindowClassName(L"xexperimente.WinUI.Window");
		};

		int WindowClass::getStyle() {
			return CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		};
		int WindowClass::getColor() {
			return COLOR_3DFACE;
		};
		WNDPROC WindowClass::getWndProc() {
			return Window::getGlobalWndProc();
		};
	};
};