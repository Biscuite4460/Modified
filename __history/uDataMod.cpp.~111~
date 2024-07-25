//---------------------------------------------------------------------------


#pragma hdrstop

#include "uDataMod.h"
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
#include <FireDAC.Phys.Oracle.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"
#define DB_FILENAME L"C:/Users/hamoz/Documents/w10crmdemocpp.sdb"
extern TDM *DM;
TDM *DM;
//---------------------------------------------------------------------------
__fastcall TDM::TDM(TComponent* Owner)
	: TDataModule(Owner)
{
	FDPhysOracleDriverLink1 = new TFDPhysOracleDriverLink(this);
	FDPhysOracleDriverLink1->DriverID = "Ora";
	//FDPhysOracleDriverLink1->VendorLib = "C:\\Users\\hamoz\\OneDrive\\Desktop\\WINDOWS.X64_193000_db_home\\oci\\include";
	LeadsFDMemTable->FieldDefs->Clear();
	LeadsFDMemTable->FieldDefs->Add("LeadId", ftInteger, 0, false);
	LeadsFDMemTable->FieldDefs->Add("Name", ftString, 100, false);
	LeadsFDMemTable->FieldDefs->Add("User", ftString, 255, true);
}
//---------------------------------------------------------------------------
__fastcall TDM::~TDM()
{
	delete FDPhysOracleDriverLink1;
	CleanupMemoryTables();
}

TDatabaseType TDM::GetDatabaseType() {
	return FDBConfig.Type;
}

void TDM::InitializeTable(TFDTable *ATable, TFDMemTable*AMemTable) {
    ATable->FieldDefs->Clear();
    if (FDBConfig.Type == dtSQLite) {
        ATable->FieldDefs->Assign(AMemTable->FieldDefs);
        ATable->CreateTable(false);
        ATable->CopyDataSet(AMemTable, TFDCopyDataSetOptions() << coStructure << coRestart << coAppend);
    } else if (FDBConfig.Type == dtOracle) {
        if (!FDConnection1->Connected) {
            ShowMessage("Database connection is not established.");
            return;
        }

        TFDQuery* checkTableQuery = new TFDQuery(nullptr);
        checkTableQuery->Connection = FDConnection1;
        try {
            checkTableQuery->SQL->Text = "SELECT column_name, data_type, char_length FROM user_tab_columns WHERE table_name = :TableName";
            checkTableQuery->ParamByName("TableName")->AsString = ATable->TableName.UpperCase();
            checkTableQuery->Open();

            if (!checkTableQuery->IsEmpty()) {
                ValidateOracleTableFields(checkTableQuery, AMemTable, ATable);
                ATable->Open();
                if (ATable->Active && ATable->RecordCount > 0) {
                    ShowMessage("Oracle table " + ATable->TableName + " has " + IntToStr(ATable->RecordCount) + " records.");
                } else {
                    ShowMessage("Oracle table " + ATable->TableName + " is empty.");
                }
            } else {
                ShowMessage("Table " + ATable->TableName + " does not exist in the Oracle database.");
            }
        } catch (const Exception &E) {
            ShowMessage("Error querying Oracle table structure: " + E.Message);
        }
        delete checkTableQuery;
    }
}


void TDM::ValidateOracleTableFields(TFDQuery* Query, TFDMemTable* MemTable, TFDTable* Table) {
    if (!Query || !Query->Active || Query->IsEmpty()) {
        throw Exception("Query is not properly initialized or has no data.");
    }

	for (int i = 0; i < MemTable->FieldDefs->Count; ++i) {
        TFieldDef* memFieldDef = MemTable->FieldDefs->Items[i];

		Query->First();
        bool found = false;
        while (!Query->Eof && !found) {
			String colName = Query->FieldByName("column_name")->AsString;
            String dataType = Query->FieldByName("data_type")->AsString;
            int charLength = Query->FieldByName("char_length")->AsInteger;

            if (colName.CompareIC(memFieldDef->Name) == 0) {
				found = true;
				if (!FieldTypesMatch(memFieldDef->DataType, dataType)) {
					//throw Exception("Data type mismatch for column " + memFieldDef->Name + ": expected " + dataType + ", found " + DataTypeToStr(memFieldDef->DataType));
				}
                if (memFieldDef->Size > 0 && memFieldDef->Size != charLength) {
					throw Exception("Character length mismatch for column " + memFieldDef->Name + ": expected " + IntToStr(charLength) + ", found " + IntToStr(memFieldDef->Size));
				}
            }

			Query->Next();
		}

		if (!found) {
			throw Exception("Column " + memFieldDef->Name + " not found in Oracle table.");
		}
	}
}

