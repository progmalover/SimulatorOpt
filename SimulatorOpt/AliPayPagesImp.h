#pragma once
#include "SimulatorMonitor.h"
#include "SimulatorGraphics.h"
namespace Simulator {

	class AliPayPageDescImp :SimulatorPageDesc
	{
		public:

			//judgment 
			static bool hasGoBackBlueArrow(SimulatorGraphics &g); //������ɫ���˰�ť
			static bool hasGoBackWhiteArrow(SimulatorGraphics &g);//���а�ɫ���˰�ť
			static bool hasBottomBar(SimulatorGraphics &g); //�ز�����ѡ��bar
			static bool hasBlueButton(SimulatorGraphics &g);//������ɫ��״button
			static bool hasPopWnd(SimulatorGraphics &g); //�е�����ǰ
			static bool hasSuccTag(SimulatorGraphics &g);//���н��׳ɹ�������

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