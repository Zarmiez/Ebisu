#pragma once  //______________________________________ Clientes_cajero.h  
#include "Resource.h"
#include "AgregarDlg.h"
#include "EditarDlg.h"
class Clientes_cajero: public Win::Dialog
{
public:
	Clientes_cajero()
	{
	}
	~Clientes_cajero()
	{
	}
	LPARAM client_id;
	void pintar();
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Toolbar toolb1;
	Win::ListView lvClientes;
protected:
	Win::Gdi::Font fontArial009A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx=Sys::Convert::CentimetersToDlgUnitX(13.52021);
		dlgTemplate.cy=Sys::Convert::CentimetersToDlgUnitY(10.76854);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"Clientes_cajero";
		toolb1.CreateX(NULL, NULL, WS_CHILD | WS_VISIBLE | CCS_NORESIZE | CCS_NOPARENTALIGN | CCS_ADJUSTABLE | CCS_NODIVIDER | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, 0.50271, 0.55563, 11.95917, 1.19063, hWnd, 1000);
		lvClientes.CreateX(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_REPORT, 0.58208, 2.88396, 12.75292, 7.69937, hWnd, 1001);
		lvClientes.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial009A.CreateX(L"Arial", 0.317500, false, false, false, false);
		lvClientes.Font = fontArial009A;
	}
	//_________________________________________________
	void Window_Open(Win::Event& e);
	void Cmd_Add(Win::Event& e);
	void Cmd_Delete(Win::Event& e);
	void Cmd_Edit(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (this->IsEvent(e, IDM_ADD)) {Cmd_Add(e); return true;}
		if (this->IsEvent(e, IDM_DELETE)) {Cmd_Delete(e); return true;}
		if (this->IsEvent(e, IDM_EDIT)) {Cmd_Edit(e); return true;}
		return false;
	}
};
