/***************************************************************************************************
    Esta definición es parte del archivo de def. x "ATmega16A"
    aún no ha sido verificado/corregido.


***************************************************************************************************/
#ifndef _IODevicePins_H_
#define _IODevicePins_H_

    /* Device Pin Definitions */

    #define SS_DDR   DDRB
    #define SS_PORT  PORTB
    #define SS_PIN   PINB
    #define SS_BIT   4

    #define MOSI_DDR   DDRB
    #define MOSI_PORT  PORTB
    #define MOSI_PIN   PINB
    #define MOSI_BIT   5

    #define MISO_DDR   DDRB
    #define MISO_PORT  PORTB
    #define MISO_PIN   PINB
    #define MISO_BIT   6

    #define SCK_DDR   DDRB
    #define SCK_PORT  PORTB
    #define SCK_PIN   PINB
    #define SCK_BIT   7

    #define RXD_DDR   DDRD
    #define RXD_PORT  PORTD
    #define RXD_PIN   PIND
    #define RXD_BIT   0

    #define TXD_DDR   DDRD
    #define TXD_PORT  PORTD
    #define TXD_PIN   PIND
    #define TXD_BIT   1

    #define INT0_DDR   DDRD
    #define INT0_PORT  PORTD
    #define INT0_PIN   PIND
    #define INT0_BIT   2

    #define INT1_DDR   DDRD
    #define INT1_PORT  PORTD
    #define INT1_PIN   PIND
    #define INT1_BIT   3

    #define OC1B_DDR   DDRD
    #define OC1B_PORT  PORTD
    #define OC1B_PIN   PIND
    #define OC1B_BIT   4

    #define OC1A_DDR   DDRD
    #define OC1A_PORT  PORTD
    #define OC1A_PIN   PIND
    #define OC1A_BIT   5

    #define ICP_DDR   DDRD
    #define ICP_PORT  PORTD
    #define ICP_PIN   PIND
    #define ICP_BIT   6

    #define OC2_DDR   DDRD
    #define OC2_PORT  PORTD
    #define OC2_PIN   PIND
    #define OC2_BIT   7

    #define SCL_DDR   DDRC
    #define SCL_PORT  PORTC
    #define SCL_PIN   PINC
    #define SCL_BIT   0

    #define SDA_DDR   DDRC
    #define SDA_PORT  PORTC
    #define SDA_PIN   PINC
    #define SDA_BIT   1

    #define PC3_DDR   DDRC
    #define PC3_PORT  PORTC
    #define PC3_PIN   PINC
    #define PC3_BIT   3

    #define PC4_DDR   DDRC
    #define PC4_PORT  PORTC
    #define PC4_PIN   PINC
    #define PC4_BIT   4

    #define PC5_DDR   DDRC
    #define PC5_PORT  PORTC
    #define PC5_PIN   PINC
    #define PC5_BIT   5

    #define ADC7_DDR   DDRA
    #define ADC7_PORT  PORTA
    #define ADC7_PIN   PINA
    #define ADC7_BIT   7

    #define ADC6_DDR   DDRA
    #define ADC6_PORT  PORTA
    #define ADC6_PIN   PINA
    #define ADC6_BIT   6

    #define ADc5_DDR   DDRA
    #define ADc5_PORT  PORTA
    #define ADc5_PIN   PINA
    #define ADc5_BIT   5

    #define ADC4_DDR   DDRA
    #define ADC4_PORT  PORTA
    #define ADC4_PIN   PINA
    #define ADC4_BIT   4

    #define ADC3_DDR   DDRA
    #define ADC3_PORT  PORTA
    #define ADC3_PIN   PINA
    #define ADC3_BIT   3

    #define ADC2_DDR   DDRA
    #define ADC2_PORT  PORTA
    #define ADC2_PIN   PINA
    #define ADC2_BIT   2

    #define ADC1_DDR   DDRA
    #define ADC1_PORT  PORTA
    #define ADC1_PIN   PINA
    #define ADC1_BIT   1

    #define ADC0_DDR   DDRA
    #define ADC0_PORT  PORTA
    #define ADC0_PIN   PINA
    #define ADC0_BIT   0

    #define T0_DDR   DDRB
    #define T0_PORT  PORTB
    #define T0_PIN   PINB
    #define T0_BIT   0

    #define T1_DDR   DDRB
    #define T1_PORT  PORTB
    #define T1_PIN   PINB
    #define T1_BIT   1

    #define AIN0_DDR   DDRB
    #define AIN0_PORT  PORTB
    #define AIN0_PIN   PINB
    #define AIN0_BIT   2

    #define AIN1_DDR   DDRB
    #define AIN1_PORT  PORTB
    #define AIN1_PIN   PINB
    #define AIN1_BIT   3



#endif