bool TDM::FieldTypesMatch(TFieldType delphiFieldType, const String& oracleType) {
	switch (delphiFieldType) {
		case ftString:
			return oracleType == "VARCHAR2" || oracleType == "CHAR";
		case ftLargeint:
		case ftInteger:
			return oracleType == "NUMBER";
		case ftFloat:
			return oracleType == "FLOAT";
		case ftDateTime:
			return oracleType == "DATE" || oracleType == "TIMESTAMP";
		default:
			return false;
	}
}

String TDM::DataTypeToStr(TFieldType fieldType) {
	switch (fieldType) {
		case ftString: return "VARCHAR2/CHAR";
		case ftLargeint:
		case ftInteger: return "NUMBER";
		case ftFloat: return "FLOAT";
		case ftDateTime: return "DATE/TIMESTAMP";
		default: return "Unknown";
	}
}

struct DatabaseConfig1 {
	TDatabaseType Type;
	String Database;
	String Username;
	String Password;
	String Server;
};

void TDM::SetDatabaseConfig(TDatabaseType dbType, const String &database,
						   const String &user, const String &password,
						   const String &server) {
	FDBConfig.Type = dbType;
	FDBConfig.Database = database;
	FDBConfig.Username = user;
	FDBConfig.Password = password;
	FDBConfig.Server = server;
}

void __fastcall TDM::InitializeDatabase() {
  try {
	if (FDBConfig.Type == dtSQLite) {
	  FDConnection1->DriverName = "SQLite";
	  FDConnection1->Params->Values[L"Database"] = DB_FILENAME;
	  FDConnection1->Open();
	  FDLocalSQL1->Active = true;

	  if (!FDConnection1->Connected) {
		ShowMessage("SQLite database connection not established.");
		return;
	  }

	  if (!TFile::Exists(DB_FILENAME)) {
		try {
		  FDConnection1->Open();
		  InitializeTable(DocsFDTable, DocsFDMemTable);
		  InitializeTable(LeadsFDTable, LeadsFDMemTable);
		  InitializeTable(AcctFDTable, AcctFDMemTable);
		  InitializeTable(UsersFDTable, UsersFDMemTable);
		  InitializeTable(ProposalsFDTable, ProposalFDMemTable);
		} __finally {
		}
	  }
	  SetTableNames();
	  OpenAllTables();
	  OpenAllQueries();

	} else if (FDBConfig.Type == dtOracle) {
	  FDLocalSQL1->Active = false;
	  SetupOracleConnection(FDBConfig.Username, FDBConfig.Password);

	  if (!FDConnection1->Connected) {
		ShowMessage("Oracle database connection not established.");
		return;
	  }

	  SetTableNames();
	  OpenAllTables();
	  OpenAllQueries();

	  SetupOracleLeadsQueries();
	  LinkDataSources();
	}

	if (UsersFDMemTable && UsersFDMemTable->Active && UsersFDMemTable->FindField("Username")) {
	  SetUser(UsersFDMemTable->FieldByName("Username")->AsString);
	}

  } catch (const Exception &E) {
	ShowMessage("An exception occurred during database initialization: " + E.Message);
  }
}

void TDM::SetupOracleConnection(String username, String password) {
	if (!FDConnection1) {
		ShowMessage("FDConnection1 is not initialized.");
		return;
	}
	FDConnection1->Params->Clear();
	FDConnection1->DriverName = "Ora";
	FDConnection1->Params->Add("User_Name=" + username);
	FDConnection1->Params->Add("Password=" + password);
	FDConnection1->Params->Add("Database=lszhhrkltyacm7p4_high");
	FDConnection1->Params->Add("WALLET_LOCATION = (SOURCE = (METHOD = file) (METHOD_DATA = (DIRECTORY=C:\\Users\\hamoz\\OneDrive\\Desktop\\Wallet_LSZHHRKLTYACM7P4)))");
	FDConnection1->LoginPrompt = false;
	try {
		FDConnection1->Open();
		if (FDConnection1->Connected)
			ShowMessage("Oracle connection established successfully.");
		else
			ShowMessage("Failed to establish Oracle connection.");
	} catch (const Exception &E) {
		ShowMessage("Oracle connection error: " + E.Message);
	}
}

