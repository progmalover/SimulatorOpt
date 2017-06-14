#pragma once
#include "stdafx.h"
#include <vector>
#include "SimulatorGraphics.h"
namespace Simulator {
	//
	//ģ�������ڼ��������Լ�ҳ��ʶ����(Graphics)����װֱ��ĳ��ҳ�����Ϊ����,
	//ҳ���ȡʶ���߼��ȡ�
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
	//ʶ��ǰapp page��ҳ,��һЩ��������ã����ˣ�ҳ����ת�ȶ���
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
		CWnd *getSimulatorWnd() { return pSimulatorWnd; }//�����������
		CWnd *getSimulatorSubWnd() { return pSubWnd; } //androidͼ�δ���
	protected:
		CWnd *pSimulatorWnd;
		CWnd *pSubWnd;
		SimulatorPages  *pPages;
	};

};