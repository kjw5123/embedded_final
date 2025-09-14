#include "FFT.h"
#include "UART.h"
#include "ADC.h"
#include "BUTTON.h"
#include "LCD.h"
#include "MACRO.h"
#define PI                      3.14159265358979 // pi 값
// ATmega4809 MCU 기반 프로젝트입니다.

// FFT 계산에 필요한 버퍼 정의
double RealNum[128]; // 실수부 버퍼
double ImageNum[128]; //FFT를 통해 계산되는 허수부 버퍼
double SIN[64]; // 주기에 따른 sin파, fft 1회 호출 후 지속 저장
double COS[64]; // 주기에 따른 cos파, fft 1회 호출 후 지속 저장
uint16_t Amplitude[16];


void setup() {
  // UART 초기화
  USART1_init();  
  // 표준 출력 스트림 설정, printf 쓰게
  setupUSART1Stream(); // stdout = &FILE_STREAM
  // 시리얼 초기화
  buttonInit();
  TWI_init(); // 100kHz로 I2C 초기화
  LCD_init();
  LCD_custom_char(0, level1); // MACRO.h에 지정된 글씨들 CG-ROM에 저장
  LCD_custom_char(1, level2);
  LCD_custom_char(2, level3);
  LCD_custom_char(3, level4);
  LCD_custom_char(4, level5);
  LCD_custom_char(5, level6);
  LCD_custom_char(6, level7);
  LCD_custom_char(7, level8);
  // 2pi라는 1주기를 진동수에 해당하는 N으로 나눈다.
  // 즉, T = 주기 (2 * pi / 128)
  double T = 2 * PI / 128;
  for (long i = 0; i < 64; i++) {
    COS[i] = cos(T * i);
    SIN[i] = -sin(T * i);
  }
  ADC_init(); 
}

void loop() {
  // printf("hello");
  // loop 비워져있는게 정상입니다.
  // 인터럽트로만 코드 진행돼요.
}
