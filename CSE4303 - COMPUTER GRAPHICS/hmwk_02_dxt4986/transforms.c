// Tam, Daniel
// dxt4986
// 2021-04-30
//----------------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "transforms.h"

//----------------------------------------------------------------
void projectPerspective(
  FLOAT64 xMin, FLOAT64 yMin, FLOAT64 xMax, FLOAT64 yMax,
  int w, int h,
  FLOAT64 d,
  Matrix xform )
{
  // Ensure the input is usable.
  if ( xMin == xMax ) {
    printf( "projectPerspective: xMin (%g) == xMax.\n", xMin );
    exit( 1 );
  }

  if ( yMin == yMax ) {
    printf( "projectPerspective: yMin (%g) == yMax.\n", yMin );
    exit( 1 );
  }

  if ( d <= 0.0 ) {
    printf( "projectPerspective: d (%g) <= 0.\n", d );
    exit( 1 );
  }

  // Perspective project onto the XY plane.
  Matrix project;

  // TODO: Construct in "project" the proper matrix to do a
  //  perspective projection with the camera position at d.
  copyMatrix( I4, project );
  project[2][2] = 0.0;
  project[3][2] = -1/d;

  // Translate the projected area to the origin.
  Matrix xlate;

  // TODO: Construct in "xlate" the proper translation matrix
  //  to move the lower-left corner of the World Space subset
  //  TO the origin.
  translateMatrix(-xMin, -yMin, 0, xlate);

  // Scale the world subset to fit screen space.
  Matrix scale;

  // TODO: Construct in "scale" the proper scale matrix to
  //  scale the World Space subset to the Screen Space size.
  FLOAT64 sx = (w-1) / (xMax - xMin);
  FLOAT64 sy = (h-1) / (yMax - yMin);
  FLOAT64 sz = 0.0;
  scaleMatrix(sx, sy, sz, scale);

  // Now combine these transform matrices into one.  Be sure to do
  //  them in the correct order.
  Matrix tmp;

  // TODO: Construct in "xform" the composition of the three
  //  preceding matrices.  Be sure to compute them IN THE PROPER
  //  ORDER.
  
  matrixMultMatrix(scale, xlate, tmp);
  matrixMultMatrix(tmp, project, xform);
}

void projectPoint( const Matrix xform, const Point p1, Point p2 )
{
  matrixMultPoint( xform, p1, p2 );
  homogenizePoint( p2 );
  p2[0] = (int) ( p2[0] + 0.5 );
  p2[1] = (int) ( p2[1] + 0.5 );
}

//----------------------------------------------------------------
void rotateXMatrix( FLOAT64 theta, Matrix xform )
{
  copyMatrix( I4, xform );

  double cth = cos( theta );
  double sth = sin( theta );

  xform[1][1] =  cth;
  xform[1][2] = -sth;
  xform[2][1] =  sth;
  xform[2][2] =  cth;
}

void rotateYMatrix( FLOAT64 theta, Matrix xform )
{
  copyMatrix( I4, xform );

  double cth = cos( theta );
  double sth = sin( theta );

  xform[0][0] =  cth;
  xform[0][2] =  sth;
  xform[2][0] = -sth;
  xform[2][2] =  cth;
}

void rotateZMatrix( FLOAT64 theta, Matrix xform )
{
  copyMatrix( I4, xform );

  double cth = cos( theta );
  double sth = sin( theta );

  xform[0][0] =  cth;
  xform[0][1] = -sth;
  xform[1][0] =  sth;
  xform[1][1] =  cth;
}

//----------------------------------------------------------------
void scaleMatrix( FLOAT64 sx, FLOAT64 sy, FLOAT64 sz, Matrix xform )
{
  copyMatrix( I4, xform );

  xform[0][0] = sx;
  xform[1][1] = sy;
  xform[2][2] = sz;
}

//----------------------------------------------------------------
void shearXMatrix( FLOAT64 hxy, FLOAT64 hxz, Matrix xform )
{
  copyMatrix( I4, xform );

  xform[0][1] = hxy;
  xform[0][2] = hxz;
}

void shearYMatrix( FLOAT64 hyx, FLOAT64 hyz, Matrix xform )
{
  copyMatrix( I4, xform );

  xform[1][0] = hyx;
  xform[1][2] = hyz;
}

void shearZMatrix( FLOAT64 hzx, FLOAT64 hzy, Matrix xform )
{
  copyMatrix( I4, xform );

  xform[2][0] = hzx;
  xform[2][1] = hzy;
}

//----------------------------------------------------------------
void translateMatrix( FLOAT64 tx, FLOAT64 ty, FLOAT64 tz, Matrix xform )
{
  copyMatrix( I4, xform );

  xform[0][3] = tx;
  xform[1][3] = ty;
  xform[2][3] = tz;
}

//----------------------------------------------------------------
