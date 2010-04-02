#include <iostream>
#include "crawler.hpp"

using namespace std;
using namespace lyrics;

int main()
{
	crawler* test = new crawler();
	lyric lyr = test->getLyric(ChartLyrics,"Give it to me","Madonna");
	cout << test->getCurlErrMessage() << endl;
	cout << lyr.getTitle() << endl << lyr.getAuth() << endl << lyr.getText() << endl;
	cout << lyr.e.getErrMsg() << endl;
	return 0;
}
