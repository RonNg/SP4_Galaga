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

void ippSaveManager::CreateNewFile()
{
	ofstream			myfile( useThisFile );
	string something = "Stuff\n";
	if( myfile.is_open() )
	{
		printf( "Created new text file called %s\n", useThisFile.c_str() );
		myfile << base64_encode( reinterpret_cast<const unsigned char*>(something.c_str()), something.length() );
		myfile.close();
	}
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
	ifstream			myfile( useThisFile );

	if( myfile.is_open() )
	{
		myfile.close();
		return true;
	}
	else
	{
		printf( "Unable to open file %s to save in by default\n", useThisFile.c_str() );

		CreateNewFile();

		return false;
	}
}

bool ippSaveManager::AddCategory( const string categoryName )
{
	int				offset;
	string			decoded = "";
	string			encoded = base64_encode(reinterpret_cast<const unsigned char*>(categoryName.c_str()), categoryName.length()) + "\n";
	string			slot = "(Blank)";
	string			blank = base64_encode(reinterpret_cast<const unsigned char*>(slot.c_str()), slot.length());
	string			line;
	ifstream		inputFile( useThisFile );

	if( inputFile.is_open() )
	{
		while( !inputFile.eof() )
		{
			getline( inputFile, line );
			decoded += line;
			decoded += "\n";
			if( ( offset = base64_decode( line ).find( categoryName, 0 ) ) != string::npos )
			{
				inputFile.close();
				printf( "This Category %s already exists\n", categoryName.c_str() );
				return false;
			}
		}
		inputFile.close();
	}
	else
	{
		printf( "Unable to open file %s to encrypt this %s\n", useThisFile.c_str(), categoryName.c_str() );
		return false;
	}

	ofstream outputFile( useThisFile );

	if( outputFile.is_open() )
	{
		outputFile << decoded;
		outputFile << encoded;
		outputFile << blank;
		outputFile.close();
		return true;
	}
	else
	{
		printf( "Unable to open file %s to encrypt this %s\n", useThisFile.c_str(), categoryName.c_str() );
		return false;
	}
}

bool ippSaveManager::AddInformationInto( const string information, const string categoryName )
{
	int				offset;
	string			decoded = "";
	string			encoded = base64_encode(reinterpret_cast<const unsigned char*>(information.c_str()), information.length());
	string			slot = "(Blank)";
	string			blank = base64_encode(reinterpret_cast<const unsigned char*>(slot.c_str()), slot.length());
	string			line;
	ifstream		inputFile( useThisFile );

	if( inputFile.is_open() )
	{
		while( getline( inputFile, line ) )
		{
			decoded += line;
			decoded += "\n";
			if( ( offset = base64_decode(line).find( categoryName, 0 ) ) != string::npos )
			{
				getline( inputFile, line );
				getline( inputFile, line );
				decoded += encoded;
				decoded += "\n";
				decoded += blank;
				decoded += "\n";
			}
		}
		inputFile.close();
		printf( "\n" );
	}
	else
	{
		printf( "Unable to open file %s to encrypt this %s\n", useThisFile.c_str(), categoryName.c_str() );
		return false;
	}

	ofstream outputFile( useThisFile );

	if( outputFile.is_open() )
	{
		outputFile << decoded;
		outputFile.close();
		return true;
	}
	else
	{
		printf( "Unable to open file %s to encrypt this %s\n", useThisFile.c_str(), categoryName.c_str() );
		return false;
	}
}

bool ippSaveManager::EditThis( const string target, const string change )
{	
	int				offset;								//	Variable for checking if fromFile matches target
	string			tempHold;							//	Takes in the string from the text file and holds it temporary
	string			fromFile = "";						//	Is the string of all of the information taken from the text file
	ifstream		inputFile( useThisFile );

	if( inputFile.is_open() )							//	Open the text file
	{
		while( !inputFile.eof() )						//	While the text file is not at the end
		{
			getline( inputFile, tempHold );
			fromFile += tempHold;
			fromFile += "\n";			
														//	if tempHold value matches target value
			if( ( offset = base64_decode( tempHold ).find( target, 0 ) ) != string::npos )
			{
				getline( inputFile, tempHold );			//	Takes in the next line
														//	Changes the value taken in
				fromFile += base64_encode( reinterpret_cast<const unsigned char*>(change.c_str()), change.length() );
				fromFile += "\n";
			}
		}
		inputFile.close();								//	Close the text file
	}
	else
	{
		printf( "Unable to open file %s to encrypt this %s\n", useThisFile.c_str(), target.c_str() );
		return false;
	}

	ofstream outputFile( useThisFile );					//	Open the text file again
	if( outputFile.is_open() )
	{
		outputFile << fromFile;							//	Enters the information taken from the above section
		outputFile.close();								//	Close the text file
		return true;
	}
	else
	{
		printf( "Unable to open file %s to encrypt this %s\n", useThisFile.c_str(), target.c_str() );
		return false;
	}
}

