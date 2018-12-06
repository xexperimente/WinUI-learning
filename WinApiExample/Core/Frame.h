#pragma once

#include "Window.h"

namespace xexperimente
{
	namespace WinUI
	{
		class FrameClass : public WindowClass
		{
		public:
			static WindowClassName getClassName()
			{
				return WindowClassName(L"xexperimente.WinUI.Frame");
			}
		};

		class Frame: public Register<FrameClass>, public Window
		{
		public:
			Frame(const std::wstring title, Window* parent = nullptr, UINT style = 0)
				:Window(FrameClass::getClassName(), parent, WS_OVERLAPPEDWINDOW | style)
			{
				if (::IsWindow(hWnd))
					SetWindowText(hWnd, title.c_str());

				ShowWindow(hWnd, SW_SHOW);
				UpdateWindow(hWnd);
			}

			~Frame()
			{
				DestroyWindow(hWnd);
			}


			void SetIcon(int id)
			{
				auto icon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(id));

				SendMessage(hWnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(icon));
			}
		};


	}
}