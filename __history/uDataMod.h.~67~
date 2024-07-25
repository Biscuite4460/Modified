//---------------------------------------------------------------------------

#ifndef uDataModH
#define uDataModH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.BatchMove.DataSet.hpp>
#include <FireDAC.Comp.BatchMove.hpp>
#include <FireDAC.Comp.BatchMove.Text.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.SQLite.hpp>
#include <FireDAC.Phys.SQLiteDef.hpp>
#include <FireDAC.Phys.SQLiteVDataSet.hpp>
#include <FireDAC.Phys.SQLiteWrapper.Stat.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.ExprFuncs.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.Stan.StorageBin.hpp>
#include <FireDAC.Stan.StorageJSON.hpp>
#include <FireDAC.Stan.StorageXML.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include <Vcl.Grids.hpp>
#include <System.Ioutils.hpp>
#include <System.Classes.hpp>
#include <sysopen.h>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.Oracle.hpp>
#include <Data.DB.hpp>
//#include <sqlite3.h>
//---------------------------------------------------------------------------
enum TDatabaseType { dtSQLite, dtOracle };

struct DatabaseConfig {
    TDatabaseType Type;
    String Database;
    String Username;
    String Password;
    String Server;
};

class TDM : public TDataModule
{
__published:	// IDE-managed Components
	TFDMemTable*LeadsFDMemTable;
	TFDStanStorageBinLink *FDStanStorageBinLink1;
	TFDStanStorageXMLLink *FDStanStorageXMLLink1;
	TFDStanStorageJSONLink *FDStanStorageJSONLink1;
	TFDMemTable *StatusFDMemTable;
	TFDMemTable *AcctFDMemTable;
	TFDMemTable *UsersFDMemTable;
	TFDMemTable *DocsFDMemTable;
	TFDMemTable *ProposalFDMemTable;
	TFDMemTable *ProposalStatusFDMemTable;
	TFDPhysSQLiteDriverLink *FDPhysSQLiteDriverLink1;
	TFDConnection *FDConnection1;
	TFDLocalSQL *FDLocalSQL1;
	TFDQuery *FDEmailsQuery;
	TFDBatchMove *FDBatchMove1;
	TFDBatchMoveDataSetReader *FDBatchMoveDataSetReader1;
	TFDBatchMoveTextWriter *FDBatchMoveTextWriter1;
	TFDQuery *FDAccountsQuery;
	TFDQuery *FDLeadsQueryNew;
	TFDQuery *FDProposalsQuery;
	TFDQuery *FDLeadsQueryActive;
	TFDQuery *FDLeadsQueryProposalSent;
	TFDQuery *FDLeadsQueryClosed;
	TFDMemTable *LineItemsFDMemTable;
	TFDMemTable *DraftProposalFDMemTable;
	TFDQuery *LineItemsTotalQuery;
	TFDQuery *FDQueryNewTotal;
	TFDQuery *FDQueryActiveTotal;
	TFDQuery *FDQueryProposalTotal;
	TFDQuery *FDQueryClosedTotal;
	TFDQuery *FDQueryTotal;
	TFDQuery *FDQueryInactiveTotal;
	TFDTable *LeadsFDTable;
	TFDSQLiteSecurity *FDSQLiteSecurity1;
	TFDTable *DocsFDTable;
	TFDTable *UsersFDTable;
	TFDTable *AcctFDTable;
	TFDTable *ProposalsFDTable;
	TFDQuery *FDDocsQuery;
	TFDQuery *FDLeadsQueryAll;
	TFDQuery *FDQuery1;
	TDataSource *DataSourceNew;
	TDataSource *DataSourceActive;
	TDataSource *DataSourceProposalSent;
	TDataSource *DataSourceClosed;
	TFDQuery *FDQueryTotal21;
	void __fastcall LeadsFDTableAfterScroll(TDataSet *DataSet);
	void __fastcall FDLeadsQueryNewAfterScroll(TDataSet *DataSet);

private:
	DatabaseConfig FDBConfig;
	TFDPhysOracleDriverLink *FDPhysOracleDriverLink1;
public:
  //  modified to choose between Oracle / SQLite
void __fastcall TDM::InitializeDatabase();
bool __fastcall TDM::FieldTypesMatch(TFieldType delphiFieldType, const String &oracleType);
  //  ------------------------------------------
  void __fastcall CompleteProposal( int ALeadId );
  void __fastcall SetUserQuery( const String AUsername, TFDQuery *AQuery );
  void __fastcall UpdateProposalStatus( int ALeadId, const String AStatus );
  void __fastcall ExportEmails( const String AFilename );
  void __fastcall SearchQuery( const String ASQL, TFDQuery *AQuery );
  void __fastcall SearchAccounts( const String ASearch );
  void __fastcall SearchLeadsSubQuery( const String ASearch, TFDQuery *AQuery );
  void __fastcall SearchLeads( const String ASearch );
  void __fastcall SearchProposals( const String ASearch );
  void __fastcall SearchEmails( const String ASearch );
  void __fastcall SetUser( const String AUsername );
  // -------------------------------------------
  void __fastcall TDM::OpenTable(TFDTable* ATable);
  void __fastcall TDM::OpenQuery(TFDQuery* AQuery);
  void __fastcall TDM::CleanupMemoryTables();
  virtual __fastcall ~TDM();
  // -------------------------------------------
	__fastcall TDM(TComponent* Owner);

