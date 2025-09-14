#ifndef ADC_H
#define ADC_H

#include "FFT.h"
#include "BUTTON.h"
#include "LCD.h"

#define F_CPU                                         16000000L

//기본 수치 - 2.5v 참조 때에 비해 값 반 정도로 줄었.
#define ADC_MIN                                       190
#define ADC_AVR                                       384
#define ADC_MAX                                       580

volatile uint8_t sampleIndex = 0;
extern double RealNum[128]; // 샘플을 저장할 배열 외부 참조
extern uint16_t Amplitude[16]; // 

void TerminalClear(uint16_t ms) {
  while (ms--) {
      for (int16_t i = 0; i < 16000; i++) {
        _NOP();
      }
  }
  // tera term용 clear
  printf("\033[2J");
  printf("\033[H");
}

void ADC_init() {
    // ADC 초기화 (PF2 핀 사용)
    ADC_CTRLA = 0x01 | (0x00 << 2); // ADC 활성화 및 10비트 해상도 설정
    
    /* 프리스케일러 설정 (ADC 클럭을 시스템 클럭의 1/64로 설정,
       분주기를 따로 설정하지 않으면, 8MHz로 작동하는데, 특정 범위를
       넘어서면 측정이 제대로 이루어지지 않는다.
       즉 1/4MHz = 4us, 4 * 13 = 52us라 100us 이내이니 괜찮다.)
       내부 참조 전압 사용(4.34V) */
    ADC_CTRLC = (0x05 << 0) | (0x00 << 4);

    VREF_CTRLA = (0x03 << 4);  // 4.34V 수정 (저음역대는 2.5V 넘을 때가 잦아서)

    ADC_MUXPOS = (0x0C << 0); // ADC 채널 설정 (F 2 핀, AIN12)
    ADC_CTRLA |= 0x02; // 프리런 모드 활성화
    ADC_COMMAND = 0x01; // 변환 시작한다.

    // 타이머 설정 (100us 마다 인터럽트 발생)
    TCA_CTRLA = (0x00 << 1); // 분주기 활성 X
    TCA_PER = 1599; // 16000000 / 10000 - 1
    TCA_CTRLB = (0x00 << 0); // 일반 모드
    TCA_INTCTRL = 0x01; // 오버플로우 인터럽트 활성화
    TCA_CTRLA = 0x01; // 타이머 시작
}

// 실제로 사용할거
ISR(TCA0_OVF_vect) {
    // 100us마다 ADC 샘플링
    if (sampleIndex < 128) { 
      while (!(ADC_INTFLAGS & 0x01));
        RealNum[sampleIndex] = (ADC_RES - ADC_AVR) / (double)(ADC_MAX-ADC_AVR);
        sampleIndex++;
    }

    if (sampleIndex >= 128) {
        // 샘플링 완료, FFT 수행
        fft(128);
        // printAmplitude(SAMPLES); // 기존 터미널 출력용 코드
        setAmplitude();
        LCD_print_ADC();
        sampleIndex = 0; // 다음 샘플링을 위해 인덱스 초기화
        // TerminalClear(1000);
    }

    // 인터럽트 플래그 클리어
    TCA_INTFLAGS = 0x01;

    if (PORTD_INTFLAGS & 0x10) { // D 4
        VOLUME_UP();
        PORTD_INTFLAGS = 0x10;
        printf("volume up\n");
    }
    if (PORTD_INTFLAGS & 0x20) { // D 5
        VOLUME_DOWN();
        PORTD_INTFLAGS = 0x20;
        printf("volume_down\n");
    }
    if (PORTD_INTFLAGS & 0x40) { // D 6
        PAUSEorPLAY();
        PORTD_INTFLAGS = 0x40;
        printf("pause or play\n");
    }
    if (PORTD_INTFLAGS & 0x80) { // D 7
        NEXT_TRACK();
        PORTD_INTFLAGS = 0x80;
        printf("next track\n");
    }
    if(PORTE_INTFLAGS & 0x01){ // E 0
        PREVIOUS_PIECE();
        PORTE_INTFLAGS = 0x01;
        printf("previous piece\n");
    }
}
#endif