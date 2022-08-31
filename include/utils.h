

#define SIGMOID(x) ((1.0) / (1.0 + exp(-x)))
#define RAND_INT(min,max) min + rand() % (max+1 - min)
#define RAND_DOUBLE(min,max) min + (double)(rand() / (static_cast <double> (RAND_MAX/(max-min))))
#define RAND_FLOAT(min,max) min + (float)(rand() / (static_cast <float> (RAND_MAX/(max-min))))
#define NORMALIZE_VALUE(VALUE,MIN,MAX) (double)((VALUE - MIN)  / (double)(MAX-MIN))