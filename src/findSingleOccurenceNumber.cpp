/*
OVERVIEW: Given an array where every element occurs three times, except one element which occurs only
once. Find the element that occurs once.
E.g.: Input: arr = 12, 1, 12, 3, 12, 1, 1, 2, 3, 3
ouput: 2

INPUTS: Integer array and length of the array.

OUTPUT: Element that occurs only once.

ERROR CASES: Return -1 for invalid inputs.

NOTES:
*/

int findSingleOccurenceNumber(int *A, int len) {
	if (!A || len < 1)
		return -1;
	int ones = 0, twos = 0, not_threes, i;
	while (len --) {
		i = A[len];
		twos |= ones & i;
		ones ^= i;
		not_threes = ~(ones & twos);
		ones &= not_threes;
		twos &= not_threes;
	}
	return ones;
}