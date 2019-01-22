#pragma once
class Board {
public:
	Board();
	~Board();
			
	void init();
	void drawUnfilled( );
	void drawFilled( );

	void solve( int iterator = 0 );
	
	void makePuzzle();

private:
	int mArray[9][9];
	int mSolvedArray[ 9 ][ 9 ];
	int mAnsNum;

	bool checkCoherence( int x, int y );

};

