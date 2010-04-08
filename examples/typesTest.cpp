#include <iostream>
#include <iomanip>
#include "types.hpp"

using namespace std;
using namespace lyrics;

int main() {

	lyric foo;

	cout<<endl<<endl;

	cout<<"Status: "<<foo.getErrMsg()<<endl;

	cout<<">> object initialize now."<<endl;
	foo.setData( "oh my gosh", "tilde", "FUCK YEA SEAKING" );

	cout<<foo.getTitle()<<'\t'<<foo.getAuth()<<'\t'<<foo.getText()<<endl;

	cout<<"Status: "<<foo.getErrMsg()<<endl;
	cout<<endl<<endl;

	return 0;

}
