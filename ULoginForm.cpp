#include <vcl.h>
#pragma hdrstop

#include "ULoginForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLoginForm *LoginForm;
//---------------------------------------------------------------------------
__fastcall TLoginForm::TLoginForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool TLoginForm::Execute(String &Username, String &Password)
{
    if (ShowModal() == mrOk)
    {
        Username = EditUsername->Text;
        Password = EditPassword->Text;
        return true;
    }
	return false;
}

void __fastcall TLoginForm::ButtonOKClick(TObject *Sender)
{
    ModalResult = mrOk;
}

void __fastcall TLoginForm::ButtonCancelClick(TObject *Sender)
{
    ModalResult = mrCancel;
}

