#include <iostream>
#include <string>
#include "dispatcher.hpp"

using namespace liblyrics;
using namespace std;

int main( int argc, char* argv[]) {
	dispatcher omg( "./examples/dispatcher.db" );
	string text;
	if( omg.get( "Give It 2 Me","Madonna", text ) == LYRIC_OK )
		cout<<"Text:"<<endl<<text<<endl;
	else
		cout<<"Here's the err message:"<<endl<<text<<endl;

	return 0;
}
