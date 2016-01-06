/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

int isLeapYear(int y) {
	// not divisible by 4
	if (y % 4)
		return 0;
	// divisible by 400
	if (!(y % 400))
		return 1;
	// divisible by 100, blocks cases like 2100
	if (!(y % 100))
		return 0;
	// divisible by 100 & not divisble by 400
	return 1;
}

int validate(char * in, int * d, int * m, int * y) {
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
	if (isLeapYear(*y))
		maxDays[1] ++;
	// checing date
	if (*d < 1 || *d > maxDays[*m - 1])
		return 0;

	// validated
	return 1;
}

int countGreaterNumbers(struct transaction *Arr, int len, char *date) {
	int day, month, year;
	if(!(Arr) || len < 1 || !validate(date, &day, &month, &year))
		return -1;
	int tday, tmonth, tyear, count = 0;
	while (len--) {
		if (validate(Arr[len].date, &tday, &tmonth, &tyear)) {
			if (year < tyear)
				count++;
			else if (year == tyear) {
				if (month < tmonth)
					count++;
				else if (tmonth == month && day < tday)
					count++;
			}
		}
		else 
			return -1;
	}
	return count;
}
