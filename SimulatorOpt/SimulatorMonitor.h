#pragma once
#include "stdafx.h"
#include <vector>
#include "SimulatorGraphics.h"
namespace Simulator {
	//
	//模拟器窗口监视器，以及页面识别器(Graphics)，封装直达某个页面的行为方法,
	//页面点取识别逻辑等。
	//

	enum PAGE_TAG {
		MAIN_PAGE = 1,
		TRANS_PAGE,
		TRANS_ENSURE_PAGE,
		TRANS_SUCC_PAGE,
		TRANS_FAIl_PAGE
	};

	class SimulatorPageDesc
	{ 
	public:
		virtual bool isPage(SimulatorGraphics &graphic) = NULL;
		virtual bool gotoPage(SimulatorGraphics &graphic) = NULL;
	};

	typedef std::vector<SimulatorPageDesc *> SIM_PAGE_OBJS;
	class SimulatorPages
	{
		 
	public:  
		virtual bool InitPages() = NULL;
		virtual bool gotoMainPage() = NULL;
	protected:
		SIM_PAGE_OBJS  simPages;

	};

	//
	//识别当前app page主页,做一些必须的重置，回退，页面跳转等动作
	//
	class SimulatorMonitor
	{
	public:
		enum Sim{
			ALIPAY = 1,
			WEICHAT
		};
	public:
		SimulatorMonitor(Sim t);
		~SimulatorMonitor();
	public:
		static SimulatorMonitor * getInst( Sim type=Sim::ALIPAY);
		//void bindSimulatorWnd(CWnd *);
		bool bindToSimulator();
		void reposSimulatorWnd();
		bool gotoPage(PAGE_TAG page);
		bool getSubWndLTPos(int &x, int &y);
		CWnd *getSimulatorWnd() { return pSimulatorWnd; }//虚拟机主窗口
		CWnd *getSimulatorSubWnd() { return pSubWnd; } //android图形窗口
	protected:
		CWnd *pSimulatorWnd;
		CWnd *pSubWnd;
		SimulatorPages  *pPages;
	};

};