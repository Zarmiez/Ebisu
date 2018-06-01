#include "stdafx.h"  //________________________________________ Clientes_cajero.cpp
#include "Clientes_cajero.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	Clientes_cajero app;
	return app.BeginDialog(IDI_Clientes_cajero, hInstance);
}

void Clientes_cajero::Window_Open(Win::Event& e)
{
	//________________________________________________________ toolb1
	TBBUTTON tbButton[3];//<< EDIT HERE THE NUMBER OF BUTTONS

	int iconSizes[] ={16, 20, 24, 32, 40, 48, 64};
	const int pixelsIconSize = Sys::Metrics::GetBestIconSize(iconSizes, 7, Sys::Convert::CentimetersToScreenPixels(0.42333));
	const int pixelsButtonSize = pixelsIconSize + Sys::Convert::CentimetersToScreenPixels(0.1);
	toolb1.imageList.Create(pixelsIconSize, pixelsIconSize, 3);//<< EDIT HERE THE NUMBER OF IMAGES
	toolb1.imageList.AddIcon(this->hInstance, IDI_ADD);
	toolb1.imageList.AddIcon(this->hInstance, IDI_DELETE);
	toolb1.imageList.AddIcon(this->hInstance, IDI_EDIT);
	/*toolb1.imageList.AddIcon(this->hInstance, IDI_EDIT);
	toolb1.imageList.AddIcon(this->hInstance, IDI_DELETE);*/
	
	toolb1.SendMessage(TB_BUTTONSTRUCTSIZE, (WPARAM)(int)sizeof(TBBUTTON), 0); 
	toolb1.SetImageList(toolb1.imageList);
	//_____________________________________
	tbButton[0].iBitmap=MAKELONG(0, 0); //<< IMAGE INDEX
	tbButton[0].idCommand=IDM_ADD;
	tbButton[0].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[0].fsStyle=BTNS_BUTTON;
	tbButton[0].dwData=0L; 
	tbButton[0].iString= (LONG_PTR)L"Agregar";

	tbButton[1].iBitmap = MAKELONG(1, 0); //<< IMAGE INDEX
	tbButton[1].idCommand = IDM_DELETE;
	tbButton[1].fsState = TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[1].fsStyle = BTNS_BUTTON;
	tbButton[1].dwData = 0L;
	tbButton[1].iString = (LONG_PTR)L"Eliminar";

	tbButton[2].iBitmap = MAKELONG(2, 0); //<< IMAGE INDEX
	tbButton[2].idCommand = IDM_EDIT;
	tbButton[2].fsState = TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[2].fsStyle = BTNS_BUTTON;
	tbButton[2].dwData = 0L;
	tbButton[2].iString = (LONG_PTR)L"Editar";
	//________________________ A separator
	
	toolb1.SetBitmapSize(pixelsIconSize, pixelsIconSize);
	toolb1.SetButtonSize(pixelsButtonSize, pixelsButtonSize);
	toolb1.AddButtons(tbButton, 3);// << EDIT HERE THE NUMBER OF BUTTONS
	toolb1.SendMessage(TB_AUTOSIZE, 0, 0);
	toolb1.SetMaxTextRows(0);// EDIT HERE TO DISPLAY THE BUTTON TEXT
	toolb1.Show(SW_SHOWNORMAL);
//	toolb1.ResizeToFit();

	this->Text = L"CLientes";
	
	lvClientes.Cols.Add(0, LVCFMT_LEFT, 200, L"Nombre");
	lvClientes.Cols.Add(1, LVCFMT_LEFT, 200, L"Direccion");
	lvClientes.Cols.Add(1, LVCFMT_LEFT, 200, L"Tipo_de_cuenta");

	//________________________________________________________ lvSolicitudes
	Sql::SqlConnection conn;
	wstring cmd;
	Sys::Format(cmd, L"SELECT id_cliente,nombre,direccion,tipo_de_cuenta name FROM cliente ");
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(cmd, 100, lvClientes);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	//________________________________________________________ lvClientes
	
}

void Clientes_cajero::pintar()
{
	lvClientes.Delete();
	lvClientes.Cols.Add(0, LVCFMT_LEFT, 200, L"Nombre");
	lvClientes.Cols.Add(1, LVCFMT_LEFT, 200, L"Direccion");
	lvClientes.Cols.Add(1, LVCFMT_LEFT, 200, L"Tipo_de_cuenta");

	//________________________________________________________ lvSolicitudes
	Sql::SqlConnection conn;
	wstring cmd;
	Sys::Format(cmd, L"SELECT id_cliente,nombre,direccion,tipo_de_cuenta name FROM cliente");
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(cmd, 100, lvClientes);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	//________________________________________________________ toolbMain

	//	toolbMain.ResizeToFit();

}

void Clientes_cajero::Cmd_Add(Win::Event& e)
{
    AgregarDlg dlg;
	dlg.BeginDialog(hWnd);
	pintar();
}

void Clientes_cajero::Cmd_Delete(Win::Event& e)
{
	if (this->MessageBox(L"Esta Seguro Que desea Eliminar al cliente?", L"Cliente", MB_YESNO | MB_ICONQUESTION) != IDYES)return;
	LPARAM cliente_id;
	if (lvClientes.GetSelectedData(cliente_id) == false)return; Sql::SqlConnection conn;
	wstring cmd;

	int rows = 0;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		Sys::Format(cmd, L"DELETE FROM cliente WHERE id_cliente=%d", cliente_id);
		rows = conn.ExecuteNonQuery(cmd);
		if (rows != 1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of deleted rows", MB_OK | MB_ICONERROR);
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	pintar();
}

void Clientes_cajero::Cmd_Edit(Win::Event& e)
{
	
	EditarDlg dlg;
    client_id;
	if (lvClientes.GetSelectedData(client_id) == false)return;
	dlg.client_id = client_id;
	dlg.BeginDialog(hWnd);
	pintar();
}

