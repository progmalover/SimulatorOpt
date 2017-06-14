#pragma once
#include "SimulatorMonitor.h"
#include "SimulatorGraphics.h"
namespace Simulator {

	class AliPayPageDescImp :SimulatorPageDesc
	{
		public:

			//judgment 
			static bool hasGoBackBlueArrow(SimulatorGraphics &g); //具有蓝色回退按钮
			static bool hasGoBackWhiteArrow(SimulatorGraphics &g);//具有白色回退按钮
			static bool hasBottomBar(SimulatorGraphics &g); //地步具有选择bar
			static bool hasBlueButton(SimulatorGraphics &g);//具有蓝色条状button
			static bool hasPopWnd(SimulatorGraphics &g); //有弹出框当前
			static bool hasSuccTag(SimulatorGraphics &g);//具有交易成功的特征

			//click 
			static void clickGoBackArrow();
			static void clickBtnBarTab(int index);
			static void closePopWnd();
			static void clickBlueButton();
			static void clickWhiteButton();
			static void clickBottomBar(int index);
			static void mouseClick(int realx, int realy);

	};

	class AliPayMainPageDescImp :public AliPayPageDescImp
	{
	public:
		bool isPage(SimulatorGraphics &graphic);
		bool gotoPage(SimulatorGraphics &graphic);
	};

	class AliPayPagesImp :public SimulatorPages
	{
		public:
			AliPayPagesImp();
			~AliPayPagesImp();

 
		bool InitPages();
		bool gotoMainPage();
	};

};