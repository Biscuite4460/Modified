//---------------------------------------------------------------------------

#ifndef UOraDBFormsH
#define UOraDBFormsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "uDataMod.h"
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TInitializationDBForm : public TForm
{
__published:	// IDE-managed Components
	TRadioGroup *RadioGroup1;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label1;
	TLabel *Label2;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TInitializationDBForm(TComponent* Owner);
	void TInitializationDBForm::CloseAllSecondaryForms();
	void TInitializationDBForm::ReopenAllSecondaryForms();
	void InitializeDatabaseAndForms(TDatabaseType dbType, const UnicodeString &dbPathOrName,
								const UnicodeString &username, const UnicodeString &password,
								const UnicodeString &server);
};
//---------------------------------------------------------------------------
extern PACKAGE TInitializationDBForm *InitializationDBForm;
//---------------------------------------------------------------------------
#endif