bool ippSaveManager::EditThis( const string target, const int change )
{	
	string change_int = ConvertInt( change );
	int				offset;								//	Variable for checking if fromFile matches target
	string			tempHold;							//	Takes in the string from the text file and holds it temporary
	string			fromFile = "";						//	Is the string of all of the information taken from the text file
	ifstream		inputFile( useThisFile );

	if( inputFile.is_open() )							//	Open the text file
	{
		while( !inputFile.eof() )						//	While the text file is not at the end
		{
			getline( inputFile, tempHold );
			fromFile += tempHold;
			fromFile += "\n";			
														//	if tempHold value matches target value
			if( ( offset = base64_decode( tempHold ).find( target, 0 ) ) != string::npos )
			{
				getline( inputFile, tempHold );			//	Takes in the next line
														//	Changes the value taken in
				fromFile += base64_encode( reinterpret_cast<const unsigned char*>(change_int.c_str()), change_int.length() );
				fromFile += "\n";
			}
		}
		inputFile.close();								//	Close the text file
	}
	else
	{
		printf( "Unable to open file %s to encrypt this %s\n", useThisFile.c_str(), target.c_str() );
		return false;
	}

	ofstream outputFile( useThisFile );					//	Open the text file again
	if( outputFile.is_open() )
	{
		outputFile << fromFile;							//	Enters the information taken from the above section
		outputFile.close();								//	Close the text file
		return true;
	}
	else
	{
		printf( "Unable to open file %s to encrypt this %s\n", useThisFile.c_str(), target.c_str() );
		return false;
	}
}

bool ippSaveManager::EncryptThis( const string information )
{
	//	Credit to René Nyffenegger
	//	Website link is http://www.adp-gmbh.ch/cpp/common/base64.html
	if( addOn )
	{
		string			decoded = "";
		string			tempHold;
		string			line;
		ifstream		inputFile( useThisFile );

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
		string			encoded = base64_encode(reinterpret_cast<const unsigned char*>(information.c_str()), information.length());
		ofstream		myfile( useThisFile );

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

	string				numberString = ConvertInt( information );

	if( addOn )
	{
		string			decoded = "";
		string			tempHold;
		string			line;
		ifstream		inputFile( useThisFile );

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

		string			encoded = base64_encode(reinterpret_cast<const unsigned char*>(numberString.c_str()), numberString.length());
		ofstream		outputFile( useThisFile );

		if( outputFile.is_open() )
		{
			outputFile << decoded;
			outputFile << encoded;
			outputFile.close();
			return true;
		}
		else
		{
			printf( "Unable to open file %s to encrypt this %d\n", useThisFile.c_str(), information );
			return false;
		}
	}
	else
	{
		string			encoded = base64_encode(reinterpret_cast<const unsigned char*>(numberString.c_str()), numberString.length());
		ofstream		myfile( useThisFile );

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
	int				offset;
	bool			found = false;
	string			line;
	string			decoded;
	ifstream		myfile( useThisFile );

	if( myfile.is_open() )
	{
		while( getline( myfile, line ) && found == false )
		{
			decoded = base64_decode(line);
			printf( "%s\n", decoded.c_str() );
			if( ( offset = decoded.find( information, 0 ) ) != string::npos )
			{
				printf( "Entering below %s!!\n", information.c_str() );
				while( getline( myfile, line ) && ( offset != decoded.find( "(Blank)", 0 ) ) != string::npos )
				{
					decoded = base64_decode(line);
					printf( "Search result: %s\n", decoded.c_str() );
				}
				found = true;
			}
		}
		if( myfile.eof() )
		{
			if( offset == -1 )
			{
				printf( "Unable to find %s\n", information.c_str() );
			}
		}
		myfile.close();
		return true;
	}
	else
	{
		printf( "Unable to open file %s to get this %s\n", useThisFile.c_str(), information.c_str() );
		return false;
	}
}

int ippSaveManager::GetInt( string information )
{
	int				offset;
	bool			found = false;
	string			line;
	string			decoded;
	ifstream		myfile( useThisFile );

	if( myfile.is_open() )
	{
		while( getline( myfile, line ) && found == false )
		{
			decoded = base64_decode(line);
			printf( "looking at %s\n", decoded.c_str() );
			if( ( offset = decoded.find( information, 0 ) ) != string::npos )
			{
				printf( "Here %s is!!\n", information.c_str() );
				while( getline( myfile, line ) && ( offset != decoded.find( "(Blank)", 0 ) ) != string::npos )
				{
					decoded = base64_decode(line);
					printf( "Search result: %d\n", decoded.c_str() );
					return atoi( base64_decode(line).c_str() );
				}
				found = true;
			}
		}
		if( myfile.eof() )
		{
			if( offset == -1 )
			{
				printf( "Unable to find %s\n", information.c_str() );
			}
		}
		myfile.close();
		return 0;
	}
	else
	{
		printf( "Unable to open file %s to get this %s\n", useThisFile.c_str(), information.c_str() );
		return 0;
	}
}

void ippSaveManager::ClearAll()
{
	ofstream			myfile( useThisFile );
	addOn = false;

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
	ifstream			myfile( useThisFile );
	useThisFile = fileName;

	if( myfile.is_open() )
	{
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
	string				line;
	string				decoded;
	ifstream			myfile( useThisFile );

	if( myfile.is_open() )
	{
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
		return true;
	}
	else
	{
		printf( "Unable to open file %s to get everything\n", useThisFile.c_str() );
		return false;
	}
}