void TDM::SetTableNames() {
  LeadsFDTable->TableName = "Leads";
  AcctFDTable->TableName = "Accounts";
  UsersFDTable->TableName = "Users";
  DocsFDTable->TableName = "Docs";
  ProposalsFDTable->TableName = "Proposals";
}

void TDM::OpenAllTables() {
  OpenTable(DocsFDTable);
  OpenTable(LeadsFDTable);
  OpenTable(AcctFDTable);
  OpenTable(UsersFDTable);
  OpenTable(ProposalsFDTable);
}

void TDM::OpenAllQueries()
{
	OpenQuery(FDLeadsQueryNew);
}

void __fastcall TDM::OpenTable(TFDTable* ATable)
{
    try {
        ATable->Open();
    } catch (Exception &e) {
        ShowMessage("Error opening " + ATable->Name + ": " + e.Message);
	}
}

void __fastcall TDM::OpenQuery(TFDQuery* AQuery)
{
	try {
		if (!AQuery->Active) {
			AQuery->Open();
		}
	} catch (Exception &e) {
		ShowMessage("Error opening " + AQuery->Name + ": " + e.Message);
	}
}

void __fastcall TDM::CleanupMemoryTables()
{
	if (LeadsFDMemTable) {
		delete LeadsFDMemTable;
		LeadsFDMemTable = nullptr;
	}
	if (AcctFDMemTable) {
		delete AcctFDMemTable;
		AcctFDMemTable = nullptr;
	}
	if (UsersFDMemTable) {
		delete UsersFDMemTable;
		UsersFDMemTable = nullptr;
	}
	if (DocsFDMemTable) {
		delete DocsFDMemTable;
		DocsFDMemTable = nullptr;
	}
	if (ProposalFDMemTable) {
		delete ProposalFDMemTable;
		ProposalFDMemTable = nullptr;
	}
}

void __fastcall TDM::CompleteProposal( int ALeadId )
{
  DM->UpdateProposalStatus( ALeadId, L"Accepted" );
}


void __fastcall TDM::UpdateProposalStatus( int ALeadId, const String AStatus )
{
  if ( ProposalsFDTable->Locate( L"LeadId", VarArrayOf(OPENARRAY(Variant, ( ALeadId )) ), TLocateOptions() ) )
  {
	ProposalsFDTable->Edit();
	ProposalsFDTable->FieldByName( L"Status" )->AsString = AStatus;
	if ( AStatus == L"Accepted" )
	  ProposalsFDTable->FieldByName( L"DateCompleted" )->AsDateTime = Now();
	ProposalsFDTable->Post();
	FDProposalsQuery->Close();
	FDProposalsQuery->Open();
	FDProposalsQuery->Locate( L"ProposalId", VarArrayOf(OPENARRAY(Variant, ( ProposalsFDTable->FieldByName( L"ProposalId" )->AsInteger ))), TLocateOptions() );
  }
}

void __fastcall TDM::SetUserQuery( const String AUsername, TFDQuery *AQuery )
{
  AQuery->Close();
  AQuery->ParamByName(L"Username")->AsString = AUsername;
  AQuery->Open();
}

void __fastcall TDM::SetUser( const String AUsername )
{
  SetUserQuery( AUsername, FDEmailsQuery );
  SetUserQuery( AUsername, FDLeadsQueryAll );
  SetUserQuery( AUsername, FDLeadsQueryNew );
  SetUserQuery( AUsername, FDProposalsQuery );
  SetUserQuery( AUsername, FDDocsQuery );
  SetUserQuery( AUsername, FDLeadsQueryActive );
  SetUserQuery( AUsername, FDLeadsQueryProposalSent );
  SetUserQuery( AUsername, FDLeadsQueryClosed );
  SetUserQuery( AUsername, FDQueryNewTotal );
  SetUserQuery( AUsername, FDQueryActiveTotal );
  SetUserQuery( AUsername, FDQueryProposalTotal );
  SetUserQuery( AUsername, FDQueryClosedTotal );
  SetUserQuery( AUsername, FDQueryTotal );
  SetUserQuery( AUsername, FDQueryInactiveTotal );
}

