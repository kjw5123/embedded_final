#ifndef FFT_H
#define FFT_H

#include <math.h> // cos, sin, log 등의 함수를 사용하기 위해서
#include <stdio.h> // 기본 입출력
#include <string.h> // 테라텀 출력용

#define PI                      3.14159265358979 // pi 값
#define CNT                     128 // adc로 읽어들일 값의 개수 (128개 달성 시 FFT 함수 호출)
#define SAMPLING_RATE           10000 // 100us마다 adc를 진행하기 때문에

extern double RealNum[128]; // ADC 값 저장용 버퍼 및 FFT 진행 후 계산되는 실수부 배열
extern double ImageNum[128]; //FFT를 통해 계산되는 허수부 배열
extern double SIN[64]; // 주기에 따른 sin파, fft 1회 호출 후 지속 저장
extern double COS[64]; // 주기에 따른 cos파, fft 1회 호출 후 지속 저장
extern uint16_t Amplitude[16];

// math.h의 log() 함수는 밑이 e인데, 여기선 밑이 2여야 하므로 직접 구현
double logB(double antilog, double base) { //log_m(N) 구현용
  return log(antilog) / log(base);  //base가 log의 밑으로, antilog가 로그의 진수로 지닌 값이 반환된다.
}

int fft(long N) { // fft 시작, 개수는 ADC가 128개 다 채웠을 때 시작할 것이므로, N 파라미터는 대게 128이 입력될 것
  
  if ((N != 0) && ((N & (N - 1)) != 0)) { // 입력된 값의 개수가 2의 제곱(128 = 2^7)이 아니면 종료
    return -1;
  }
  
  int log2N = (int)logB(N, 2); // log_2(N)의 정수 값 ( = 7)
  
  // 비트 뒤집기. 분할/정복 중 분할에 해당
  // 추가적인 메모리 호출 없이 제자리 계산
  // 이 과정을 통해 인덱스를 fft 연산에 용이한 형태로 변환
  double temp; 
  for (long n = 1; n < N - 1; n++) { // 1~6에 대해 0과 7은 비트 반전 해도 값이 그대로다.
    long m = 0;
    
    for (int i = 0; i < log2N; i++) {
      m |= ((n >> i) & 1) << (log2N - i - 1);
    }
    
    if (n < m) { // 중복 교환 방지용.
      temp = RealNum[n];
      RealNum[n] = RealNum[m];
      RealNum[m] = temp;
    }
  }
  
  // 본격적인 연산 시작 전, 허수부 배열 초기화.
  for (int i = 0; i < 128; i++) { 
    ImageNum[i] = 0;
  }
  
  // 영역을 지정해가면서 연산 진행. 외부의 loop가 반복될수록, 2, 4, 8 ... 이런식으로 region이 넓어짐
  // region이 넓어짐에 따라, 배열을 건너 뛰어야 하게 됨. 나비형 패턴을 위한 구현
  for (int time = 0; time < log2N; time++) {
    int regionSize = 1 << (time + 1);
    int kJump = 1 << (log2N - time - 1);
    int half = regionSize >> 1;
    
    for (int i = 0; i < N; i += regionSize) {
      int blockEnd = i + half - 1;
      int k = 0;
      double TR, TI;
      
      for (long j = i; j <= blockEnd; j++) {
        TR = COS[k] * RealNum[j + half] - SIN[k] * ImageNum[j + half];
        TI = SIN[k] * RealNum[j + half] + COS[k] * ImageNum[j + half];
        
        RealNum[j + half] = RealNum[j] - TR;
        ImageNum[j + half] = ImageNum[j] - TI;
        
        RealNum[j] = RealNum[j] + TR;
        ImageNum[j] = ImageNum[j] + TI;
        
        k += kJump;
      }
    }
  }
  return 0;
}

// 0~1023까지 값을 변환할 것이므로, 이렇게 진행하게 됨.
// atmega 용량이 감당 못하거나, 속도 부족 시 개량 필요
// 단, double 자료형의 정수부가 11비트다 보니,
// int8_t로 re와 im에 대한 형 변환은 불가능함
// 개량 필요 시 많은 고민 필요 -> 개량 할 필요 우선 X
// 아무튼, 진폭 세기 계산 알고리즘 (sqrt 미사용, 비트 단위 연산)
uint16_t fftAmplitude(int16_t re, int16_t im) {
  uint32_t bit = ((uint32_t)1) << 30;
  uint32_t num = ((uint32_t)re)*re + ((uint32_t)im) * im;
  uint32_t res = 0;
  
  while (bit > num) {
    bit >>= 2;
  }
  
  while (bit != 0) {
    if (num >= res + bit) {
      num -= res + bit;
      res = (res >> 1) + bit;
    } else {
      res >>= 1;
    }
    bit >>= 2;
  }
  return ((uint16_t) res);
}

// void printAmplitude(int N) {
//   double frequency_interval = (double)SAMPLING_RATE / N * 2; // 156.5 저장된다.
//   for (int i = 0; i < 32; i++) {
//     uint16_t frequency_amplitude = fftAmplitude((int16_t)RealNum[i+1], (int16_t)ImageNum[i+1]);
//     if (i % 2 == 0) {
//       Amplitude[i/2] = frequency_amplitude;
//     }
//     //%lf, %f 등 c언어 출력 함수 사용 불가해서, double -> int16_t로 명시적 형 변환 진행
//     printf("%dHz : %d", (uint16_t)frequency_interval*(i+1), frequency_amplitude);
//     // 주파수 별 성분 막대 그래프 모양으로 출력
//     printf("\n"); 
//   }
// }
void setAmplitude(){ // lcd 출력용 Amplitude 배열 설정
  for (int i = 0; i < 32; i++) {
    uint16_t frequency_amplitude = fftAmplitude((int16_t)RealNum[i+1], (int16_t)ImageNum[i+1]);
    if (i % 2 == 0) {
      Amplitude[i/2] = frequency_amplitude / 400;
    }
  }
}

#endif // FFT_H
