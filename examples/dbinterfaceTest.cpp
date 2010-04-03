#include <iostream>
#include <iomanip>
#include "dbinterface.hpp"
#include "types.hpp"

using namespace std;
using namespace lyrics;

int main() {

	lyric song( "fossi figo", "elio", "....." );
	dbinterface db( "./examples/dbinterfaceTest.db" );

	db.addEntry( &song );

	if( song.e.getStatus() != OK ) {
		cout<<song.e.getErrMsg()<<endl;
		return -1;
	}
	
	lyric ret = db.get( "fossi figo", "elio" );

	cout<<"Autore"<<setw(10)<<"Titolo"<<endl;
	cout<<ret.getAuth()<<setw(16)<<ret.getTitle()<<endl;

	return 0;

}
