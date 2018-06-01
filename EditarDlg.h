#pragma once   //_____________________________________________ EditarDlg.h  
#include "resource.h"

class EditarDlg: public Win::Dialog
{
public:
	EditarDlg()
	{
	}
	~EditarDlg()
	{
	}
	int client_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Textbox tbxNombre;
	Win::Label lb1;
	Win::Button btOK;
	Win::Button btCancel;
	Win::Textbox tbxDireccion;
	Win::Textbox tbxTPC;
	Win::Label lb2;
	Win::Label lb3;
protected:
	Win::Gdi::Font fontArial009A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx=Sys::Convert::CentimetersToDlgUnitX(9.78958);
		dlgTemplate.cy=Sys::Convert::CentimetersToDlgUnitY(3.81000);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		tbxNombre.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 3.62479, 0.87313, 3.20146, 0.60854, hWnd, 1000);
		lb1.CreateX(NULL, L"Nombre", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 0.79375, 0.79375, 2.61938, 0.60854, hWnd, 1001);
		btOK.CreateX(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 7.85813, 0.79375, 1.74625, 0.68792, hWnd, 1002);
		btCancel.CreateX(NULL, L"Cancelar", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 7.91104, 1.87854, 1.64042, 0.68792, hWnd, 1003);
		tbxDireccion.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 3.81000, 1.95792, 2.91042, 0.60854, hWnd, 1004);
		tbxTPC.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 3.75708, 2.93688, 2.98979, 0.60854, hWnd, 1005);
		lb2.CreateX(NULL, L"Dirreccion", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 0.89958, 1.98438, 2.38125, 0.60854, hWnd, 1006);
		lb3.CreateX(NULL, L"Tipo de dato", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 0.63500, 3.01625, 2.75167, 0.60854, hWnd, 1007);
		fontArial009A.CreateX(L"Arial", 0.317500, false, false, false, false);
		tbxNombre.Font = fontArial009A;
		lb1.Font = fontArial009A;
		btOK.Font = fontArial009A;
		btCancel.Font = fontArial009A;
		tbxDireccion.Font = fontArial009A;
		tbxTPC.Font = fontArial009A;
		lb2.Font = fontArial009A;
		lb3.Font = fontArial009A;
	}
	//_________________________________________________
	void btOK_Click(Win::Event& e);
	void btCancel_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (btOK.IsEvent(e, BN_CLICKED)) {btOK_Click(e); return true;}
		if (btCancel.IsEvent(e, BN_CLICKED)) {btCancel_Click(e); return true;}
		return false;
	}
};
