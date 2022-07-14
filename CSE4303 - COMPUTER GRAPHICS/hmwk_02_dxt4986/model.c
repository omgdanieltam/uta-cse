// Tam, Daniel
// dxt4986
// 2021-04-30
//----------------------------------------------------------------
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "model.h"
#include "transforms.h"

static char *ensureExtension( char *fName, char *ext );

//----------------------------------------------------------------
Model *loadModel( char *fName )
{
  // Is the input file available?
  FILE *fp = fopen( fName, "r" );
  if ( fp == NULL ) {
    // Rats!  A file open-to-read error.
    printf( "# Unable to open \"%s\" for read.  (%d) %s.\n",
      fName, errno, strerror( errno ) );
    exit( 1 );
  }

  // Allocate an empty Model structure
  Model *model = (Model *) calloc( 1, sizeof( Model ) );
  if ( model == NULL ) {
    printf( "# (%s) Unable to allocate a Model structure (%lu bytes).\n",
      fName, sizeof( Model ) );
    exit( 1 );
  }

  // Remember the source file name (for messages)
  model->sourceFileName = strdup( fName );

  // Replace the extension with "sdf" for the output file.
  model->drawFileName = ensureExtension( fName, "sdf" );

  //-- Scan ------------------------------------------------------
  // Scan the model file counting each vertex and face so we know
  //  how big to make the data structures.
  int     numFaces  = 0;
  int     numPoints = 0;
  char   *line      = NULL;
  size_t  len       = 0;
  size_t  read;

  while ( ( read = getline( &line, &len, fp ) ) != -1ul ) {
    char *ptr = line;

    while ( *ptr && isspace( *ptr ) ) ptr++;
    if ( *ptr == 'v' ) ++numPoints;
    if ( *ptr == 'f' ) ++numFaces;
  }

  //-- Allocate --------------------------------------------------
  model->numFaces    = numFaces;
  model->faces       = (Face *) calloc( numFaces, sizeof( Face ) );
  if ( model->faces == NULL ) {
    printf( "# (%s) Unable to allocate %d Face structure%s (%lu bytes each).\n",
      model->sourceFileName,
      numFaces, numFaces == 1 ? "" : "s", sizeof( Face ) );
    exit( 1 );
  }

  model->numPoints = numPoints;
  model->points    = (Point *) calloc( numPoints, sizeof( Point ) );
  if ( model->points == NULL ) {
    printf( "# (%s) Unable to allocate %d Point structure%s (%lu bytes each).\n",
      model->sourceFileName,
      numPoints, numPoints == 1 ? "" : "s", sizeof( Point ) );
    exit( 1 );
  }

  //-- Read ------------------------------------------------------
  // Now that we have the space to keep the data, reread the model
  //  file to get the vertex and face info.
  rewind( fp );

  Point *point   = model->points;
  Face  *face    = model->faces;
  int    lineNum = 0;

  model->xMin = HUGE_VAL;
  model->xMax = -HUGE_VAL;
  model->yMin = HUGE_VAL;
  model->yMax = -HUGE_VAL;
  model->zMin = HUGE_VAL;
  model->zMax = -HUGE_VAL;

  while ( ( read = getline( &line, &len, fp ) ) != -1ul ) {
    lineNum++;

    char *ptr = line;

    while ( *ptr && isspace( *ptr ) ) ptr++;

    if ( *ptr == 'v' ) {
      int conv = sscanf( ptr+1, " %lf %lf %lf",
        &(*point)[0], &(*point)[1], &(*point)[2] );

      if ( conv != 3 ) {
        printf( "# (%s) Unable to load vertex at line %d.\n",
          model->sourceFileName, lineNum );
      }


      // TODO:  Update model->xMin if the just-read point's X
      //        coordinate is less than that.
      if( (*point)[0] < model->xMin) { model->xMin = (*point)[0]; }

      // TODO:  Update model->xMax if the just-read point's X
      //        coordinate is greater than that.
      if( (*point)[0] > model->xMax) { model->xMax = (*point)[0]; }

      // TODO:  Update model->yMin if the just-read point's Y
      //        coordinate is less than that.
      if( (*point)[1] < model->yMin) { model->yMin = (*point)[1]; }

      // TODO:  Update model->yMax if the just-read point's Y
      //        coordinate is greater than that.
      if( (*point)[1] > model->yMax) { model->yMax = (*point)[1]; }

      // TODO:  Update model->zMin if the just-read point's Z
      //        coordinate is less than that.
      if( (*point)[2] < model->zMin) { model->zMin = (*point)[2]; }

      // TODO:  Update model->zMax if the just-read point's Z
      //        coordinate is greater than that.
      if( (*point)[2] > model->zMax) { model->zMax = (*point)[2]; }

      (*point)[3] = 1;  // The w coordinate

      point++;
      continue;

    } else if ( *ptr == 'f' ) {
      int conv = sscanf( ptr+1, " %d %d %d",
        &(*face)[0], &(*face)[1], &(*face)[2] );

      (*face)[0]--;
      (*face)[1]--;
      (*face)[2]--;

      if ( conv != 3 ) {
        printf( "# (%s) Unable to load face at line %d.\n",
          model->sourceFileName, lineNum );
      }

      face++;
      continue;

    } else if ( *ptr == '#' || *ptr == '\0' ) {
      // Comment or blank line -- ignore

    } else {
      printf( "# (%s) Line %d not understood:\n%s\n",
        model->sourceFileName, lineNum, ptr );
    }
  }

  // TODO: Compute model->xCenter using model->xMax and
  //       model->xMin.
  model->xCenter = (model->xMax + model->xMin)/2;
  

  // TODO: Compute model->yCenter using model->yMax and
  //       model->yMin.
  model->yCenter = (model->yMax + model->yMin)/2;

  // TODO: Compute model->zCenter using model->zMax and
  //       model->zMin.
  model->zCenter = (model->zMax + model->zMin)/2;

  //-- Done! -----------------------------------------------------
  // Free/close local items.
  if ( line != NULL ) free( line );
  fclose( fp );

  // Ta-da!  All done!
  return model;
}

