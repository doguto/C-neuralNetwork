#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INPUT_AMOUNT 6
#define OUTPUT_AMOUNT 6
#define HIDDEN_LAYER_AMOUNT 2
#define HIDDEN_LAYER_SIZE 10

typedef struct {
  double inputs[INPUT_AMOUNT];
  double hiddenLayerCoefs[HIDDEN_LAYER_AMOUNT][HIDDEN_LAYER_SIZE]
                         [HIDDEN_LAYER_SIZE + 1];
  double outputs[OUTPUT_AMOUNT];
} NewralNetwork;

/// マクローリン展開に基づくlog2(x)の近似式
double Log(double x) {
  double t = x - 1;
  return (t - t * t / 2 + t * t * t / 3);
}

/// マクロ―リン展開に基づくe^xの近似式
double Exp(double x) { return (1 + x + x * x / 2 + x * x * x / 6); }

void SetInputs(NewralNetwork *network, double *inputs, int length) {
  for (int i = 0; i < length; i++) {
    network->inputs[i] = inputs[i];
  }
}

/// 活性化関数(ReLU関数)
double ActivateByReLU(double x, double coef) { return (x < 0) ? 0 : coef * x; }

/// 活性化関数(SoftMax関数)
double ActivateBySoftMax(double *params, int length, int index) {
  double sum = 0;
  for (int i = 0; i < length; i++) {
    sum += Exp(params[i]);
  }
  return Exp(params[index]) / sum;
}

/// 活性化関数(ReLU関数)の使用
double SummarizeActivatedInputs(double *inputs, NewralNetwork *network,
                                int layerY, int layerX) {
  double sum = 0;
  for (int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
    sum +=
        ActivateByReLU(inputs[i], network->hiddenLayerCoefs[layerY][layerX][i]);
  }
  sum += network->hiddenLayerCoefs[layerY][layerX][HIDDEN_LAYER_SIZE];
  return sum;
}

/// 損失関数(交差エントロピー法)
double CalcurateLose(int answer, double *probability, int length) {
  /// log0の発生を防ぐため、1e-12を加算
  double lose = -Log(probability[answer] + 1e-12);
  return lose;
}

void RunNewralNetwork(NewralNetwork *network, double *inputs, int inputLength) {
  double data[HIDDEN_LAYER_AMOUNT][HIDDEN_LAYER_SIZE] = {0};
  for (int y = 0; y < HIDDEN_LAYER_AMOUNT; y++) {
    for (int x = 0; x < HIDDEN_LAYER_SIZE; x++) {
      if (y == 0) {
        data[y][x] = SummarizeActivatedInputs(inputs, network, y, x);
        continue;
      }
      data[y][x] = SummarizeActivatedInputs(&data[y - 1][0], network, y, x);
    }
  }
  for (int i = 0; i < OUTPUT_AMOUNT; i++) {
    network->outputs[i] =
        ActivateBySoftMax(&data[HIDDEN_LAYER_AMOUNT - 1][0], OUTPUT_AMOUNT, i);
  }
}

void Learn();
