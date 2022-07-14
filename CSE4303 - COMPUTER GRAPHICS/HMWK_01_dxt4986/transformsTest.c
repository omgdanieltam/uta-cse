// Dalio, Brian A.
// dalioba
// 2021-03-03
//----------------------------------------------------------------
#include <stdio.h>

#include "matrix.h"
#include "transforms.h"

//----------------------------------------------------------------
int main()
{
  Point  pX   = { 1.0, 0.0, 0.0, 1.0 };
  Point  pXY  = { 1.0, 1.0, 0.0, 1.0 };
  Point  pXZ  = { 1.0, 0.0, 1.0, 1.0 };

  Point  pY   = { 0.0, 1.0, 0.0, 1.0 };
  Point  pYZ  = { 0.0, 1.0, 1.0, 1.0 };

  Point  pZ   = { 0.0, 0.0, 1.0, 1.0 };

  Point  pXYZ = { 1.0, 1.0, 1.0, 1.0 };

  Point  pTmp;

  printf( "//-----------------------------------------------------------------\n" );
  printf( "//-- pX ---------------------\n" );
  dumpPoint( pX );

  printf( "\n//-- pXY --------------------\n" );
  dumpPoint( pXY );

  printf( "\n//-- pXZ --------------------\n" );
  dumpPoint( pXZ );

  printf( "\n//-- pY ---------------------\n" );
  dumpPoint( pY );

  printf( "\n//-- pYZ --------------------\n" );
  dumpPoint( pYZ );

  printf( "\n//-- pZ ---------------------\n" );
  dumpPoint( pZ );

  printf( "\n//-- pXYZ -------------------\n" );
  dumpPoint( pXYZ );

  printf( "\n//-----------------------------------------------------------------\n" );
  Matrix rotX;

  rotateXMatrix( DEG2RAD( 30.0 ), rotX );
  printf( "//-- rotX 30° ---------------\n" );
  dumpMatrix( rotX );

  matrixMultPoint( rotX, pX, pTmp );
  printf( "\n//-- (rotX 30°)·pX ----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotX, pXY, pTmp );
  printf( "\n//-- (rotX 30°)·pXY ---------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotX, pXZ, pTmp );
  printf( "\n//-- (rotX 30°)·pXZ ---------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotX, pY, pTmp );
  printf( "\n//-- (rotX 30°)·pY ----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotX, pYZ, pTmp );
  printf( "\n//-- (rotX 30°)·pYZ ---------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotX, pZ, pTmp );
  printf( "\n//-- (rotX 30°)·pZ ----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotX, pXYZ, pTmp );
  printf( "\n//-- (rotX 30°)·pXYZ --------\n" );
  dumpPoint( pTmp );

  printf( "\n//-----------------------------------------------------------------\n" );
  Matrix rotY;

  rotateYMatrix( DEG2RAD( 45.0 ), rotY );
  printf( "//-- rotY 45° ---------------\n" );
  dumpMatrix( rotY );

  matrixMultPoint( rotY, pX, pTmp );
  printf( "\n//-- (rotY 45°)·pX ----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotY, pXY, pTmp );
  printf( "\n//-- (rotY 45°)·pXY ---------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotY, pXZ, pTmp );
  printf( "\n//-- (rotY 45°)·pXZ ---------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotY, pY, pTmp );
  printf( "\n//-- (rotY 45°)·pY ----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotY, pYZ, pTmp );
  printf( "\n//-- (rotY 45°)·pYZ ---------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotY, pZ, pTmp );
  printf( "\n//-- (rotY 45°)·pZ ----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotY, pXYZ, pTmp );
  printf( "\n//-- (rotY 45°)·pXYZ --------\n" );
  dumpPoint( pTmp );

  printf( "\n//-----------------------------------------------------------------\n" );
  Matrix rotZ;

  rotateZMatrix( DEG2RAD( 60.0 ), rotZ );
  printf( "//-- rotZ 60° ---------------\n" );
  dumpMatrix( rotZ );

  matrixMultPoint( rotZ, pX, pTmp );
  printf( "\n//-- (rotZ 60°)·pX ----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotZ, pXY, pTmp );
  printf( "\n//-- (rotZ 60°)·pXY ---------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotZ, pXZ, pTmp );
  printf( "\n//-- (rotZ 60°)·pXZ ---------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotZ, pY, pTmp );
  printf( "\n//-- (rotZ 60°)·pY ----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotZ, pYZ, pTmp );
  printf( "\n//-- (rotZ 60°)·pYZ ---------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotZ, pZ, pTmp );
  printf( "\n//-- (rotZ 60°)·pZ ----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( rotZ, pXYZ, pTmp );
  printf( "\n//-- (rotZ 60°)·pXYZ --------\n" );
  dumpPoint( pTmp );

  printf( "\n//-----------------------------------------------------------------\n" );
  Matrix scale;

  scaleMatrix( 4.5, 6.7, 8.9, scale );
  printf( "//-- scale 4.5, 6.7, 8.9 ----\n" );
  dumpMatrix( scale );

  matrixMultPoint( scale, pX, pTmp );
  printf( "\n//-- scale·pX ---------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( scale, pXY, pTmp );
  printf( "\n//-- scale·pXY --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( scale, pXZ, pTmp );
  printf( "\n//-- scale·pXZ --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( scale, pY, pTmp );
  printf( "\n//-- scale·pY ---------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( scale, pYZ, pTmp );
  printf( "\n//-- scale·pYZ --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( scale, pZ, pTmp );
  printf( "\n//-- scale·pZ ---------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( scale, pXYZ, pTmp );
  printf( "\n//-- scale·pXYZ -------------\n" );
  dumpPoint( pTmp );

  printf( "\n//-----------------------------------------------------------------\n" );
  Matrix shearX;

  shearXMatrix( 1.2, 3.4, shearX );
  printf( "//-- shearX 1.2, 3.4 --------\n" );
  dumpMatrix( shearX );

  matrixMultPoint( shearX, pX, pTmp );
  printf( "\n//-- shearX·pX --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearX, pXY, pTmp );
  printf( "\n//-- shearX·pXY -------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearX, pXZ, pTmp );
  printf( "\n//-- shearX·pXZ -------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearX, pY, pTmp );
  printf( "\n//-- shearX·pY --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearX, pYZ, pTmp );
  printf( "\n//-- shearX·pYZ -------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearX, pZ, pTmp );
  printf( "\n//-- shearX·pZ --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearX, pXYZ, pTmp );
  printf( "\n//-- shearX·pXYZ ------------\n" );
  dumpPoint( pTmp );

  printf( "\n//-----------------------------------------------------------------\n" );
  Matrix shearY;

  shearYMatrix( 5.6, 7.8, shearY );
  printf( "//-- shearY 5.6, 7.8 --------\n" );
  dumpMatrix( shearY );

  matrixMultPoint( shearY, pX, pTmp );
  printf( "\n//-- shearY·pX --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearY, pXY, pTmp );
  printf( "\n//-- shearY·pXY -------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearY, pXZ, pTmp );
  printf( "\n//-- shearY·pXZ -------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearY, pY, pTmp );
  printf( "\n//-- shearY·pY --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearY, pYZ, pTmp );
  printf( "\n//-- shearY·pYZ -------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearY, pZ, pTmp );
  printf( "\n//-- shearY·pZ --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearY, pXYZ, pTmp );
  printf( "\n//-- shearY·pXYZ ------------\n" );
  dumpPoint( pTmp );

  printf( "\n//-----------------------------------------------------------------\n" );
  Matrix shearZ;

  shearZMatrix( 9.1, 2.3, shearZ );
  printf( "//-- shearZ 9.1, 2.3 --------\n" );
  dumpMatrix( shearZ );

  matrixMultPoint( shearZ, pX, pTmp );
  printf( "\n//-- shearZ·pX --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearZ, pXY, pTmp );
  printf( "\n//-- shearZ·pXY -------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearZ, pXZ, pTmp );
  printf( "\n//-- shearZ·pXZ -------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearZ, pY, pTmp );
  printf( "\n//-- shearZ·pY --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearZ, pYZ, pTmp );
  printf( "\n//-- shearZ·pYZ -------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearZ, pZ, pTmp );
  printf( "\n//-- shearZ·pZ --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( shearZ, pXYZ, pTmp );
  printf( "\n//-- shearZ·pXYZ ------------\n" );
  dumpPoint( pTmp );

  printf( "\n//-----------------------------------------------------------------\n" );
  Matrix xlate;

  translateMatrix( 4.5, 6.7, 8.9, xlate );
  printf( "//-- xlate 4.5, 6.7, 8.9 ----\n" );
  dumpMatrix( xlate );

  matrixMultPoint( xlate, pX, pTmp );
  printf( "\n//-- xlate·pX ---------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( xlate, pXY, pTmp );
  printf( "\n//-- xlate·pXY --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( xlate, pXZ, pTmp );
  printf( "\n//-- xlate·pXZ --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( xlate, pY, pTmp );
  printf( "\n//-- xlate·pY ---------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( xlate, pYZ, pTmp );
  printf( "\n//-- xlate·pYZ --------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( xlate, pZ, pTmp );
  printf( "\n//-- xlate·pZ ---------------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( xlate, pXYZ, pTmp );
  printf( "\n//-- xlate·pXYZ -------------\n" );
  dumpPoint( pTmp );

  printf( "\n//-----------------------------------------------------------------\n" );
  Matrix composite;
  Matrix mTmp;

  copyMatrix( I4, composite );

  matrixMultMatrix( composite, rotX,   mTmp );
  matrixMultMatrix( mTmp,      rotY,   composite );
  matrixMultMatrix( composite, rotZ,   mTmp );
  matrixMultMatrix( mTmp,      scale,  composite );
  matrixMultMatrix( composite, shearX, mTmp );
  matrixMultMatrix( mTmp,      shearY, composite );
  matrixMultMatrix( composite, shearZ, mTmp );
  matrixMultMatrix( mTmp,      xlate,  composite );

  printf( "//-- composite --------------\n" );
  dumpMatrix( composite );

  matrixMultPoint( composite, pX, pTmp );
  printf( "\n//-- composite·pX -----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( composite, pXY, pTmp );
  printf( "\n//-- composite·pXY ----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( composite, pXZ, pTmp );
  printf( "\n//-- composite·pXZ ----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( composite, pY, pTmp );
  printf( "\n//-- composite·pY -----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( composite, pYZ, pTmp );
  printf( "\n//-- composite·pYZ ----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( composite, pZ, pTmp );
  printf( "\n//-- composite·pZ -----------\n" );
  dumpPoint( pTmp );

  matrixMultPoint( composite, pXYZ, pTmp );
  printf( "\n//-- composite·pXYZ ---------\n" );
  dumpPoint( pTmp );

  printf( "\n//-----------------------------------------------------------------\n" );

  return 0;
}

//----------------------------------------------------------------