void __fastcall TDM::LeadsFDTableAfterScroll( TDataSet *DataSet )
{
  FDDocsQuery->Close();
  FDDocsQuery->ParamByName( L"LeadId" )->AsInteger = LeadsFDTable->FieldByName( L"LeadId" )->AsInteger;
  FDDocsQuery->Open();
}

void __fastcall TDM::ExportEmails( const String AFilename )
{
  FDBatchMoveTextWriter1->FileName = AFilename;
  FDBatchMove1->Execute();
}

void __fastcall TDM::SearchQuery( const String ASQL, TFDQuery *AQuery )
{
  AQuery->Close();
  AQuery->MacroByName( L"Where" )->AsRaw = ASQL;
  AQuery->Open();
}

void __fastcall TDM::FDLeadsQueryNewAfterScroll( TDataSet *DataSet )
{
  LeadsFDTable->Locate( L"LeadId", VarArrayOf(OPENARRAY(Variant, ( DataSet->FieldByName( L"LeadId" )->AsInteger ))), TLocateOptions() );
}

void __fastcall TDM::SearchAccounts( const String ASearch )
{
  SearchQuery( (!ASearch.IsEmpty() ? L"UPPER(AccountName) LIKE '%" + UpperCase( ASearch ) + L"%'" : L"" ), FDAccountsQuery );
}

void __fastcall TDM::SearchLeadsSubQuery( const String ASearch, TFDQuery *AQuery )
{
  SearchQuery( (!ASearch.IsEmpty() ? L"AND UPPER(Name) LIKE '%" + UpperCase( ASearch ) + L"%' OR UPPER(AccountName) LIKE '%" + UpperCase( ASearch ) + L"%' OR UPPER(OfficePhone) LIKE '%" + UpperCase( ASearch ) + L"%' OR UPPER(Email) LIKE '%" + UpperCase( ASearch ) + L"%'" : L""), AQuery );
}

// modified for Oracle - not displaying problem (leads)
void __fastcall TDM::SearchLeads(const String ASearch)
{
	if (ASearch.IsEmpty()) {
		ShowMessage("Search is empty, reloading all queries.");
		ReloadAllQueries();
	} else {
		ShowMessage("Applying search filter.");
		SearchLeadsSubQuery(ASearch, FDLeadsQueryNew);
		SearchLeadsSubQuery(ASearch, FDLeadsQueryActive);
		SearchLeadsSubQuery(ASearch, FDLeadsQueryProposalSent);
		SearchLeadsSubQuery(ASearch, FDLeadsQueryClosed);
	}
}

void __fastcall TDM::ReloadAllQueries()
{
	FDLeadsQueryNew->Close();
	FDLeadsQueryNew->SQL->Clear();
	FDLeadsQueryNew->SQL->Add("SELECT * FROM Leads WHERE Status = 'New'");
	FDLeadsQueryNew->Open();
	FDLeadsQueryActive->Close();
	FDLeadsQueryActive->SQL->Clear();
	FDLeadsQueryActive->SQL->Add("SELECT * FROM Leads WHERE Status = 'Active'");
	FDLeadsQueryActive->Open();
	FDLeadsQueryProposalSent->Close();
	FDLeadsQueryProposalSent->SQL->Clear();
	FDLeadsQueryProposalSent->SQL->Add("SELECT * FROM Leads WHERE Status = 'Proposal Sent'");
	FDLeadsQueryProposalSent->Open();
	FDLeadsQueryClosed->Close();
	FDLeadsQueryClosed->SQL->Clear();
	FDLeadsQueryClosed->SQL->Add("SELECT * FROM Leads WHERE Status = 'Closed'");
	FDLeadsQueryClosed->Open();
}

void TDM::ReloadAccountQueries()
{
	FDAccountsQuery->Close();
	FDAccountsQuery->SQL->Clear();
	FDAccountsQuery->SQL->Add("SELECT * FROM Accounts");
	FDAccountsQuery->Open();
}

void TDM::ReloadProposalsQuaeries()
{
	   FDProposalsQuery->Close();
	   FDProposalsQuery->SQL->Clear();
	   FDProposalsQuery->SQL->Add("SELECT * FROM Proposals");
	   FDProposalsQuery->Open();
}

