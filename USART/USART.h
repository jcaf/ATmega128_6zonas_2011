/***********************************************************************************************

    Los únicos parametros "fijos" seteados para todo el programa serian hasta ahora:

    - ASYNC - NORMAL O DOUBLE SPEED... puesto que seria casi imposible cambiar pues el cristal del sitsema
    es fijo

***********************************************************************************************/
#ifndef _USART_H_
#define _USART_H_

    /************************************************************

    *************************************************************/
	#define _USART0_
	//#define _USART1_
	
	#if !(defined __AVR_ATmega128__ || defined __AVR_ATmega64__) && !(defined _USART1_)
		#define UCSR0A	UCSRA 
		#define UCSR0B	UCSRB 
		#define UCSR0C	UCSRC 
		#define UDR0	UDR
		#define UBRR0H	UBRRH
		#define UBRR0L	UBRRL
	#endif

	#if defined __AVR_ATmega128__ || defined __AVR_ATmega64__
		#define URSEL	7	//solo por compatilibilida al codigo ya escrito/URSEL no existe en MEGA128/64
		#define PE		2	//UPE
	#endif					
    /************************************************************

    *************************************************************/
    #define ASYNCH_NORMAL_MODE          (0)  //U2X = 0
    #define ASYNCH_DOUBLE_SPEED_MODE    (1)  //U2X = 1
    //
    #define SYNCH_MASTER_MODE           (2)

    //#define BAUD_RATE ()
    /************************************************************

            DEFINICION DE VELOCIDAD DE OPERACION: NORMAL/DOUBLE
    *************************************************************/
    #define OPERATING_MODE_SPEED        (ASYNCH_NORMAL_MODE)
    //#define OPERATING_MODE_SPEED      (ASYNCH_DOUBLE_SPEED_MODE)

        #if OPERATING_MODE_SPEED == ASYNCH_NORMAL_MODE
            #define _U2X_   (0)
            #define _KTE_EQU_UBRR_ (16UL)
        #elif OPERATING_MODE_SPEED == ASYNCH_DOUBLE_SPEED_MODE
            #define _U2X_   (1)
            #define _KTE_EQU_UBRR_ (8UL)
        #elif OPERATING_MODE_SPEED == SYNCH_MASTER_MODE
            #define _U2X_   (0)
            #define _KTE_EQU_UBRR_ (2UL)
        #endif
    /************************************************************

    *************************************************************/
    #define Set_UBRR0_VALUE(_BAUD_) do{\
                    UBRR0H = (byte)(((word)((FREQ_SYSTEM/(_KTE_EQU_UBRR_*_BAUD_)) - 1 ))>>8);\
                    UBRR0L = (byte)(((word)((FREQ_SYSTEM/(_KTE_EQU_UBRR_*_BAUD_)) - 1 ))>>0);\
                            }while(0)

    /*******************************************************************************************

                DEFINICION DE KTES BITS PARA UCSRB
    *******************************************************************************************/
    //BIT 7 RX Complete Interrupt Enable RXCIE
    #define RX_COMPLETE_INT_DISABLE     (0)
    #define RX_COMPLETE_INT_ENABLE      (1)

    //BIT 6 TX Complete Interrupt Enable TXCIE
    #define TX_COMPLETE_INT_DISABLE     (0)
    #define TX_COMPLETE_INT_ENABLE      (1)

    //BIT 5 USART Data Register Empty Enable UDRIE
    #define DATA_EMPTY_INT_DISABLE      (0)
    #define DATA_EMPTY_INT_ENABLE       (1)

    //BIT 4 RXEN Receiver Enable
    #define RECEIVER_DISABLE            (0)
    #define RECEIVER_ENABLE             (1)

    //BIT 3 TXEN Receiver Enable
    #define TRANSMITTER_DISABLE         (0)
    #define TRANSMITTER_ENABLE          (1)

    //BIT 2 UCSZE USART Character Size 2
    //BIT 1 RXB8
    //BIT 0 TXB8
    /*******************************************************************************************
          DEFINICION DE KTES BITS PARA UCSRC
    *******************************************************************************************/
    //BIT 7 USART Register Select URSEL

    #define UBRRH_SELECTION_REGISTER    (0)
    #define UCSRC_SELECTION_REGISTER    (1)

    //BIT 6 USART Mode Select  UMSEL
    #define ASYNCHRONOUS_OPERATION      (0)
    #define SYNCHRONOUS_OPERATION       (1)

    //BIT 5:4 USART Parity Mode UPM1:UPM0
    #define PARITY_MODE_DISABLE         (0)
    #define PARITY_MODE_RESERVED        (1)
    #define PARITY_MODE_ENABLE_EVEN     (2)
    #define PARITY_MODE_ENABLE_ODD      (3)

    //BIT 3 USART Stop Bit Select USBS
    #define BIT_STOP_1 (0)
    #define BIT_STOP_2 (1)

    //BIT 2:1 USART Character Size UCSZ1:UCSZ0
    #define CHARACTER_SIZE_5_BIT      (0)
    #define CHARACTER_SIZE_6_BIT      (1)
    #define CHARACTER_SIZE_7_BIT      (2)
    #define CHARACTER_SIZE_8_BIT      (3)
    #define CHARACTER_SIZE_RESERVED   (4)
    //#define CHARACTER_SIZE_RESERVED   (5)
    //#define CHARACTER_SIZE_RESERVED   (6)
    #define CHARACTER_SIZE_9_BIT_     (7)

    //BIT 0
    #define CLOCK_POLARITY_0 (0)
    #define CLOCK_POLARITY_1 (1)

    /*******************************************************************************************


    *******************************************************************************************/
    void Init_USART0(void);

    void    TxByteNoWaitTXC_USART0(byte DATA);
    void    TxByteWaitTXC_USART0(byte DATA);

    byte RxDataUSART0(void);

#endif
