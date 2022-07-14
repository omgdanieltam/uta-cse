# Dalio, Brian A.
# dalioba
# 2021-03-03

PROJS   = matrixTest transformsTest IDTest
CC      = gcc
CFLAGS  = -g -Wall -Wextra -fsanitize=address -fsanitize=leak -static-libasan
LIBS    = -lm

all : $(PROJS)

matrixTest : matrix.h matrix.c matrixTest.c
	$(CC) $(CFLAGS) -o matrixTest matrix.c matrixTest.c

transformsTest: matrix.h matrix.c transforms.h transforms.c transformsTest.c
	$(CC) $(CFLAGS) -o transformsTest matrix.c transforms.c transformsTest.c $(LIBS)

IDTest: matrix.h matrix.c transforms.h transforms.c IDTest.c
	$(CC) $(CFLAGS) -o IDTest matrix.c transforms.c IDTest.c $(LIBS)

clean:
	rm -f *.o $(PROJS)
