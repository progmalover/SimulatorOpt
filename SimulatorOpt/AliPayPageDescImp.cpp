#include "stdafx.h"
#include "SimulatorMonitor.h"
#include "AliPayPagesImp.h"
#include "fakeinput.hpp"
namespace Simulator {
	typedef struct color_pair {
		COLORREF focusClr;
		COLORREF normalClr;
	}COLOR_PAIR;

	static POINT blueArrow[4] =  { {16,43},{26,43},{20,48},{20,38}};
	static COLORREF blueColors[2] = { RGB(17,143,233),RGB(158,208,245)};//0xe98e10

	//white arrow 2 种位置坐标
	static POINT whiteArrow[2][4] = { { {22,43},{32,43},{26,48},{26,38}},{{17,44},{21,39},{22,49},{27,44}} };

	static POINT btmBar[4] = { {39,525},{124,525},{193,546},{273,527} };
	static COLOR_PAIR tabsColor[4] = { { RGB(234,244,253) ,RGB(181,182,183) },
									 { RGB(240,248,255),RGB(202,202,204)},
									 { RGB(147,195,234),RGB(197,198,199)},
									 { RGB(243,249,254),RGB(142,142,143)} };

	static POINT blueBtn[4] = { 0 };
	static POINT topWnd[10] = { 0 };
	static POINT succTag[10] = { 0 };
	
 
	//3分量测试差距在30之内 ： r 30, g 30,b 30
	bool isSameColor(COLORREF clrRef, COLORREF clr,int offsetclr=30)
	{
		BYTE r = GetRValue(clrRef);
		BYTE g = GetGValue(clrRef);
		BYTE b  = GetBValue(clrRef);

		BYTE r1 = GetRValue(clr);
		BYTE g1 = GetGValue(clr);
		BYTE b1 = GetBValue(clr);

		return ((abs(g1 - g) <= offsetclr) && (abs(b1 - b) <= offsetclr)&&(abs(r - r1)<= offsetclr));
	}

	bool AliPayPageDescImp::hasGoBackBlueArrow(SimulatorGraphics &g) //具有蓝色回退按钮
	{
		COLORREF clrRef = blueColors[0];
		COLORREF clrRef2 = blueColors[1];
	 
		for (int i = 0; i < sizeof(blueArrow)/sizeof(POINT); i++)
		{
			COLORREF clr = g.getPixel(blueArrow[i].x, blueArrow[i].y);
			if (!isSameColor(clrRef, clr) && !isSameColor(clrRef2,clr))
				return false;
			
		}
		return true;
	}

	bool AliPayPageDescImp::hasGoBackWhiteArrow(SimulatorGraphics &g)//具有白色回退按钮
	{
		COLORREF clrRef = RGB(255, 255, 255);
	
		bool bhas = true;
		for (int j = 0; j < 2; j++)
		{
			bhas = true;
			for (int i = 0; i < 4; i++)
			{
				COLORREF clr = g.getPixel(whiteArrow[j][i].x, whiteArrow[j][i].y);
				if (!isSameColor(clrRef, clr))
				{
					bhas = false;
					break;
				}

			}

			if (bhas)
				break;
		}
		return bhas;
	}


	//不可能同时出现2个focus点，每个tab中点必须符合萃取值
	bool AliPayPageDescImp::hasBottomBar(SimulatorGraphics &g) //底部具有选择bar
	{
		//int focusIndex = -1;
		BOOL tabs[4] = { FALSE };
		int foucsIndex = -1;

		for (int i = 0; i < 4; i++)
		{
			COLORREF clr = g.getPixel(btmBar[i].x, btmBar[i].y);
			if (isSameColor(clr, tabsColor[i].focusClr, 10))
			{
				if (foucsIndex != -1)//不可能出现同时focus状态的2个点，出现证明不是btmBar.
					return false;

				foucsIndex = i;
				tabs[i] = TRUE;
			}

			if (isSameColor(clr, tabsColor[i].normalClr, 10))
			{
				tabs[i] = TRUE;
			}

		}


		return  (TRUE == tabs[0]) && (TRUE == tabs[1]) && (TRUE == tabs[2]) && (TRUE == tabs[3]);
	}

	bool AliPayPageDescImp::hasBlueButton(SimulatorGraphics &g)//具有蓝色条状button
	{
		return true;
	}

	bool AliPayPageDescImp::hasPopWnd(SimulatorGraphics &g) //有弹出框当前
	{
		return true;
	}

	bool AliPayPageDescImp::hasSuccTag(SimulatorGraphics &g)//具有交易成功的特征
	{
		return true;
	}


	void AliPayPageDescImp::clickGoBackArrow()
	{

	}

	void AliPayPageDescImp::clickBtnBarTab(int index)
	{

	}

	void AliPayPageDescImp::closePopWnd()
	{
		int x, y;
		SimulatorMonitor::getInst()->getSubWndLTPos(x, y);

		int realx = x +  239;
		int realy = y +  332;

		mouseClick(realx, realy);
	}

	void AliPayPageDescImp::clickBlueButton()
	{
		int x, y;
		SimulatorMonitor::getInst()->getSubWndLTPos(x, y);

		int realx = x + blueArrow[0].x;
		int realy = y + blueArrow[0].y;

		mouseClick(realx, realy);
	}

	void AliPayPageDescImp::clickWhiteButton()
	{
		int x, y;
		SimulatorMonitor::getInst()->getSubWndLTPos(x, y);

		FakeInput::Mouse mouse;
		int realx = x + whiteArrow[0][0].x;
		int realy = y + whiteArrow[0][0].y;

		mouseClick(realx, realy);
	}

	void AliPayPageDescImp::clickBottomBar(int index)
	{
		if (index < 0 || index >= 4)
		{
			::OutputDebugString(_T("\n clickBottomBar:out of bottom bar index range!\n"));
			return;
		}

		int x, y;
		SimulatorMonitor::getInst()->getSubWndLTPos(x, y);

		FakeInput::Mouse mouse;
		int realx = x + btmBar[index].x;
		int realy = y + btmBar[index].y;

		mouseClick(realx, realy);
	}

	void AliPayPageDescImp::mouseClick(int realx, int realy)
	{
		FakeInput::Mouse mouse;
		mouse.moveTo(realx, realy);
		mouse.pressButton(FakeInput::MouseButton::Mouse_Left, realx, realy);
		Sleep(50);
		mouse.releaseButton(FakeInput::MouseButton::Mouse_Left, realx, realy);
	}

};