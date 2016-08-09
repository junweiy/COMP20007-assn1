
typedef struct {
    int from;      
    int to;
    char type;    
} Frame;

Frame *frame_new(int low, int high, char type);