void disposeModel( Model *model )
{
  if ( model ) {
    if ( model->sourceFileName ) free( model->sourceFileName );
    if ( model->drawFileName )   free( model->drawFileName );
    if ( model->points )         free( model->points );
    if ( model->faces )          free( model->faces );

    free( model );
  }
}

void dumpModel( Model *model, int pLimit, int fLimit )
{
  printf( "#---------------------------------------\n" );
  printf( "# Model \"%s\"\n", model->sourceFileName );
  printf( "#   %d point%s, %d face%s\n",
    model->numPoints,
    model->numPoints == 1 ? "" : "s",
    model->numFaces,
    model->numFaces == 1 ? "" : "s" );

  printf( "#   Limits (%g, %g), (%g, %g), (%g, %g)\n",
    model->xMin, model->xMax,
    model->yMin, model->yMax,
    model->zMin, model->zMax );

  printf( "#   Center (%g, %g, %g)\n",
    model->xCenter, model->yCenter, model->zCenter );

  printf( "#   Draw file \"%s\"\n", model->drawFileName );

  if ( pLimit > 0 ) {
    printf( "#-- Points -----------------------------\n" );
    for ( int i = 0; i < pLimit && i < model->numPoints; i++ ) {
      printf( "v %10g %10g %10g\n",
        model->points[i][0],
        model->points[i][1],
        model->points[i][2] );
    }
  }

  if ( fLimit > 0 ) {
    printf( "#-- Faces ------------------------------\n" );
    for ( int i = 0; i < fLimit && i < model->numFaces; i++ ) {
      printf( "f %4d %4d %4d\n",
        model->faces[i][0],
        model->faces[i][1],
        model->faces[i][2] );
    }
  }

  printf( "#---------------------------------------\n" );
}

