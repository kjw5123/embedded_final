#ifndef UART_H
#define UART_H

//#define F_CPU 20000000L <- 20MHz로 설정하니 uart통신이 어떤 baud rate에서 잘 안됨
#define F_CPU 16000000L
#include <util/delay.h>
#include <stdio.h>

#define BAUD_RATE                   115200
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

// 컴퓨터랑 통신하기
void USART1_init(void) {
  PORTC.DIRSET = PIN0_bm; // TX
  PORTC.DIRCLR = PIN1_bm; // RX

  USART1.BAUD = (uint16_t)USART0_BAUD_RATE(BAUD_RATE);
  USART1.CTRLB = USART_TXEN_bm | USART_RXEN_bm;
}

void USART1_TRANSMIT(unsigned char data) {
  while (!(USART1.STATUS & USART_DREIF_bm));
  USART1.TXDATAL = data;
}

void USART1_SEND_COMMAND(unsigned char data[]) {
  int i = 0;
  while (data[i] != '\0') {
    USART1_TRANSMIT(data[i]);
    i++;
  }
}

unsigned char USART1_RECEIVE_ANSWER(void) { // 받을 일은 없지만 일단 추가한 문자열 받는 통신
  while (!(USART1.STATUS & USART_RXCIF_bm));
  return USART1.RXDATAL;
}

int USART1_printChar(char c, FILE *stream) { 
  if (c == '\n') {
    USART1_TRANSMIT('\r');
  }
  USART1_TRANSMIT(c);
  return 0;
}

FILE USART1_stream;

void setupUSART1Stream() {
  fdev_setup_stream(&USART1_stream, USART1_printChar, NULL, _FDEV_SETUP_WRITE);
  stdout = &USART1_stream;
}

// bluetooth 제어용 코드
void USART2_init(){
	PORTF.DIRSET = PIN0_bm;
	PORTF.DIRCLR = PIN1_bm;
	
	USART2_BAUD = (uint16_t)USART0_BAUD_RATE(BAUD_RATE);
	USART2_CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
}

void USART2_TRANSMIT(unsigned char data) {
  while (!(USART2.STATUS & USART_DREIF_bm));
  USART2.TXDATAL = data;
}

void USART2_SEND_COMMAND(unsigned char data[]) {
  int i = 0;
  while (data[i] != '\0') {
    USART2_TRANSMIT(data[i]);
    i++;
  }
}
#endif // UART_H
