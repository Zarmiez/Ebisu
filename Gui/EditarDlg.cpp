#include "stdafx.h"  //_____________________________________________ EditarDlg.cpp
#include "EditarDlg.h"

void EditarDlg::Window_Open(Win::Event& e)
{
	
	
	//wchar_t  resultado;
	
	//Sys::Format(cmd, L"SELECT nombre name FROM cliente WHERE id_cliente=%d",client_id);
	//try
	//{
	//	//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
	//	conn.OpenSession(hWnd, CONNECTION_STRING);
	//	tbxNombre.Text=Sys::Convert::ToString(conn.ExecuteSelect(cmd,tbxNombre.Text));
	//}
	//catch (Sql::SqlException e)
	//{
	//	this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	//}
	
}



void EditarDlg::btOK_Click(Win::Event& e)
{
	Sql::SqlConnection conn;
	wstring cmd;
	wstring Nombre = tbxNombre.Text;
	wstring Direccion = tbxDireccion.Text;
	wstring TPC = tbxTPC.Text;
	int rows = 0;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		Sys::Format(cmd, L"UPDATE cliente SET nombre='%s',direccion='%s',tipo_de_cuenta='%s' WHERE  id_cliente=%d ",Nombre.c_str(),Direccion.c_str(), TPC.c_str(),client_id);

		rows = conn.ExecuteNonQuery(cmd);
		if (rows != 1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of updated rows", MB_OK | MB_ICONERROR);
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	this->EndDialog(FALSE);
}

void EditarDlg::btCancel_Click(Win::Event& e)
{
}

