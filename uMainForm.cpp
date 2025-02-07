//---------------------------------------------------------------------------

#include <vcl.h>
#include <frxClass.hpp>
#include <frxExportPDF.hpp>
#pragma hdrstop

#include <Windows.h>
#include "UOraDBForms.h"
#include "uMainForm.h"
#include "uDataMod.h"
#include "uLeads.h"
#include "uDraftProposal.h"
#include "uProposal.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frCoreClasses"
#pragma link "frxClass"
#pragma link "frxExportBaseDialog"
#pragma link "frxExportPDF"
#pragma link "frxExportBaseDialog"
#pragma link "frxExportPDF"
#pragma resource "*.dfm"

TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner) {
	SetupPanelClickHandlers();
	LoadDataIntoGrid();
	FDetailData.clear();
	CaptureOriginalData();
	//LoadMenuFromDatabase();
	//DM->SetDatabaseConfig(TDatabaseType::Oracle, "YourOracleDB", "username", "password", "server");
	DM->InitializeDatabase();
	DM->ReloadAllQueries();
	DM->ReloadAccountQueries();
	DM->ReloadProposalsQuaeries();
//	CurrentUsername = GetCurrentUsername();
	DM->ReloadLeadsQuery();

	//LoadMenuIntoListView();

	//ImageList1->Width = 1;   // Width is not important for item height
	//ImageList1->Height = 40; // Set the height you want for the list items
	//ListView1->SmallImages = ImageList1;

	LoadMenuIntoListBox();
	ListBox1->Style = lbOwnerDrawFixed;
	ListBox1->ItemHeight = 40;
	}

 void ForceForegroundWindow(HWND hwnd) {
	DWORD foregroundThreadID = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
	DWORD currentThreadID = GetCurrentThreadId();

	// Attach foreground window thread to current thread
	AttachThreadInput(foregroundThreadID, currentThreadID, true);

	// Bring window to foreground
	BringWindowToTop(hwnd);
	ShowWindow(hwnd, SW_NORMAL);

	// Detach the attached thread
	AttachThreadInput(foregroundThreadID, currentThreadID, false);
}

//String TMainForm::GetCurrentUsername()
//{
//	String currentUsername = "";
//
//	if (DM->UsersFDMemTable && DM->UsersFDMemTable->Active) {
//		TField *usernameField = DM->UsersFDMemTable->FindField("Username");
//		if (usernameField) {
//			if (!DM->UsersFDMemTable->IsEmpty()) {
//				currentUsername = usernameField->AsString;
//			} else {
//				ShowMessage("Users table is empty!");
//			}
//		} else {
//			ShowMessage("Username field not found in Users table!");
//		}
//	} else {
//		ShowMessage("Users table is not active!");
//	}
//
//	if (!currentUsername.IsEmpty()) {
//		//DM->ReloadLeadsQuery(currentUsername);
//	} else {
//		ShowMessage("Failed to retrieve current username!");
//	}
//
//	return currentUsername;
//}

/*void __fastcall TMainForm::LoadMenuIntoListView() {
	ListView1->SmallImages = ImageList1;

	ListView1->Items->BeginUpdate();
	try {
		ListView1->Items->Clear();
		DM->FDQuery1->SQL->Text = "SELECT * FROM MenuItems ORDER BY ParentID, SortOrder";
		DM->FDQuery1->Open();

		while (!DM->FDQuery1->Eof) {
			TListItem *Item = ListView1->Items->Add();
            Item->Caption = DM->FDQuery1->FieldByName("Name")->AsString;

			Item->ImageIndex = DetermineImageIndexForItem(Item->Caption);

			DM->FDQuery1->Next();
		}
	} catch (const Exception &E) {
		ShowMessage("Error loading menu from database: " + E.Message);
	}
	ListView1->Items->EndUpdate();

	SetupListViewColumns();
} */

__fastcall TMainForm::~TMainForm() {
	CloseAllSecondaryForms();
}

void TMainForm::LoadMenuIntoListBox() {
	ListBox1->Items->BeginUpdate();
	try {
		ListBox1->Items->Clear();
		DM->FDQuery1->SQL->Text = "SELECT Name FROM MenuItems ORDER BY SortOrder";
		DM->FDQuery1->Open();

		while (!DM->FDQuery1->Eof) {
			String itemName = DM->FDQuery1->FieldByName("Name")->AsString;
			int imageIndex = DetermineImageIndexForItem(itemName);
			ListBox1->Items->AddObject(itemName, (TObject*)(intptr_t)imageIndex);

			DM->FDQuery1->Next();
		}
	} catch (const Exception &E) {
		ShowMessage("Error loading menu from database: " + E.Message);
	}
	ListBox1->Items->EndUpdate();
}

int TMainForm::DetermineImageIndexForItem(const String& itemName) {
	if (itemName == "Dashboard") {
		return 3;
	} else if (itemName == "Accounts") {
		return 1;
	} else if (itemName == "Leads") {
		return 2;
	} else if (itemName == "Sales") {
		return 0;
	} else if (itemName == "Marketing" ) {
		return 4;
	} else if (itemName == "Calendar" ) {
		return 5;
	} else if (itemName == "Users" ) {
		return 6;
	}  else if (itemName == "Reports" ) {
		return 7;
	}
	return -1;
}

void __fastcall TMainForm::ListBox1DrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State) {
	TListBox *ListBox = static_cast<TListBox*>(Control);
	TCanvas *Canvas = ListBox->Canvas;

	Canvas->Font->Size = 14;

	Canvas->FillRect(Rect);

	if(Index < VirtualImageList1->ImageCollection->Count) {
		VirtualImageList1->Draw(Canvas, Rect.Left, Rect.Top, Index, true);
	}

	Rect.Left += VirtualImageList1->Width + 4;

	Canvas->TextOut(Rect.Left, Rect.Top + (Rect.Height() - Canvas->TextHeight(ListBox->Items->Strings[Index])) / 2, ListBox->Items->Strings[Index]);

	if (State.Contains(odSelected)) {

	}
}

void __fastcall TMainForm::ListView1SelectItem(TObject *Sender, TListItem *Item, bool Selected) {
	if (Selected && Item != nullptr) {
		for (int i = 0; i < PageControl->PageCount; i++) {
			if (PageControl->Pages[i]->Caption == Item->Caption) {
				PageControl->ActivePageIndex = i;
				break;
			}
		}
	}
}

int TMainForm::GetRecordCount(String status) {
    TFDQuery* query = new TFDQuery(nullptr);
    query->Connection = DM->FDConnection1;
    try {
		query->SQL->Text = "SELECT COUNT(*) AS Count FROM Leads WHERE Status = :Status";
		query->ParamByName("Status")->AsString = status;
        query->Open();
		int count = query->FieldByName("Count")->AsInteger;
        query->Close();
        delete query;
        return count;
	} catch (...) {
		delete query;
		throw;
	}
}

void TMainForm::UpdatePanelVisibility() {
	NewLeadsPanel->Visible = GetRecordCount("New") > 0;
	ActiveLeadsPanel->Visible = GetRecordCount("Active") > 0;
	ProposalSentPanel->Visible = GetRecordCount("Proposal Sent") > 0;

	NewLeadsPanel->Invalidate();
	ActiveLeadsPanel->Invalidate();
	ProposalSentPanel->Invalidate();
} 

