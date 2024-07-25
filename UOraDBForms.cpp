#include <vcl.h>
#pragma hdrstop

#include "UOraDBForms.h"
#include "ULoginForm.h"
#include "uDataMod.h"
#include "uMainForm.h"
#include "uDraftProposal.h"
#include "uProposal.h"
#include "uLeads.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <FireDAC.Phys.Oracle.hpp>
#define DB_FILENAME L"C:/Users/hamoz/Documents/w10crmdemocpp.sdb"
TInitializationDBForm *InitializationDBForm;
//---------------------------------------------------------------------------
__fastcall TInitializationDBForm::TInitializationDBForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void InitializeForms() {
    if (!MainForm)
        Application->CreateForm(__classid(TMainForm), &MainForm);
    MainForm->RefreshFormsPublic();

    if (!DraftProposalForm)
        Application->CreateForm(__classid(TDraftProposalForm), &DraftProposalForm);
    if (!ProposalForm)
        Application->CreateForm(__classid(TProposalForm), &ProposalForm);
	if (!LeadsForm)
        Application->CreateForm(__classid(TLeadsForm), &LeadsForm);
}

void TInitializationDBForm::InitializeDatabaseAndForms(TDatabaseType dbType, const UnicodeString &dbPathOrName,
								const UnicodeString &username, const UnicodeString &password,
								const UnicodeString &server) {
	DM->SetDatabaseConfig(dbType, dbPathOrName, username, password, server);
	DM->InitializeDatabase();

	if (!MainForm) {
		Application->CreateForm(__classid(TMainForm), &MainForm);
		MainForm->Show();
	} else {
		MainForm->BringToFront();
	}

	InitializeForms();  // Make sure this correctly initializes all needed forms
}

void __fastcall TInitializationDBForm::Button1Click(TObject *Sender) {
	Hide();
	InitializeDatabaseAndForms(dtSQLite, DB_FILENAME, L"", L"", L"");
}

void __fastcall TInitializationDBForm::Button2Click(TObject *Sender) {
    Hide();
    Application->CreateForm(__classid(TLoginForm), &LoginForm);
    String username, password;
    if (LoginForm && LoginForm->Execute(username, password)) {
        DM->SetDatabaseConfig(dtOracle, "OracleDB", username, password, "server");
        DM->InitializeDatabase();
        if (DM->FDConnection1->Connected) { // Check if Oracle database connection was successful
            if (!MainForm) {
                Application->CreateForm(__classid(TMainForm), &MainForm);
            }
            MainForm->Show();
        } else {
            ShowMessage("Failed to connect to Oracle Database.");
            Show(); // Re-show initialization form if connection fails
        }
    } else {
        Show();  // Show InitializationDBForm again if login fails
    }
}


//---------------------------------------------------------------------------

