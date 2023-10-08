#include <arm_math.h>
#include "mbed.h"

#include "mfccs_consts.h"
#include "dct_wei_mtx_q15_T.h"
#include "hann_lut_q15.h"
#include "log_lut_q13_3.h"
#include "mel_wei_mtx_q15_T.h"
#include "test_src.h"
#include "test_dst.h"

class MFCC_Q15 {
public:
  MFCC_Q15() {
    // RFFT instance
    arm_rfft_init_q15(&_rfft_inst, FFT_LENGTH, 0, 1);

    // Mel-weight matrix instance
    _mel_wei_mtx_inst.numRows = mel_wei_mtx_q15_T_dim1;
    _mel_wei_mtx_inst.numCols = mel_wei_mtx_q15_T_dim0;
    _mel_wei_mtx_inst.pData = (q15_t *)&mel_wei_mtx_q15_T_data[0];

    // DCT-weight matrix instance
    _dct_wei_mtx_inst.numRows = dct_wei_mtx_q15_T_dim1;
    _dct_wei_mtx_inst.numCols = dct_wei_mtx_q15_T_dim0;
    _dct_wei_mtx_inst.pData = (q15_t *)&dct_wei_mtx_q15_T_data[0];
  }

  void run(const q15_t* src, float* dst) {
    for(int i = 0; i < NUM_FRAMES; ++i ) {
      // Apply the Hann window
      arm_mult_q15((q15_t*)&src[i * FRAME_STEP], (q15_t*)hann_lut_q15_data, _bufA, FRAME_LENGTH);

      // Calculate the RFFT
      arm_rfft_q15(&_rfft_inst, _bufA, _bufB);

      // Calculate the magnitude
      _bufA[0]                 = _bufB[0];
      _bufA[NUM_FFT_FREQS - 1] = _bufB[1];
      arm_cmplx_mag_q15(&_bufB[2], &_bufA[1], NUM_FFT_FREQS - 2);

      // Mel-scale conversion
      arm_mat_vec_mult_q15(&_mel_wei_mtx_inst, _bufA, _bufB);

      for(int idx = 0; idx < NUM_MEL_FREQS; ++idx) {
        const int16_t val = (int16_t)_bufB[idx];
        _bufA[idx] = log_lut_q13_3_data[val];
      }

      // Calculate the MFCCs through the DCT
      arm_mat_vec_mult_q15(&_dct_wei_mtx_inst, _bufA, _bufB);

      for(int k = 0; k < NUM_MFCCS; ++k) {
        dst[k + i * NUM_MFCCS] = ((float)_bufB[k] / (float)(8.f));
      }
    }
  }
private:
  arm_rfft_instance_q15   _rfft_inst;
  arm_matrix_instance_q15 _mel_wei_mtx_inst;
  arm_matrix_instance_q15 _dct_wei_mtx_inst;
  q15_t                   _bufA[FRAME_LENGTH];
  q15_t                   _bufB[FRAME_LENGTH * 2];
};

MFCC_Q15 mfccs;

#define DST_SIZE (NUM_FRAMES * NUM_MFCCS)
static float dst[DST_SIZE];

void setup() {
  Serial.begin(115200);
  while (!Serial);
}

void loop() {

  mbed::Timer timer;

  // Start timer
  timer.start();

  // MFCC computation
  mfccs.run(test_src_data, dst);

  // Stop timer
  auto t0 = timer.elapsed_time();

  using std::chrono::duration_cast;
  using std::chrono::microseconds;
  auto t_diff = duration_cast<microseconds>(t0);

  Serial.print("Exec. time [ms]: ");
  Serial.println(t_diff.count() * 0.001, 2);

  for(int i = 0; i < DST_SIZE; ++i) {
    float v0 = dst[i];
    float v1 = test_dst_data[i];

    // 1-bit is the maximum error (1/8 = 0.125)
    if(abs(v0 - v1) > 0.125f) {
      Serial.println("TEST FAILED");
      while(1);
    }
  }

  Serial.println("TEST PASSED");
  while(1);
}
