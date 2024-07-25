//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("uMainForm.cpp", MainForm);
USEFORM("uProposal.cpp", ProposalForm);
USEFORM("uDataMod.cpp", DM); /* TDataModule: File Type */
USEFORM("uDraftProposal.cpp", DraftProposalForm);
USEFORM("uLeads.cpp", LeadsForm);
USEFORM("Unit1.cpp", Form1);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try
    {
        Application->Initialize();
        TStyleManager::TrySetStyle("Windows10 Blue");
        Application->MainFormOnTaskBar = true;

        Application->CreateForm(__classid(TDM), &DM); // Create the data module

        // Initially create and show Form1
        Application->CreateForm(__classid(TForm1), &Form1);
        Form1->ShowModal(); // Use ShowModal to wait until the form is closed

        // After Form1 is closed, create and show MainForm
        if (Form1->ModalResult == mrOk) { // Check if Form1 closed with an 'OK' result
            Application->CreateForm(__classid(TMainForm), &MainForm);
            Application->MainForm = MainForm; // Set MainForm as the main application form
            Application->Run(); // Start the main event loop
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
