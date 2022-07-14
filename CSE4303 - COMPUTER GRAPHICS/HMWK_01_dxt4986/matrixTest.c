// Dalio, Brian A.
// dalioba
// 2021-03-03
//----------------------------------------------------------------
#include <stdio.h>

#include "matrix.h"

//----------------------------------------------------------------
int main()
{
  Point p = { 2, 7, 1, 8 };
  Point pTmp;

  Matrix m = {
    {  3,  1,  4,  1 },
    {  5,  9,  2,  6 },
    {  5,  3,  5,  8 },
    {  9,  7,  9,  3 } };
  Matrix mTmp;

  printf( "//-----------------------------------------------------------------\n" );
  printf( "//-- p ----------\n" );
  dumpPoint( p );

  scalarMultPoint( 3, p, pTmp );
  printf( "\n//-- 3 · p ------\n" );
  dumpPoint( pTmp );

  printf( "\n//-- Z4 ---------\n" );
  dumpMatrix( Z4 );

  printf( "\n//-- I4 ---------\n" );
  dumpMatrix( I4 );

  printf( "\n//-- m ----------\n" );
  dumpMatrix( m );

  printf( "\n//-----------------------------------------------------------------\n" );
  matrixMultPoint( I4, p, pTmp );
  printf( "//-- I4 · p -----\n" );
  dumpPoint( pTmp );

  matrixMultPoint( m, p, pTmp );
  printf( "\n//-- m · p ------\n" );
  dumpPoint( pTmp );

  printf( "\n//-----------------------------------------------------------------\n" );
  matrixPlusMatrix( m, m, mTmp );
  printf( "//-- m + m ------\n" );
  dumpMatrix( mTmp );

  scalarMultMatrix( 3, m, mTmp );
  printf( "\n//-- 3 · m ------\n" );
  dumpMatrix( mTmp );

  matrixMultMatrix( I4, m, mTmp );
  printf( "\n//-- I4 · m -----\n" );
  dumpMatrix( mTmp );

  matrixMultMatrix( m, I4, mTmp );
  printf( "\n//-- m · I4 -----\n" );
  dumpMatrix( mTmp );

  matrixMultMatrix( m, m, mTmp );
  printf( "\n//-- m · m ------\n" );
  dumpMatrix( mTmp );

  printf( "\n//-----------------------------------------------------------------\n" );

  return 0;
}

//----------------------------------------------------------------
