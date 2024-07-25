//---------------------------------------------------------------------------

#ifndef uMainFormH
#define uMainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.Controls.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Data.Bind.Grid.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.ImageList.hpp>
#include <System.Rtti.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.Bind.DBEngExt.hpp>
#include <Vcl.Bind.Editors.hpp>
#include <Vcl.Bind.Grid.hpp>
#include <Vcl.Bind.Navigator.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.VirtualImage.hpp>
#include <Vcl.VirtualImageList.hpp>
#include <Vcl.WinXCalendars.hpp>
#include <Vcl.WinXCtrls.hpp>
#include <Vcl.TitleBarCtrls.hpp>
#include <Vcl.ControlList.hpp>
#include "frCoreClasses.hpp"
#include "frxClass.hpp"
#include <System.Generics.Collections.hpp>
#include "frxExportBaseDialog.hpp"
#include "frxExportPDF.hpp"
#include <Vcl.Menus.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <FireDAC.Comp.Client.hpp>
#include <map>
//#include <oci.h>    // Oracle OCI include
//#include <sqlite3.h> // SQLite3 include
//---------------------------------------------------------------------------

class TMainForm : public TForm
{
protected:
	virtual void __fastcall WndProc(TMessage &Message) override;

__published:	// IDE-managed Components
	TSplitView *SplitView;
	TPanel *pnlToolbar;
	TLabel *lblTitle;
	TVirtualImage *MenuVirtualImage;
	TPanel *NavPanel;
	TImage *Image5;
	TPageControl *PageControl;
	TTabSheet *DashboardTab;
	TPanel *Panel5;
	TLabel *Label4;
	TVirtualImage *VirtualImage1;
	TFlowPanel *FlowPanel1;
	TRelativePanel *RelativePanel1;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TVirtualImage *VirtualImage9;
	TRelativePanel *RelativePanel2;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TVirtualImage *VirtualImage10;
	TRelativePanel *RelativePanel3;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TVirtualImage *VirtualImage11;
	TRelativePanel *RelativePanel4;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TVirtualImage *VirtualImage12;
	TRelativePanel *RelativePanel5;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TVirtualImage *VirtualImage13;
	TRelativePanel *RelativePanel6;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TVirtualImage *VirtualImage14;
	TTabSheet *AccountsTab;
	TPanel *Panel7;
	TLabel *Label24;
	TVirtualImage *VirtualImage2;
	TRelativePanel *AcctsRelativePanel;
	TSearchBox *AcctSearchBox;
	TSpeedButton *ExportAcctsButton;
	TSpeedButton *RemoveAcctButton;
	TSpeedButton *CreateAcctButton;
	TStringGrid *AccountsSG;
	TBindNavigator *BindNavigator4;
	TTabSheet *LeadsTab;
	TSplitter *Splitter1;
	TSplitter *Splitter2;
	TSplitter *Splitter3;
	TBindNavigator *BindNavigator1;
	TPanel *Panel2;
	TLabel *Label1;
	TVirtualImage *VirtualImage3;
	TRelativePanel *LeadsRelativePanel;
	TSpeedButton *CreateLeadButton;
	TSpeedButton *ExportLeadsButton;
	TSearchBox *LeadsSearchBox;
	TSpeedButton *ViewLeadButton;
	TPanel *NewLeadsPanel;
	TLabel *Label27;
	TStringGrid *NewLeadsSG;
	TPanel *ActiveLeadsPanel;
	TLabel *Label28;
	TStringGrid *ActiveLeadsSG;
	TPanel *ProposalSentPanel;
	TLabel *Label29;
	TStringGrid *ProposalSentLeadsSG;
	TPanel *ClosedPanel;
	TLabel *Label30;
	TStringGrid *ClosedLeadsSG;
	TTabSheet *SalesTab;
	TPanel *Panel6;
	TLabel *Label23;
	TVirtualImage *VirtualImage4;
	TRelativePanel *ProposalsRelativePanel;
	TSearchBox *SalesSearchBox;
	TSpeedButton *CancelProposalButton;
	TSpeedButton *CompleteProposalButton;
	TStringGrid *ProposalStringGrid;
	TBindNavigator *BindNavigator3;
	TTabSheet *MarketingTab;
	TPanel *Panel3;
	TLabel *Label2;
	TVirtualImage *VirtualImage5;
	TRelativePanel *MarketingRelativePanel;
	TSearchBox *EmailsSearchBox;
	TSpeedButton *ExportEmailsButton;
	TStringGrid *StringGrid2;
	TTabSheet *CalendarTab;
	TCalendarView *CalendarView1;
	TPanel *Panel4;
	TLabel *Label3;
	TVirtualImage *VirtualImage6;
	TTabSheet *UsersTab;
	TPanel *Panel8;
	TLabel *Label25;
	TVirtualImage *VirtualImage7;
	TRelativePanel *UsersRelativePanel;
	TSearchBox *SearchBox7;
	TSpeedButton *CreateUserButton;
	TSpeedButton *RemoveUserButton;
	TStringGrid *UsersSG;
	TBindNavigator *BindNavigator5;
	TTitleBarPanel *TitleBarPanel1;
	TComboBox *UsernameComboBox;
	TComboBox *VCLStylesCB;
	TBindSourceDB *LeadsBindNewSourceDB;
	TBindingsList *BindingsList1;
	TLinkGridToDataSource *LinkGridToDataSourceUsersBindSourceDB;
	TLinkGridToDataSource *LinkGridToDataSourceBindSourceDB5;
	TLinkListControlToField *LinkListControlToField1;
	TLinkGridToDataSource *LinkGridToDataSourceBindSourceDB4;
	TLinkGridToDataSource *LinkGridToDataSourceLeadsBindActiveSourceDB;
	TLinkGridToDataSource *LinkGridToDataSourceLeadsBindClosedSourceDB;
	TLinkGridToDataSource *LinkGridToDataSourceAcctBindSourceDB;
	TLinkGridToDataSource *LinkGridToDataSourceLeadsBindProposalSentSourceDB;
	TLinkPropertyToField *LinkPropertyToFieldCaption;
	TLinkPropertyToField *LinkPropertyToFieldCaption2;
	TLinkPropertyToField *LinkPropertyToFieldCaption3;
	TLinkPropertyToField *LinkPropertyToFieldCaption4;
	TLinkPropertyToField *LinkPropertyToFieldCaption5;
	TLinkPropertyToField *LinkPropertyToFieldCaption6;
	TOpenDialog *ImportLeadsDialog;
	TSaveDialog *ExportLeadsDialog;
	TBindSourceDB *UsersBindSourceDB;
	TBindSourceDB *ProposalBindSourceDB;
	TBindSourceDB *AcctBindSourceDB;
	TBindSourceDB *EmailsBindSourceDB;
	TSaveDialog *SaveEmailsDialog;
	TBindSourceDB *LeadsBindActiveSourceDB;
	TBindSourceDB *LeadsBindSourceDB;
	TBindSourceDB *LeadsBindProposalSentSourceDB;
	TBindSourceDB *LeadsBindClosedSourceDB;
	TVirtualImageList *VirtualImageList1;
	TImageCollection *ImageCollection1;
	TSaveDialog *ExportAcctsDialog;
	TBindSourceDB *NewTotalBindSourceDB;
	TBindSourceDB *ActiveTotalBindSourceDB;
	TBindSourceDB *ProposalTotalBindSourceDB;
	TBindSourceDB *ClosedTotalBindSourceDB;
	TBindSourceDB *InactiveTotalBindSourceDB;
	TBindSourceDB *AllTotalBindSourceDB;
	TTabSheet *ReportsTab;
	TScrollBox *ScrollBox1;
	TCategoryPanelGroup *CategoryPanelGroup1;
	TfrxReport *frxReport1;
	TStringGrid *StringGrid1;
	TCategoryPanel *CategoryPanel1;
	TPanel *Panel1;
	TPanel *Panel9;
	TPanel *Panel10;
	TPanel *Panel11;
	TCategoryPanel *CategoryPanel2;
	TPanel *Panel12;
	TPanel *Panel13;
	TPanel *Panel14;
	TPanel *Panel15;
	TPanel *Panel16;
	TPanel *Panel17;
	TPanel *Panel18;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton40;
	TfrxUserDataSet *frxUserDataSet1;
	TfrxPDFExport *frxPDFExport1;
	TCategoryPanel *CategoryPanel3;
	TPanel *Panel19;
	TPanel *Panel20;
	TPanel *Panel21;
	TPanel *Panel22;
	TPanel *Panel23;
	TPanel *Panel24;
	TCategoryPanel *CategoryPanel4;
	TPanel *Panel25;
	TCategoryPanel *CategoryPanel5;
	TPanel *Panel26;
	TSearchBox *SearchBox1;
	TfrxReport *frxReport2;
	TfrxUserDataSet *frxUserDataSet2;
	TfrxReport *frxReport3;
	TfrxUserDataSet *frxUserDataSet3;
	TButton *Button1;
	TfrxUserDataSet *frxUserDataSet4;
	TImageList *ImageList1;
	TListBox *ListBox1;
	TBindSourceDB *BindSourceDB1;
	TLinkGridToDataSource *LinkGridToDataSourceLeadsBindNewSourceDB;
	void __fastcall RemoveAcctButtonClick(TObject *Sender);
	void __fastcall CreateAcctButtonClick(TObject *Sender);
	void __fastcall ExportAcctsButtonClick(TObject *Sender);
	void __fastcall ExportLeadsButtonClick(TObject *Sender);
	void __fastcall ViewLeadButtonClick(TObject *Sender);
	void __fastcall CreateLeadButtonClick(TObject *Sender);
	void __fastcall CancelProposalButtonClick(TObject *Sender);
	void __fastcall CompleteProposalButtonClick(TObject *Sender);
	void __fastcall ExportEmailsButtonClick(TObject *Sender);
	void __fastcall RemoveUserButtonClick(TObject *Sender);
	void __fastcall CreateUserButtonClick(TObject *Sender);
	void __fastcall AcctSearchBoxKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall CalendarView1DrawDayItem(TObject *Sender, TDrawViewInfoParams *DrawParams,
		  TCellItemViewInfo *CalendarViewViewInfo);
	void __fastcall PageControlChange(TObject *Sender);
	void __fastcall SalesSearchBoxKeyPress(TObject *Sender, System::WideChar &Key);
	//void __fastcall SplitViewClosing(TObject *Sender);
	//void __fastcall SplitViewOpening(TObject *Sender);
	void __fastcall AccountsTabResize(TObject *Sender);
	void __fastcall UsersTabResize(TObject *Sender);
	void __fastcall UsernameComboBoxChange(TObject *Sender);
	void __fastcall UsernameComboBoxKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall UsersRelativePanelResize(TObject *Sender);
	void __fastcall VCLStylesCBChange(TObject *Sender);
	void __fastcall VCLStylesCBKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall MenuVirtualImageClick(TObject *Sender);
	void __fastcall AcctsRelativePanelResize(TObject *Sender);
	void __fastcall ProposalSentLeadsSGEnter(TObject *Sender);
	void __fastcall ActiveLeadsSGEnter(TObject *Sender);
	void __fastcall NewLeadsSGEnter(TObject *Sender);
	void __fastcall ClosedLeadsSGEnter(TObject *Sender);
	void __fastcall NewLeadsSGDragDrop(TObject *Sender, TObject *Source, int X, int Y);
	void __fastcall NewLeadsSGDragOver(TObject *Sender, TObject *Source, int X, int Y,
		  TDragState State, bool &Accept);
	void __fastcall NewLeadsSGDblClick(TObject *Sender);
	void __fastcall ProposalsRelativePanelResize(TObject *Sender);
	void __fastcall DashboardButtonClick(TObject *Sender);
	void __fastcall LeadsRelativePanelResize(TObject *Sender);
	void __fastcall LeadsSearchBoxKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall MarketingRelativePanelResize(TObject *Sender);
	void __fastcall NewLeadsSGMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall EmailsSearchBoxKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall frxUserDataSet1GetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall SpeedButton40Click(TObject *Sender);
	void __fastcall frxUserDataSet1CheckEOF(TObject *Sender, bool &Eof);
	void __fastcall frxUserDataSet2GetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall frxUserDataSet2CheckEOF(TObject *Sender, bool &Eof);
	void __fastcall SearchBox1Change(TObject *Sender);
	void __fastcall StringGrid1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall frxUserDataSet4CheckEOF(TObject *Sender, bool &Eof);
	void __fastcall frxUserDataSet4First(TObject *Sender);
	void __fastcall frxUserDataSet4Next(TObject *Sender);
	void __fastcall frxUserDataSet4GetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall ListView1SelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall ListBox1DrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall ListBox1Click(TObject *Sender);

private:	// User declarations
	bool FRanOnce;
    String CurrentUsername;
	//void __fastcall AppIdle( TObject* Sender, bool& Done );
	void __fastcall RefreshGrids();
	//void __fastcall UpdateNavButtons();

