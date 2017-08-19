#include "Menu.h"

Menu::Menu() : wxFrame(NULL, wxID_ANY, "Injector v0.5"){
	std::vector<std::wstring> proc_list;
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL | wxHORIZONTAL | wxEXPAND);
	wxPanel* main_panel = new wxPanel(this);
	/*
	wxIcon icon;
	wxBitmap bitmap;
	bitmap.LoadFile("needle.ico", wxBITMAP_TYPE_ICO);
	icon.CopyFromBitmap(bitmap);
	SetIcon(wxIcon(icon));*/

	sizer->AddSpacer(10);
	wxFilePickerCtrl* dll_browse = new wxFilePickerCtrl(main_panel, wxID_DLL_LOCATION);
	wxButton* inject = new wxButton(main_panel, wxID_INJECT, _T("Inject"), wxDefaultPosition, wxDefaultSize, 0);
	wxButton* save_config = new wxButton(main_panel, wxID_SAVE_CONFIG, _T("Save Config"), wxDefaultPosition, wxDefaultSize, 0);
	wxButton* load_config = new wxButton(main_panel, wxID_LOAD_CONFIG, _T("Load Config"), wxDefaultPosition, wxDefaultSize, 0);
	wxButton* refresh_button = new wxButton(main_panel, wxID_REFRESH_PROC, _T("Refresh Processor List"), wxDefaultPosition, wxDefaultSize, 0);
	
	// Create dropdown lists for processes
	MiscFunc::GetProcessNames(&proc_list);
	wxChoice* process_dropdown = new wxChoice(main_panel, wxID_PROCESS_NAME);
	for(unsigned int x = 0; x < proc_list.size(); x++){
		process_dropdown->Append(proc_list.at(x));
	}

	// Store everything in sizer for formatting
	sizer->Add(dll_browse, wxSizerFlags().Expand());
	sizer->Add(0,10, wxSizerFlags().Expand());
	sizer->Add(process_dropdown, wxSizerFlags().Expand());
	sizer->Add(0,10, wxSizerFlags().Expand());
	sizer->Add(inject, wxSizerFlags().Centre());
	sizer->Add(0,10, wxSizerFlags().Expand());
	sizer->Add(save_config, wxSizerFlags().Centre());
	sizer->Add(0,10, wxSizerFlags().Expand());
	sizer->Add(load_config, wxSizerFlags().Centre());
	sizer->Add(0,10, wxSizerFlags().Expand());
	sizer->Add(refresh_button, wxSizerFlags().Centre());	
	main_panel->SetSizer(sizer);
}

void Menu::SetProcess(std::string process){
	this->process = process;
}

void Menu::SetInjection(std::string injection){
	this->injection = injection;
}

std::string Menu::GetInjection(){
	return this->injection;
}

std::string Menu::GetProcess(){
	return this->process;
}

void Menu::Inject(wxCommandEvent& e){
	int choice = ((wxChoice*) (this->FindWindow(wxID_PROCESS_NAME)))->GetCurrentSelection();
	wxString process_name = ((wxChoice*) (this->FindWindow(wxID_PROCESS_NAME)))->GetString(choice);
	wxString path = ((wxFilePickerCtrl*) (this->FindWindow(wxID_DLL_LOCATION)))->GetPath();
	if(MiscFunc::Inject(path.ToStdString().c_str(), process_name.ToStdString().c_str())) wxLogMessage("Successful Injection");
	else wxLogMessage("Injection Failure");
}

void Menu::SaveConfig(wxCommandEvent& e){
	FILE* config;
	config = fopen("config", "w");
	wxString content = ((wxTextCtrl*) (this->FindWindow(wxID_PROCESS_NAME)))->GetLineText(1);
	wxString path = ((wxFilePickerCtrl*) (this->FindWindow(wxID_DLL_LOCATION)))->GetPath();
	int string_length = (content.ToStdString().length() + path.ToStdString().length() + 1);
	char* config_data = (char*) malloc(sizeof(char) * string_length);
	sprintf(config_data, "%s\n%s", path.ToStdString().c_str(), content.ToStdString().c_str());
	fwrite(config_data, sizeof(char), string_length, config);
	fclose(config);
	free(config_data);
}

void Menu::LoadConfig(wxCommandEvent& e){
	FILE* config;
	config = fopen("config", "r");
	if(config == NULL) wxLogMessage("No config to load");	
	else{
		unsigned int initial_size = 1024;
		char* config_data = (char*) calloc(initial_size, sizeof(char));
		char tmp;
		int counter = 0;
		tmp = fgetc(config);
		while(tmp != EOF){
			if(tmp == '\n'){
				((wxFilePickerCtrl*) (this->FindWindow(wxID_DLL_LOCATION)))->SetPath(config_data);
				memset(config_data, 0x0, initial_size);
				counter = 0;
			}
			else{
				config_data[counter] = tmp;
				counter++;
			}
			tmp = fgetc(config);
		}
		((wxTextCtrl*) (this->FindWindow(wxID_PROCESS_NAME)))->SetValue(config_data);
		wxLogMessage("Config Loaded");
		fclose(config);
		free(config_data);
	}
}

void Menu::Refresh(wxCommandEvent& e){
	((wxChoice*) (this->FindWindow(wxID_PROCESS_NAME)))->Clear();
	std::vector<std::wstring> proc_list;
	MiscFunc::GetProcessNames(&proc_list);
	for(unsigned int x = 0; x < proc_list.size(); x++) ((wxChoice*) (this->FindWindow(wxID_PROCESS_NAME)))->Append(proc_list.at(x));
}