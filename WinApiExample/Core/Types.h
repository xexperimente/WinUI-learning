#pragma once

namespace xexperimente
{
	namespace WinUI
	{
		class Size
		{
		public:
			int w = 0;
			int h = 0;

			Size(int width, int height)
				:w(width), h(height)
			{ };
		};
	}
}