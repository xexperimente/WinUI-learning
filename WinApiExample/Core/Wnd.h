#pragma once

#include "stdafx.h"

namespace xexperimente
{
	namespace WinUI
	{
		class Wnd {
			
		public:
			HWND hWnd = nullptr;
			HWND hParent = nullptr;

			Wnd(HWND parent)
			{
				hParent = parent;
			}

			~Wnd()
			{
				DestroyWindow(hWnd);
			}

			static Wnd* FromHandle(HWND hWnd) {

				LONG_PTR ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);

				Wnd *w = 0;

				if (ptr) {
					w = reinterpret_cast<Wnd*>(ptr);
				}

				return w;
			}

			virtual void OnCommand(WPARAM wParam, LPARAM lParam)
			{
				OutputDebugStringW(L"Wnd::OnCommand\n");
				return;
			}

		};
	}
}