#ifndef MACRO_H
#define MACRO_H

/*---------------------default----------------------*/
#define DIRA (*((volatile unsigned char*) 0x0400)) // 포트 A 입, 출력 방향 설정
#define PORTA (*((volatile unsigned char*) 0x0404)) // 포트 A 출력 값
#define PORTA_PIN0CTRL  (*((volatile unsigned char*) 0x0410))
#define PORTA_PIN1CTRL  (*((volatile unsigned char*) 0x0411))
#define PORTA_PIN2CTRL  (*((volatile unsigned char*) 0x0412))
#define PORTA_PIN3CTRL  (*((volatile unsigned char*) 0x0413))
#define PORTA_PIN4CTRL  (*((volatile unsigned char*) 0x0414))
#define PORTA_PIN5CTRL  (*((volatile unsigned char*) 0x0415))
#define PORTA_PIN6CTRL  (*((volatile unsigned char*) 0x0416))
#define PORTA_PIN7CTRL  (*((volatile unsigned char*) 0x0417))

#define DIRC (*((volatile unsigned char*) 0x0440)) // 포트 C 입, 출력 방향 설정
#define PORTC (*((volatile unsigned char*) 0x0444)) // 포트 C 출력 값
#define PORTC_PIN0CTRL  (*((volatile unsigned char*) 0x0450))
#define PORTC_PIN1CTRL  (*((volatile unsigned char*) 0x0451))
#define PORTC_PIN2CTRL  (*((volatile unsigned char*) 0x0452))
#define PORTC_PIN3CTRL  (*((volatile unsigned char*) 0x0453))
#define PORTC_PIN4CTRL  (*((volatile unsigned char*) 0x0454))
#define PORTC_PIN5CTRL  (*((volatile unsigned char*) 0x0455))
#define PORTC_PIN6CTRL  (*((volatile unsigned char*) 0x0456))
#define PORTC_PIN7CTRL  (*((volatile unsigned char*) 0x0457))

#define DIRD (*((volatile unsigned char*) 0x0460)) // 포트 D 입, 출력 방향 설정
#define PORTD_DIRCLR  (*((volatile unsigned char*) 0x0462)) // 포트 D 입력 값
#define PORTD (*((volatile unsigned char*) 0x0464)) // 포트 D 출력 값
#define PORTD_PIN0CTRL  (*((volatile unsigned char*) 0x0470))
#define PORTD_PIN1CTRL  (*((volatile unsigned char*) 0x0471))
#define PORTD_PIN2CTRL  (*((volatile unsigned char*) 0x0472))
#define PORTD_PIN3CTRL  (*((volatile unsigned char*) 0x0473))
#define PORTD_PIN4CTRL  (*((volatile unsigned char*) 0x0474))
#define PORTD_PIN5CTRL  (*((volatile unsigned char*) 0x0475))
#define PORTD_PIN6CTRL  (*((volatile unsigned char*) 0x0476))
#define PORTD_PIN7CTRL  (*((volatile unsigned char*) 0x0477))
#define PORTD_INTFLAGS  (*((volatile unsigned char*) 0x0469))

#define DIRE (*((volatile unsigned char*) 0x0480)) // 포트 E 입, 출력 방향 설정
#define PORTE_DIRCLR (*((volatile unsigned char*) 0x0482)) // 포트 E 입력 값
#define PORTE (*((volatile unsigned char*) 0x0484)) // 포트 E 출력 값
#define PORTE_PIN0CTRL  (*((volatile unsigned char*) 0x0490))
#define PORTE_PIN1CTRL  (*((volatile unsigned char*) 0x0491))
#define PORTE_PIN2CTRL  (*((volatile unsigned char*) 0x0492))
#define PORTE_PIN3CTRL  (*((volatile unsigned char*) 0x0493))
#define PORTE_PIN4CTRL  (*((volatile unsigned char*) 0x0494))
#define PORTE_PIN5CTRL  (*((volatile unsigned char*) 0x0495))
#define PORTE_PIN6CTRL  (*((volatile unsigned char*) 0x0496))
#define PORTE_PIN7CTRL  (*((volatile unsigned char*) 0x0497))
#define PORTE_INTFLAGS  (*((volatile unsigned char*) 0x0489))

#define DIRF (*((volatile unsigned char*) 0x04A0)) // 포트 F 입, 출력 방향 설정
#define PORTF (*((volatile unsigned char*) 0x04A4)) // 포트 F 출력 값
#define PORTF_PIN0CTRL  (*((volatile unsigned char*) 0x04B0))
#define PORTF_PIN1CTRL  (*((volatile unsigned char*) 0x04B1))
#define PORTF_PIN2CTRL  (*((volatile unsigned char*) 0x04B2))
#define PORTF_PIN3CTRL  (*((volatile unsigned char*) 0x04B3))
#define PORTF_PIN4CTRL  (*((volatile unsigned char*) 0x04B4))
#define PORTF_PIN5CTRL  (*((volatile unsigned char*) 0x04B5))
#define PORTF_PIN6CTRL  (*((volatile unsigned char*) 0x04B6))
#define PORTF_PIN7CTRL  (*((volatile unsigned char*) 0x04B7))

// /*---------------------SPI for LED control-----------------------*/
// 아쉽지만 안쓴다..
// // 1bit -> HIGH(1) 5클럭(=0.625us) / LOW(0) 5클럭(=0.625us)
// // 해당 패턴을 통해 4개의 1 신호 입력
// uint8_t high_pattern_1 = 0b11111000; 
// uint8_t high_pattern_2 = 0b00111110; 
// uint8_t high_pattern_3 = 0b00001111; 
// uint8_t high_pattern_4 = 0b10000011; 
// uint8_t high_pattern_5 = 0b11100000; 

