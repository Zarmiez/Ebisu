#pragma once   //_____________________________________________ Deposito.h  
#include "resource.h"

class Deposito: public Web::Page
{
public:
	Deposito()
	{
	}
	~Deposito()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Service serviceDeposito;
protected:
	void InitializeGui()
	{
		this->ID=L"Deposito";
		this->Title=L"Deposito";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"Deposito.js";
		this->WebSiteIcon=L"WebSiteIcon.png";
		this->serviceDeposito.ID = L"serviceDeposito";
		this->serviceDeposito.Text = L"Deposito";
		this->AddChild(serviceDeposito);
	}
	//_________________________________________________
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
	}
};