void __fastcall TMainForm::RefreshGrids()
{
    LeadsBindClosedSourceDB->DataSet->Refresh();
    LeadsBindActiveSourceDB->DataSet->Refresh();
    LeadsBindNewSourceDB->DataSet->Refresh();
    LeadsBindProposalSentSourceDB->DataSet->Refresh();
    UpdatePanelVisibility();
}

void __fastcall TMainForm::RemoveAcctButtonClick( TObject* Sender )
{
  AcctBindSourceDB->DataSet->Delete();
}


void __fastcall TMainForm::RemoveUserButtonClick( TObject* Sender )
{
  UsersBindSourceDB->DataSet->Delete();
}


void __fastcall TMainForm::AcctSearchBoxKeyPress(TObject *Sender, System::WideChar &Key)
{
  DM->SearchAccounts( AcctSearchBox->Text );
}


void __fastcall TMainForm::CalendarView1DrawDayItem(TObject *Sender, TDrawViewInfoParams *DrawParams,
		  TCellItemViewInfo *CalendarViewViewInfo)
{
int LCurrentDay = DayOfWeek( CalendarViewViewInfo->Date );
  if ( LCurrentDay == 1 || LCurrentDay == 7 )
  {
	DrawParams->Font->Style = TFontStyles() << fsBold;
  }
}


void __fastcall TMainForm::CancelProposalButtonClick( TObject* Sender )
{
  if ( ProposalBindSourceDB->DataSet->RecordCount > 0 )
  {
	DM->UpdateProposalStatus( ProposalBindSourceDB->DataSet->FieldByName( L"LeadId" )->AsInteger, L"Canceled" );
  }
}


void __fastcall TMainForm::PageControlChange(TObject* Sender)
{
  if (PageControl->ActivePageIndex == 0)
  {
	try
	{
	  if (!DM->FDQueryNewTotal->Active)
		DM->FDQueryNewTotal->Open();
	  DM->FDQueryNewTotal->Refresh();
	}
	catch (Exception &E)
	{
	  ShowMessage("An error occurred while refreshing FDQueryNewTotal: " + E.Message);
	}

	try
	{
	  if (!DM->FDQueryActiveTotal->Active)
		DM->FDQueryActiveTotal->Open();
	  DM->FDQueryActiveTotal->Refresh();
	}
	catch (Exception &E)
	{
	  ShowMessage("An error occurred while refreshing FDQueryActiveTotal: " + E.Message);
	}

	try
	{
	  if (!DM->FDQueryProposalTotal->Active)
		DM->FDQueryProposalTotal->Open();
	  DM->FDQueryProposalTotal->Refresh();
	  RefreshGrids();
		UpdatePanelVisibility();
	}
	catch (Exception &E)
	{
	  ShowMessage("An error occurred while refreshing FDQueryProposalTotal: " + E.Message);
	}

	try
	{
      if (!DM->FDQueryInactiveTotal->Active)
		DM->FDQueryInactiveTotal->Open();
	  DM->FDQueryInactiveTotal->Refresh();
	}
	catch (Exception &E)
	{
	  ShowMessage("An error occurred while refreshing FDQueryInactiveTotal: " + E.Message);
	}

	try
	{
	  if (!DM->FDQueryClosedTotal->Active)
		DM->FDQueryClosedTotal->Open();
	  DM->FDQueryClosedTotal->Refresh();
	}
	catch (Exception &E)
	{
	  ShowMessage("An error occurred while refreshing FDQueryClosedTotal: " + E.Message);
	}

	try
	{
	  if (!DM->FDQueryTotal->Active)
		DM->FDQueryTotal->Open();
	  DM->FDQueryTotal->Refresh();
	}
	catch (Exception &E)
	{
	  ShowMessage("An error occurred while refreshing FDQueryTotal: " + E.Message);
	}
	switch (PageControl->ActivePageIndex)
  {
	case 7:
	  //ReportsButton->SetFocus();
	  break;
  }
  }
}

void __fastcall TMainForm::SalesSearchBoxKeyPress(TObject *Sender, System::WideChar &Key)
{
  DM->SearchProposals( SalesSearchBox->Text );
}


/*void __fastcall TMainForm::SplitViewClosing( TObject* Sender )
{
  DashboardButton->Caption = L"";
  AcctsButton->Caption = L"";
  LeadsButton->Caption = L"";
  SalesButton->Caption = L"";
  MarketingButton->Caption = L"";
  CalendarButton->Caption = L"";
  UsersButton->Caption = L"";
  ReportsButton->Caption = L"";  // Report button
}


void __fastcall TMainForm::SplitViewOpening( TObject* Sender )
{
  DashboardButton->Caption = L"          " + DashboardButton->Hint;
  AcctsButton->Caption = L"          " + AcctsButton->Hint;
  LeadsButton->Caption = L"          " + LeadsButton->Hint;
  SalesButton->Caption = L"          " + SalesButton->Hint;
  MarketingButton->Caption = L"          " + MarketingButton->Hint;
  CalendarButton->Caption = L"          " + CalendarButton->Hint;
  UsersButton->Caption = L"          " + UsersButton->Hint;
  ReportsButton->Caption = L"          " + ReportsButton->Hint;
}*/


void __fastcall TMainForm::AccountsTabResize( TObject* Sender )
{
  LinkGridToDataSourceAcctBindSourceDB->Columns->Items[1]->Width = AccountsSG->Width - LinkGridToDataSourceAcctBindSourceDB->Columns->Items[0]->Width;
}


void __fastcall TMainForm::UsersTabResize( TObject* Sender )
{
  LinkGridToDataSourceUsersBindSourceDB->Columns->Items[1]->Width = UsersSG->Width - LinkGridToDataSourceUsersBindSourceDB->Columns->Items[0]->Width;
}

void __fastcall TMainForm::UsernameComboBoxChange(TObject* Sender)
{
	LeadsForm->Close();
	DraftProposalForm->Close();
	ProposalForm->Close();

	String selectedUsername = UsernameComboBox->Text;

	DM->SetUser(selectedUsername);

	DM->ReloadLeadsQuery1(selectedUsername);
	DM->ReloadEmailsQuery(selectedUsername);
}



void __fastcall TMainForm::UsernameComboBoxKeyPress( TObject *Sender, System::WideChar &Key )
{
  Key = L'\x00';
}


void __fastcall TMainForm::UsersRelativePanelResize( TObject* Sender )
{
  if ( UsersRelativePanel->Width <= 436 )
  {
	CreateUserButton->Caption = L"";
	CreateUserButton->Width = 40;
	RemoveUserButton->Caption = L"";
	RemoveUserButton->Width = 40;
  }
  else
  {
	CreateUserButton->Caption = CreateUserButton->Hint;
	CreateUserButton->Width = 121;
	RemoveUserButton->Caption = RemoveUserButton->Hint;
	RemoveUserButton->Width = 121;
  }
}

// ------------------------------------------------------------------
void __fastcall TMainForm::WndProc(TMessage &Message)
{
	if (Message.Msg == WM_CLOSE) {
		CloseAllSecondaryForms();
		Application->Terminate();
		return;
	}
	TForm::WndProc(Message);
}