  // -------------------------------------------

	void CreateTableFromGrid(const String &tableName, TStringGrid *grid);
	void InsertDataFromGrid(const String &tableName, TStringGrid *grid);
	String GetDbColumnName(const String &gridHeader);
  // ------------------------------------------
	void SetDatabaseConfig(TDatabaseType dbType, const String &database,
                           const String &user = "", const String &password = "",
						   const String &server = "");
  // ------------------------------------------
   TDatabaseType GetDatabaseType();
   void TDM::ValidateOracleTableFields(TFDQuery* checkTableQuery, TFDMemTable* AMemTable, TFDTable *ATable);
   void TDM::CreateOracleTable(TFDTable *ATable, TFDMemTable* AMemTable);
   String TDM::OracleFieldType(TFieldDef *fieldDef);
   void TDM::AdjustOracleTableField(TFDTable *ATable, TFieldDef *fieldDef, TFDQuery *query);
// uDataMod.h
	void __fastcall TDM::InitializeTable(TFDTable *ATable, TFDMemTable*AMemTable);
	String TDM::DataTypeToStr(TFieldType fieldType);
//
	void TDM::OpenAllTables();
	void TDM::SetTableNames();
	void TDM::LinkDataSources();
	void TDM::SetupOracleLeadsQueries();
	void TDM::SetupOracleConnection();
	void __fastcall TDM::ReloadAllQueries();
	void TDM::ReloadAccountQueries();
	void TDM::ReloadProposalsQuaeries();
	void ReloadLeadsQuery();
	void TDM::ReloadLeadsQuery1(const String& username);
    String TDM::GetFieldType(const String &headerName);
};

//---------------------------------------------------------------------------
const wchar_t DB_FILENAME[] = L"C:/Users/hamoz/Documents/Employees.s3db";
//const wchar_t DB_PASSWORD[] = L"SecretPassword";
const wchar_t DB_ENCRYPTION[] = L"aes-256";
const wchar_t DB_LEADSTABLE[] = L"Leads";
const wchar_t DB_ACCTSTABLE[] = L"Accounts";
const wchar_t DB_USERSTABLE[] = L"Users";
const wchar_t DB_DOCSTABLE[] = L"Docs";
const wchar_t DB_PROPOSALSTABLE[] = L"Proposals";
extern PACKAGE TDM *DM;
//---------------------------------------------------------------------------
#endif