void TDM::ReloadLeadsQuery()
{
	FDEmailsQuery->Close();
	FDEmailsQuery->SQL->Clear();
	FDEmailsQuery->SQL->Add("SELECT Email, Name FROM Leads WHERE Status <> 'Inactive'");
	//FDEmailsQuery->ParamByName("Username")->AsString = username;
	FDEmailsQuery->Open();
}

void __fastcall TDM::SearchProposals( const String ASearch )
{
  SearchQuery( (!ASearch.IsEmpty() ? L"AND UPPER(ProposalName) LIKE '%" + UpperCase( ASearch ) + L"%'" : L""), FDProposalsQuery );
}


void __fastcall TDM::SearchEmails( const String ASearch )
{
  SearchQuery( (!ASearch.IsEmpty() ? L"AND UPPER(Email) LIKE '%" + UpperCase( ASearch ) + L"%'" : L"" ), FDEmailsQuery );
}

//---------------------------------------------------------------------------
String TDM::GetDbColumnName(const String &gridHeader) {
	// Map the grid headers to the database column names
	if (gridHeader == "Lead ID") return "LeadID";
	if (gridHeader == "Proposal ID") return "ProposalID";
	if (gridHeader == "Date Created") return "DateCreated";
	return gridHeader;
}

String TDM::GetFieldType(const String &headerName) {
	switch (FDBConfig.Type) {
		case dtSQLite:
			if (headerName == "LeadID" || headerName == "AccountID" || headerName == "UserID")
				return "INTEGER PRIMARY KEY AUTOINCREMENT";
			else if (headerName == "Value")
				return "REAL";
			else if (headerName == "DateCreated" || headerName == "DateContacted" || headerName == "DateCompleted")
				return "DATETIME";
			else if (headerName == "DOCUMENT" || headerName == "PROPOSAL")
				return "BLOB";
			else
				return "VARCHAR(100)";
		case dtOracle:
			if (headerName == "LeadID" || headerName == "AccountID" || headerName == "UserID")
				return "NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY";
			else if (headerName == "Value")
				return "FLOAT";
			else if (headerName == "DateCreated" || headerName == "DateContacted" || headerName == "DateCompleted")
				return "DATE";
			else if (headerName == "DOCUMENT" || headerName == "PROPOSAL")
				return "BLOB";
			else
				return "VARCHAR2(100)";
		default:
			return "VARCHAR(100)";  // Default case to handle unexpected values
	}
}

void TDM::CreateTableFromGrid(const String &tableName, TStringGrid *grid) {
	FDQuery1->Connection = FDConnection1;
	ShowMessage("Starting table creation for: " + tableName);

    String createTableSQL;
    if (FDBConfig.Type == dtSQLite) {
        createTableSQL = "CREATE TABLE IF NOT EXISTS \"" + tableName + "\" (ID INTEGER PRIMARY KEY AUTOINCREMENT, Data TEXT)";
	} else if (FDBConfig.Type == dtOracle) {
		createTableSQL = "BEGIN EXECUTE IMMEDIATE 'CREATE TABLE \"" + tableName + "\" (ID NUMBER GENERATED BY DEFAULT AS IDENTITY, Data VARCHAR2(255))'; EXCEPTION WHEN OTHERS THEN NULL; END;";
    }

    ShowMessage("Executing SQL: " + createTableSQL);

    FDQuery1->SQL->Text = createTableSQL;
    FDQuery1->ExecSQL();

    ShowMessage("Table creation completed for: " + tableName);
}


