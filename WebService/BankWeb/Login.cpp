#include "stdafx.h"  //_____________________________________________ Login.cpp
#include "Login.h"

//#include "Login.h" //<< ADD THIS LINE IN THE BankWeb.cpp FILE

// http://localhost/BankWeb.dll?windowID=Login
void Login::Window_Open(Web::HttpConnector& h)
{
	serviceLogin.soapEnvelope.ActionXmlns = L"http://www.MYDOMAIN.com/MyService";
	const wstring cajero_nombre = serviceLogin.GetStringParameter(h, L"Nombre_Cajero");
	const wstring password= serviceLogin.GetStringParameter(h, L"Contraseña");
	serviceLogin.Text = L"Login";
	//serviceLogin.soapEnvelope.AddParameter(L"result", x+y);
	list<Sys::Xml>::iterator response;
	wstring cmd;
	//Aqui dependiendo de la tabla
	Sys::Format(cmd, L"SELECT count(*) FROM cajero WHERE nombre_cajero= \'%s'\ AND contraseña= \'%s'\ ", cajero_nombre.c_str(), password.c_str());
	Sql::SqlConnection conn;
	int count = 0;
	int es_admin = 0;
	try
	{

		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		//conn.ExecuteSelect(L"SELECT message_id, submited_date, sender_id, recipient_id, content, is_read,is_sent FROM messagex", 100, serviceMessageList.soapEnvelope);
		count = conn.GetInt(cmd);
		if (count == 1)
		{

			//Sys::Format(cmd, L"SELECT count(*) FROM userx WHERE userx_id= %d  ", contact_id);
			count = conn.GetInt(cmd);
			Sys::Format(cmd, L"SELECT es_adm FROM cajero WHERE nombre_cajero= \'%s'\ AND contraseña= \'%s'\ ", cajero_nombre.c_str(), password.c_str());
			//Sys::Format(cmd, L"INSERT INTO contact(userx_id,contact_id,namee) VALUES(%d,%d,\'%s\') ", user_id, contact_id, Namee.c_str());
			es_admin = conn.GetInt(cmd);
			serviceLogin.soapEnvelope.AddParameter(L"es_admin", es_admin);
			serviceLogin.soapEnvelope.AddParameter(L"ERROR", 0);


		}
		else {
			serviceLogin.soapEnvelope.AddParameter(L"es_admin", -1);
			serviceLogin.soapEnvelope.AddParameter(L"ERROR", 1);
		}
		//conn.ExecuteNonQuery(cmd);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}

}





