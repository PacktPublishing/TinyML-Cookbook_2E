#include "arm_math.h"

void init_random(float* src, int32_t sz) {
  for(int32_t i = 0; i < sz; ++i) {
    src[i] = (float)random(0, 99) / 100.0f;
  }
}

void mat_mul(float* lhs, float* rhs, float* dst, int32_t M, int32_t N, int32_t K) {
  arm_matrix_instance_f32 lhs_i, rhs_i, dst_i;

  lhs_i.numRows = M;
  lhs_i.numCols = K;
  lhs_i.pData = lhs;

  rhs_i.numRows = K;
  rhs_i.numCols = N;
  rhs_i.pData = rhs;

  dst_i.numRows = M;
  dst_i.numCols = N;
  dst_i.pData = dst;

  arm_mat_mult_f32(&lhs_i, &rhs_i, &dst_i);
}

void sigmoid(float* src, float* dst, int32_t sz) {
  for(int32_t i = 0; i < sz; ++i) {
    float x = -src[i];
    arm_vexp_f32(&x, &x, 1);
    dst[i] = 1.0f / (1.0f + x);
  }
}

void d_sigmoid(float* src, float* dst, int32_t sz) {
  for(int32_t i = 0; i < sz; ++i) {
    float x = src[i];
    dst[i] = x * (1.0f - x);
  }
}

void fc_sigmoid(float* src, // input
              float* w, // weights
              float* b, // biases
              float* dst, // destination
              int32_t src_sz, int32_t dst_sz) {

  mat_mul(src, w, dst, 1, dst_sz, src_sz);

  // Add bias
  arm_add_f32(dst, b, dst, dst_sz);

  // Sigmoid activation
  sigmoid(dst, dst, dst_sz);
}

class NN {
  public:
  NN(int32_t input_sz, int32_t out_fc0_sz, int32_t out_fc1_sz) {

    _input_sz = input_sz;
    _out_fc0_sz = out_fc0_sz;
    _out_fc1_sz = out_fc1_sz;

    // Allocate weights and biases
    _w0 = new float[input_sz * out_fc0_sz];
    _b0 = new float[out_fc0_sz];
    _w1 = new float[out_fc0_sz * out_fc1_sz];
    _b1 = new float[out_fc1_sz];

    _w0_1 = new float[input_sz * out_fc0_sz];
    _b0_1 = new float[out_fc0_sz];
    _w1_1 = new float[out_fc0_sz * out_fc1_sz];
    _b1_1 = new float[out_fc1_sz];

    _out_fc0 = new float[out_fc0_sz];
    _out_fc1 = new float[out_fc1_sz];

    _e_out_fc0 = new float[out_fc0_sz];
    _d_out_fc0 = new float[out_fc0_sz];
    _e_out_fc1 = new float[out_fc1_sz];
    _d_out_fc1 = new float[out_fc1_sz];

    init_random(_w0, input_sz * out_fc0_sz);
    init_random(_b0, out_fc0_sz);
    init_random(_w1, out_fc0_sz * out_fc1_sz);
    init_random(_b1, out_fc1_sz);
  };

  ~NN() {
    delete[] _w0;
    delete[] _b0;
    delete[] _w1;
    delete[] _b1;
    delete[] _w0_1;
    delete[] _b0_1;
    delete[] _w1_1;
    delete[] _b1_1;
    delete[] _out_fc0;
    delete[] _out_fc1;
    delete[] _e_out_fc0;
    delete[] _d_out_fc0;
    delete[] _e_out_fc1;
    delete[] _d_out_fc1;
  }

  float* forward(float* x) {
    fc_sigmoid(x, _w0, _b0, _out_fc0, _input_sz, _out_fc0_sz);
    fc_sigmoid(_out_fc0, _w1, _b1, _out_fc1, _out_fc0_sz, _out_fc1_sz);

    return _out_fc1;
  }

