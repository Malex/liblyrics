#include <iostream>
#include "crawler.hpp"

using namespace std;
using namespace liblyrics;

int main()
{
	crawler* test = new crawler();
	lyric lyr = test->getLyric( "Give it to me","Madonna");
	cout << test->getCurlErrMessage() << endl;
	cout << lyr.getTitle() << endl << lyr.getAuth() << endl << lyr.getText() << endl;
	cout << lyr.getErrMsg() << endl;
	return 0;
}