	// Variables for the selected and default colors
	static TPanel* SelectedPanel; // Declare as a static member of the class
	const TColor clSelected = TColor(0x00FFCCAA); // Example color
	const TColor clDefault = clBtnFace; // Default color
	static const TColor clHover;

	// Method declarations for updating panel styles
	void ResetPanelsAppearance();
	void __fastcall AnyPanelClick(TObject *Sender);
	// above
	int FCurrentRow;
	int FSummaryCurrentRow;
	int FSelectedRow;
	int FDetailCurrentColumn;

	// search
	std::vector<std::vector<String>> OriginalData;

	std::vector<std::vector<String>> FDetailData;
	int FDetailCurrentRow;
	TWndMethod OldListViewWndProc;

	std::unordered_map<String, int> menuItemImageMap;
	// -----------------------------------------------------
	void ChangeVCLStyle(const String& styleName);
	void RefreshForms();
	bool DraftProposalFormVisible;
    bool ProposalFormVisible;
	bool LeadsFormVisible;
	// -----------------------------------------------------

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
	// -----
	__fastcall TMainForm::~TMainForm();
	// ----
	void TMainForm::SetupPanelClickHandlers();
	void TMainForm::DisplayProfitAndLoss();
	void TMainForm::PrepareUserDataSet();
	void TMainForm::ClearAndResetStringGrid(int headerRows, int dataRows, int colCount);
	void TMainForm::DisplaySummaryInformation();
	void TMainForm::SetupPanelClickAndMouseHandlers();
	void UpdatePanelStyle(TPanel* Panel, bool Selected, bool Hovered = false);
	void __fastcall TMainForm::PanelMouseLeave(TObject *Sender);
	void __fastcall TMainForm::PanelMouseEnter(TObject *Sender);
	// search
	void LoadDataIntoGrid();
	void TMainForm::CaptureOriginalData();
	void SearchInStringGrid(const String& searchText);
	void FilterStringGrid(const String &searchTerm);
	void __fastcall TMainForm::FormCreate3(TObject *Sender);
	void TMainForm::ResetGridToOriginalData();
	// above
	void DisplayDetailInformation(int leadID);
	void TMainForm::PrepareDataSetForReport(bool detailedReport);
	void TMainForm::UpdateOriginalDataToDataset(bool generateDetailedReport);
	void TMainForm::UpdatePanelVisibility();

