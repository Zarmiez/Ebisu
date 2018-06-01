#pragma once   //_____________________________________________ AgregarDlg.h  
#include "resource.h"

class AgregarDlg: public Win::Dialog
{
public:
	AgregarDlg()
	{
	}
	~AgregarDlg()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button btOK;
	Win::Button btCancelar;
	Win::Textbox tbxNombre;
	Win::Textbox tbxDireccion;
	Win::Textbox tbxTPC;
	Win::Label lb1;
	Win::Label lb2;
	Win::Label lb3;
protected:
	Win::Gdi::Font fontArial009A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx=Sys::Convert::CentimetersToDlgUnitX(9.07521);
		dlgTemplate.cy=Sys::Convert::CentimetersToDlgUnitY(3.30729);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		btOK.CreateX(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 6.53521, 0.26458, 1.27000, 0.68792, hWnd, 1000);
		btCancelar.CreateX(NULL, L"Cancelar", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 6.45583, 1.27000, 2.43417, 0.68792, hWnd, 1001);
		tbxNombre.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 2.01083, 0.29104, 3.57187, 0.60854, hWnd, 1002);
		tbxDireccion.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 2.03729, 1.24354, 3.59833, 0.60854, hWnd, 1003);
		tbxTPC.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 2.19604, 2.35479, 3.59833, 0.60854, hWnd, 1004);
		lb1.CreateX(NULL, L"Nombre", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 0.02646, 0.26458, 1.66688, 0.60854, hWnd, 1005);
		lb2.CreateX(NULL, L"Direccion", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 0.02646, 1.24354, 1.77271, 0.60854, hWnd, 1006);
		lb3.CreateX(NULL, L"Tipo de Cuenta", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 0.07938, 2.30187, 1.69333, 0.82021, hWnd, 1007);
		fontArial009A.CreateX(L"Arial", 0.317500, false, false, false, false);
		btOK.Font = fontArial009A;
		btCancelar.Font = fontArial009A;
		tbxNombre.Font = fontArial009A;
		tbxDireccion.Font = fontArial009A;
		tbxTPC.Font = fontArial009A;
		lb1.Font = fontArial009A;
		lb2.Font = fontArial009A;
		lb3.Font = fontArial009A;
	}
	//_________________________________________________
	void btOK_Click(Win::Event& e);
	void btCancelar_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (btOK.IsEvent(e, BN_CLICKED)) {btOK_Click(e); return true;}
		if (btCancelar.IsEvent(e, BN_CLICKED)) {btCancelar_Click(e); return true;}
		return false;
	}
};
