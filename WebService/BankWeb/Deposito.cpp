#include "stdafx.h"  //_____________________________________________ Deposito.cpp
#include "Deposito.h"

//#include "Deposito.h" //<< ADD THIS LINE IN THE BankWeb.cpp FILE

// http://localhost/BankWeb.dll?windowID=Deposito
void Deposito::Window_Open(Web::HttpConnector& h)
{
	serviceDeposito.soapEnvelope.ActionXmlns = L"http://www.MYDOMAIN.com/MyService";
	const wstring cajero_nombre = serviceDeposito.GetStringParameter(h, L"Nombre_Cajero");
	const wstring password = serviceDeposito.GetStringParameter(h, L"Contraseña_cajero");
	const int id_destinatario = serviceDeposito.GetIntParameter(h, L"id_Destinatario");
	const int id_cuenta = serviceDeposito.GetIntParameter(h, L"id_cuenta");
	const int passcuenta = serviceDeposito.GetIntParameter(h, L"Pass Cuenta");
	const double Cantidad= serviceDeposito.GetDoubleParameter(h, L"Cantidad");

	serviceDeposito.Text = L"Deposito";

	list<Sys::Xml>::iterator response;
	wstring cmd;
	//Aqui dependiendo de la tabla
	Sys::Format(cmd, L"SELECT count(*) FROM cajero WHERE nombre_cajero= \'%s'\ AND contraseña= \'%s'\ ", cajero_nombre.c_str(), password.c_str());
	Sql::SqlConnection conn;
	int count = 0;
	int id_cajero = 0;
	double Balance = 0.0;
	double NewBalance = 0.0;
	try
	{

		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		//conn.ExecuteSelect(L"SELECT message_id, submited_date, sender_id, recipient_id, content, is_read,is_sent FROM messagex", 100, serviceMessageList.soapEnvelope);
		count = conn.GetInt(cmd);
		if (count == 1)
		{
			//Existe el cajero, se procede

			count = conn.GetInt(cmd);
			Sys::Format(cmd, L"SELECT count(*) FROM cuenta WHERE id_cuenta= %d ", id_destinatario);
			//Sys::Format(cmd, L"INSERT INTO contact(userx_id,contact_id,namee) VALUES(%d,%d,\'%s\') ", user_id, contact_id, Namee.c_str());
			count = conn.GetInt(cmd);
			if (count == 1) {
				//Existe el cliente, se procede a hacer el deposito
				if (id_cuenta == 1)
				{
					//Si el cliente es un cliente sin cuenta.
					if (id_destinatario != 1)
					{
						Sys::Format(cmd, L"SELECT balance FROM cuenta WHERE id_cuenta= %d ", id_destinatario);
						Balance = conn.GetDouble(cmd);
						Balance += Cantidad;
						Sys::Format(cmd, L"UPDATE cuenta SET balance=%f WHERE id_cuenta=%d ", Balance, id_destinatario);
						conn.ExecuteSelect(cmd, 100, serviceDeposito.soapEnvelope);
					
						//Se agrega la transaccion
						
						Sys::Format(cmd, L"SELECT id_cajero FROM cajero WHERE nombre_cajero= \'%s'\ AND contraseña= \'%s'\ ", cajero_nombre.c_str(), password.c_str());
						id_cajero = conn.GetInt(cmd);
						Sys::Format(cmd, L"INSERT INTO transaccion(id_cuenta,id_destinatario, id_cajero, movimientos, fecha, monto) VALUES (%d,%d,%d,'D','20180525',%f)", id_destinatario, id_cuenta,id_cajero, Cantidad);
						conn.ExecuteSelect(cmd,100,serviceDeposito.soapEnvelope);

						

						serviceDeposito.soapEnvelope.AddParameter(L"ERROR", 0);//Ningun Error
					}
					else {
						serviceDeposito.soapEnvelope.AddParameter(L"ERROR", 2);//Error, No existe cuenta
					}
					
				}
				else {
					//Si el cliente es un cliente con cuenta.
					if (id_destinatario != 1)
					{
						Sys::Format(cmd, L"SELECT balance FROM cuenta WHERE id_cuenta=%d", id_cuenta);
						Balance = conn.GetDouble(cmd);
						NewBalance = Balance;
						if (Balance >= Cantidad)//Se verifica que tenga saldo suficiente en su cuenta.
						{

							Sys::Format(cmd, L"SELECT balance FROM cuenta WHERE id_cuenta= %d ", id_destinatario);
							Balance = conn.GetDouble(cmd);
							Balance += Cantidad;
							Sys::Format(cmd, L"UPDATE cuenta SET balance=%f WHERE id_cuenta=%d ", Balance, id_destinatario);
							conn.ExecuteSelect(cmd, 100, serviceDeposito.soapEnvelope);//Se hace el deposito al destinatario.

							NewBalance = NewBalance - Cantidad;
							Sys::Format(cmd, L"UPDATE cuenta SET balance=%f WHERE id_cuenta=%d ", NewBalance, id_cuenta);
							conn.ExecuteSelect(cmd, 100, serviceDeposito.soapEnvelope);//Se elimina la cantidad del cliente.

																					   //Se registra la transaccion/.

							Sys::Format(cmd, L"SELECT id_cajero FROM cajero WHERE nombre_cajero= \'%s'\ AND contraseña= \'%s'\ ", cajero_nombre.c_str(), password.c_str());
							id_cajero = conn.GetInt(cmd);
							Sys::Format(cmd, L"INSERT INTO transaccion(id_cuenta,id_destinatario, id_cajero, movimientos, fecha, monto) VALUES (%d,%d,%d,'D','20180525',%f)", id_destinatario, id_cuenta, id_cajero, Cantidad);
							conn.ExecuteSelect(cmd, 100, serviceDeposito.soapEnvelope);
							Sys::Format(cmd, L"INSERT INTO transaccion(id_cuenta,id_destinatario, id_cajero, movimientos, fecha, monto) VALUES (%d,%d,%d,'R','20180525',%f)", id_cuenta, id_destinatario, id_cajero, Cantidad);
							conn.ExecuteSelect(cmd);



							serviceDeposito.soapEnvelope.AddParameter(L"ERROR", 0);//Ningun Error
						}
						else {
							serviceDeposito.soapEnvelope.AddParameter(L"ERROR", 3);//Error, No hay saldo suficiente.
						}
					}
					else {
						serviceDeposito.soapEnvelope.AddParameter(L"ERROR", 2);//Error, No existe cuenta
					}
					
				}
				


		//		Sys::Format(cmd, L"INSERT INTO ");
				
			}
			else {
				serviceDeposito.soapEnvelope.AddParameter(L"ERROR", 2);//Error, No existe cuenta
			}
		}
		else {
			serviceDeposito.soapEnvelope.AddParameter(L"ERROR", 1);//Error, No existe cajero
		}
		//conn.ExecuteNonQuery(cmd);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}

