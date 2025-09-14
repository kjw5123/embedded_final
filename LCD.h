#ifndef LCD_H
#define LCD_H

#include "MACRO.h"
#include "UART.h"
#define F_CPU 16000000L
#define LCD_ADDRESS 0x27 // PCF8574 기본 주소

extern uint16_t Amplitude[16];

void TWI_init()
{
  TWI_MBAUD = 0x1F; // 보드레이트 설정
  TWI_MCTRLB |= 0x08; // flush 초기화
  TWI_MSTATUS |= (0x80 | 0x40); // RIF WIF 클리어(초기화)
  TWI_MCTRLA = 0x03; // 스마트 모드, MASTER모드 ENABLE
  TWI_MSTATUS |= 0x01; // 버스 상태 IDLE로 만들어주기

  PORTA_PIN3CTRL = (1 << 3);
  PORTA_PIN2CTRL = (1 << 3);

}

uint8_t TWI_Start(uint8_t addr)
{
    // BUS가 BUSY 상태가 아니면
    while ((TWI_MSTATUS & TWI_BUSSTATE_gm) == (0x03 << 0));

    // START 조건 설정
    TWI_MADDR = addr;

    // WIF 플래그가 설정될 때까지 대기
    while (!(TWI_MSTATUS & 0x40))
    {
        // printf("is TWI START WIF is what? : %d\n", (TWI0.MSTATUS >> 6) & 1);
    }

    // ACK/NACK 확인
    if (TWI_MSTATUS & TWI_RXACK_bm)
    {
        return 0; // NACK 수신
    }

    return 1; // ACK 수신
}

void TWI_Write(uint8_t data)
{

  while (!((TWI_MSTATUS & 0x40) | (TWI_MSTATUS & 0x10))); // WIF가 셋되거나, 슬레이브로부터 가장 최근에 받은 신호가 NACK라면

  TWI_MDATA = data;

}

void TWI_Stop()
{
  TWI_MCTRLB |= 0x03; // STOP 커맨드
}

void LCD_send_nibble(uint8_t nib)
{
    TWI_Start((LCD_ADDRESS << 1) | WRITEBIT);
    TWI_Write(nib | 0x08); // 생 데이터 넣어주기 (LCD 전용 프로토콜로 파악됨)
    TWI_Stop();

    TWI_Start((LCD_ADDRESS << 1) | WRITEBIT);
    TWI_Write(nib | 0x04 | 0x08); // en 비트를 1로 만들어줌 0x04 = 0b00000100
    TWI_Stop();

    _delay_us(1);

    TWI_Start((LCD_ADDRESS << 1) | WRITEBIT);
    TWI_Write(nib & 0xF7 | 0x08); // en 비트를 0로 만들어줌 0xF7 = ~0b00000100 = Ob11111011
    TWI_Stop();
    _delay_us(50);
}

void LCD_send_command(uint8_t command)
{
    LCD_send_nibble(command & 0xF0);    // 상위 4비트 전송 11110000
    LCD_send_nibble((command << 4) & 0xF0); // 하위 4비트 전송
}

void LCD_send_data(uint8_t data)
{
    TWI_Start((LCD_ADDRESS << 1 ) | WRITEBIT);
    LCD_send_nibble((data & 0xF0) | 0x01); // 상위 4비트 전송, RS=1
    LCD_send_nibble(((data << 4) & 0xF0) | 0x01); // 하위 4비트 전송, RS=1
    TWI_Stop();
    _delay_ms(2);
    
}

void LCD_set_cursor(uint8_t col, uint8_t row)
{
    uint8_t address;
    if (row == 0) {
        address = 0x80 + col;
    } else {
        address = 0xC0 + col;
    }
    LCD_send_command(address);
}

void LCD_print(const char *str)
{
    while (*str) {
        LCD_send_data(*str++);
    }
}

void LCD_custom_char(uint8_t to_save, uint8_t letter[]){
  to_save &= 0x7;
  LCD_send_command(0x40 | (to_save << 3));
  for (int i = 0; i < 8; i++) {
    LCD_send_data(letter[i]);
  }
}

