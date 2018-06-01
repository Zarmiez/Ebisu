#include "stdafx.h"  //_____________________________________________ NewClient.cpp
#include "NewClient.h"

//#include "NewClient.h" //<< ADD THIS LINE IN THE BankWeb.cpp FILE

// http://localhost/BankWeb.dll?windowID=NewClient
void NewClient::Window_Open(Web::HttpConnector& h)
{
	serviceNewClient.soapEnvelope.ActionXmlns = L"http://www.MYDOMAIN.com/MyService";
	const wstring cajero_nombre = serviceNewClient.GetStringParameter(h, L"cajero_nombre");
	const wstring password = serviceNewClient.GetStringParameter(h, L"contraseña");
	const wstring nombre = serviceNewClient.GetStringParameter(h, L"Nombre");
	const wstring direccion = serviceNewClient.GetStringParameter(h, L"Direccion");
	//Faltan datos. ACT: YA NO

	serviceNewClient.Text = L"NewCLient";
	//serviceNewClient.soapEnvelope.AddParameter(L"Hasta qui todo bien", 0);

	list<Sys::Xml>::iterator response;
	wstring cmd;
	//Aqui dependiendo de la tabla
	Sys::Format(cmd, L"SELECT count(*) FROM cajero WHERE nombre_cajero= \'%s'\ AND contraseña= \'%s'\ ", cajero_nombre.c_str(), password.c_str());
	Sql::SqlConnection conn;
	int count = 0;
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
			Sys::Format(cmd, L"INSERT INTO cliente(nombre,direccion) VALUES(\'%s\',\'%s\')", nombre.c_str(),direccion.c_str());
			//Sys::Format(cmd, L"INSERT INTO contact(userx_id,contact_id,namee) VALUES(%d,%d,\'%s\') ", user_id, contact_id, Namee.c_str());
			conn.ExecuteSelect(cmd, 100, serviceNewClient.soapEnvelope);
			serviceNewClient.soapEnvelope.AddParameter(L"ERROR", 0);


		}
		else {
			serviceNewClient.soapEnvelope.AddParameter(L"ERROR", 1);
		}
			//conn.ExecuteNonQuery(cmd);
	}catch (Sql::SqlException e)
		{
			this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		}
	
}