// // 0bit -> HIGH(1) 3클럭(=0.375us) + LOW(0) 7클럭(=0.875us)
// // 해당 패턴을 통해 4개의 0 신호 입력
// uint8_t low_pattern_1 = 0b11100000; 
// uint8_t low_pattern_2 = 0b00111000; 
// uint8_t low_pattern_3 = 0b00001110; 
// uint8_t low_pattern_4 = 0b00000011; 
// uint8_t low_pattern_5 = 0b10000000;

// uint8_t pattern1[5] = {high_pattern_1 ,high_pattern_2, high_pattern_3, high_pattern_4, high_pattern_5};
// uint8_t pattern0[5] = {low_pattern_1, low_pattern_2, low_pattern_3, low_pattern_4, low_pattern_5}; 

/*---------------------ADC-----------------------*/

#define VREF_CTRLA  (*((volatile unsigned char*) 0x00A0)) // 4.34v 내부 참조 전압 사용하기 위해

#define ADC_CTRLA (*((volatile unsigned char*) 0x0600)) // resolution
#define ADC_CTRLB (*((volatile unsigned char*) 0x0601)) // accumulation
#define ADC_CTRLC (*((volatile unsigned char*) 0x0602))
#define ADC_CTRLD (*((volatile unsigned char*) 0x0603))
#define ADC_MUXPOS (*((volatile unsigned char*) 0x0606))
#define ADC_COMMAND (*((volatile unsigned char*) 0x0608))
#define ADC_INTCTRL (*((volatile unsigned char*) 0x060A))
#define ADC_INTFLAGS (*((volatile unsigned char*) 0x060B))
#define ADC_RES (*((volatile uint16_t*) 0x0610)) // RES total
#define ADC_RESL (*((volatile unsigned char*) 0x0610)) // RES[7:0]
#define ADC_RESH (*((volatile unsigned char*) 0x0611)) // RES[15:8]

/*---------------------BUTTON--------------------*/
#define PORTD_INTFLAGS (*((volatile unsigned char*) 0x0469))
#define PORTE_INTFLAGS  (*((volatile unsigned char*) 0x0489))
/*---------------------LCD---------------------*/

#define TWI_CTRLA (*((volatile uint8_t*) 0x08A0))
#define TWI_MCTRLA (*((volatile uint8_t*) 0x08A3))
#define TWI_MCTRLB (*((volatile uint8_t*) 0x08A4))
#define TWI_MSTATUS (*((volatile uint8_t*) 0x08A5))
#define TWI_MBAUD (*((volatile uint8_t*) 0x08A6))
#define TWI_MADDR (*((volatile uint8_t*) 0x08A7))
#define TWI_MDATA (*((volatile uint8_t*) 0x08A8))

#define WRITEBIT 0x00 // SCL + W
#define ACK 1
#define NACK 0

//level0은 공백 문잔데, CG_ROM 위치 11111110(0xFE)에 위치함
//LCD_send_data(0xFE)로 대체한다.

uint8_t level1[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111
};

uint8_t level2[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111
};

uint8_t level3[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111
};

uint8_t level4[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
uint8_t level5[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
uint8_t level6[8] = {
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
uint8_t level7[8] = {
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
uint8_t level8[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
/*---------------------TCA-----------------------*/
// ADC 100us 간격으로 샘플링하게끔 설정 아래는 전부 single모드
#define TCA_CTRLA (*((volatile unsigned char*) 0x0A00)) // 몇 분주, TCA Enable
#define TCA_CTRLB (*((volatile unsigned char*) 0x0A01)) // 비교 채널 활성화 여부
#define TCA_CTRLC (*((volatile unsigned char*) 0x0A02))
#define TCA_CTRLD (*((volatile unsigned char*) 0x0A03))
#define TCA_CTRLESET (*((volatile unsigned char*) 0x0A05))
#define TCA_EVCTRL (*((volatile unsigned char*) 0x0A09)) // 모드
#define TCA_INTCTRL (*((volatile unsigned char*) 0x0A0A)) // 인터럽트 활성화 여부
#define TCA_INTFLAGS (*((volatile unsigned char*) 0x0A0B)) // 0-bit 오버플로우 체크
#define TCA_CNTL (*((volatile unsigned char*) 0x0A20)) // 카운터 [7:0]
#define TCA_CNTH (*((volatile unsigned char*) 0x0A21)) // 카운터 [15:8]
#define TCA_PER (*((volatile uint16_t*) 0x0A26))
#define TCA_PERL (*((volatile unsigned char*) 0x0A26)) // TOP [7:0]
#define TCA_PERH (*((volatile unsigned char*) 0x0A27)) // TOP [15:8]
#define TCA_PERBUF (*((volatile uint16_t*) 0x0A36))
#define TCA_PERBUFL (*((volatile unsigned char*) 0x0A36)) // TOP [15:8]
#define TCA_PERBUFH (*((volatile unsigned char*) 0x0A37)) // TOP [15:8]
#define TCA_CTRLESET (*((volatile unsigned char*) 0x0A05))
#define TCA_CMP0L (*((volatile unsigned char*) 0x0A28)) // TOP [15:8]
#define TCA_CMP0H (*((volatile unsigned char*) 0x0A29)) // TOP [15:8]
#define PORTMUX_TCAROUTEA (*((volatile unsigned char*) 0x05E4))


#endif