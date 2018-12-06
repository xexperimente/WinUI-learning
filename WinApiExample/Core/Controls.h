#pragma once

#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "Frame.h"
#include "WindowClass.h"

namespace xexperimente
{
	namespace WinUI
	{
		typedef std::function<void()> callback_t;

		class CallbackHandler {
			std::vector<callback_t> handlers;
		public:
			void connect(const callback_t &cb)
			{
				handlers.push_back(cb);
			}

			void fire()
			{
				for (const callback_t& f : handlers)
				{
					OutputDebugStringW(L"Firing\n");
					f();
				}
			}
		};

		class StaticText : public WinUI::Window {
		public:
			StaticText(const std::wstring& text, Window* parent, UINT style = 0)
				:Window(WindowClassName(WC_STATIC), parent, style)
			{
			}
		};

		class Button : public WinUI::Window {
		public:
			Button(const std::wstring& text, Window* parent, UINT style)
				:Window(WindowClassName(WC_BUTTON), parent, style)
			{
				SetWindowText(hWnd, text.c_str());
				
				auto font = GetStockObject(DEFAULT_GUI_FONT);

				SendMessage(hWnd, WM_SETFONT, (WPARAM)font, TRUE);
			}

			virtual bool OnCommand(WPARAM wParam, LPARAM lParam)
			{
				OutputDebugStringW(L"Button::OnCommand\n");

				Click.fire();
				return true;
			}

			CallbackHandler Click;
		};
	}
}
