#pragma once

#include "Register.h"
#include "WindowClass.h"
#include "types.h"

namespace xexperimente
{
	namespace WinUI
	{
		class Window: public Register<WindowClass> 
		{
			
		public:
			HWND hWnd = nullptr;
			Window *m_parent = nullptr;

			Window(const WindowClassName& className, Window *parent, UINT style)
			{
				m_parent = parent;

				hWnd = create(className.getString(), parent, style);

				SetWindowLongPtr(hWnd, GWL_USERDATA, (ULONG_PTR)this);
			}

			~Window()
			{
				DestroyWindow(hWnd);
			}

			static Window* fromHandle(HWND hWnd) {

				LONG_PTR ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);

				Window *w = 0;

				if (ptr) {
					w = reinterpret_cast<Window*>(ptr);
				}

				return w;
			}
			
			static WNDPROC getGlobalWndProc() { 
				return Window::globalWndProc; 
			};


			virtual bool OnCommand(WPARAM wParam, LPARAM lParam)
			{
				OutputDebugStringW(L"Wnd::OnCommand\n");
				return true;
			};

			Size SetSize(Size size)
			{
				assert(::IsWindow(hWnd));

				RECT rc;
				GetClientRect(hWnd, &rc);

				MoveWindow(hWnd, rc.left, rc.top, rc.left + size.w, rc.top + size.h, TRUE);

				return Size(rc.right - rc.left, rc.bottom - rc.top);
			};

		private:
			static LRESULT CALLBACK globalWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
			{
				Window* window = Window::fromHandle(hWnd);

				if (window)
				{
					LRESULT lResult;

					auto used = window->wndProc(message, wParam, lParam, lResult);
					if (!used)
						lResult = window->defWndProc(message, wParam, lParam);
					
					return lResult;
				}
				return DefWindowProc(hWnd, message, wParam, lParam);
			};

		protected:

			virtual HWND create(const std::wstring className, Window* parent, UINT style)
			{
				auto ret = CreateWindowEx(0/* styleex*/, className.c_str(), L"",
					style,
					CW_USEDEFAULT, CW_USEDEFAULT,
					500, 500,
					parent ? parent->hWnd : (HWND)NULL,
					(HMENU)NULL,
					GetModuleHandle(NULL),
					reinterpret_cast<LPVOID>(this));

				if (ret != NULL) 
					return ret;

				auto i = GetLastError();

				return NULL;
			}

			LRESULT defWndProc(UINT message, WPARAM wParam, LPARAM lParam)
			{
				return ::DefWindowProc(hWnd, message, wParam, lParam);
			}

			virtual bool wndProc(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
			{
				if (message == WM_COMMAND)
				{
					if (reinterpret_cast<HWND>(lParam) != NULL) 
					{
						HWND hwndCtrl = reinterpret_cast<HWND>(lParam);
						Window* child = Window::fromHandle(hwndCtrl);
					}
					Window *wnd = Window::fromHandle((HWND)lParam);
					if (wnd)
						return wnd->OnCommand(wParam, lParam);

					return OnCommand(wParam, lParam);

				}
				if (message == WM_ERASEBKGND)
				{
					//HDC hdc = reinterpret_cast<HDC>(wParam);

					//RECT rc{ 0, 0, 100, 100 };
					//FillRect(hdc, &rc, CreateSolidBrush(RGB(255, 0, 0)));
				}
				if (message == WM_DESTROY)
				{
					PostQuitMessage(0);
					lResult = 0;
					return true;
				}
				return false;
			}
		};
	}
}