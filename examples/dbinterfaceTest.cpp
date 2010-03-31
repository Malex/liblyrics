#include <iostream>
#include "dbinterface.hpp"
#include "types.hpp"

using namespace std;
using namespace lyrics;

int main() {

	lyric song( "fossi figo", "elio", "....." );
	dbinterface db( "test.db" );

	db.addEntry( song );
	
	lyric ret = db.get( "fossi figo", "elio" );

	cout<<ret.getAuth()<<ret.getTitle()<<endl;

	return 0;

}
