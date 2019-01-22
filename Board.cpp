#include "Board.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
using namespace std;

Board::Board() {
    srand((unsigned int)time(NULL));
    this->init();
}


Board::~Board() {
}

void Board::init() {
    for( int i = 0; i < 9; i++ ) {
        for( int j = 0; j < 9; j++ ) {
            mArray[ i ][ j ] = 0;
            mSolvedArray[ i ][ j ] = 0;
        }
    }
    mAnsNum = 0;
}

void Board::drawUnfilled( ) {
    for( int i = 0; i < 9; i++ ) {
        for( int j = 0; j < 9; j++ ) {
            if( mArray[ i ][ j ] == 0 ) {
                cout << " ";
            } else {
                cout << mArray[ i ][ j ];
            }
        }
        cout << endl;
    }

}

void Board::drawFilled( ) {

    for( int i = 0; i < 9; i++ ) {
        for( int j = 0; j < 9; j++ ) {
            cout << mSolvedArray[ i ][ j ];
        }
        cout << endl;
    }
}


void Board::makePuzzle() {
    const auto startTime = chrono::system_clock::now( );

    bool filled[81];
    for( int i = 0; i < 81; i++ ) {
        filled[ i ] = false;
    }
    int index;

    while( 1 ) {
        while( 1 ) {
            index = rand() % 81;
            if( !filled[ index ] ) {
                mArray[ index / 9 ][ index % 9 ] = rand() % 9 + 1;
                filled[ index ] = true;
                break;
            }
        }
        if( this->checkCoherence( index/9, index%9 ) == false ) {
            mArray[ index / 9 ][ index % 9 ] = 0;
            filled[ index ] = false;
            continue;
        }

        this->solve();
        if( mAnsNum == 1 ) {
            cout << "genarated" << endl;
            break;
        } else if ( mAnsNum >= 2 ) {
            cout << 2;
            mAnsNum = 0;
            continue;
        } else if( mAnsNum == 0 ) {
            cout << 0;
            mArray[ index / 9 ][ index % 9 ] = 0;
            filled[ index ] = false;
            continue;
        }
        
    }

    const auto endTime = chrono::system_clock::now( );
    const auto timeSpan = endTime - startTime;
    cout << "caluclation time:"
        << chrono::duration_cast<chrono::milliseconds>( timeSpan ).count( )
        << "[ms]" << endl;

}


void Board::solve( int iterator ) {
    //backtracking algorithm
    if( mAnsNum >= 2 ) return;

    if( iterator >= 81 ) {
        mAnsNum++;
        for( int i = 0; i < 81; i++ ) {
            mSolvedArray[ i / 9 ][ i % 9 ] = mArray[ i / 9 ][ i % 9 ];

        }
        
        return;
    }

    if( mArray[ iterator / 9 ][ iterator % 9 ] != 0 ) {
        solve( iterator + 1 );
    } else {
        for( int i = 1; i <= 9; i++ ) {
            mArray[ iterator / 9 ][ iterator % 9 ] = i;
            if( checkCoherence( iterator / 9, iterator % 9 ) ) {
                solve( iterator + 1 );
            }
            mArray[ iterator / 9 ][ iterator % 9 ] = 0;
        }
    }

    return;
}

bool Board::checkCoherence( int x, int y ) {

    int numAry[ 9 ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };;

    //row
    for( int j = 0; j < 9; j++ ) {
        if( mArray[ x ][ j ] == 0 ) continue;
        numAry[ mArray[ x ][ j ] - 1 ]++;
    }

    for( int j = 0; j < 9; j++ ) {
        if( numAry[ j ] >= 2 ) {
            return false;
        }
        numAry[ j ] = 0;
    }

    //collumn
    for( int j = 0; j < 9; j++ ) {
        if( mArray[ j ][ y ] == 0 ) continue;
        numAry[ mArray[ j ][ y ] - 1 ]++;
    }

    for( int j = 0; j < 9; j++ ) {
        if( numAry[ j ] >= 2 ) {
            return false;
        }
        numAry[ j ] = 0;
    }

    //3*3cell
    int cx = ( int ) ( x / 3 ) * 3 + 1;
    int cy = ( int ) ( y / 3 ) * 3 + 1;

    for( int k = -1; k <= 1; k++ ) {
        for( int l = -1; l <= 1; l++ ) {
            if( mArray[ cx + k ][ cy + l ] == 0 ) continue;
            numAry[ mArray[ cx + k ][ cy + l ] - 1 ]++;
        }
    }
    for( int m = 0; m < 9; m++ ) {
        if( numAry[ m ] >= 2 ) {
            return false;
        }
        numAry[ m ] = 0;
    }
    return true;
}

