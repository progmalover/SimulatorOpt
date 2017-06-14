#pragma once



// CWinDeamonApp

class CWinDeamonApp : public CWinApp
{
	DECLARE_DYNCREATE(CWinDeamonApp)

public:
	CWinDeamonApp();           // protected constructor used by dynamic creation
	virtual ~CWinDeamonApp();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