TThread *workerThread;

void StopAndFreeThread() {
	if (workerThread && workerThread->Finished == false) {
		workerThread->Terminate();
		workerThread->WaitFor();
		delete workerThread;
		workerThread = nullptr;
	}
} 

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	CloseAllSecondaryForms();
	Application->Terminate();
	Action = caNone;
}

void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose) {
	CanClose = (Screen->FormCount == 1);
	if (!CanClose) {
        ShowMessage("Other forms are still open!");
    }
}

void __fastcall TMainForm::ExitButtonClick(TObject *Sender) {
	Application->Terminate();
}

void TMainForm::RefreshFormsPublic()
{
	RefreshForms();
}
// close ------------------ free
void TMainForm::CloseAllSecondaryForms() {
	if (DraftProposalForm) {
        DraftProposalForm->Close();
        delete DraftProposalForm;
        DraftProposalForm = nullptr;
	}
    if (ProposalForm) {
        ProposalForm->Close();
        delete ProposalForm;
        ProposalForm = nullptr;
	}
    if (LeadsForm) {
        LeadsForm->Close();
        delete LeadsForm;
        LeadsForm = nullptr;
	}
}

void TMainForm::ReopenAllSecondaryForms() {
    if (!DraftProposalForm) {
		Application->CreateForm(__classid(TDraftProposalForm), &DraftProposalForm);
	}
	DraftProposalForm->Visible = false;

	if (!ProposalForm) {
		Application->CreateForm(__classid(TProposalForm), &ProposalForm);
	}
	ProposalForm->Visible = false;

	if (!LeadsForm) {
		Application->CreateForm(__classid(TLeadsForm), &LeadsForm);
	}
	LeadsForm->Visible = false;
}


 // --------------------------
void __fastcall TMainForm::VCLStylesCBChange(TObject *Sender) {
	try {
		CloseAllSecondaryForms();
		TStyleManager::TrySetStyle(VCLStylesCB->Text);
		ReopenAllSecondaryForms();
    } catch (const Exception &E) {
		ShowMessage("An error occurred while changing the style: " + E.Message);
	}
}

void TMainForm::RefreshForms()
{
	if (DraftProposalForm && !DraftProposalForm->ComponentState.Contains(csDestroying)) {
		DraftProposalForm->Invalidate();
	}
	if (ProposalForm && !ProposalForm->ComponentState.Contains(csDestroying)) {
		ProposalForm->Invalidate();
	}
	if (LeadsForm && !LeadsForm->ComponentState.Contains(csDestroying)) {
		LeadsForm->Invalidate();
	}
	if (!this->ComponentState.Contains(csDestroying)) {
		this->Invalidate();
	}
}

// ----------------------------------------------------------------

void __fastcall TMainForm::VCLStylesCBKeyPress(TObject *Sender, System::WideChar &Key)
{
  Key = L'\x00';
}


void __fastcall TMainForm::ViewLeadButtonClick( TObject* Sender )
{
  LeadsForm->Show();
}


void __fastcall TMainForm::MenuVirtualImageClick( TObject* Sender )
{
  SplitView->Opened = !SplitView->Opened;
}


void __fastcall TMainForm::AcctsRelativePanelResize( TObject* Sender )
{
  if ( AcctsRelativePanel->Width <= 634 )
  {
	ExportAcctsButton->Caption = L"";
	ExportAcctsButton->Width = 40;
	CreateAcctButton->Caption = L"";
	CreateAcctButton->Width = 40;
	RemoveAcctButton->Caption = L"";
	RemoveAcctButton->Width = 40;
  }
  else
  {
	ExportAcctsButton->Caption = ExportAcctsButton->Hint;
	ExportAcctsButton->Width = 112;
	CreateAcctButton->Caption = CreateAcctButton->Hint;
	CreateAcctButton->Width = 112;
	RemoveAcctButton->Caption = RemoveAcctButton->Hint;
	RemoveAcctButton->Width = 112;
  }
}

void __fastcall TMainForm::ActiveLeadsSGEnter(TObject* Sender)
{
    if (!LeadsBindActiveSourceDB || !LeadsBindActiveSourceDB->DataSet || !LeadsBindActiveSourceDB->DataSet->Active) {
        ShowMessage("The dataset is not properly initialized or not active.");
        return;
    }

    TField* field = LeadsBindActiveSourceDB->DataSet->FindField("LeadId");
    if (!field) {
        ShowMessage("LeadId field not found in the dataset.");
        return;
    }

    int leadId = field->AsInteger;

    if (LeadsForm) {
        LeadsForm->LocateLead(leadId);
    } else {
        ShowMessage("LeadsForm is not initialized.");
    }

    BindNavigator1->DataSource = LeadsBindActiveSourceDB;
}



void __fastcall TMainForm::ProposalSentLeadsSGEnter( TObject* Sender )
{
  LeadsForm->LocateLead( LeadsBindProposalSentSourceDB->DataSet->FieldByName( L"LeadId" )->AsInteger );
  BindNavigator1->DataSource = LeadsBindProposalSentSourceDB;
}

 // changing schema -- DateDraftedPicker
void __fastcall TMainForm::ProposalsRelativePanelResize( TObject* Sender )
{
  if ( ProposalsRelativePanel->Width <= 436 )
  {
	CompleteProposalButton->Caption = L"";
	CompleteProposalButton->Width = 40;
	CancelProposalButton->Caption = L"";
	CancelProposalButton->Width = 40;
  }
  else
  {
    CompleteProposalButton->Caption = CompleteProposalButton->Hint;
	CompleteProposalButton->Width = 121;
    CancelProposalButton->Caption = CancelProposalButton->Hint;
    CancelProposalButton->Width = 121;
  }
}


void __fastcall TMainForm::ClosedLeadsSGEnter( TObject* Sender )
{
  LeadsForm->LocateLead( LeadsBindClosedSourceDB->DataSet->FieldByName( L"LeadId" )->AsInteger );
  BindNavigator1->DataSource = LeadsBindClosedSourceDB;
}


void __fastcall TMainForm::CompleteProposalButtonClick( TObject* Sender )
{
  if ( ProposalBindSourceDB->DataSet->RecordCount > 0 )
  {
	DM->UpdateProposalStatus( ProposalBindSourceDB->DataSet->FieldByName( L"LeadId" )->AsInteger, L"Accepted" );
	ProposalBindSourceDB->DataSet->Refresh();
  }
}


void __fastcall TMainForm::CreateAcctButtonClick( TObject* Sender )
{
  String LNewAccount;
  LNewAccount = InputBox( "Create New Account", L"Account Name", L"New Account" );
  AcctBindSourceDB->DataSet->DisableControls();
  AcctBindSourceDB->DataSet->AppendRecord( ARRAYOFCONST(( 0, LNewAccount )) );
  AcctBindSourceDB->DataSet->EnableControls();
  LinkGridToDataSourceAcctBindSourceDB->Active = false;
  LinkGridToDataSourceAcctBindSourceDB->Active = true;
}
// -------------------------------------------------------------------------------

