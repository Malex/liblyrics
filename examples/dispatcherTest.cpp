#include <iostream>
#include <string>
#include "dispatcher.hpp"

using namespace lyrics;
using namespace std;

int main( int argc, char* argv[]) {
	dispatcher omg;
	cout<<omg.get( (string)argv[1], (string)argv[2] )<<endl;
	return 0;
}
