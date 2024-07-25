//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include <Windows.h>
#include "UOraDBForms.h"
#include "ULoginForm.h"
#include "uMainForm.h"
#include "uDataMod.h"
#include "uDraftProposal.h"
#include "uLeads.h"
#include "uProposal.h"
USEFORM("UOraDBForms.cpp", InitializationDBForm);
USEFORM("uProposal.cpp", ProposalForm);
USEFORM("uMainForm.cpp", MainForm);
USEFORM("uDataMod.cpp", DM);
USEFORM("uDraftProposal.cpp", DraftProposalForm);
USEFORM("uLeads.cpp", LeadsForm);
USEFORM("ULoginForm.cpp", LoginForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try
    {
        Application->Initialize();
        TStyleManager::TrySetStyle("Windows10 Blue");
        Application->MainFormOnTaskBar = true;

        Application->CreateForm(__classid(TDM), &DM);
        Application->CreateForm(__classid(TInitializationDBForm), &InitializationDBForm);
		Application->CreateForm(__classid(TLeadsForm), &LeadsForm);
		Application->CreateForm(__classid(TDraftProposalForm), &DraftProposalForm);
		Application->CreateForm(__classid(TProposalForm), &ProposalForm);

		if (InitializationDBForm->ShowModal() == mrOk)
        {
            if (DM->FDBConfig.Type == dtOracle)
            {
                Application->CreateForm(__classid(TLoginForm), &LoginForm);
                if (LoginForm->ShowModal() == mrOk)
                {
					Application->CreateForm(__classid(TMainForm), &MainForm);
                    if (DM->FDConnection1->Connected) {
                        MainForm->Show();
						ForceForegroundWindow(MainForm->Handle);
                    } else {
						ShowMessage("Failed to connect to Oracle Database.");
                    }
                }
            }
            else if (DM->FDBConfig.Type == dtSQLite)
            {
				Application->CreateForm(__classid(TMainForm), &MainForm);

                MainForm->Show();
                ForceForegroundWindow(MainForm->Handle);
            }
        }

		Application->Run();
		ReportMemoryLeaksOnShutdown = true;
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    catch (const std::exception& stdEx)
    {
        ShowMessage("Standard exception: " + String(stdEx.what()));
    }
    catch (...)
    {
        ShowMessage("An unknown exception occurred.");
    }
    return 0;
}

//---------------------------------------------------------------------------