	// represhing the grid
	void __fastcall TMainForm::CompleteRefreshAction();

	// load from the database the hamburger menu
	//void __fastcall TMainForm::LoadMenuIntoListView();
	void __fastcall TMainForm::ListView1CustomDrawItem(TCustomListView *Sender, TListItem *Item,
		  TCustomDrawState State, bool &DefaultDraw);
	//void __fastcall ListViewWndProc(Messages::TMessage &Message);
	void TMainForm::SetupListViewColumns();
	void __fastcall TMainForm::FormPaint(TObject *Sender);
	void LoadMenuIntoListBox();
	int TMainForm::DetermineImageIndexForItem(const String& itemName);
	//void TMainForm::PopulateImageMap();
	//void HideListViewScrollBars(TListView *ListView);
	//void __fastcall TMainForm::LoadMenuFromDatabase();
	//TMenuItem* __fastcall FindMenuItemByID(TMainMenu* MainMenu, int ID);
	//TMenuItem* __fastcall FindMenuItemInSubMenus(TMenuItem* ParentItem, int ID);
	//void __fastcall MenuItemClickHandler(TObject *Sender);
	// ----------------------------------------------------------
	void __fastcall RefreshFormsPublic();
	void TMainForm::CloseSecondaryForms();
	void TMainForm::ReopenAllSecondaryForms();
	void TMainForm::CloseAllSecondaryForms();
	void __fastcall TMainForm::ExitButtonClick(TObject *Sender);
	void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose);
	void TMainForm::RefreshLeadsGrid();
	void TMainForm::PopulateStringGridFromDataset(TFDQuery* Query, TStringGrid* Grid);

	//int TMainForm::GetLeadIdFromSelectedRow(TStringGrid* grid);
	int TMainForm::GetRecordCount(String status);
	void TMainForm::RefreshAccountGrid();
    void __fastcall TMainForm::FormShow(TObject *Sender);
	void PopulateDBGrid();
    String GetCurrentUsername();
};

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
