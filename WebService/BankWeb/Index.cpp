#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
{
}



void Index::btLogin_onclick(Web::HttpConnector& h)
{
	h.NavigateTo(L"Login");
}

void Index::btNuevosClientes_onclick(Web::HttpConnector& h)
{
	h.NavigateTo(L"NewClient");
}

void Index::btDeposito_onclick(Web::HttpConnector& h)
{
	h.NavigateTo(L"Deposito");
}

