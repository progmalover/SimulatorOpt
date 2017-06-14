#pragma once
#include "fakeinput.hpp"
#include "SimulatorMonitor.h"
#include <list>
namespace SimulatorActions {

	using namespace std;

	class Action {
	public:
		virtual void DoAction(FakeInput::Mouse  &mouse , Simulator::SimulatorMonitor *pMonitor) = 0;
	};

	class MouseAction :public Action {
	public:
		MouseAction(FakeInput::MouseButton btn, int xpos, int ypos) {
			this->btn = btn;
			this->xpos = xpos;
			this->ypos = ypos;

		}
		void DoAction(FakeInput::Mouse  &mouse , Simulator::SimulatorMonitor *pMonitor)
		{
			ASSERT(pMonitor != NULL);
			int offx, offy;
			pMonitor->getSubWndLTPos(offx,offy);

			int realx = offx + xpos;
			int realy = offy + ypos;
			mouse.moveTo(realx, realy);
			Sleep(200);
			mouse.pressButton(btn, realx, realy);
			Sleep(50);
			mouse.releaseButton(btn, realx, realy);
		}
	protected:
		int xpos, ypos;
		FakeInput::MouseButton  btn;
	};

	typedef list<MouseAction>  ACTION_LIST;
	class ActionScene
	{
	
		public:
			ActionScene();
			~ActionScene();

			BOOL InitActions(CString &actionFile);
			BOOL ActionsReady();
			void clearActions();
			void Run();
	protected:
			void SetBaseWndOffset(int x, int y);
			void bindEmulatorWnd(CWnd *pWnd);
		protected:
			ACTION_LIST   actions;
			//CWnd *pEmulatorWnd;
			int  basePosX;
			int  basePosY;
	};

};