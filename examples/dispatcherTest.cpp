#include <iostream>
#include <string>
#include "dispatcher.hpp"

using namespace lyrics;
using namespace std;

int main( int argc, char* argv[]) {
	dispatcher omg;
	string text;
	if( !omg.get( "michael jackson", "beat it", text ) )
		cout<<text<<endl;
	else
		cout<<"Here's the err message:"<<endl<<text<<endl;

	return 0;
}
