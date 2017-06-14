#include "stdafx.h"
#include "AliPayPagesImp.h"
//#include "AliPayMainPageImp.h"
namespace Simulator {
	AliPayPagesImp::AliPayPagesImp()
	{
		this->simPages.resize(10);
		InitPages();
	}


	AliPayPagesImp::~AliPayPagesImp()
	{
	}

	bool AliPayPagesImp::InitPages()
	{
		this->simPages[PAGE_TAG::MAIN_PAGE] = (SimulatorPageDesc *) new AliPayMainPageDescImp();
		return true;
	}

	//
	//��ȡ��ǰ���ڽ�ͼ��������ж�goto�߼�
	//
	bool AliPayPagesImp::gotoMainPage()
	{
		SimulatorMonitor *pMonitor = Simulator::SimulatorMonitor::getInst();
		CWnd *pSubWnd = pMonitor->getSimulatorSubWnd();

		if (NULL == pSubWnd)
		{
			::OutputDebugString("\n SimulatorMonitor ��ȡAndroid�滭����ʧ��! \n");
			return false;
		}

		SimulatorGraphics graphic(pSubWnd);
		pMonitor->reposSimulatorWnd();
		graphic.copyImage();

		if (simPages.size() <= 0)
			return false;
		bool bret = simPages[PAGE_TAG::MAIN_PAGE]->isPage(graphic);
		if (bret)
			return true;
		else
		{
			return simPages[PAGE_TAG::MAIN_PAGE]->gotoPage(graphic);
		}
			//simPages[page]->gotoPage();
		return false;
	}
};