void __fastcall TMainForm::CreateLeadButtonClick(TObject* Sender)
{
    try
    {
		LeadsBindNewSourceDB->DataSet->DisableControls();

        if (!LeadsBindNewSourceDB->DataSet->Active)
            LeadsBindNewSourceDB->DataSet->Open();

        LeadsBindNewSourceDB->DataSet->Append();
        ShowMessage("Appending new record");

        LeadsBindNewSourceDB->DataSet->FieldByName("Status")->AsString = "New";
        LeadsBindNewSourceDB->DataSet->FieldByName("Name")->AsString = "First Last";
        LeadsBindNewSourceDB->DataSet->FieldByName("DateCreated")->AsDateTime = Now();

        LeadsBindNewSourceDB->DataSet->Post();
        ShowMessage("Record posted, ID: " + LeadsBindNewSourceDB->DataSet->FieldByName("LeadId")->AsString);

        LeadsBindNewSourceDB->DataSet->Refresh();  // Synchronize data

        if (LeadsBindNewSourceDB->DataSet->Locate("LeadId", LeadsBindNewSourceDB->DataSet->FieldByName("LeadId")->AsInteger, TLocateOptions())) {
            ShowMessage("Successfully located new lead.");
			LeadsForm->Show();
if (!LeadsForm->LocateLead1(LeadsBindNewSourceDB->DataSet->FieldByName("LeadId")->AsInteger)) {
    ShowMessage("Failed to locate the new lead with ID: " + IntToStr(LeadsBindNewSourceDB->DataSet->FieldByName("LeadId")->AsInteger));
} else {
    ShowMessage("Lead located and form displayed.");
}
        } else {
            ShowMessage("Failed to locate the new lead after creation.");
        }
    }
    catch (const Exception &E)
    {
        ShowMessage("An error occurred while creating a new lead: " + E.Message);
        LeadsBindNewSourceDB->DataSet->Cancel();  // Cancel changes on error
    }

	LeadsBindNewSourceDB->DataSet->EnableControls();

    RefreshGrids();
    UpdatePanelVisibility();
}


// ------------------------------------------------------------------------------

void __fastcall TMainForm::CreateUserButtonClick(TObject* Sender)       // EDITED
{
	String LNewUser = InputBox("Create New User", "User Name", "user");

	Variant LExistingUserVariant = UsersBindSourceDB->DataSet->Lookup("Username", LNewUser, "Username");
	String LExistingUser = LExistingUserVariant.IsNull() ? "" : LExistingUserVariant;

	// Compare strings to determine if the user exists
	if (LExistingUser != LNewUser)
	{
		UsersBindSourceDB->DataSet->Append();
		UsersBindSourceDB->DataSet->FieldByName("Username")->AsString = LNewUser;
		UsersBindSourceDB->DataSet->Post();
		DM->UsersFDTable->Refresh();
	}
	else
	{
		ShowMessage("A user with that username already exists.");
	}
}



void __fastcall TMainForm::DashboardButtonClick( TObject* Sender )
{
  PageControl->ActivePageIndex = ((TButton*)( Sender ))->Tag;
}


void __fastcall TMainForm::LeadsRelativePanelResize( TObject* Sender )
{
  if ( LeadsRelativePanel->Width <= 781 )
  {
    ExportLeadsButton->Caption = L"";
	ExportLeadsButton->Width = 40;
	CreateLeadButton->Caption = L"";
	CreateLeadButton->Width = 40;
    ViewLeadButton->Caption = L"";
	ViewLeadButton->Width = 40;
  }
  else
  {
	ExportLeadsButton->Caption = ExportLeadsButton->Hint;
	ExportLeadsButton->Width = 153;
	CreateLeadButton->Caption = CreateLeadButton->Hint;
	CreateLeadButton->Width = 153;
	ViewLeadButton->Caption = ViewLeadButton->Hint;
	ViewLeadButton->Width = 153;
  }
}


void __fastcall TMainForm::LeadsSearchBoxKeyPress(TObject* Sender, System::WideChar &Key)
{
  DM->SearchLeads( LeadsSearchBox->Text );
  RefreshGrids();
  UpdatePanelVisibility();
}

void __fastcall TMainForm::MarketingRelativePanelResize( TObject* Sender )
{
  if ( MarketingRelativePanel->Width <= 320 )
  {
	ExportEmailsButton->Caption = L"";
	ExportEmailsButton->Width = 40;
  }
  else
  {
	ExportEmailsButton->Caption = ExportEmailsButton->Hint;
	ExportEmailsButton->Width = 121;
  }
}

void __fastcall TMainForm::NewLeadsSGDblClick( TObject* Sender )
{
  ViewLeadButtonClick( Sender );
}

