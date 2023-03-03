 /******************************************************************************
 *
 * Module: Private
 *
 * File Name: private.h
 *
 * Description: Header file for the AVR registers
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/
#ifndef MCU_CONFIG_PRIVATE_H_
#define MCU_CONFIG_PRIVATE_H_

#include "../mcu_config/std_types.h"


// Define the memory addresses of status registers
#define SREG   (*(volatile uint8*) 0x005F)

#define sei()  SREG |=  (1<<I); /*Enable Interrupts*/
#define cli()  SREG &= ~(1<<I); /*Disable Interrupts*/
// Define the bit positions of the registers
// Example: SREG
#define C     0
#define Z     1
#define N     2
#define V     3
#define S     4
#define H     5
#define T     6
#define I     7



// Define the memory addresses of the I/O and UART registers
#define PORTA   (*(volatile uint8*) 0x003B)
#define DDRA    (*(volatile uint8*) 0x003A)
#define PINA    (*(volatile uint8*) 0x0039)

#define PORTB   (*(volatile uint8*) 0x0038)
#define DDRB    (*(volatile uint8*) 0x0037)
#define PINB    (*(volatile uint8*) 0x0036)

#define PORTC   (*(volatile uint8*) 0x0035)
#define DDRC    (*(volatile uint8*) 0x0034)
#define PINC    (*(volatile uint8*) 0x0033)

#define PORTD   (*(volatile uint8*) 0x0032)
#define DDRD    (*(volatile uint8*) 0x0031)
#define PIND    (*(volatile uint8*) 0x0030)

#define UDR     (*(volatile uint8*) 0x002C)
#define UCSRA   (*(volatile uint8*) 0x002B)
#define UCSRB   (*(volatile uint8*) 0x002A)
#define UCSRC   (*(volatile uint8*) 0x0029)
#define UBRRH   (*(volatile uint8*) 0x002C)
#define UBRRL   (*(volatile uint8*) 0x0029)

// Define the bit positions of the registers
// Example: PORTA
#define PA0     0
#define PA1     1
#define PA2     2
#define PA3     3
#define PA4     4
#define PA5     5
#define PA6     6
#define PA7     7

// Example: UCSRA
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0

// Example: UCSRB
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0


// Example: UCSRC
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0








// Define the memory addresses of the SPI registers
#define SPCR    (*(volatile uint8*) 0x002D)
#define SPSR    (*(volatile uint8*) 0x002E)
#define SPDR    (*(volatile uint8*) 0x002F)


// Define the bit positions of the registers
// Example: SPCR
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0

// Example: SPSR
#define SPIF    7
#define WCOL    6
#define SPI2X   0


// Example: SPDR
#define  MSB    7
#define  LSB    0



// Define the memory addresses of the timers registers
#define TCCR0   (*(volatile uint8*) 0x0053)
#define TCNT0   (*(volatile uint8*) 0x0052)
#define OCR0    (*(volatile uint8*) 0x005C)

#define TCCR1A  (*(volatile uint8*) 0x004F)
#define TCCR1B  (*(volatile uint8*) 0x004E)
#define TCNT1   (*(volatile uint32*)  0x004C)
#define OCR1A   (*(volatile uint32*)  0x004A)
#define OCR1B   (*(volatile uint32*)  0x0048)
#define ICR1    (*(volatile uint32*)  0x0046)

#define TCCR2   (*(volatile uint8*) 0x0045)
#define TCNT2   (*(volatile uint8*) 0x0044)
#define OCR2    (*(volatile uint8*) 0x0043)

// Define the bit positions of the registers
// Example: TCCR0
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

// Example: TCCR1A
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

// Example: TCCR1B
#define ICNC1   7
#define ICES1   6
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

// Example: TCNT1
#define ICNC1   7
#define ICES1   6
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

// Example: OCR1A
// No bit definitions needed, as OCR1A is a 16-bit register

// Example: TCCR2
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0



// Define the memory addresses of the ADC registers
#define ADMUX    (*(volatile uint8*) 0x0027)
#define ADCSRA   (*(volatile uint8*) 0x0026)
#define ADCH     (*(volatile uint8*) 0x0025)
#define ADCL     (*(volatile uint8*) 0x0024)
#define ADC      (*(volatile uint16*) 0x0024)
#define SFIOR    (*(volatile uint8*) 0x0050)


// Example: ADMUX
#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define MUX4    4
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0


// Example: ADCSRA
#define ADEN     7
#define ADSC     6
#define ADATE    5
#define ADIF     4
#define ADIE     3
#define ADPS2    2
#define ADPS1    1
#define ADPS0    0


// Example: SFIOR
#define ADTS2    7
#define ADTS1    6
#define ADTS0    5
#define ACME     3
#define PUD      2
#define PSR2     1
#define PSR10    0



// Define the memory addresses of the I2C registers
#define TWBR    (*(volatile uint8*) 0x0020)
#define TWSR    (*(volatile uint8*) 0x0021)
#define TWAR    (*(volatile uint8*) 0x0022)
#define TWDR    (*(volatile uint8*) 0x0023)
#define TWCR    (*(volatile uint8*) 0x0056)





// Define the bit positions of the registers
// Example: TWBR
#define TWBR7    7
#define TWBR6    6
#define TWBR5    5
#define TWBR4    4
#define TWBR3    3
#define TWBR2    2
#define TWBR1    1
#define TWBR0    0


// Example: TWSR
#define TWS7     7
#define TWS6     6
#define TWS5     5
#define TWS4     4
#define TWS3     3
#define TWPS1    1
#define TWPS0    0

// Example: TWAR
#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE   0


// Example: TWDR
#define TWD7    7
#define TWD6    6
#define TWD5    5
#define TWD4    4
#define TWD3    3
#define TWD2    2
#define TWD1    1
#define TWD0    0



// Example: TWCR
#define TWINT    7
#define TWEA     6
#define TWSTA    5
#define TWSTO    4
#define TWWC     3
#define TWEN     2
#define TWIE     0

#endif /* MCU_CONFIG_PRIVATE_H_ */
