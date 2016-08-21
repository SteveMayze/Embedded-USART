/////////////////////////////////////////////////////////////////////////
///	\file main.c
///	\brief This is the main program code.
///
///	\author: Ronald Sousa (Opticalworm)
/////////////////////////////////////////////////////////////////////////
#include "common.h"
#include "MCU/led.h"
#include "MCU/usart2.h"
#include "MCU/tick.h"


#define TEST_BLOCK_5


/////////////////////////////////////////////////////////////////////////
///	\brief the first user code function to be called after the ARM M0
///	has initial.
/////////////////////////////////////////////////////////////////////////
#ifdef TEST_BLOCK_1
void main(void)
{
    uint8_t tempData;
    uint32_t delayCount = 0;

    Led_Init();
    Tick_init();

    SerialPort2.Open(115200);

    for ( ;; )
    {
        if(SerialPort2.GetByte(&tempData))
        {
        	SerialPort2.SendByte(tempData);

        	// Application simulation
        	for(delayCount = 1000; delayCount; delayCount--);
    		Led_Toggle(); // Toggle each byte
        }
    }
}
#endif

#ifdef TEST_BLOCK_2
#include "LIST/fifo.h"
void main(void)
{
    FIFOQueue queue;
    FIFO.Initialize(&queue);

	uint8_t data = 10;
	uint8_t tempData;
    for ( ;; )
    {
    	while(FIFO.Insert(&queue, data++)){
    		;
    	}
    	while(FIFO.Remove(&queue, &tempData)){
    		data = tempData;
    	}
    }
}
#endif

#ifdef TEST_BLOCK_3
#include "LIST/fifo.h"
void main(void)
{
    uint8_t tempData, sendData;

    Led_Init();
    Tick_init();

    SerialPort2.Open(115200);

    FIFOQueue queue;
    FIFO.Initialize(&queue);

    for ( ;; )
    {
        if(SerialPort2.GetByte(&tempData))
        {
        	if ( FALSE == FIFO.Insert(&queue, tempData)) {
        		SerialPort2.SendString("Buffer is full\r\n");
        	}
        }
        if(FIFO.Remove(&queue, &sendData)) {
        	SerialPort2.SendByte(sendData);
    		Led_Toggle(); // Toggle each byte
        }
    }
}
#endif

#ifdef TEST_BLOCK_4
#include "LIST/fifo.h"

void main(void)
{
    uint8_t tempData, sendData;
    uint_fast8_t fifoReturnValue;

    Led_Init();
    Tick_init();

    SerialPort2.Open(115200);

    FIFOQueue queue;
    FIFO.Initialize(&queue);

    for ( ;; )
    {
        if(SerialPort2.GetByte(&tempData))
        {
        	if ( FALSE == FIFO.Insert(&queue, tempData)) {
        		// SerialPort2.SendString("Buffer is full\r\n");
        		for(;;){
            		fifoReturnValue = FIFO.Remove(&queue, &sendData);
            		if( FALSE == fifoReturnValue){
            			FIFO.Insert(&queue, tempData);
    					break;
            		}
            		else if ( TRUE == fifoReturnValue){
            			SerialPort2.SendByte(sendData);
                		Led_Toggle(); // Toggle each byte
            		}
        		}
        	}
        }
    }
}
#endif


#ifdef TEST_BLOCK_5
void main(void)
{
    uint8_t tempData;

    Led_Init();
    Tick_init();

    SerialPort2.Open(9600);

    for ( ;; )
    {
        while ( TRUE == SerialPort2.GetByte(&tempData))
        {
			SerialPort2.SendByte(tempData);
        }
        // Some code to run
        Tick_DelayMs(500);
		Led_Toggle(); // Toggle each byte
    }
}
#endif
