#include "stdafx.h"
#include "SimulatorMonitor.h"
#include "AliPayPagesImp.h"
namespace Simulator{
 
	//�����ҳ����˵�䣬���ṩ�жϼ��
	bool AliPayMainPageDescImp::isPage(SimulatorGraphics &graphic)
	{
		return  __super::hasBottomBar(graphic);
	}


	bool AliPayMainPageDescImp::gotoPage(SimulatorGraphics &graphic)
	{
		Sleep(200);
		if (__super::hasPopWnd(graphic))
		{
			__super::closePopWnd();
			Sleep(500);
			graphic.copyImage();
		}

		bool bHasBackArrow = __super::hasGoBackBlueArrow(graphic);
		while (bHasBackArrow)
		{
			//click it
			__super::clickBlueButton();
			Sleep(500);
			//graphic renew
			graphic.copyImage();

			//
			bHasBackArrow = __super::hasGoBackBlueArrow(graphic);
		}


		bHasBackArrow = __super::hasGoBackWhiteArrow(graphic);
		while(bHasBackArrow)
		{
			//click return;
			__super::clickWhiteButton();
			//graphic renew
			Sleep(500);
			graphic.copyImage();

			//
			bHasBackArrow = __super::hasGoBackBlueArrow(graphic);
		}


		bool bHasBtmBar = __super::hasBottomBar(graphic);

		return bHasBtmBar;
	}
};