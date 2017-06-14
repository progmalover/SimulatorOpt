#include "stdafx.h"
#include "ActionScene.h"
#include "SimulatorMonitor.h"
namespace SimulatorActions {
	ActionScene::ActionScene():basePosX(0), basePosY(0)
	{}

	ActionScene::~ActionScene(){}
	BOOL  ActionScene::ActionsReady()
	{
		return actions.size();
	}
	BOOL ActionScene:: InitActions(CString &actionFile)
	{
		if (FALSE == ::PathFileExists(actionFile))
		{
			::OutputDebugString(_T("\n ActionFile:") + actionFile +  " not exist!\n");
			return FALSE;
		}
		try 
		{
		
			CStdioFile  file(actionFile, CStdioFile::modeRead);
			CString strLine;
			while (file.ReadString(strLine))
			{
				::OutputDebugString(strLine + "\n");
				CString strTag ;

				AfxExtractSubString(strTag, strLine, 0, _T(','));
				if (0 == strTag.CompareNoCase("mouse")) //鼠标 
				{
					CString strSec1, strSec2, strSec3;
					AfxExtractSubString(strSec1, strLine, 1, _T(','));
					AfxExtractSubString(strSec2, strLine, 2, _T(','));
					AfxExtractSubString(strSec3, strLine, 3, _T(','));

					int btn = ::StrToInt(strSec1);
					int xpos = ::StrToInt(strSec2) ;
					int ypos = ::StrToInt(strSec3) ; //to real screen pos.

					MouseAction action((FakeInput::MouseButton)btn, xpos, ypos);
					actions.push_back(action);

				}else
				if (0 == strTag.CompareNoCase("keyboard"))
				{
					::OutputDebugString("\n not implement keyboard!\n");
				}
				else
				{
					::OutputDebugString("\n not implement " + strTag + "\n");
				}
				
			}
		}
		catch (CException *e) {

			e->ReportError();
			e->Delete();
			return FALSE;
		}

		return TRUE;
	}

	void  ActionScene::clearActions()
	{
		this->actions.clear();
	}

	void ActionScene::Run()
	{
		if (actions.size() <= 0)
			return;

		//跑脚本前，一定要确定窗口位置
		Simulator::SimulatorMonitor *pMonitor = Simulator::SimulatorMonitor::getInst();
		pMonitor->reposSimulatorWnd();
		pMonitor->gotoPage(Simulator::PAGE_TAG::MAIN_PAGE);

		FakeInput::Mouse mouse;
		for (auto a = actions.begin(); a != actions.end(); a++)
		{
			MouseAction & act = *a;
			act.DoAction(mouse ,pMonitor);
			Sleep(500);
		}

		 
	}

}