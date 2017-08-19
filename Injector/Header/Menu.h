#ifndef MENU
#define MENU

#include "MiscFunc.h"
#include <wx/wxprec.h>
#include <string>
#include <wx/filepicker.h>
#include <stdio.h>
enum{
	wxID_INJECT = wxID_HIGHEST + 1,
	wxID_SAVE_CONFIG = wxID_HIGHEST + 2,
	wxID_DLL_LOCATION = wxID_HIGHEST + 3,
	wxID_PROCESS_NAME = wxID_HIGHEST + 4,
	wxID_LOAD_CONFIG = wxID_HIGHEST + 5,
	wxID_REFRESH_PROC = wxID_HIGHEST + 6,
};
class Menu : public wxFrame{
	public:
		Menu();
		void SetProcess(std::string);
		void SetInjection(std::string);
		void Inject(wxCommandEvent& e);
		void SaveConfig(wxCommandEvent& e);
		void LoadConfig(wxCommandEvent& e);
		void Refresh(wxCommandEvent& e);
		std::string GetProcess();
		std::string GetInjection();
		DECLARE_EVENT_TABLE()
	private:
		std::string process;
		std::string injection;
};

#endif