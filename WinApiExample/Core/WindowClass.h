#pragma once

#include <string>

namespace xexperimente
{
	namespace WinUI 
	{
		class WindowClassName
		{
		private:
			std::wstring m_className;
			
			WindowClassName()
				:m_className(L"")
			{
			};
		public:
			
			explicit WindowClassName(const std::wstring className)
				:m_className(className)
			{
			};

			//WindowClassName(const WindowClassName& className)
			//{

			//}

			virtual ~WindowClassName()
			{

			}

			inline const wchar_t* c_str() const { return m_className.c_str(); }
			inline const std::wstring getString() const { return m_className; }
		};

		class WindowClass 
		{
		public:

			static WindowClassName getClassName();
			static int getStyle();
			static int getColor();
			static WNDPROC getWndProc();
		};
	}
}