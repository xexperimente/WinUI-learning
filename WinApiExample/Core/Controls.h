#pragma once

#include "stdafx.h"

#include <string>
#include <memory>

#include "Frame.h"

namespace xexperimente
{
	namespace WinUI
	{
		class StaticText : public WinUI::Wnd {
		public:
			StaticText(const std::wstring& text, HWND parent)
				:Wnd(parent)
			{
				hWnd = CreateWindowEx(
					WS_EX_CLIENTEDGE,
					L"STATIC",
					text.c_str(),
					WS_VISIBLE | WS_CHILD | SS_LEFT,
					0,
					0,
					100,
					20,
					parent,
					0,
					GetModuleHandle(NULL),
					0
				);

				if (!hWnd)
					return;

				SetWindowLongPtr(hWnd, GWL_USERDATA, (ULONG_PTR)this);
			}
		};

		class Button : public WinUI::Wnd {
		public:
			Button(const std::wstring& text, HWND parent)
				:Wnd(parent)
			{
				hWnd = CreateWindowEx(
					0,
					L"BUTTON",
					text.c_str(),
					WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_MAXIMIZEBOX,
					0,
					0,
					100,
					20,
					parent,
					0,
					GetModuleHandle(NULL),
					0
				);

				if (!hWnd)
					return;

				SetWindowLongPtr(hWnd, GWL_USERDATA, (ULONG_PTR)this);
				
				auto font = GetStockObject(DEFAULT_GUI_FONT);

				SendMessage(hWnd, WM_SETFONT, (WPARAM)font, TRUE);
			}

			virtual void OnCommand(WPARAM wParam, LPARAM lParam)
			{
				OutputDebugStringW(L"Button::OnCommand\n");
			}

		};
	}
}
