/*
quite a straight forward algorithm, just the same idea of recursive
mergesort. The use of stacks replaces the recursion by storing the
range of array to be processed and the type of process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stack.h"
#include "frame.h"

#define PARTITION 'P'
#define MERGE 'M'

void myMergesort(void **A, int n, int(cmp)(void *, void*)) {
	Stack *s;
	int from, mid, to;
	int i, j, k;
	void **B; /* buffer */
	Frame *temp;
	B = (void**)malloc(n*sizeof(*B));
	s = stack_new();
	temp = frame_new(0, n-1, PARTITION);
	stack_push(s, (void*)temp);
	while (!stack_isEmpty(s)) {
		temp = (Frame*)stack_pop(s);
		from = temp->from;
		to = temp->to;
		mid = (from+to)/2;
		if (temp->type == MERGE) {
			/* merge the array <from,mid,to> */
			i = from;
			j = from;
			k = mid+1;
			while (i <= mid && k <= to) {
				if (cmp(A[i],A[k])>0) {
					memcpy(&B[j++],&A[k++], sizeof(void*));
				} else {
					memcpy(&B[j++],&A[i++], sizeof(void*));
				}
			}
			while (i<=mid) {
				memcpy(&B[j++],&A[i++],sizeof(void*));
			}
			while (k<=to) {
				memcpy(&B[j++],&A[k++],sizeof(void*));
			}
			memcpy(&A[from],&B[from],(to-from+1)*sizeof(void*));
		} else {
			/* merge two items when two items are asked to partition */
			if (from+1>=to) {
				i = from;
				j = from;
				k = mid+1;
				while (i <= mid && k <= to) {
					if (cmp(A[i],A[k])>0) {
						memcpy(&B[j++],&A[k++], sizeof(void*));
					} else {
						memcpy(&B[j++],&A[i++], sizeof(void*));
					}
				}
				while (i<=mid) {
					memcpy(&B[j++],&A[i++],sizeof(void*));
				}
				while (k<=to) {
					memcpy(&B[j++],&A[k++],sizeof(void*));
				}
				memcpy(&A[from],&B[from],(to-from+1)*sizeof(void*));
			} else {
				/* push the stack to merge the array again later and 
				partition the left and right part in the next loop
				*/
				temp = frame_new(from, to, MERGE);
				stack_push(s, temp);
				temp = frame_new(from, mid, PARTITION);
				stack_push(s, temp);
				temp = frame_new(mid+1, to, PARTITION);
				stack_push(s, temp);
			}
		}
	}
}