//----------------------------------------------------------------
void rotateModel( Model *model, Parameters *params )
{
  Matrix toOrigin;
  Matrix xRot;
  Matrix yRot;
  Matrix zRot;
  Matrix fromOrigin;

  // TODO: Use translateMatrix() to compute the proper
  //  translation matrix to move the center of this model TO the
  //  origin.  Ensure the result is in toOrigin.
  translateMatrix(-model->xCenter, -model->yCenter, -model->zCenter, toOrigin);
 
  // TODO: Use rotateXMatrix() to compute the proper "rotation
  //  about the X axis" matrix.  Ensure the result is in xRot.
  rotateXMatrix(params->phi, xRot);

  // TODO: Use rotateYMatrix() to compute the proper "rotation
  //  about the Y axis" matrix.  Ensure the result is in yRot.
  rotateYMatrix(params->theta, yRot);

  // TODO: Use rotateZMatrix() to compute the proper "rotation
  //  about the Z axis" matrix.  Ensure the result is in zRot.
  rotateZMatrix(params->psi, zRot);

  // TODO: Use translateMatrix() to compute the proper
  //  translation matrix to move the center of this model FROM the
  //  origin back to where it was originally.  Ensure the result
  //  is in fromOrigin.
  translateMatrix(model->xCenter, model->yCenter, model->zCenter, fromOrigin);

  Matrix tmpA, tmpB;
  Matrix composite;

  // TODO: Multiply all five of those matrices you just created
  //  together IN THE CORRECT ORDER.  Ensure the result is in
  //  composite.  (Use tmpA and tmpB as intermediate temporaries
  //  to make this easier.)
  matrixMultMatrix(fromOrigin, xRot, tmpA);
  matrixMultMatrix(tmpA, yRot, tmpB);
  matrixMultMatrix(tmpB, zRot, tmpA);
  matrixMultMatrix(tmpA, toOrigin, composite);
  //matrixMultMatrix(fromOrigin, zRot, tmpA);
  //matrixMultMatrix(tmpA, yRot, tmpB);
  //matrixMultMatrix(tmpB, xRot, tmpA);
  //matrixMultMatrix(tmpA, toOrigin, composite);

  Point rotPt;

  for ( int i=0; i<model->numPoints; i++ ) {
    // TODO: Multiply the composite matrix against the ith point
    //  of the model to get rotPt.  Then use memcpy() to copy
    //  rotPT back into the ith point of the model.
    matrixMultPoint(composite, model->points[i], rotPt);
    memcpy(&model->points[i], &rotPt, sizeof(Point));
  }
}

void projectModel( Model *model, Parameters *params )
{
  Matrix project;
  Point  projPt;

  projectPerspective(
   params->xMin,  params->yMin,   params->xMax, params->yMax,
   params->width, params->height,
   params->d,
   project );

  for ( int i=0; i<model->numPoints; i++ ) {
    projectPoint( project, model->points[i], projPt );
    memcpy( &model->points[i], &projPt, sizeof( Point ) );
  }
}

void drawModel( Model *model, Parameters *params )
{
  FILE *fp = fopen( model->drawFileName, "w" );

  fprintf( fp, "c %4d %4d\n", params->width, params->height );

  for ( int i=0; i<model->numFaces; i++ ) {
    int v1 = model->faces[i][0];
    int v2 = model->faces[i][1];
    int v3 = model->faces[i][2];

#define X(v)  ((int) (model->points[v][0]))
#define Y(v)  ((int) (model->points[v][1]))

    fprintf( fp, "l %4d %4d %4d %4d\n", X(v1), Y(v1), X(v2), Y(v2) );
    fprintf( fp, "l %4d %4d %4d %4d\n", X(v2), Y(v2), X(v3), Y(v3) );
    fprintf( fp, "l %4d %4d %4d %4d\n", X(v3), Y(v3), X(v1), Y(v1) );
  }
}

//----------------------------------------------------------------

char *ensureExtension( char *fName, char *ext )
{
  int   fNameLen = strlen( fName );
  int   extLen   = strlen( ext );

  char *outStr   = (char *) calloc( fNameLen+1+extLen+1, sizeof( char ) );
  if ( outStr == NULL ) {
    printf( "Could not allocate enough space for a changed-extension fName.\n" );
    exit( 1 );
  }

  memcpy( outStr, fName, fNameLen );

  char *dotPtr   = strrchr( outStr, '.' );
  char *slashPtr = strrchr( outStr, '/' );

  if ( dotPtr ) {
    if ( slashPtr ) {
      int dotPos   = dotPtr   - outStr;
      int slashPos = slashPtr - outStr;

      if ( dotPos < slashPos ) {
        // There's a dot, but it's on the left side of a slash so
        //  it's not the start of an extension.  We just stick the
        //  new extension on the end.
        strcat( outStr, "." );
        strcat( outStr, ext );
      } else {
        // There's a dot on the right side of the last slash, so
        //  it marks the start of an extension.  Put the new
        //  extension starting at the spot after that dot.
        strcpy( dotPtr+1, ext );
      }
    } else {
      // Dot but no slash so after the dot is the original
      //  extension.  Put the new extension starting the character
      //  after the original extension.
      strcpy( dotPtr+1, ext );
    }
  } else {
    // No dot in the original fName, so just stick a dot and the
    //  new extension on the end.
    strcat( outStr, "." );
    strcat( outStr, ext );
  }

  // Ta-da!  Done!
  return outStr;
}

//----------------------------------------------------------------
