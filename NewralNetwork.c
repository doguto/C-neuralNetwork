#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INPUT_AMOUNT 6
#define HIDDEN_LAYER_AMOUNT 2
#define HIDDEN_LAYER_SIZE 10


typedef struct
{
    double inputs[INPUT_AMOUNT];
    double hiddenParams[HIDDEN_LAYER_AMOUNT][HIDDEN_LAYER_SIZE];
} NewralNetwork;

double Log2(double x)
{
    /// マクローリン展開に基づく近似式
    double t = x - 1;
    return (t - t*t/2 + t*t*t/3) / 0.693;
}

/// 活性化関数
double Activate(double x)
{
    
}

/// 損失関数(交差エントロピー法)
double CalcurateLose(int answer, double* probability, int length)
{
    /// log0の発生を防ぐため、1e-12を加算
    double lose = -Log2(probabloty[answer] + 1e-12);
    return lose;
}
