#include "stdafx.h"  //_____________________________________________ AgregarDlg.cpp
#include "AgregarDlg.h"

void AgregarDlg::Window_Open(Win::Event& e)
{
	
}


void AgregarDlg::btOK_Click(Win::Event& e)
{
	Sql::SqlConnection conn;
	int rows = 0;
	wstring nombre = tbxNombre.Text;
	wstring direccion = tbxDireccion.Text;
	wstring tipo_de_cuenta = tbxTPC.Text;

	wstring cmd;
	Sys::Format(cmd, L"INSERT INTO cliente(nombre,direccion,tipo_de_cuenta)VALUES('%s','%s','%s')", nombre.c_str(), direccion.c_str(), tipo_de_cuenta.c_str());
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		rows = conn.ExecuteNonQuery(cmd);
		if (rows != 1)
		{
			this->MessageBoxW(Sys::Convert::ToString(rows), L"Error-Inserted rows", MB_OK | MB_ICONERROR);
		}
		this->EndDialog(TRUE);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}

}

void AgregarDlg::btCancelar_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}