void __fastcall TMainForm::NewLeadsSGDragDrop( TObject* Sender, TObject* Source, int X, int Y )
{
  String LStatus;
  int LIndex = 0;
  TDataSet *LDataSet;
  String LDateField;
  LIndex = - 1;
  if ( Source == Sender )
  {
  }
  else
  {
	switch ( ((TStringGrid*)( Sender ))->Parent->Tag )
	{
	  case 1:
	  {
		LStatus = L"New";
		LDateField = L"DateCreated";
		LDataSet = LeadsBindNewSourceDB->DataSet;
	  }
	  break;
	  case 2:
	  {
		LStatus = L"Active";
		LDateField = L"DateContacted";
		LDataSet = LeadsBindActiveSourceDB->DataSet;
	  }
	  break;
	  case 3:
	  {
		LStatus = L"Proposal Sent";
		LDateField = L"DateDrafted";
		LDataSet = LeadsBindProposalSentSourceDB->DataSet;
	  }
	  break;
	  case 4:
	  {
		LStatus = L"Closed";
		LDateField = L"DateClosed";
		LDataSet = LeadsBindClosedSourceDB->DataSet;
	  }
	  break;
	default:
	  LDataSet = LeadsBindNewSourceDB->DataSet;
	}
	switch ( ((TStringGrid*)( Source ))->Parent->Tag )
	{
	  case 1:
	  {
		if ( LeadsBindNewSourceDB->DataSet->RecordCount > 0 )
		{
		  LIndex = LeadsBindNewSourceDB->DataSet->FieldByName( L"LeadId" )->AsInteger;
		  if ( LeadsBindSourceDB->DataSet->Locate( L"LeadId", VarArrayOf( OPENARRAY(Variant, ( LIndex )) ), TLocateOptions() ) )
		  {
			LeadsBindSourceDB->DataSet->Edit();
			LeadsBindSourceDB->DataSet->FieldByName( L"Status" )->AsString = LStatus;
			if ( (double)LeadsBindSourceDB->DataSet->FieldByName( LDateField )->AsDateTime == 0.0 )
			  LeadsBindSourceDB->DataSet->FieldByName( LDateField )->AsDateTime = Now();
			LeadsBindSourceDB->DataSet->Post();
		  }
		  LDataSet->Locate( L"LeadId", VarArrayOf( OPENARRAY(Variant, ( LIndex )) ), TLocateOptions() );
		}
	  }
	  break;
	  case 2:
	  {
		if ( LeadsBindActiveSourceDB->DataSet->RecordCount > 0 )
		{
		  LIndex = LeadsBindActiveSourceDB->DataSet->FieldByName( L"LeadId" )->AsInteger;
		  if ( LeadsBindSourceDB->DataSet->Locate( L"LeadId", VarArrayOf( OPENARRAY(Variant, ( LIndex ))  ), TLocateOptions() ))
		  {
			LeadsBindSourceDB->DataSet->Edit();
			LeadsBindSourceDB->DataSet->FieldByName( L"Status" )->AsString = LStatus;
			if ( (double)LeadsBindSourceDB->DataSet->FieldByName( LDateField )->AsDateTime == 0.0 )
			  LeadsBindSourceDB->DataSet->FieldByName( LDateField )->AsDateTime = Now();
			LeadsBindSourceDB->DataSet->Post();
		  }
		  LDataSet->Locate( L"LeadId", VarArrayOf( OPENARRAY(Variant, ( LIndex )) ), TLocateOptions() );
		}
	  }
	  break;
	  case 3:
	  {
		if ( LeadsBindProposalSentSourceDB->DataSet->RecordCount > 0 )
		{
		  LIndex = LeadsBindProposalSentSourceDB->DataSet->FieldByName( L"LeadId" )->AsInteger;
		  if ( LeadsBindSourceDB->DataSet->Locate( L"LeadId", VarArrayOf( OPENARRAY(Variant, ( LIndex )) ), TLocateOptions() ) )
		  {
			LeadsBindSourceDB->DataSet->Edit();
			LeadsBindSourceDB->DataSet->FieldByName( L"Status" )->AsString = LStatus;
			if ( (double)LeadsBindSourceDB->DataSet->FieldByName( LDateField )->AsDateTime == 0.0 )
			  LeadsBindSourceDB->DataSet->FieldByName( LDateField )->AsDateTime = Now();
			LeadsBindSourceDB->DataSet->Post();
		  }
		  LDataSet->Locate( L"LeadId", VarArrayOf( OPENARRAY(Variant, ( LIndex )) ), TLocateOptions() );
		}
	  }
	  break;
	  case 4:
	  {
		if ( LeadsBindClosedSourceDB->DataSet->RecordCount > 0 )
		{
		  LIndex = LeadsBindClosedSourceDB->DataSet->FieldByName( L"LeadId" )->AsInteger;
		  if ( LeadsBindSourceDB->DataSet->Locate( L"LeadId", VarArrayOf( OPENARRAY(Variant, ( LIndex )) ), TLocateOptions() ) )
		  {
			LeadsBindSourceDB->DataSet->Edit();
			LeadsBindSourceDB->DataSet->FieldByName( L"Status" )->AsString = LStatus;
			if ( (double)LeadsBindSourceDB->DataSet->FieldByName( LDateField )->AsDateTime == 0.0)
			  LeadsBindSourceDB->DataSet->FieldByName( LDateField )->AsDateTime = Now();
			LeadsBindSourceDB->DataSet->Post();
		  }
		  LDataSet->Locate( L"LeadId", VarArrayOf( OPENARRAY(Variant, ( LIndex )) ), TLocateOptions());
		}
	  }
	  break;
	}
	RefreshGrids();
	LDataSet->Locate( L"LeadId", VarArrayOf( OPENARRAY(Variant, ( LIndex )) ), TLocateOptions() );
  }
}

void __fastcall TMainForm::NewLeadsSGDragOver( TObject* Sender, TObject* Source, int X, int Y, TDragState State, bool& Accept )
{
  Accept = dynamic_cast< TStringGrid* >( Source );
}


void __fastcall TMainForm::NewLeadsSGEnter(TObject* Sender)
{
	if (!LeadsBindNewSourceDB || !LeadsBindNewSourceDB->DataSet || !LeadsBindNewSourceDB->DataSet->Active) {
		ShowMessage("The dataset is not properly initialized or not active.");
		return;
	}

	TField* field = LeadsBindNewSourceDB->DataSet->FindField("LeadId");
	if (field == nullptr) {
        ShowMessage("LeadId field not found in the dataset.");
		return;
	}

	int leadId = field->AsInteger;

	LeadsForm->LocateLead(leadId);

	BindNavigator1->DataSource = LeadsBindNewSourceDB;
}



void __fastcall TMainForm::NewLeadsSGMouseDown( TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y )
{
  if ( Button == mbLeft )
	((TStringGrid*)( Sender ))->BeginDrag( false, 4 );
}


void __fastcall TMainForm::EmailsSearchBoxKeyPress( TObject* Sender, Char& Key )
{
  DM->SearchEmails( EmailsSearchBox->Text );
}


void __fastcall TMainForm::ExportAcctsButtonClick( TObject* Sender )
{
  if ( ExportAcctsDialog->Execute() )
  {
	DM->AcctFDTable->SaveToFile( ExportAcctsDialog->FileName );
  }
}


void __fastcall TMainForm::ExportEmailsButtonClick( TObject* Sender )
{
  if ( SaveEmailsDialog->Execute() )
  {
	DM->ExportEmails( SaveEmailsDialog->FileName );
  }
}


void __fastcall TMainForm::ExportLeadsButtonClick( TObject* Sender )
{
  if ( ExportLeadsDialog->Execute() )
  {
	DM->LeadsFDTable->SaveToFile( ExportLeadsDialog->FileName );
  }
}


/*void __fastcall TMainForm::AppIdle( TObject* Sender, bool& Done )
{
  if ( ! FRanOnce )
  {
	FRanOnce = true;
	DM->InitializeDatabase();
	DashboardButton->SetFocus();
  }
}

void __fastcall TMainForm::UpdateNavButtons()
{
  DashboardButton->Font->Style = TFontStyles();
  AcctsButton->Font->Style = TFontStyles();
  LeadsButton->Font->Style = TFontStyles();
  SalesButton->Font->Style = TFontStyles();
  MarketingButton->Font->Style = TFontStyles();
  CalendarButton->Font->Style = TFontStyles();
  UsersButton->Font->Style = TFontStyles();
  ReportsButton->Font->Style = TFontStyles();

  TButton *ActiveButton = nullptr;
  switch (PageControl->ActivePageIndex)
  {
	case 0: ActiveButton = DashboardButton; break;
	case 1: ActiveButton = AcctsButton; break;
	case 2: ActiveButton = LeadsButton; break;
	case 3: ActiveButton = SalesButton; break;
	case 4: ActiveButton = MarketingButton; break;
	case 5: ActiveButton = CalendarButton; break;
	case 6: ActiveButton = UsersButton; break;
	case 7: ActiveButton = ReportsButton; break;
	// Add more cases if you have more tabs
  }

  if (ActiveButton)
  {
	// Set the active button font to bold
	ActiveButton->Font->Style = TFontStyles() << fsBold;
  }

} */


void __fastcall TMainForm::FormResize( TObject* Sender )
{
  if ( MainForm->Width <= 640 )
  {
	if ( SplitView->Opened == true )
	  SplitView->Opened = false;
  }
  else
  {
	if ( SplitView->Opened == false )
	  SplitView->Opened = true;
  }
}

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
  StringGrid1->OnMouseDown = StringGrid1MouseDown;
  String StyleName;
  //Application->OnIdle = AppIdle;
  for(String StyleName: TStyleManager::StyleNames) {
	VCLStylesCB->Items->Add( StyleName );
  }

  VCLStylesCB->ItemIndex = VCLStylesCB->Items->IndexOf( TStyleManager::ActiveStyle->Name );
  //UpdateNavButtons();
}

