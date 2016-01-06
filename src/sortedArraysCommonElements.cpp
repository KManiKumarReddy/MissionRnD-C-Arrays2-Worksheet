/*
OVERVIEW: You are given 2 bank statements that are ordered by date. Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>
#include <malloc.h>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

// 1 means leap year
int isLeapYear1(int y) {
	// not divisible by 4
	if (y % 4)
		return 0;
	// divisible by 400
	if (!(y % 400))
		return 1;
	// divisible by 100, blocks cases like 2100
	if (!(y % 100))
		return 0;
	// ot divisible by 100 & not divisble by 400, divisible by 4
	return 1;
}

// 1 means validated
int validate1(char * in, int * d, int * m, int * y) {
	int firstDash = -1, secondDash = -1, i;
	for (i = 0; in[i]; i++)
	if (in[i] == '-')
	if (firstDash >= 0)
	if (secondDash >= 0)
		return 0;
	else
		secondDash = i;
	else
		firstDash = i;
	if (firstDash < 1 || secondDash - firstDash < 1)
		return 0;
	*d = in[0] - '0';
	for (i = 1; i < firstDash; i++)
		*d = *d * 10 + (in[i] - '0');
	*m = in[firstDash + 1] - '0';
	for (i = firstDash + 2; i < secondDash; i++)
		*m = *m * 10 + (in[i] - '0');
	*y = in[secondDash + 1] - '0';
	for (i = secondDash + 2; in[i]; i++)
		*y = *y * 10 + (in[i] - '0');
	// checking month and year
	if (*m < 1 || *m > 12 || *y < 1 || *y > 9999)
		return 0;
	// initializing maximum days in a month
	int maxDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	// increasing max days in feb for leap years
	if (isLeapYear1(*y))
		maxDays[1] ++;
	// checing date
	if (*d < 1 || *d > maxDays[*m - 1])
		return 0;

	// validated
	return 1;
}

int isOlder(char *dob1, char *dob2) {
	int d1, d2, m1, m2, y1, y2;
	if (!validate1(dob1, &d1, &m1, &y1))
		return -1;
	if (!validate1(dob2, &d2, &m2, &y2))
		return -1;
	if (y2 > y1)
		return 1;
	else if (y2 < y1)
		return 2;
	else {
		if (m2 > m1)
			return 1;
		else if (m2 < m1)
			return 2;
		else {
			if (d2 > d1)
				return 1;
			else if (d2 < d1)
				return 2;
			else
				return 0;
		}
	}
}

struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	if (!A || !B || ALen < 1 || BLen < 1)
		return NULL;
	struct transaction *result = (struct transaction *)malloc((ALen > BLen ? ALen : BLen) * sizeof(struct transaction));
	if (!result)
		return NULL;
	int i = 0, j = 0, count = 0;
	while (i < ALen && j < BLen) {
		int dec = isOlder(A[i].date, B[j].date);
		if (!dec) {
			*(result + count++) = A[i];
			i++;
			j++;
		}
		else if (dec == -1)
			return NULL;
		else if (dec == 1)
			j++;
		else
			i++;
	}
	return count ? result : NULL;
}