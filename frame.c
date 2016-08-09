/*
A frame containing two ints indicating the range to be processed
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "frame.h"

/*
Create a new frame with values <start end>
and return a pointer to that frame.
*/
Frame *frame_new(int low, int high, char type) {
    Frame *f = (Frame *)malloc(sizeof(Frame));
    assert(f);
    f->from = low;
    f->to = high;
    f->type = type;
    return f;
}