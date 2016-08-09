/*
The basic idea to do quicksort with an explicit stack is that firstly
push a range that cannot be processed(left>right), and while the left
index <= right index, every time after the partition, push the range
from the pivot index to the right side and go to the next loop with
low unchanged and high changed to pindex-1. After that pop those ranges 
out and send them into the loop to partition until the stack becomes
empty.

Some special cases are considered such as uniform array of numbers,
which can cause the numbers involved in partition process not changed.
Other cases are similar.

*/

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "partition.h"
#include "frame.h"


void myQuicksort(void **A, int n, int(cmp)(void *, void*)) {
	Stack *s;
	Frame *item, *temp;
	int loc, low, high, i, uni, sorted, from, to;
	char type;
	item = (Frame*)malloc(sizeof(*item));
	temp = (Frame*)malloc(sizeof(*temp));
	s = stack_new();
	low = 0;
	high = n-1;
	uni = 1;
	sorted = 1;
	from = 1;
	to = 0;
	type = 'N'; /* nonsense, type is for the use of mergesort */
	stack_push(s, (void*)item);  /* make the stack not empty */
	while (!stack_isEmpty(s)) {
		/* push the range to be partitioned into the stack and
		   pop out to partition again */
		while (low <= high) {
			loc = partition(A+low, n, A[low], cmp) + low;
			from = loc;
			to = high;
			/* do not push uniform array */
			for (i=loc;i<high;i++) {
				if (cmp(A[i+1],A[i])!=0) {
					uni = 0;
				}
			}
			/* if the number of array does not change, the first item is
			the smallest one , so go to the next item*/
			if (high-loc+1==n) {
				from++;
			}
			/* check if what's go into the stack is sorted */
			for (i=loc;i<high;i++) {
				if (cmp(A[i],A[i+1])>0) {
					sorted = 0;
				}
			}
			if (from!=to && !uni && !sorted) {
				item = frame_new(from,to,type);
				stack_push(s, (void*)item);
			}
			high = loc - 1;
			n = high - low + 1;
			uni = 1;
			sorted = 1;
		}
		temp = (Frame*)stack_pop(s);
		low = temp->from;
		high = temp->to;
		n = high - low + 1;
	}
    return;
}
