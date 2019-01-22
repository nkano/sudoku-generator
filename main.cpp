#include <iostream>
#include <stdlib.h>
#include<time.h>
#include "Board.h"
using namespace std;

int main( void ) {
	srand( ( unsigned ) time( NULL ) );

	Board* b = new Board( );
	
	cout << "generation starts." << endl;
	b->makePuzzle( );
	cout << "---------" << endl;
	cout << "problem" << endl;
	cout << "---------" << endl;
	b->drawUnfilled( );
	cout << "---------" << endl << endl;
	cout << "---------" << endl;
	cout << "solution" << endl;
	cout << "---------" << endl;
	b->drawFilled( );
	cout << "---------" << endl;

	b->init();

	delete b;

	return 0;
}