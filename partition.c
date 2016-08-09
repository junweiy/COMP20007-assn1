/* 
items less than pivot are in the left part of returnvalue,
items not less than pivot are in the right part of rvalue,
*/

#include <stdio.h>
#include <stdlib.h>

int partition(void **A, int n, void *pivot, int (cmp)(void *, void *)) {
	int left, right;
	void *temp;
	left = 0;
	right = n-1;
	while (left<right) {
		while (cmp(A[left],pivot)<0 && left<right) {
			left++;
		}
		while (cmp(A[right],pivot) >= 0 && left<=right) {
			right--;
		}
		if (left<right) {
			temp = A[left];
			A[left] = A[right];
			A[right] = temp;
		}
	}
	return left;
}