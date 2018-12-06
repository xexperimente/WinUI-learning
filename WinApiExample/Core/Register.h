#pragma once

#include "WindowClass.h"

namespace xexperimente
{
	namespace WinUI
	{
		template<class T>
		class Register
		{
		public:
			Register()
			{
				WindowClassName class_name = T::getClassName();
				WNDCLASSEX wcex;
				auto hInstance = GetModuleHandle(NULL);

				if (!GetClassInfoEx(hInstance, class_name.c_str(), &wcex)) {

					wcex.cbSize = sizeof(WNDCLASSEX);

					wcex.style = T::getStyle();
					wcex.lpfnWndProc = T::getWndProc();
					wcex.cbClsExtra = 0;
					wcex.cbWndExtra = 0;
					wcex.hInstance = hInstance;
					wcex.hIcon = 0;
					wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
					wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
					wcex.lpszMenuName = (LPCTSTR)NULL;
					wcex.lpszClassName = class_name.c_str();
					wcex.hIconSm = NULL;

					if (RegisterClassEx(&wcex) == 0)
					{
						assert(true); //registration failed
					};
				}
			}
		};
	}
}