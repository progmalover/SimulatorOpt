#include "stdafx.h"

CString g_rootWndClass, g_rootWndCap, g_subClass, g_subCap;
CWnd *g_pWnd = NULL;
BOOL CALLBACK EnumSubWindowProc(HWND hwnd, LPARAM lparam)
{
	if (::IsWindowVisible(hwnd) == FALSE)
		return TRUE;

	CString strClass;
	LPTSTR pClass = strClass.GetBufferSetLength(255);
	::RealGetWindowClass(hwnd, pClass, 255);
	strClass.ReleaseBuffer();
	if (strClass.Compare(g_subClass) == 0)
	{
		g_pWnd = CWnd::FromHandle(hwnd);
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lparam)
{
	if (::IsWindowVisible(hwnd) == FALSE)
		return TRUE;
	CString strClass;
	LPTSTR pClass = strClass.GetBufferSetLength(255);
	::RealGetWindowClass(hwnd, pClass, 255);
	strClass.ReleaseBuffer();
	if (strClass.Compare(g_rootWndClass) == 0)
	{
		CWnd *pWnd = CWnd::FromHandle(hwnd);
	 
		if (g_subClass.IsEmpty() && g_subCap.IsEmpty())
		{
			g_pWnd = pWnd;
			return TRUE;
		}
		::EnumChildWindows(hwnd, EnumSubWindowProc, 0);
		return FALSE;
	}

	return TRUE;
}

CWnd * FindSimulateWindow(CString rootWndClass, CString rootCap, CString wndClass, CString wndCap)
{
	g_rootWndClass = rootWndClass;
	g_rootWndCap = rootCap;
	g_subClass = wndClass;
	g_subCap = wndCap;
	g_pWnd = NULL;
	::EnumWindows(EnumWindowProc, 0);

	return g_pWnd;
}