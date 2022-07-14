#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>

extern uint64_t add64(uint64_t x, uint64_t y); // returns x + y
extern uint64_t sub64(uint64_t x, uint64_t y); // returns x - y
extern uint16_t minU8(uint8_t x, uint8_t y); // returns the minimum of x, y
extern int16_t minS8(int8_t x, int8_t y); // returns the minimum of x, y
extern bool isLessThanU32(uint32_t x, uint32_t y); // returns 1 if x < y, 0 else
extern bool isLessThanS32(int32_t x, int32_t y); // returns 1 if x < y, 0 else
extern uint32_t shiftLeftU32 (uint32_t x, uint32_t p); // returns x << p = x * 2p for p = 0 .. 31
extern uint32_t shiftU32(uint32_t x, int32_t p); // return x * 2p for p = -31 .. 31
extern int32_t shiftS32(int32_t x, int32_t p); // return x * 2p for p = -31 .. 31
extern bool isEqualU16(uint16_t x, uint16_t y); // returns 1 if x = y, 0 if x != y
extern bool isEqualS16(int16_t x, int16_t y); // returns 1 if x = y, 0 if x != y
extern void stringCopy(char* strTo, char* strFrom); // copies strFrom to strTo
extern void stringCat(char* strFrom, char* strTo); // adds strFrom to end of strTo

int main(void) {
	
	uint64_t x = 22222222222;
	uint64_t y = 11111111111;
	
	printf("Question 1, add64: Correct answer = %lld\n", x + y);
	printf("Question 1, add64: Student answer = %lld\n\n", add64(x, y));
	
	printf("Question 2, sub64: Correct answer = %lld\n", x - y);
	printf("Question 2, sub64: Student answer = %lld\n\n", sub64(x, y));
	
	uint8_t a = 254;
	uint8_t b = 4;
	
	printf("Question 3, minU8, test 1: Correct answer = %hhu\n", b);
	printf("Question 3, minU8, test 1: Student answer = %hu\n\n", minU8(a, b));
	
	printf("Question 3, minU8, test 2: Correct answer = %hhu\n", b);
	printf("Question 3, minU8, test 2: Student answer = %hu\n\n", minU8(b, a));
	
	int8_t c = -8;
	int8_t d = 8;
	
	printf("Question 4, minS8, test 1: Correct answer = %hhd\n", c);
	printf("Question 4, minS8, test 1: Student answer = %hd\n\n", minS8(c, d));
	
	printf("Question 4, minS8, test 2: Correct answer = %hhd\n", c);
	printf("Question 4, minS8, test 2: Student answer = %hd\n\n", minS8(d, c));
	
	uint32_t e = 32;
	uint32_t f = 16;
	
	printf("Question 5, isLessThanU32, test 1: Correct answer = %d\n", 0);
	printf("Question 5, isLessThanU32, test 1: Student answer = %d\n\n", isLessThanU32(e, f));
	
	printf("Question 5, isLessThanU32, test 2: Correct answer = %d\n", 1);
	printf("Question 5, isLessThanU32, test 2: Student answer = %d\n\n", isLessThanU32(f, e));
	
	int32_t g = -32;
	int32_t h = 16;
	
	printf("Question 6, isLessThanS32, test 1: Correct answer = %d\n", 1);
	printf("Question 6, isLessThanS32, test 1: Student answer = %d\n\n", isLessThanS32(g, h));
	
	printf("Question 6, isLessThanS32, test 2: Correct answer = %d\n", 0);
	printf("Question 6, isLessThanS32, test 2: Student answer = %d\n\n", isLessThanS32(h, g));
	
	
	printf("Question 7, shiftLeftU32: Correct answer = %d\n", 2097152);
	printf("Question 7, shiftLeftU32: Student answer = %d\n\n", shiftLeftU32(e, f));
	
	printf("Question 8, shiftU32, test 1: Correct answer = %d\n", 2097152);
	printf("Question 8, shiftU32, test 1: Student answer = %d\n\n", shiftU32(e, f));
	
	printf("Question 8, shiftU32, test 2: Correct answer = %d\n", 8);
	printf("Question 8, shiftU32, test 2: Student answer = %d\n\n", shiftU32(e, -2));
	
	printf("Question 9, shiftS32, test 1: Correct answer = %d\n", -2097152);
	printf("Question 9, shiftS32, test 1: Student answer = %d\n\n", shiftS32(g, h));
	
	printf("Question 9, shiftS32, test 2: Correct answer = %d\n", -8);
	printf("Question 9, shiftS32, test 2: Student answer = %d\n\n", shiftS32(g, -2));
	
	uint16_t i = 32;
	uint16_t j = 16;
	
	printf("Question 10, isEqualU16, test 1: Correct answer = %d\n", 0);
	printf("Question 10, isEqualU16, test 1: Student answer = %d\n\n", isEqualU16(i, j));
	
	printf("Question 10, isEqualU16, test 2: Correct answer = %d\n", 1);
	printf("Question 10, isEqualU16, test 2: Student answer = %d\n\n", isEqualU16(i, i));
	
	int16_t k = 32;
	int16_t l = 16;
	
	printf("Question 11, isEqualS16, test 1: Correct answer = %d\n", 0);
	printf("Question 11, isEqualS16, test 1: Student answer = %d\n\n", isEqualS16(k, l));
	
	printf("Question 11, isEqualS16, test 2: Correct answer = %d\n", 1);
	printf("Question 11, isEqualS16, test 2: Student answer = %d\n\n", isEqualS16(k, k));
	
	char test1[20] = "aaaaaaa";
	char test2[44] = "bbbbbbb";

	stringCopy(test1, test2);
	
	printf("Question 12, stringCopy: Correct answer = bbbbbbb\n");
	printf("Question 12, stringCopy: Student answer = %s\n\n", test1);

	char test3[20] = "aaaaaaa";
	char test4[44] = "bbbbbbb"; 

	stringCat(test3, test4);	

	printf("Question 13, stringCat: Correct answer = bbbbbbbaaaaaaa\n");
	printf("Question 13, stringCat: Student answer = %s\n\n", test4);
	
	return EXIT_SUCCESS;
}
