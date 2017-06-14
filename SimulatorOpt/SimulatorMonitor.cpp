#include "stdafx.h"
#include "SimulatorMonitor.h"
#include "SimulatorWnd.h"
#include "AliPayPagesImp.h"
namespace Simulator {

	SimulatorMonitor * SimulatorMonitor::getInst(SimulatorMonitor::Sim t )
	{
		static SimulatorMonitor *_pInst;
		if (NULL == _pInst)
		{
			_pInst = new SimulatorMonitor(t);
		}

		return _pInst;
	}

	SimulatorMonitor::SimulatorMonitor(SimulatorMonitor::Sim t):pSimulatorWnd(NULL)
	{
		if (t == Sim::ALIPAY)
		{
			this->pPages = new AliPayPagesImp();
		}
		else
			::OutputDebugString("\n not implement apppages monitor!\n");
	}

	SimulatorMonitor::~SimulatorMonitor()
	{}


	bool SimulatorMonitor::bindToSimulator()
	{
		this->pSimulatorWnd = FindSimulateWindow(_T("Qt5QWindowIcon"), _T(""), _T(""), _T(""));
		this->pSubWnd = FindSimulateWindow(_T("Qt5QWindowIcon"), _T(""), _T("subWin"), _T("sub"));
		if (NULL == pSubWnd || NULL == pSimulatorWnd)
		{
			pSubWnd = NULL;
			pSimulatorWnd = NULL;
			return false;
		}
		return true;
	}

	void SimulatorMonitor::reposSimulatorWnd()
	{
		if (NULL != pSimulatorWnd)
		{
			DWORD dwStyple = pSimulatorWnd->GetStyle();
			//最大最小化窗口都需要重置为一般状态
			if ((dwStyple & WS_ICONIC) == WS_ICONIC || 
						(dwStyple & WS_MAXIMIZE) == WS_MAXIMIZE)
			{
				pSimulatorWnd->SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			}

			CRect wndRect;
			pSimulatorWnd->GetWindowRect(&wndRect);
			wndRect.SetRect(wndRect.left, wndRect.top, wndRect.left + 400, wndRect.top + 600);
			pSimulatorWnd->MoveWindow(&wndRect);
			pSimulatorWnd->CenterWindow();
			pSimulatorWnd->SetForegroundWindow();
			pSimulatorWnd->ModifyStyle((DWORD)(WS_MINIMIZEBOX | WS_MAXIMIZEBOX),0);
			
		}
	}

	bool SimulatorMonitor::getSubWndLTPos(int &x, int &y)
	{
		x = 0;  
		y = 0;

		if (NULL == pSubWnd)
			return false;

		CRect wndRect;
		pSubWnd->GetWindowRect(&wndRect);
		x = wndRect.left;
		y = wndRect.top;

		return true;
	}

	bool SimulatorMonitor::gotoPage(PAGE_TAG page)
	{
		if(page == PAGE_TAG::MAIN_PAGE)
			return this->pPages->gotoMainPage();
	}
};