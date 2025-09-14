#ifndef BUTTON_H
#define BUTTON_H
#include "UART.h"

void VOLUME_UP() {
	USART2_SEND_COMMAND("AT+CE\r\n");
}

void VOLUME_DOWN() {
	USART2_SEND_COMMAND("AT+CF\r\n");
}

void PAUSEorPLAY() {
	USART2_SEND_COMMAND("AT+CB\r\n");
}

void NEXT_TRACK() {
	USART2_SEND_COMMAND("AT+CC\r\n");
}

void PREVIOUS_PIECE() {
	USART2_SEND_COMMAND("AT+CD\r\n");
}

// 아래부턴 버튼 인터럽트 제어 코드 
// 실제로 인터럽트
void buttonInit(){
  USART2_init();
  PORTD_DIRCLR = 0x10 | 0x20 | 0x40 | 0x80; // D 4 5 6 7
  PORTE_DIRCLR = 0x01 | 0x02; // E 0 1, 단, E1은 미사용 및 미구현

  PORTD_PIN4CTRL = (0x03<<0) | (1<<3); // falling edge 검출 시 인터럽트, 내부 풀업 저항 활성화
  PORTD_PIN5CTRL = (0x03<<0) | (1<<3); // 이하 동일
  PORTD_PIN6CTRL = (0x03<<0) | (1<<3);
  PORTD_PIN7CTRL = (0x03<<0) | (1<<3);

  PORTE_PIN0CTRL = (0x03<<0) | (1<<3);
  PORTE_PIN1CTRL = (0x03<<0) | (1<<3);

  // 인터럽트 플래그 클리어
  PORTD_INTFLAGS = 0x10 | 0x20 | 0x40 | 0x80;
  PORTE_INTFLAGS = 0x01 | 0x02;

  sei();
}

#endif