  void backward(float* x, float* y) {

    // Error fully connected 1
    _e_out_fc1[0] = y[0] - _out_fc1[0];

    // Delta fully connected 1
    delta(_out_fc1, _e_out_fc1, _d_out_fc1, _out_fc1_sz);
    //-------------------------

    // Error fully connected 0 - last layer
    arm_matrix_instance_f32 w1_i, w1T_i;

    w1_i.numRows = _out_fc0_sz;
    w1_i.numCols = _out_fc1_sz;
    w1_i.pData = _w1;

    w1T_i.numRows = _out_fc1_sz;
    w1T_i.numCols = _out_fc0_sz;
    w1T_i.pData = _w1_1;

    arm_mat_trans_f32(&w1_i, &w1T_i);

    mat_mul(_d_out_fc1, _w1_1, _e_out_fc0, 1, _out_fc0_sz, _out_fc1_sz);

    // Delta fully connected 0 - hidden layer
    delta(_out_fc0, _e_out_fc0, _d_out_fc0, _out_fc0_sz);

    // Update weights and biases
    update_weights_biases(x, 0.1);
  }
  private:

  void delta(float* out_fc, float* err, float* delta, int32_t out_fc_sz) {
    d_sigmoid(out_fc, delta, out_fc_sz);

    arm_mult_f32(delta, err, delta, out_fc_sz);
  }

  void update_weights_biases(float* x, float lr) {
    int32_t w0_total_sz = _out_fc0_sz * _input_sz;
    int32_t w1_total_sz = _out_fc0_sz * _out_fc1_sz;
    int32_t b0_total_sz = _out_fc0_sz;
    int32_t b1_total_sz = _out_fc1_sz;

    // Weights adjustment - Fully connected 0
    mat_mul(x, _d_out_fc0, _w0_1, _input_sz, _out_fc0_sz, 1);
    arm_scale_f32(_w0_1, lr, _w0_1, w0_total_sz);

    // Weights adjustment - Fully connected 1
    mat_mul(_out_fc0, _d_out_fc1, _w1_1, _out_fc0_sz, _out_fc1_sz, 1);
    arm_scale_f32(_w1_1, lr, _w1_1, w1_total_sz);

    // Biases adjustment - Fully connected 0
    arm_scale_f32(_d_out_fc0, lr, _b0_1, b0_total_sz);

    // Biases adjustment - Fully connected 1
    arm_scale_f32(_d_out_fc1, lr, _b1_1, b1_total_sz);

    // Update weights and biases
    arm_add_f32(_w0, _w0_1, _w0, w0_total_sz);
    arm_add_f32(_w1, _w1_1, _w1, w1_total_sz);
    arm_add_f32(_b0, _b0_1, _b0, b0_total_sz);
    arm_add_f32(_b1, _b1_1, _b1, b1_total_sz);
  }

  float* _w0 {nullptr};
  float* _b0 {nullptr};
  float* _w1 {nullptr};
  float* _b1 {nullptr};

  float* _w0_1 {nullptr};
  float* _b0_1 {nullptr};
  float* _w1_1 {nullptr};
  float* _b1_1 {nullptr};

  float* _out_fc0 {nullptr};
  float* _out_fc1 {nullptr};
  float* _e_out_fc0 {nullptr};
  float* _d_out_fc0 {nullptr};
  float* _e_out_fc1 {nullptr};
  float* _d_out_fc1 {nullptr};

  int32_t _input_sz {0};
  int32_t _out_fc0_sz {0};
  int32_t _out_fc1_sz {0};
};

NN nn(3, 3, 1);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  randomSeed(analogRead(0));

  float X[8][3] = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 1.0f}
  };

  float Y[8] = {0.0f, 1.0f, 1.0f, 0.0f, /* XOR */
                1.0f, 1.0f, 1.0f, 0.0f  /* NAND */};

  const int32_t num_epochs = 10000;

  for(int32_t epoch = 0; epoch < num_epochs; ++epoch) {
    float loss = 0.0;
    int32_t num_correct_pred = 0;

    for(int32_t smp_idx = 0; smp_idx < 8; ++smp_idx) {
      float *input        = &X[smp_idx][0];
      float *actual_out   = &Y[smp_idx];

      // Forward
      float *predicted_out = nn.forward(input);

      // Update accuracy
      if(round(predicted_out[0]) == actual_out[0]) {
        num_correct_pred++;
      }

      // Update loss
      float err = (actual_out[0] - predicted_out[0]);
      loss += (err * err) / 8.0f;

      // Backward
      nn.backward(input, actual_out);
    }

    if((epoch % 100) == 0) {
      float acc = num_correct_pred / 8.0f;
      Serial.print(loss);
      Serial.print(",");
      Serial.println(acc);
    }
  }
  Serial.println("Training finished!");
}

void loop() {

}
