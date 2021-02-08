#include "Includes/InitializeAllModules.h"
#ifdef _USART_

#ifdef _USART0_
	
	/********************************************************************************************

    *El bloque del receptor esta dividido practicamente en 3 registros/fifo circular

        Exterior PIN RX ->  RECEIVE SHIFT REGISTER (arma los bits q ingresan)
                            UDR (Receive)   (1er level)
                            UDR (Receive)   (2do level)

    The receiver includes a parity checker, control logic, a Shift Register and a two level
    receive buffer (UDR). The receiver supports the same frame formats as the Transmitter, and can
    detect frame error, data overrun and parity errors.

    A second buffer register has been added. The two buffer registers operate as a circular FIFO
    buffer. Therefore the UDR must only be read once for each incoming data! More important is
    the fact that the error flags (FE and DOR) and the ninth data bit (RXB8) are buffered with the
    data in the receive buffer. Therefore the status bits must always be read before the UDR
    Register is read. Otherwise the error status will be lost since the buffer state is lost.

    NOTA:
    -----
    The receiver Shift Register can now act as a third buffer level. This is done by allowing the
    received data to remain in the serial Shift Register (see Figure 79) if the buffer registers are
    full, until a new start bit is detected. The USART is therefore more resistant to Data OverRun
    (DOR) error conditions.

    LO QUE SE PUEDE INTERPRETAR, ES QUE, SI LOS 2 BUFFERS DE PRIMER Y SEGUNDO NIVEL: UDR(1) Y UDR(2) ESTAN LLENOS PORQ NO HAN SIDO LEIDOS,
    EL "RECEIVE SHIFT REGISTER" ACTUARÁ COMO UN BUFFER DE TERCEL NIVEL, Y RETENDRÁ LA DATA HASTA DETECTAR UN NUEVO
    BIT DE START.


    GENERACION DE CLOCK:
    -------------------
    The clock generation logic generates the base clock for the transmitter and receiver.
    The USART supports four modes of clock operation:

    1- Normal Asynchronous,
    2- Double Speed Asyn-chronous,

    3- Master Synchronous,
    4- and Slave Synchronous mode.

    The UMSEL bit in USART Control and Status Register C (UCSRC) selects between asynchronous and synchronous oper-
    ation.

    Double speed (Asynchronous mode only) is controlled by the U2X found in the UCSRA Register.

    When using Synchronous mode (UMSEL = 1), the Data Direction Register for the XCK
    pin (DDR_XCK) controls whether the clock source is internal (Master mode) or external (Slave
    mode). The XCK pin is only active when using Synchronous mode.

    The baud rate mode of operation and frame format must be set up once before doing any transmissions.
    If synchro-nous operation is used, the clock on the XCK pin will be overridden and used as transmission clock.


    FRAME FORMAT
    ------------
    - St Start bit, always low.
    - (n) Data bits (0 to 8).
    - P Parity bit. Can be odd or even.
    - Sp Stop bit, always high.
    - IDLE No transfers on the communication line (RxD or TxD). An IDLE line must be high.

    The frame format used by the USART is set by the UCSZ2:0, UPM1:0 and USBS bits in UCSRB
    and UCSRC. The receiver and transmitter use the same setting. Note that changing the setting
    of any of these bits will corrupt all ongoing communication for both the receiver and transmitter.


    TIP
    ---
    For interrupt driven USART operation, the
    global interrupt flag should be cleared (and interrupts globally disabled) when doing the
    initialization.

	********************************************************************************************/

	void Init_USART0(void)
    //void InitUSART(byte BAUD, MODE, STOP,DATA,PARITY,etc)
    {
        Set_UBRR0_VALUE(9600);   //BPS
		
		//UBRRH = (416)>>8;//2400
		//UBRRL = (byte)(416);//2400

        //The transfer rate can be doubled by setting the U2X bit in UCSRA. Setting this bit only has effect
        //for the asynchronous operation. Set this bit to zero when using synchronous operation.
        //For compat-ibility with future devices, always write this bit to zero when writing the UCSRA Register
        UCSR0A = ( _U2X_ << U2X ) | ( 0 << MPCM ) ;

        //Habilitar receptor y transmisor

        //When the Transmitter is enabled, the normal port operation of the TxD pin is overrid-den by the USART and given the function as the transmitter’s serial output.
        //The TXEN bit in UCR enables the UART Transmitter when set (one). When this bit is
        //cleared (zero), the PE1 pin can be used for general I/O. When TXEN is set, the UART
        //Transmitter will be connected to PE1, which is forced to be an output pin regardless of
        //the setting of the DDE1 bit in DDRE.
        UCSR0B =     ( \
                    (RX_COMPLETE_INT_DISABLE            <<  RXCIE)  | \
                    (TX_COMPLETE_INT_DISABLE            <<  TXCIE)  | \
                    (DATA_EMPTY_INT_DISABLE             <<  UDRIE)  | \
                    (RECEIVER_ENABLE                    <<  RXEN)   | \
                    (TRANSMITTER_ENABLE                 <<  TXEN)   | \
                    ((((CHARACTER_SIZE_8_BIT)&0x04)>>2) <<  UCSZ2)  \
                    );


        //The UMSEL bit in USART Control and Status Register C (UCSRC) selects between asynchronous and synchronous operation.
        //USART Control and Status Register C
        UCSR0C =    ( \
                    (UCSRC_SELECTION_REGISTER        << URSEL )   | \
                    (ASYNCHRONOUS_OPERATION          << UMSEL )   | \
                    (PARITY_MODE_DISABLE             << UPM0  )   | \
                    (BIT_STOP_1                      << USBS  )   | \
                    (((CHARACTER_SIZE_8_BIT)&0x03)   << UCSZ0 )   | \
                    (CLOCK_POLARITY_0                << UCPOL )     \
                    );

    }//End fx()
    /********************************************************************************************
    The USART Transmitter has two flags that indicate its state: USART Data Register Empty
    (UDRE) and Transmit Complete (TXC). Both flags can be used for generating interrupts

    The USART Transmitter has two flags that indicate its state: USART Data Register Empty
    (UDRE) and Transmit Complete (TXC). Both flags can be used for generating interrupts.

    The Data Register Empty (UDRE) flag indicates whether the transmit buffer is ready to receive
    new data. This bit is set when the transmit buffer is empty, and cleared when the transmit buffer
    contains data to be transmitted that has not yet been moved into the Shift Register. For compat-
    ibility with future devices, always write this bit to zero when writing the UCSRA Register.


    When the Data Register empty Interrupt Enable (UDRIE) bit in UCSRB is written to one, the
    USART Data Register Empty Interrupt will be executed as long as UDRE is set (provided that
    global interrupts are enabled). UDRE is cleared by writing UDR. W hen interrupt-driven data
    transmission is used, the data register empty Interrupt routine must either write new data to UDR
    in order to clear UDRE or disable the data register empty interrupt, otherwise a new interrupt will
    occur once the interrupt routine terminates.

    The Transmit Complete (TXC) flag bit is set one when the entire frame in the Transmit Shift Reg-
    ister has been shifted out and there are no new data currently present in the transmit buffer. The
    TXC flag bit is automatically cleared when a transmit complete interrupt is executed, or it can be
    cleared by writing a one to its bit location. The TXC flag is useful in half-duplex communication
    interfaces (like the RS485 standard), where a transmitting application must enter receive mode
    and free the communication bus immediately after completing the transmission.
    W hen the Transmit Compete Interrupt Enable (TXCIE) bit in UCSRB is set, the USART Transmit
    Complete Interrupt will be executed when the TXC flag becomes set (provided that global inter-
    rupts are enabled). W hen the transmit complete interrupt is used, the interrupt handling routine
    does not have to clear the TXC flag, this is done automatically when the interrupt is executed.


    *INTERPRETACION:

    Tal como su nombre refiere, UDR Empty, solo chequea si el contenido de UDR fue volcado hacia su respectivo Shift register.

    Newbies in AVR are always confused by these two interrupts (I’m not an exception here). What’s the difference between these two interrupts ? After googling for a while, I found avrfreaks forum discussion about the difference between the two (here).

    To summarize the discussion:

    Timing Diagram of UDRE vs TXC
    Example for transmitting 2 bytes, loading on UDRE

    Action    Flags         Comment
    Startup   UDRE=1 TXC=0
    Load UDR  UDRE=0 TXC=0  Software loads UDR
    UDR->SR   UDRE=1 TXC=0  Hardware loads Shift Register
    LOAD UDR  UDRE=0 TXC=0  Software loads UDR

    after first byte finishes shifting
    UDR->SR   UDRE=1 TXC=0  Hardware Loads Shift Register -> SACADO DE ATmega103

    after second byte finishes shifting
    nothing   UDRE=1 TXC=1

    Application
    UDRE is normally used. TXC is normally not used, except for these situations:

    Half duplex communication, such as RS485: where the application needs to know whether all of the bits has been transmitted or not, before releasing the bus.
    Power saving mode: where the application needs to know whether the transmission has done, before switching to deeper power saving mode (where the UART peripheral is not available anymore).


    Osea que para conmutar entre TX/RX en un ambiente como RS485 Half-duplex, NO ES RECOMENDABLE cargar 2 veces
    seguidos UDR, pues,segun la literatura, perderiamos el rastro del primer envio de toda la trama(incluido STOP bit), pues
    aun estaria lleno el SHIFT REGISTER del segundo byte que encolamos, y por esa condicion no se pondria a TXC='1'

    ATmega103:

    Data transmission is initiated by writing the data to be transmitted to the UART I/O Data
    Register, UDR. Data is transferred from UDR to the Transmit Shift Register when:

    + A new character has been written to UDR after the stop bit from the previous
    character has been shifted out. The Shift Register is loaded immediately.
    + A new character has been written to UDR before the stop bit from the previous
    character has been shifted out. The Shift Register is loaded when the stop bit of the
    character currently being transmitted has been shifted out.

    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    On the baud rate clock following the transfer operation to the Shift Register, the start bit
    is shifted out on the TXD pin, followed by the data, LSB first. When the stop bit has been
    shifted out, the Shift Register is loaded if any new data has been written to the UDR dur-
    ing the transmission. During loading, UDRE is set. If there is no new data in the UDR
    Register to send when the stop bit is shifted out, the UDRE Flag will remain set. In this
    case, after the stop bit has been present on TXD for one bit length, the TX Complete
    Flag (TXC) in USR is set.
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    //The write buffer allows a continuous transfer of data without any delay between frames.
    //This bit is set (one) when a character written to UDR is transferred to the Transmit Shift
    //Register. Setting of this bit indicates that the Transmitter is ready to receive a new char-
    //acter for transmission.
    //When the UDRIE bit in UCR is set, the UART Transmit Complete interrupt to be exe-
    //cuted as long as UDRE is set. UDRE is cleared by writing UDR. When interrupt-driven
    //data transmittal is used, the UART Data Register Empty Interrupt routine must write
    //UDR in order to clear UDRE, otherwise a new interrupt will occur once the interrupt rou-
    //tine terminates.
    //UDRE is set (one) during reset to indicate that the Transmitter is ready.

    ********************************************************************************************/

    /********************************************************************************************
    void    TxByteNoWaitTXC_USART(byte DATA)    //
		Dado la arquitectura de los registros de transmision y UDRE, se podria encolar hasta 2
		cargas consecutivas ... el hardware es el encargado de traspasar desde el ultimo UDR permitido
		por ser cargado hacia el registro de corrimiento SHIFT REGISTER

    ********************************************************************************************/
    void    TxByteNoWaitTXC_USART0(byte DATA)    //
    {
        while ( !(UCSR0A & (1<<UDRE)) )     {;}
        UDR0 = DATA;
		//Podria enviarse dos bytes consecutivos, mientras el shift register esta sacandolo por Tx
    }
    /*******************************************************************************************
    //Note that the TXC Flag must be
    //cleared before each transmission (before UDR is written) if it is used for this purpose
    
	//This bit is set (one) when the entire character (including the stop bit) in the Transmit
    //Shift Register has been shifted out and no new data has been written to the UDR. 
	
	//This
    //flag is especially useful in half-duplex communications interfaces, where a transmitting
    //application must enter Receive mode and free the communications bus immediately
    //after completing the transmission.
    //When the TXCIE bit in UCR is set, setting of TXC causes the UART Transmit Complete
    //interrupt to be executed. TXC is cleared by hardware when executing the corresponding
    //interrupt handling vector. Alternatively, the TXC bit is cleared (zero) by writing a logical
    //“1” to the bit.
    *******************************************************************************************/
    void TxByteWaitTXC_USART0(byte DATA)
    {
		if (!(UCSR0A & (1<<TXC)))
		{
			while (!(UCSR0A & (1<<TXC))){;}		//Esperar q finalice por completo ultima trama encolada
			BitTo1(UCSR0A,TXC);					//Clear flag
		}
			
        //while ( !(UCSR0A & (1<<UDRE)) ){;}	//ya estaria demás preguntar por UDRE solo si se espera por while ( !(UCSRA & (1<<TXC)) ){;}
        UDR0 = DATA;

        while (!(UCSR0A & (1<<TXC))){;}

		//BitTo1(UCSR0A,TXC);		//clear por software...
		//This bit is set (one) when the entire character (including the stop bit) in the Transmit
		//Shift Register has been shifted out and no new data has been written to the UDR. 
		/*
		Lo que espero que suceda es lo sgte:
		q pasaria si primero llamo a TxByteNoWaitTXC_USART(), y luego a TxByteWaitTXC_USART().
		con la primera llamada,, si no hay nada encolado
		*/
    }
    /********************************************************************************************
    Lectura de 8 bits

    //EnviaCmdLCD_an(XYFILA_2 + 0);
    if (STATUS_USART & (1<<FE) )
    {
    }
    }
    if (STATUS_USART & (1<<DOR) )
    {
    }
    if (STATUS_USART & (1<<PE) )
    {
    }

    A second buffer register has been added. The two buffer registers operate as a circular FIFO
    buffer. Therefore the UDR must only be read once for each incoming data! More important is
    the fact that the error flags (FE and DOR) and the ninth data bit (RXB8) are buffered with the
    data in the receive buffer. Therefore the status bits must always be read before the UDR
    Register is read. Otherwise the error status will be lost since the buffer state is lost


    For interrupt driven USART operation, the
    global interrupt flag should be cleared (and interrupts globally disabled) when doing the
    initialization.

	********************************************************************************************/
    byte    RxDataUSART0(void)
    {
        //volatile byte DATA_USART;
        volatile byte STATUS_USART0;

        /*
         Therefore the status bits must always be read before the UDR
        Register is read. Otherwise the error status will be lost since the buffer state is lost.
        */

        //Leer data desde UDR
        STATUS_USART0    = UCSR0A;
        //DATA_USART0      = UDR0;

        if ( STATUS_USART0  & ( (1<<FE)|(1<<DOR)|(1<<PE)) )
        {
            //return (-1);
            return (0);
        }
        //return DATA_USART0;
        return UDR0;
    }
    /********************************************************************************************
	When interrupt-driven data reception is used, the receive complete routine
	must read the received data from UDR in order to clear the RXC Flag, otherwise a new interrupt
	will occur once the interrupt routine terminates.
	********************************************************************************************/
    /*
    ISR(USART_RXC_vect)
	{
	    volatile byte DATA_USART;

        DATA_USART0 = RxDataUSART0();

	    if (DATA_USART0 != (0) )
	    {
	        EnviaCarLCD_an(DATA_USART);
	    }

        TxDataUSART0(DATA_USART0);
	}
    */

#endif

#ifdef _USART1_


#endif

#endif