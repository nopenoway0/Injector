// Injector.cpp : Defines the entry point for the console application.
//

#include <wx/wxprec.h>
#include "Menu.h"
#include <wx/icon.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif


class Injector : public wxApp{
	public:
		virtual bool OnInit(){
			wxInitAllImageHandlers();
			Menu* main_menu = new Menu();
			main_menu->Show(true);
			return true;
		}
};

wxIMPLEMENT_APP(Injector);
BEGIN_EVENT_TABLE(Menu, wxFrame)
	EVT_BUTTON(wxID_INJECT,  Menu::Inject)
	EVT_BUTTON(wxID_SAVE_CONFIG, Menu::SaveConfig)
	EVT_BUTTON(wxID_LOAD_CONFIG, Menu::LoadConfig)
END_EVENT_TABLE()