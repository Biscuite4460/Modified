#include <vcl.h>
#pragma hdrstop

#include "UOraDBForms.h"
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
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
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

void __fastcall TForm1::InitializeDatabaseAndForms(TDatabaseType dbType, const UnicodeString &dbPathOrName,
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

    InitializeForms();
}

void __fastcall TForm1::Button1Click(TObject *Sender) {
	Hide();
	InitializeDatabaseAndForms(dtSQLite, DB_FILENAME, L"", L"", L"");
}

void __fastcall TForm1::Button2Click(TObject *Sender) {
    Hide();
	InitializeDatabaseAndForms(dtOracle, "OracleDB", "username", "password", "server");
}

//---------------------------------------------------------------------------

