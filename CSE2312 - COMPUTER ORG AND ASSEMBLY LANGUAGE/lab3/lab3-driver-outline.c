#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 32
#define COUNT 5

typedef struct _BUSINESS {
	uint32_t taxId;
	char name[MAX_NAME_LENGTH + 1];
	uint32_t addNo;
	char direction;
	char street[MAX_NAME_LENGTH + 1];
	char city[MAX_NAME_LENGTH + 1];
	char state[2 + 1];
	uint32_t zip;
} BUSINESS;

extern void sortDecendingInPlace (int32_t x[], uint32_t count);
extern float sumF32(float x[], uint32_t count);
extern double prodF64(double x[], uint32_t count);
extern double dotpF64(double x[], double y[], uint32_t count);
extern float maxF32(float x[], uint32_t count);
extern double absSumF64 (double x[], uint32_t count);
extern double sqrtSumF64(double x[], uint32_t count);
extern double geoMean(double x[], uint32_t count);
extern char getDirection (BUSINESS business[], uint32_t index);
extern uint32_t getAddNo (BUSINESS business[], uint32_t index);
extern char * getCity(BUSINESS business[], uint32_t index);

int main(void) {
	uint32_t i;
	BUSINESS business[3] = {
	        {12342332, "Home Depot", 201, 'W', "Road to Six Flags", "Arlington", "TX", 76011},
	        {18091123, "Kroger", 945, 'W', "Lamar Blvd", "Arlington", "TX", 76012},
	        {81927322, "Round1", 3811, 'S', "Cooper St", "Arlington", "TX", 76015} 
	};

}