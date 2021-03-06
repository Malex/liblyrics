#include <iostream>
#include <iomanip>
#include <string>
#include "dbinterface.hpp"
#include "types.hpp"

using namespace std;
using namespace liblyrics;

int main() {

	lyric song( "fossi figo", "elio", "...''.." );
	lyric ret;
	dbinterface db( "./examples/dbinterfaceTest.db" );

	db.addEntry( song );

	if( song.getStatus() != OK ) {
		cout<<song.getErrMsg()<<endl;
		return -1;
	}
	
	db.get( "fossi figo", "elio", ret );

	cout<<"Autore"<<setw(10)<<"Titolo"<<endl;
	cout<<ret.getAuth()<<setw(16)<<ret.getTitle()<<endl;

	cout<<"Testo:"<<endl<<ret.getText()<<endl;
	cout<<ret.getErrMsg()<<endl;
	return 0;

}
