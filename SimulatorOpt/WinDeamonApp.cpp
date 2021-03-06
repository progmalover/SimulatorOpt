// WinDeamonApp.cpp : implementation file
//

#include "stdafx.h"
#include "Cashier_deamon.h"
#include "fakeinput.hpp"
#include "WinDeamonApp.h"
#include "Process.h"
#include "SimulatorWnd.h"
#include "ActionScene.h"
#include <stdio.h>
#include "SimulatorMonitor.h"
#include "SimulatorGraphics.h"
#include "AliPayPagesImp.h"
// CWinDeamonApp
using namespace Simulator;
IMPLEMENT_DYNCREATE(CWinDeamonApp, CWinApp)

CWinDeamonApp::CWinDeamonApp()
{
}

CWinDeamonApp::~CWinDeamonApp()
{
}


BOOL CWinDeamonApp::InitInstance()
{
 
	TCHAR *mutex_name= _T("single-instance-for-simulator-server-flag");
	HANDLE handle = ::OpenMutex(0x20000,FALSE,mutex_name);
    
	//ensure singleton 
	if(handle == NULL)
	{
		::CreateMutex(NULL,FALSE,mutex_name);
	}else
		return 0;
 
 
	SimulatorActions::ActionScene  scenes;

	TCHAR appPathName[255] = {0};
	::GetModuleFileName(this->m_hInstance, appPathName, 255);
	::PathRemoveFileSpec(appPathName);
	 
 
    while(true)
	{
		//::Sleep(5000);
		 SimulatorMonitor *pMonitor = SimulatorMonitor::getInst();

		 bool bBind = pMonitor->bindToSimulator();
		 if (!bBind)
		 {
			  int nRet = AfxGetApp()->DoMessageBox("未发现模拟器窗口", MB_RETRYCANCEL, MB_OK);
			  if (nRet == IDRETRY)
				  continue;
			  else
				  break;
		 }

		 ::Sleep(1000);
	
		 pMonitor->reposSimulatorWnd();

		 
		// CWnd *pSubWnd = pMonitor->getSimulatorSubWnd();
		// SimulatorGraphics sg(pSubWnd);
		// sg.copyImage();

	//	 bool bhas = AliPayPageDescImp::hasBottomBar(sg);
		// AliPayPageDescImp::clickBottomBar(3);
		 
		 scenes.clearActions();
		 CString strPath = appPathName;
	     scenes.InitActions(strPath + "\\actions");
		 
		 scenes.Run();

		 int nRet = AfxGetApp()->DoMessageBox("退出吗？", MB_YESNO, MB_OK);
		 if (nRet == IDYES)
			 break;


		 ::Sleep(2000);

	}
	return TRUE;
}

int CWinDeamonApp::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinApp::ExitInstance();
}

BEGIN_MESSAGE_MAP(CWinDeamonApp, CWinApp)
END_MESSAGE_MAP()


// CWinDeamonApp message handlers
