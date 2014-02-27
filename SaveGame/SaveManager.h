#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "base64.h"

using namespace std;

class ippSaveManager
{
private:
	static ippSaveManager *s_mInstance;
	string useThisFile;
	bool addOn;
	
	string ConvertInt					( int num );
	bool IsInteger						( string &ss );
	void CreateNewFile					();

public:
	static ippSaveManager* GetInstance	();
	void DropInstance					();

	bool Init							( string fileName );
	
	bool AddCategory					( const string categoryName );
	bool AddInformationInto				( const string information, const string categoryName );
	bool EditThis						( const string target, const string change );

	bool EncryptThis					( const string information );
	bool EncryptThis					( const int information );
	bool Get							( string information );
	int GetInt							( string information );
	
	void ClearAll						();

	bool SaveTo							( string fileName );
	bool GetEverything					();

	ippSaveManager(void);
	~ippSaveManager(void);
};
