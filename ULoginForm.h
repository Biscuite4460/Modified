//---------------------------------------------------------------------------
#ifndef ULoginFormH
#define ULoginFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TLoginForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TEdit *EditUsername;
    TEdit *EditPassword;
    TButton *ButtonOK;
    TButton *ButtonCancel;
    void __fastcall ButtonOKClick(TObject *Sender);
    void __fastcall ButtonCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TLoginForm(TComponent* Owner);
    bool Execute(String &Username, String &Password);
};
//---------------------------------------------------------------------------
extern PACKAGE TLoginForm *LoginForm;
//---------------------------------------------------------------------------
#endif

