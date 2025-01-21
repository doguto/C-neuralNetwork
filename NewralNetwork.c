#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INPUT_AMOUNT 6
#define HIDDEN_LAYER_AMOUNT 2
#define HIDDEN_LAYER_SIZE 10

typedef struct
{
    double input[6];
    double hiddenParams[HIDDEN_LAYER_AMOUNT][HIDDEN_LAYER_SIZE];
} NewralNetwork;

/// 活性化関数
double Activate(double x)
{
    
}