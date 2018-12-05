#pragma once

#include "stdafx.h"
#include "Frame.h"

namespace xexperimente
{
	namespace WinUI
	{
		class App {

		public:

			App() {
				INITCOMMONCONTROLSEX icce;
				icce.dwSize = sizeof(INITCOMMONCONTROLSEX);
				icce.dwICC = 0
					| ICC_WIN95_CLASSES
					| ICC_BAR_CLASSES
					| ICC_COOL_CLASSES
					;

				InitCommonControlsEx(&icce);
			}

			void run() {

				// Main message loop:
				MSG msg;
				while (GetMessage(&msg, NULL, 0, 0))
				{
					HWND hwnd = GetForegroundWindow();
					if (hwnd == NULL || !IsDialogMessage(hwnd, &msg))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}

			}

			//Frame *mainFrame = nullptr;

		};
	}
}