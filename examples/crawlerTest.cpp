#include <iostream>
#include "crawler.hpp"

using namespace std;
using namespace liblyrics;

int main()
{
	lyric lyr;
	crawler* test = new crawler();
	test->getLyric( "Give it to me","Madonna", lyr);
	cout << lyr.getTitle() << endl << lyr.getAuth() << endl << lyr.getText() << endl;
	cout << lyr.getErrMsg() << endl;
	return 0;
}
