#pragma once   //_____________________________________________ Index.h  
#include "resource.h"

class Index: public Web::Page
{
public:
	Index()
	{
	}
	~Index()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Button btLogin;
	Web::Button btNuevosClientes;
	Web::Button btDeposito;
protected:
	void InitializeGui()
	{
		this->ID=L"Index";
		this->Title=L"Index";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"Index.js";
		this->WebSiteIcon=L"WebSiteIcon.png";
		this->btLogin.ID=L"btLogin";
		this->btNuevosClientes.ID=L"btNuevosClientes";
		this->btDeposito.ID=L"btDeposito";
		this->btLogin.Text=L"Login";
		this->btNuevosClientes.Text=L"NuevosClientes";
		this->btDeposito.Text=L"Deposito";
		this->AddChild(btLogin);
		this->AddChild(btDeposito);
		this->AddChild(btNuevosClientes);
	}
	//_________________________________________________
	void btLogin_onclick(Web::HttpConnector& h);
	void btNuevosClientes_onclick(Web::HttpConnector& h);
	void btDeposito_onclick(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (btLogin.IsEvent(h, LEX_HTML_ONCLICK)) {btLogin_onclick(h);}
		if (btNuevosClientes.IsEvent(h, LEX_HTML_ONCLICK)) {btNuevosClientes_onclick(h);}
		if (btDeposito.IsEvent(h, LEX_HTML_ONCLICK)) {btDeposito_onclick(h);}
	}
};
