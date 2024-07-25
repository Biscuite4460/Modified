//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "UOraDBForms.h"
USEFORM("UOraDBForms.cpp", Form1);
USEFORM("uProposal.cpp", ProposalForm);
USEFORM("uMainForm.cpp", MainForm);
USEFORM("uDataMod.cpp", DM); /* TDataModule: File Type */
USEFORM("uDraftProposal.cpp", DraftProposalForm);
USEFORM("uLeads.cpp", LeadsForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try
    {
        Application->Initialize();
        TStyleManager::TrySetStyle("Windows10 Blue");
        Application->MainFormOnTaskBar = true;

        Application->CreateForm(__classid(TDM), &DM);
        Application->CreateForm(__classid(TForm1), &Form1);
		Form1->ShowModal();

        if (Form1->ModalResult == mrOk) {
            Application->CreateForm(__classid(TMainForm), &MainForm);
            // Application->MainForm is set automatically if MainForm is created first
            Application->Run();
        }

        ReportMemoryLeaksOnShutdown = true;
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    catch (...)
    {
        try
        {
            throw Exception("");
        }
        catch (Exception &exception)
        {
            Application->ShowException(&exception);
        }
    }
    return 0;
}




//---------------------------------------------------------------------------