void LCD_init()
{
    _delay_ms(50); // 전원 안정화 대기

    LCD_send_command(0x30); // 초기화 명령
    _delay_ms(5);
    LCD_send_command(0x30); // 초기화 명령 반복
    _delay_us(150);
    LCD_send_command(0x30); // 초기화 명령 반복
    _delay_us(150);
    LCD_send_command(0x02); // 4비트 모드 전환
    _delay_us(150);

    LCD_send_command(0x28); // 4비트 모드, 2줄, 5x8 폰트
    _delay_us(150);
    LCD_send_command(0x0c); // 디스플레이 켜기, 커서 끄기, 블링크 끄기
    _delay_us(150);
    LCD_send_command(0x06); // 자동 커서 이동
    _delay_us(150);
    LCD_send_command(0x01); // 디스플레이 클리어
    _delay_ms(2);
}

void LCD_print_ADC(){
  for(int i = 0; i < 16; i++){
    switch(Amplitude[i]){
    case 0:
      LCD_set_cursor(i,1);
      LCD_send_data(0xFE); // level 0
      LCD_set_cursor(i,0);
      LCD_send_data(0xFE); // 0~8은 윗칸 공백처리
      break;
    case 1:
      LCD_set_cursor(i,1);
      LCD_send_data(0); // level 0
      LCD_set_cursor(i,0);
      LCD_send_data(0xFE); // 0~8은 윗칸 공백처리
      break;
    case 2:
      LCD_set_cursor(i,1);
      LCD_send_data(1); // level 0
      LCD_set_cursor(i,0);
      LCD_send_data(0xFE); // 0~8은 윗칸 공백처리
      break;
    case 3:
      LCD_set_cursor(i,1);
      LCD_send_data(2); // level 0
      LCD_set_cursor(i,0);
      LCD_send_data(0xFE); // 0~8은 윗칸 공백처리
      break;
    case 4:
      LCD_set_cursor(i,1);
      LCD_send_data(3); // level 0
      LCD_set_cursor(i,0);
      LCD_send_data(0xFE); // 0~8은 윗칸 공백처리
      break;
    case 5:
      LCD_set_cursor(i,1);
      LCD_send_data(4); // level 0
      LCD_set_cursor(i,0);
      LCD_send_data(0xFE); // 0~8은 윗칸 공백처리
      break;
    case 6:
      LCD_set_cursor(i,1);
      LCD_send_data(5); // level 0
      LCD_set_cursor(i,0);
      LCD_send_data(0xFE); // 0~8은 윗칸 공백처리
      break;
    case 7:
      LCD_set_cursor(i,1);
      LCD_send_data(6); // level 0
      LCD_set_cursor(i,0);
      LCD_send_data(0xFE); // 0~8은 윗칸 공백처리
      break;
    case 8:
      LCD_set_cursor(i,1);
      LCD_send_data(7); // level 0
      LCD_set_cursor(i,0);
      LCD_send_data(0xFE); // 0~8은 윗칸 공백처리
      break;
    case 9:
      LCD_set_cursor(i,1);
      LCD_send_data(7); // level 8 고정
      LCD_set_cursor(i,0);
      LCD_send_data(0);
      break;
    case 10:
      LCD_set_cursor(i,1);
      LCD_send_data(7); // level 8 고정
      LCD_set_cursor(i,0);
      LCD_send_data(1);
      break;
    case 11:
      LCD_set_cursor(i,1);
      LCD_send_data(7); // level 8 고정
      LCD_set_cursor(i,0);
      LCD_send_data(2);
      break;
    case 12:
      LCD_set_cursor(i,1);
      LCD_send_data(7); // level 8 고정
      LCD_set_cursor(i,0);
      LCD_send_data(3);
      break;
    case 13:
      LCD_set_cursor(i,1);
      LCD_send_data(7); // level 8 고정
      LCD_set_cursor(i,0);
      LCD_send_data(4);
      break;
    case 14:
      LCD_set_cursor(i,1);
      LCD_send_data(7); // level 8 고정
      LCD_set_cursor(i,0);
      LCD_send_data(5);
      break;
    case 15:
      LCD_set_cursor(i,1);
      LCD_send_data(7); // level 8 고정
      LCD_set_cursor(i,0);
      LCD_send_data(6);
      break;
    case 16:
      LCD_set_cursor(i,1);
      LCD_send_data(7); // level 8 고정
      LCD_set_cursor(i,0);
      LCD_send_data(7);
      break;
    default: // 진폭 값 6400 넘어가면 그냥 최대 처리
      LCD_set_cursor(i,1);
      LCD_send_data(7); // level 8 고정
      LCD_set_cursor(i,0);
      LCD_send_data(7);
      break;
    }
  }
}
#endif