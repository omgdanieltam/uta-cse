// Dalio, Brian A.
// dalioba
// 2021-03-06
//----------------------------------------------------------------
#include <stdio.h>

#include "matrix.h"
#include "transforms.h"

//----------------------------------------------------------------
int main()
{
  // TODO: Separate your Student ID into ten (10) separate digits
  //        and put the first nine (9) of those digits in the
  //        points p1, p2, and p3 as their x, y, z components.
  //
  //        KEEP ALL THREE OF THE w COMPONENTS 1!
  //
  //        So, if your student ID happened to be 2718281828, the
  //        points would be as follows,

  Point p1 = { 1, 0, 0, 1 };
  Point p2 = { 1, 7, 4, 1 };
  Point p3 = { 9, 8, 6, 1 };

  //        Notice that we used only the first nine (9) digits of
  //        the Student ID.  We have three points each of which
  //        has x, y, and z components so only 9 digits are
  //        needed.
  //
  //        THE w COMPONENT FOR EACH POINT IS ALWAYS 1!

  //--------------------------------------
  // Spots to put the three rotation transform matrices.
  Matrix rotX;
  Matrix rotY;
  Matrix rotZ;

  // The transformed point goes here.
  Point pTmp;

  //--------------------------------------
  // Compute the three rotation matrices, one about each of the
  //  three axes.

  // We have to supply the angle in radians, so we use the
  //  handy-dandy DEG2RAD() macro to do the conversion for us.

  rotateXMatrix( DEG2RAD( 30.0 ), rotX );
  rotateYMatrix( DEG2RAD( 45.0 ), rotY );
  rotateZMatrix( DEG2RAD( 60.0 ), rotZ );

  //--------------------------------------
  // Rotate each of p1, p2, and p3 and display the transformed
  //  points.

  //----- p1
  printf( "//-- (rotX 30°)·p1 ----------\n" );

  // Rotate point p1 about the X axis WITH RESPECT TO THE ORIGIN
  //  by 30°.  We do this by multiplying the rotation matrix rotX
  //  by point p1 and the result comes back to us in point pTmp.
  matrixMultPoint( rotX, p1, pTmp );

  // Dump an easily readable version of pTmp, the transformed
  //  version of point p1, to the console.
  dumpPoint( pTmp );

  //----- p2
  printf( "\n//-- (rotY 45°)·p2 ----------\n" );

  // Rotate point p2 about the Y axis WITH RESPECT TO THE ORIGIN
  //  by 45°.  We do this by multiplying the rotation matrix rotY
  //  by point p2 and the result comes back to us in point pTmp.
  matrixMultPoint( rotY, p2, pTmp );

  // Dump an easily readable version of pTmp, the transformed
  //  version of point p2, to the console.
  dumpPoint( pTmp );

  //----- p3
  printf( "\n//-- (rotZ 60°)·p3 ----------\n" );

  // Rotate point p3 about the Z axis WITH RESPECT TO THE ORIGIN
  //  by 60°.  We do this by multiplying the rotation matrix rotZ
  //  by point p3 and the result comes back to us in point pTmp.
  matrixMultPoint( rotZ, p3, pTmp );

  // Dump an easily readable version of pTmp, the transformed
  //  version of point p3, to the console.
  dumpPoint( pTmp );
}

//----------------------------------------------------------------
