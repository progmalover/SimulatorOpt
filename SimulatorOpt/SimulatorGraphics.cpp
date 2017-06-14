#include "stdafx.h"
#include "SimulatorGraphics.h"

namespace Simulator {
	static CBitmap bitmap;
	SimulatorGraphics::SimulatorGraphics(CWnd *pSimSubWnd = NULL)
	{
		this->pSimSubWnd = pSimSubWnd;
		if (NULL == this->pSimSubWnd)
			return;
	}

	SimulatorGraphics::~SimulatorGraphics()
	{
	}

	//位图内坐标直接获取像素点 
	COLORREF SimulatorGraphics::getPixel(int x, int y)
	{
		if (NULL == bitmap.GetSafeHandle())
			return RGB(0, 0, 0);
		//graphic.Detach();
		//graphic.Attach(bitmap);
		return graphic.GetPixel(x, y);
	}

	bool SimulatorGraphics::copyImage()
	{
	    HGDIOBJ hg = bitmap.GetSafeHandle();
		if (NULL != hg)
			bitmap.DeleteObject();

		if (NULL == this->pSimSubWnd)
			return false;
		if (FALSE == pSimSubWnd->IsWindowVisible())
			return false;

		//pSimSubWnd->LockWindowUpdate();

		CDC memdc;
		CDC *pDC = pSimSubWnd->GetDC();
	
		memdc.CreateCompatibleDC( pDC);
		CRect wndRect;
		pSimSubWnd->GetWindowRect(&wndRect);
		
		bitmap.CreateCompatibleBitmap(pDC, wndRect.Width(),wndRect.Height());
		
		int top = memdc.SaveDC();
		memdc.SelectObject(bitmap);
		memdc.StretchBlt(0, 0, wndRect.Width(), wndRect.Height(), pDC, 0,0,wndRect.Width(), wndRect.Height(), SRCCOPY| CAPTUREBLT);
		memdc.RestoreDC(top);
		
		//test ...
		if(!graphic.IsNull())
		    graphic.Detach();
		graphic.Attach((HBITMAP)bitmap.GetSafeHandle());

#ifdef _DEBUG
		graphic.Save(_T("d:\\image.bmp"));
#endif
		 
		return true;
	}
};