void TDM::InsertDataFromGrid(const String &tableName, TStringGrid *grid) {
    FDQuery1->Connection = FDConnection1;

    for (int rowIndex = 1; rowIndex < grid->RowCount; ++rowIndex) {
		String leadID = grid->Cells[0][rowIndex];

        FDQuery1->SQL->Text = "SELECT COUNT(*) FROM \"" + tableName + "\" WHERE LeadID = :LeadID";
        FDQuery1->ParamByName("LeadID")->AsString = leadID;
        FDQuery1->Open();
		int count = FDQuery1->Fields->FieldByName("COUNT(*)")->AsInteger;
        FDQuery1->Close();

		if (count == 0) {
            String insertSQL = "INSERT INTO \"" + tableName + "\" (";
            String valuesSQL = "VALUES (";
            bool firstCol = true;

            for (int colIndex = 0; colIndex < grid->ColCount; ++colIndex) {
				if (grid->Cells[colIndex][0] == "LeadID" && FDBConfig.Type == dtOracle) continue;

                if (!firstCol) {
                    insertSQL += ", ";
                    valuesSQL += ", ";
                }

                String dbColumnName = GetDbColumnName(grid->Cells[colIndex][0]);
                insertSQL += "\"" + dbColumnName + "\"";
				valuesSQL += ":" + dbColumnName;
                firstCol = false;
            }

            insertSQL += ") " + valuesSQL + ")";
            FDQuery1->SQL->Text = insertSQL;

            for (int colIndex = 0; colIndex < grid->ColCount; ++colIndex) {
                if (grid->Cells[colIndex][0] == "LeadID" && FDBConfig.Type == dtOracle) continue;
                String dbColumnName = GetDbColumnName(grid->Cells[colIndex][0]);
                FDQuery1->ParamByName(dbColumnName)->AsString = grid->Cells[colIndex][rowIndex];
            }

            FDQuery1->ExecSQL();
        }
    }
}

//---------------------------------------------------------------------------

void TDM::SetupOracleLeadsQueries() {
	if (!FDLeadsQueryNew) {
		FDLeadsQueryNew = new TFDQuery(nullptr);
		FDLeadsQueryNew->Connection = FDConnection1;
		FDLeadsQueryNew->SQL->Text = "SELECT * FROM Leads WHERE Status = 'New' ORDER BY DateCreated DESC";
		FDLeadsQueryNew->Open();
	}
	if (!FDLeadsQueryActive) {
		FDLeadsQueryActive = new TFDQuery(nullptr);
		FDLeadsQueryActive->Connection = FDConnection1;
		FDLeadsQueryActive->SQL->Text = "SELECT * FROM Leads WHERE Status = 'Active' ORDER BY DateContacted DESC";
		FDLeadsQueryActive->Open();
	}
	if (!FDLeadsQueryProposalSent) {
		FDLeadsQueryProposalSent = new TFDQuery(nullptr);
		FDLeadsQueryProposalSent->Connection = FDConnection1;
		FDLeadsQueryProposalSent->SQL->Text = "SELECT * FROM Leads WHERE Status = 'Proposal Sent' ORDER BY DateContacted DESC";
		FDLeadsQueryProposalSent->Open();
	}
	if (!FDLeadsQueryClosed) {
		FDLeadsQueryClosed = new TFDQuery(nullptr);
		FDLeadsQueryClosed->Connection = FDConnection1;
		FDLeadsQueryClosed->SQL->Text = "SELECT * FROM Leads WHERE Status = 'Closed' ORDER BY DateContacted DESC";
		FDLeadsQueryClosed->Open();
	}
}

//---------------------------------------------------------------------------

void TDM::LinkDataSources() {
  DataSourceNew->DataSet = FDLeadsQueryNew;
  DataSourceActive->DataSet = FDLeadsQueryActive;
  DataSourceProposalSent->DataSet = FDLeadsQueryProposalSent;
  DataSourceClosed->DataSet = FDLeadsQueryClosed;
}

//---------------------------------------------------------------------------
void TDM::ReloadLeadsQuery1(const String& username)
{
	FDLeadsQueryNew->Close();

	FDLeadsQueryNew->SQL->Clear();
	FDLeadsQueryNew->Params->Clear();

	FDLeadsQueryNew->SQL->Add("SELECT * FROM Leads WHERE Status = 'New' AND User = :Username");

	FDLeadsQueryNew->Params->ParamByName("Username")->AsString = username;

	FDLeadsQueryNew->Open();
}
void TDM::ReloadEmailsQuery(const String& username)
{
    FDEmailsQuery->Close();
    FDEmailsQuery->SQL->Clear();
    FDEmailsQuery->Params->Clear();

    // Ensure no syntax errors and correctly named parameters
    FDEmailsQuery->SQL->Add("SELECT Email, Name FROM Leads WHERE Status <> 'Inactive' AND User = :Username");

    FDEmailsQuery->Params->ParamByName("Username")->AsString = username;

    FDEmailsQuery->Open();
}

//---------------------------------------------------------------------------