void PopulateDBGrid()
{
	if (!DM->FDLeadsQueryNew->Active)
		DM->FDLeadsQueryNew->Open();
}


//---------------------------------------------------------------------------
// Represhing the grid.
 void __fastcall TMainForm::CompleteRefreshAction()
{
	((TBindSourceDB*)(BindNavigator1->DataSource))->DataSet->Refresh();

	RefreshGrids();
	UpdatePanelVisibility();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormActivate(TObject *Sender)
{
  if (FRanOnce)
  {
	if (LeadsBindSourceDB->DataSet->State == TDataSetState::dsEdit) {
	  LeadsBindSourceDB->DataSet->Post();
	}

	CompleteRefreshAction();
  }
}

//---------------------------------------------------------------------------
TPanel* TMainForm::SelectedPanel = nullptr;
const TColor TMainForm::clHover = clSkyBlue;

// <-- design

void TMainForm::UpdatePanelStyle(TPanel* Panel, bool Selected, bool Hovered) {
	if (Selected) {
		Panel->Color = clSelected; // Color when selected
		Panel->BevelOuter = bvLowered;
		Panel->Font->Style = TFontStyles() << fsBold;
	} else if (Hovered) {
		Panel->Color = clHover; // Different color when hovered
		Panel->Font->Style = TFontStyles() << fsBold;
	} else {
		Panel->Color = clDefault; // Default color when neither selected nor hovered
		Panel->BevelOuter = bvNone;
		Panel->Font->Style = TFontStyles();
	}
}

void __fastcall TMainForm::PanelMouseEnter(TObject *Sender) {
	TPanel *Panel = dynamic_cast<TPanel*>(Sender);
	if (Panel && Panel != SelectedPanel) {
		UpdatePanelStyle(Panel, false, true); // true for Hovered
	}
}

void __fastcall TMainForm::PanelMouseLeave(TObject *Sender) {
	TPanel *Panel = dynamic_cast<TPanel*>(Sender);
	if (Panel && Panel != SelectedPanel) {
        UpdatePanelStyle(Panel, false, false); // false for Hovered
    }
}

void TMainForm::ResetPanelsAppearance() {
	UpdatePanelStyle(Panel1, Panel1 == SelectedPanel, false);
	UpdatePanelStyle(Panel9, Panel9 == SelectedPanel, false);
	UpdatePanelStyle(Panel10, Panel10 == SelectedPanel, false);
	UpdatePanelStyle(Panel11, Panel11 == SelectedPanel, false);
	UpdatePanelStyle(Panel12, Panel12 == SelectedPanel, false);
}

void TMainForm::SetupPanelClickAndMouseHandlers() {
	Panel1->OnClick = AnyPanelClick;
	Panel1->OnMouseEnter = PanelMouseEnter;
	Panel1->OnMouseLeave = PanelMouseLeave;
}
// design <-- above

void TMainForm::ClearAndResetStringGrid(int headerRows, int dataRows, int colCount) {
	StringGrid1->RowCount = headerRows + max(dataRows, 1);
	StringGrid1->ColCount = colCount;
	for (int row = 0; row < StringGrid1->RowCount; ++row) {
		for (int col = 0; col < colCount; ++col) {
			StringGrid1->Cells[col][row] = "";
        }
	}
	StringGrid1->Invalidate();
}

void __fastcall TMainForm::AnyPanelClick(TObject *Sender) {
    TPanel *clickedPanel = dynamic_cast<TPanel*>(Sender);

    if (clickedPanel != nullptr) {
        if (SelectedPanel) {
			UpdatePanelStyle(SelectedPanel, false, false);
		}
		UpdatePanelStyle(clickedPanel, true);
		SelectedPanel = clickedPanel;

        if (clickedPanel->Name == "Panel11") {
            DisplayProfitAndLoss();
			FCurrentRow = StringGrid1->Row;
        } else if (clickedPanel->Name == "Panel1") {
            DisplaySummaryInformation();
			FCurrentRow = StringGrid1->Row;
		} else {
            String tableName = clickedPanel->Caption;
            tableName = StringReplace(tableName, " ", "", TReplaceFlags() << rfReplaceAll);
			tableName = StringReplace(tableName, "&", "", TReplaceFlags() << rfReplaceAll);
			ClearAndResetStringGrid(0, 0, 4);
            DM->CreateTableFromGrid(tableName, StringGrid1);
			FCurrentRow = StringGrid1->Row;
		}
    }
}


// Sets up the event handlers for the panels
void TMainForm::SetupPanelClickHandlers() {
	Panel1->OnClick = AnyPanelClick;
	Panel9->OnClick = AnyPanelClick;
	Panel10->OnClick = AnyPanelClick;
	Panel11->OnClick = AnyPanelClick;
	//Sales
	Panel12->OnClick = AnyPanelClick;
	Panel13->OnClick = AnyPanelClick;
	Panel14->OnClick = AnyPanelClick;
	Panel15->OnClick = AnyPanelClick;
	Panel16->OnClick = AnyPanelClick;
	Panel17->OnClick = AnyPanelClick;
	Panel18->OnClick = AnyPanelClick;
	// Purchase & Expanses
	Panel19->OnClick = AnyPanelClick;
	Panel20->OnClick = AnyPanelClick;
	Panel21->OnClick = AnyPanelClick;
	Panel22->OnClick = AnyPanelClick;
	Panel23->OnClick = AnyPanelClick;
	Panel24->OnClick = AnyPanelClick;
	// Items
	Panel25->OnClick = AnyPanelClick;
	//Taxes
	Panel26->OnClick = AnyPanelClick;
}

void TMainForm::DisplaySummaryInformation() {
    ClearAndResetStringGrid(1, 0, 6);
    StringGrid1->Cells[0][0] = "Lead ID";
    StringGrid1->Cells[1][0] = "Name";
    StringGrid1->Cells[2][0] = "Status";
    StringGrid1->Cells[3][0] = "Email";
    StringGrid1->Cells[4][0] = "User";
    StringGrid1->Cells[5][0] = "Date Created";

	OriginalData.clear();
    auto query = std::make_unique<TFDQuery>(nullptr);
    query->Connection = DM->FDConnection1;
    query->SQL->Text = "SELECT LeadID, Name, Status, Email, User, DateCreated FROM Leads";
    query->Open();

	int rowIndex = 1;
    while (!query->Eof) {
        std::vector<String> row;
        row.push_back(query->FieldByName("LeadID")->AsString);
        row.push_back(query->FieldByName("Name")->AsString);
        row.push_back(query->FieldByName("Status")->AsString);
        row.push_back(query->FieldByName("Email")->AsString);
        row.push_back(query->FieldByName("User")->AsString);
        row.push_back(query->FieldByName("DateCreated")->AsString);

		OriginalData.push_back(row);
        for (size_t colIndex = 0; colIndex < row.size(); ++colIndex) {
            StringGrid1->Cells[colIndex][rowIndex] = row[colIndex];
		}
		rowIndex++;
		query->Next();
	}

	query->Close();

	StringGrid1->RowCount = OriginalData.size() + 1;
	StringGrid1->Invalidate();
}

void TMainForm::DisplayProfitAndLoss() {
	ClearAndResetStringGrid(1, 0, 4);

    StringGrid1->Cells[0][0] = "Proposal ID";
    StringGrid1->Cells[1][0] = "User";
    StringGrid1->Cells[2][0] = "Value";
    StringGrid1->Cells[3][0] = "Type";

	OriginalData.clear();

    TFDQuery *query = new TFDQuery(nullptr);
    query->Connection = DM->FDConnection1;
    query->SQL->Text = "SELECT ProposalID, User, Value, Status FROM Proposals";
    query->Open();

    double totalProfit = 0.0;
    double totalLoss = 0.0;
    int rowIndex = 1;

    while (!query->Eof) {
        std::vector<String> row;
        row.push_back(query->FieldByName("ProposalID")->AsString);
        row.push_back(query->FieldByName("User")->AsString);
        double value = query->FieldByName("Value")->AsFloat;
        row.push_back(FormatFloat("0.00", value));

        String status = query->FieldByName("Status")->AsString;
        if (status == "Accepted") {
            row.push_back("Profit");
			totalProfit += value;
        } else if (status == "Canceled") {
            row.push_back("Loss");
            totalLoss += value;
        } else {
			row.push_back(status);
        }

        OriginalData.push_back(row);
        rowIndex++;
        query->Next();
    }

    query->Close();
	delete query;

	StringGrid1->RowCount = rowIndex + 3;

    for (int i = 1; i < rowIndex; ++i) {
        for (int j = 0; j < 4; ++j) {
			StringGrid1->Cells[j][i] = OriginalData[i-1][j];
        }
    }

    StringGrid1->Cells[1][rowIndex] = "Total Profit";
    StringGrid1->Cells[2][rowIndex++] = FormatFloat("0.00", totalProfit);
    StringGrid1->Cells[1][rowIndex] = "Total Loss";
    StringGrid1->Cells[2][rowIndex++] = FormatFloat("0.00", totalLoss);
    StringGrid1->Cells[1][rowIndex] = "Net";
    StringGrid1->Cells[2][rowIndex] = FormatFloat("0.00", totalProfit - totalLoss);

	StringGrid1->Invalidate();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::frxUserDataSet1CheckEOF(TObject *Sender, bool &Eof) {
	Eof = (FCurrentRow >= StringGrid1->RowCount);
}

void __fastcall TMainForm::frxUserDataSet1GetValue(const UnicodeString VarName, Variant &Value) {
	if (FCurrentRow < StringGrid1->RowCount) {
		int col = StrToIntDef(VarName.SubString(7, VarName.Length() - 6), -1);
		if (col >= 0 && col < StringGrid1->ColCount) {
            Value = StringGrid1->Cells[col][FCurrentRow];
		} else {
			Value = "";
		}

        if (col == StringGrid1->ColCount - 1) {
            FCurrentRow++;
		}
    } else {
		Value = "";
	}
}

void __fastcall TMainForm::frxUserDataSet2GetValue(const UnicodeString VarName, Variant &Value)

{
	int col = StrToInt(VarName.SubString(7, VarName.Length() - 6));
	Value = StringGrid1->Cells[col][FCurrentRow];

	if (VarName == "Column" + IntToStr(StringGrid1->ColCount - 1)) {
		FCurrentRow++;
	}

}

void __fastcall TMainForm::frxUserDataSet2CheckEOF(TObject *Sender, bool &Eof)
{
	Eof = (FCurrentRow >= StringGrid1->RowCount);
}



void __fastcall TMainForm::SpeedButton40Click(TObject *Sender) {
    TfrxReport* reportToExport = nullptr;

    bool generateDetailedReport = !FDetailData.empty();

    if (SelectedPanel->Name == "Panel11") {
		reportToExport = frxReport2;
        frxPDFExport1->FileName = "ProfitAndLossReport.pdf";
        frxUserDataSet1->Enabled = true;
        frxUserDataSet4->Enabled = false;
    } else if (SelectedPanel->Name == "Panel1") {
        reportToExport = frxReport1;
        frxPDFExport1->FileName = generateDetailedReport ? "DetailedSummaryInformationReport.pdf" : "SummaryInformationReport.pdf";
        frxUserDataSet1->Enabled = !generateDetailedReport;
        frxUserDataSet4->Enabled = generateDetailedReport;
    }

    FCurrentRow = 0;
    FDetailCurrentRow = 0;

	if (reportToExport != nullptr) {
		reportToExport->PrepareReport(false);

        reportToExport->ShowPreparedReport();

        if (MessageDlg("Do you want to export this report to PDF?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes) {
            frxPDFExport1->OverwritePrompt = true;
            reportToExport->Export(frxPDFExport1);
        }

		frxUserDataSet1->Enabled = false;
		frxUserDataSet4->Enabled = false;
	} else {
		ShowMessage("No report is selected for export.");
	}
}



//---------------------------------------------------------------------------
// searching

void TMainForm::CaptureOriginalData() {
	OriginalData.clear();
	for (int i = 1; i < StringGrid1->RowCount; i++) {
		std::vector<String> row;
		for (int j = 0; j < StringGrid1->ColCount; j++) {
			row.push_back(StringGrid1->Cells[j][i]);
		}
		OriginalData.push_back(row);
	}
}

void TMainForm::SearchInStringGrid(const String& searchText) {
	String lcSearchTerm = searchText.LowerCase();
	StringGrid1->RowCount = 1;

	for (const auto& row : OriginalData) {
		String concatenatedRow;
		for (const auto& cell : row) {
			concatenatedRow += cell.LowerCase() + " ";
		}

		if (lcSearchTerm.IsEmpty() || concatenatedRow.Pos(lcSearchTerm) > 0) {
			int newRow = StringGrid1->RowCount;
			StringGrid1->RowCount++;
			for (size_t colIndex = 0; colIndex < row.size(); ++colIndex) {
				StringGrid1->Cells[colIndex][newRow] = row[colIndex];
			}
		}
	}
}

void __fastcall TMainForm::SearchBox1Change(TObject *Sender) {
	SearchInStringGrid(SearchBox1->Text);
}


void TMainForm::LoadDataIntoGrid() {
	OriginalData.clear();
	for (int i = 1; i < StringGrid1->RowCount; i++) {
		std::vector<String> row(StringGrid1->ColCount);
		for (int j = 0; j < StringGrid1->ColCount; j++) {
			row[j] = StringGrid1->Cells[j][i];
		}
		OriginalData.push_back(row);
	}
}

void __fastcall TMainForm::FormCreate3(TObject *Sender) {
	LoadDataIntoGrid();
	CaptureOriginalData();
}

void TMainForm::ResetGridToOriginalData() {
	StringGrid1->RowCount = OriginalData.size() + 1;
	for (int i = 1; i < StringGrid1->RowCount; ++i) {
		for (int j = 0; j < StringGrid1->ColCount; ++j) {
			StringGrid1->Cells[j][i] = OriginalData[i-1][j];
		}
	}
}

//---------------------------------------------------------------------------
// Trying to create the tables

/*void TMainForm::CreateTableAndInsertData(const String &panelName, const String &uniqueIDName) {
	TFDConnection *connection = DM->FDConnection1;

	connection->StartTransaction();
	try {
		TFDQuery *query = new TFDQuery(nullptr);
		query->Connection = connection;

		String createTableSQL = "CREATE TABLE IF NOT EXISTS " + panelName + " (";
		String columnName, paramName;

		for (int colIndex = 0; colIndex < StringGrid1->ColCount; ++colIndex) {
			columnName = StringGrid1->Cells[colIndex][0]; // Assuming row 0 contains headers
			paramName = StringReplace(columnName, " ", "_", TReplaceFlags() << rfReplaceAll); // Replace spaces with underscores
			if (colIndex > 0) createTableSQL += ", ";
			createTableSQL += "\"" + columnName + "\" TEXT";
		}
		createTableSQL += ")";
		query->SQL->Text = createTableSQL;
		query->ExecSQL();

		//String uniqueIDName = "LeadID"; // Adjust if your unique identifier column has a different name
		String sqlSelect, sqlInsert, sqlUpdate;

		// Loop through each row in StringGrid1 starting from the first data row
		for (int rowIndex = 1; rowIndex < StringGrid1->RowCount; ++rowIndex) {
			String uniqueID = ""; // Initialize uniqueID with an empty string
			bool uniqueIDColumnExists = false;

			// Find the uniqueID from the grid based on the header name
			for (int colIndex = 0; colIndex < StringGrid1->ColCount; ++colIndex) {
				if (StringGrid1->Cells[colIndex][0].CompareIC(uniqueIDName) == 0) { // Case insensitive comparison
					uniqueID = StringGrid1->Cells[colIndex][rowIndex];
					uniqueIDColumnExists = true;
					break;
				}
			}

			if (!uniqueIDColumnExists) {
				continue; // Skip to the next row if the unique identifier column does not exist
			}

			// Check if a row with the same uniqueID already exists
			query->SQL->Text = "SELECT COUNT(*) AS Cnt FROM " + panelName + " WHERE \"" + uniqueIDName + "\" = :UniqueID";
			query->ParamByName("UniqueID")->AsString = uniqueID;
			query->Open();
			int count = query->FieldByName("Cnt")->AsInteger; // Correct usage
			query->Close();

			if (count == 0) { // No existing row with the same uniqueIDName, insert new record
				String insertDataSQL = "INSERT INTO " + panelName + " (";
				String columnNames, columnValues;

				// Construct the INSERT SQL statement
				for (int colIndex = 0; colIndex < StringGrid1->ColCount; ++colIndex) {
					String columnName = StringGrid1->Cells[colIndex][0]; // Get header name
					String paramName = StringReplace(columnName, " ", "_", TReplaceFlags() << rfReplaceAll);
					if (colIndex > 0) {
						columnNames += ", ";
						columnValues += ", ";
					}
					columnNames += columnName;
                    columnValues += ":" + paramName;
				}
				insertDataSQL += columnNames + ") VALUES (" + columnValues + ")";

                // Set the parameter values and execute the SQL statement
				query->SQL->Text = insertDataSQL;
				for (int colIndex = 0; colIndex < StringGrid1->ColCount; ++colIndex) {
					String paramName = StringReplace(StringGrid1->Cells[colIndex][0], " ", "_", TReplaceFlags() << rfReplaceAll);
					query->ParamByName(paramName)->AsString = StringGrid1->Cells[colIndex][rowIndex];
				}
				query->ExecSQL();
			}
			// count!=0, the record already exists and we do nothing
		}

		connection->Commit();
		delete query;
	} catch(...) {
		connection->Rollback();
		throw;
	}
}*/

//---------------------------------------------------------------------------

void __fastcall TMainForm::StringGrid1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	int ACol, ARow;
	StringGrid1->MouseToCell(X, Y, ACol, ARow);
	if (ARow > 0 && Button == mbLeft) {
		int leadID = StrToInt(StringGrid1->Cells[0][ARow]);
		DisplayDetailInformation(leadID);
	}
}


void __fastcall TMainForm::DisplayDetailInformation(int leadID) {
	ClearAndResetStringGrid(1, 0, 3);

    TFDQuery *query = new TFDQuery(nullptr);
    query->Connection = DM->FDConnection1;
    query->SQL->Text = "SELECT LeadID, OFFICEPHONE, NOTES FROM Leads WHERE LeadID = :LeadID";
    query->ParamByName("LeadID")->AsInteger = leadID;
    query->Open();

	FDetailData.clear();
    std::vector<String> detailRow;
    detailRow.push_back(query->FieldByName("LeadID")->AsString);
    detailRow.push_back(query->FieldByName("OFFICEPHONE")->AsString);
    detailRow.push_back(query->FieldByName("NOTES")->AsString);
	FDetailData.push_back(detailRow);

    StringGrid1->Cells[0][0] = "Lead ID";
    StringGrid1->Cells[1][0] = "Office Phone";
    StringGrid1->Cells[2][0] = "Notes";
    if (!query->Eof) {
		StringGrid1->Cells[0][1] = query->FieldByName("LeadID")->AsString;
        StringGrid1->Cells[1][1] = query->FieldByName("OFFICEPHONE")->AsString;
        StringGrid1->Cells[2][1] = query->FieldByName("NOTES")->AsString;
		StringGrid1->RowCount = 2;
    } else {
		StringGrid1->RowCount = 1;
    }

    query->Close();
    delete query;

	StringGrid1->Invalidate();
    FDetailCurrentRow = 0;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
	DisplaySummaryInformation();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::frxUserDataSet4CheckEOF(TObject *Sender, bool &Eof) {
    Eof = (FDetailCurrentRow >= FDetailData.size());
}

void __fastcall TMainForm::frxUserDataSet4First(TObject *Sender) {
	FDetailCurrentRow = 0;
}

void __fastcall TMainForm::frxUserDataSet4Next(TObject *Sender) {
    if (FDetailCurrentRow < FDetailData.size()) {
        FDetailCurrentRow++;
    }
}

void __fastcall TMainForm::frxUserDataSet4GetValue(const UnicodeString VarName, Variant &Value) {
    int col = std::stoi(String(VarName).SubString(7, VarName.Length() - 6).c_str(), nullptr, 10);
    if (FDetailCurrentRow < FDetailData.size() && col >= 0 && col < FDetailData[FDetailCurrentRow].size()) {
        Value = FDetailData[FDetailCurrentRow][col];
    } else {
		Value = "";
    }

    if (FDetailData.size() > 0 && col == FDetailData[FDetailCurrentRow].size() - 1) {
        FDetailCurrentRow++;
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ListBox1Click(TObject *Sender)
{
    TListBox *ListBox = static_cast<TListBox*>(Sender);
    int Index = ListBox->ItemIndex;
	if (Index == -1) return;

    String itemCaption = ListBox->Items->Strings[Index];

    for (int i = 0; i < PageControl->PageCount; i++) {
        if (PageControl->Pages[i]->Caption == itemCaption) {
            PageControl->ActivePageIndex = i;
            break;
        }
	}
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

