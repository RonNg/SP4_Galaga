#include "SaveManager.h"

ippSaveManager * ippSaveManager::s_mInstance = NULL;

ippSaveManager::ippSaveManager()
{
	useThisFile = "";
	addOn = false;
}


ippSaveManager::~ippSaveManager(void)
{
}

string ippSaveManager::ConvertInt( int num )
{
	stringstream number;
	number << num;
	return number.str();
}

bool ippSaveManager::IsInteger( string &ss )
{
	if( ss.empty() || ( ( !isdigit( ss[0] ) ) && ( ss[0] != '-' ) && (ss[0] != '+' ) ) )
	{
		return false;
	}

	char *p;
	strtol( ss.c_str(), &p, 10 );

	return( *p == 0 );
}

ippSaveManager* ippSaveManager::GetInstance()
{
	if( s_mInstance == NULL )
	{
		s_mInstance = new ippSaveManager();
	}

	return s_mInstance;
}

void ippSaveManager::DropInstance()
{
	if( s_mInstance != NULL )
	{
		delete s_mInstance;
		s_mInstance = NULL;
	}
}

bool ippSaveManager::Init( string fileName )
{
	useThisFile = fileName;
	return true;
}

bool ippSaveManager::EncryptThis( const string information )
{
	//	Credit to René Nyffenegger
	//	Website link is http://www.adp-gmbh.ch/cpp/common/base64.html
	if( addOn )
	{
		string tempHold, line;
		ifstream inputFile( useThisFile );
		string decoded = "";
		if( inputFile.is_open() )
		{
			while( !inputFile.eof() )
			{
				getline( inputFile, tempHold );
				decoded += tempHold;
				decoded += "\n";
			}
			inputFile.close();
		}
		else
		{
			printf( "Unable to open file %s to encrypt this %s\n", useThisFile.c_str(), information.c_str() );
			return false;
		}

		string encoded = base64_encode(reinterpret_cast<const unsigned char*>(information.c_str()), information.length());

		ofstream outputFile( useThisFile );
		if( outputFile.is_open() )
		{
			outputFile << decoded;
			outputFile << encoded;
			outputFile.close();
		}
		else
		{
			printf( "Unable to open file %s to encrypt this %s\n", useThisFile.c_str(), information.c_str() );
			return false;
		}
	}
	else
	{
		string encoded = base64_encode(reinterpret_cast<const unsigned char*>(information.c_str()), information.length());

		ofstream myfile( useThisFile );
		if( myfile.is_open() )
		{
			myfile << encoded;
			addOn = true;
			return true;
		}
		else
		{
			printf( "Unable to open file %s to encrypt this %s\n", useThisFile.c_str(), information.c_str() );
			return false;
		}
	}
}

bool ippSaveManager::EncryptThis( const int information )
{
	//	Credit to René Nyffenegger
	//	Website link is http://www.adp-gmbh.ch/cpp/common/base64.html

	string numberString = ConvertInt( information );

	if( addOn )
	{
		string tempHold, line;
		ifstream inputFile( useThisFile );
		string decoded = "";
		if( inputFile.is_open() )
		{
			while( !inputFile.eof() )
			{
				getline( inputFile, tempHold );
				decoded += tempHold;
				decoded += "\n";
			}
			inputFile.close();
		}
		else
		{
			printf( "Unable to open file %s to encrypt this %d\n", useThisFile.c_str(), information );
			return false;
		}

		string encoded = base64_encode(reinterpret_cast<const unsigned char*>(numberString.c_str()), numberString.length());

		ofstream outputFile( useThisFile );
		if( outputFile.is_open() )
		{
			outputFile << decoded;
			outputFile << encoded;
			outputFile.close();
		}
		else
		{
			printf( "Unable to open file %s to encrypt this %d\n", useThisFile.c_str(), information );
			return false;
		}
	}
	else
	{
		string encoded = base64_encode(reinterpret_cast<const unsigned char*>(numberString.c_str()), numberString.length());

		ofstream myfile( useThisFile );
		if( myfile.is_open() )
		{
			myfile << encoded;
			addOn = true;
			return true;
		}
		else
		{
			printf( "Unable to open file %s to encrypt this %d\n", useThisFile.c_str(), information );
			return false;
		}
	}
}

bool ippSaveManager::Get( string information )
{
	int offset, cc = 0;
	bool found = false;
	string line, decoded;
	ifstream myfile( useThisFile );
	if( myfile.is_open() )
	{
		printf( "< - - -Opening file %s- - - >\n", useThisFile.c_str() );
		printf( "Searchin for %s\n\n", information.c_str() );
		while( getline( myfile, line ) && found == false )
		{
			//printf( "This is before decoding <%s>\n", line.c_str() );
			decoded = base64_decode(line);
			//printf( "cc = %d\n", cc++ );
			//printf( "looking at %s\n", decoded.c_str());
			if( ( offset = decoded.find( information, 0 ) ) != string::npos )
			{
				printf( "Found %s ! !\n", information.c_str() );
				getline( myfile, line );
				printf( "Search result: %s\n", base64_decode(line).c_str() );
				found = true;
			}
		}
		if( myfile.eof() )
		{
			if( offset == -1 )
			{
				printf( "Unable to find %s\n", information.c_str() );
			}
			printf( "\n<---End of file--->\n" );
		}
		myfile.close();
		printf( "< - - -Closing file %s- - - >\n", useThisFile.c_str() );
		return true;
	}
	else
	{
		printf( "Unable to open file %s to get this %s\n", useThisFile.c_str(), information.c_str() );
		return false;
	}
}

void ippSaveManager::ClearAll()
{
	addOn = false;
	ofstream myfile( useThisFile );
	if( myfile.is_open() )
	{
		myfile.close();
	}
	else
	{
		printf( "Unable to clear file %s\n", useThisFile );
	}
}

bool ippSaveManager::SaveTo( string fileName )
{
	useThisFile = fileName;
	ifstream myfile( useThisFile );
	if( myfile.is_open() )
	{
		//printf( "< - - -Able to open file %s for saving- - - >\n", useThisFile.c_str() );
		//myfile << "Testing Save";
		myfile.close();
		return 1;
	}
	else
	{
		printf( "Unable to open file %s to save in by default\n", useThisFile.c_str() );
		return 0;
	}
}

bool ippSaveManager::GetEverything()
{
	string line, decoded;
	ifstream myfile( useThisFile );
	if( myfile.is_open() )
	{
		printf( "< - - -Opening file %s- - - >\n", useThisFile.c_str() );
		printf( "-@-@-Start of file-@-@-\n" );
		while( !myfile.eof() ) 
		{
			getline( myfile, line );
			decoded = base64_decode(line);
			printf( "%s\n", decoded.c_str());
		}
		if( myfile.eof() )
		{
			printf( "-@-@-End of file-@-@-\n" );
		}
		myfile.close();
		printf( "< - - -Closing file %s- - - >\n", useThisFile.c_str() );
		return true;
	}
	else
	{
		printf( "Unable to open file %s to get everything\n", useThisFile.c_str() );
		return false;
	}
}
