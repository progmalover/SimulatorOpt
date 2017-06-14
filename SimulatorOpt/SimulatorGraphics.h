#pragma once
#include "atlimage.h"
namespace Simulator {
	class SimulatorGraphics
	{
	public:
		SimulatorGraphics(CWnd *pSimSubWnd);
		~SimulatorGraphics();
		bool copyImage();
		COLORREF getPixel(int x, int y);
	private:
		CWnd *pSimSubWnd;
		CImage graphic;
	};

};