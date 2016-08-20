/////////////////////////////////////////////////////////////////////////
///	\file main.c
///	\brief This is the main program code.
///
///	Author: Ronald Sousa (Opticalworm)
/////////////////////////////////////////////////////////////////////////
#include "common.h"
#include "MCU/led.h"
#include "MCU/usart2.h"
#include "MCU/tick.h"


#define TEST_BLOCK_2


#ifdef TEST_BLOCK_1
/////////////////////////////////////////////////////////////////////////
///	\brief the first user code function to be called after the ARM M0
///	has initial.
/////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////
///	\brief the first user code function to be called after the ARM M0
///	has initial.
/////////////////////////////////////////////////////////////////////////
void main(void)
{
    FIFOQueue queue;
    queue.front = queue.rear = MAXQUEUESIZE-1;

	uint_fast8_t data = 10;
	uint_fast8_t tempData;
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
