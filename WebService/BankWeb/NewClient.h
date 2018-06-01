#pragma once   //_____________________________________________ NewClient.h  
#include "resource.h"

class NewClient: public Web::Page
{
public:
	NewClient()
	{
	}
	~NewClient()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Service serviceNewClient;
protected:
	void InitializeGui()
	{
		this->ID=L"NewClient";
		this->Title=L"NewClient";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"NewClient.js";
		this->WebSiteIcon=L"WebSiteIcon.png";
		this->serviceNewClient.ID=L"serviceNewClient";
		this->serviceNewClient.Text=L"NewClient";
		this->AddChild(serviceNewClient);
	}
	//_________________________________________________
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
	}
};
