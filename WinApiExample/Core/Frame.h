#pragma once

#include "stdafx.h"
#include "Wnd.h"

namespace xexperimente
{
	namespace WinUI
	{
		class Frame {
			HWND hParent = nullptr;
			
			//HFONT font = nullptr;
			//WNDPROC WindowProc = nullptr;
		public:
			HWND hWnd = nullptr;

			Frame(HWND parent = nullptr)
			{
				hParent = parent;

				registerWindowClass();

				hWnd = CreateWindowW(
					L"WinUI.Frame",
					L"Titulek",
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					800,
					500,
					parent,
					nullptr,
					GetModuleHandle(NULL),
					nullptr
				);

				if (!hWnd)
					return;

				SetWindowLongPtr(hWnd, GWL_USERDATA, (ULONG_PTR)this);

				ShowWindow(hWnd, SW_SHOW);
				UpdateWindow(hWnd);
			}
			~Frame()
			{
				DestroyWindow(hWnd);
			}

			static void registerWindowClass() {

				WNDCLASSEX wcex;

				wcex.cbSize = sizeof(WNDCLASSEX);

				wcex.style = CS_HREDRAW | CS_VREDRAW;
				wcex.lpfnWndProc = globalWndProc;
				wcex.cbClsExtra = 0;
				wcex.cbWndExtra = 0;
				wcex.hInstance = GetModuleHandle(NULL);
				wcex.hIcon = 0;
				wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
				wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
				wcex.lpszMenuName = 0;
				wcex.lpszClassName = L"WinUI.Frame";
				wcex.hIconSm = 0;

				RegisterClassEx(&wcex);
			}

			static LRESULT CALLBACK globalWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
			{
				Frame *frame = (Frame*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

				if (frame) {
					return frame->LocalWindowProc(hWnd, Msg, wParam, lParam);
				}

				if (Msg == WM_NCDESTROY) {
					delete frame;
				}

				return DefWindowProc(hWnd, Msg, wParam, lParam);
			}

			LRESULT CALLBACK LocalWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
			{
				if (Msg == WM_COMMAND) {

					int id = LOWORD(wParam);
					DWORD nCode = HIWORD(wParam);
					HWND handle = (HWND)lParam;

					Wnd *w = Wnd::FromHandle(handle);

					if (w) 
						w->OnCommand(wParam, lParam);
				}

				if (Msg == WM_DESTROY) {
					PostQuitMessage(0);
					return 0;
				}

				//if (WindowProc) {
				//	return WindowProc(hWnd, Msg, wParam, lParam);
				//}

				return DefWindowProc(hWnd, Msg, wParam, lParam);
			}

		};
	}
}