#include <MCU/usart2.h>
#include "cmsis_device.h"
#include "common.h"

// #define USART_OVER_SAMPLE_16

uint_fast8_t isOpenFlag = FALSE;

uint_fast8_t isSerialOpen(void) {
	return isOpenFlag;
}

static void close(void) {
	USART2->CR1 &= ~(1);
}


static void setBaudRate(uint32_t baud) {

	uint_fast8_t wasUARTEnabled = FALSE;
	uint16_t baudRateTemp = 0;

	if(isOpenFlag){
		wasUARTEnabled = TRUE;
		close();
	}

#ifdef USART_OVER_SAMPLE_16

	baudRateTemp = (SystemCoreClock) / (baud);

#else

	// Section 23.4.4 of the Reference Manual
	baudRateTemp = (2 * SystemCoreClock) / (baud);
	baudRateTemp = ((baudRateTemp & 0xFFFFFFF0) | ((baudRateTemp >> 1 ) & 0x00000007));

#endif

	USART2->BRR = baudRateTemp;
	if( wasUARTEnabled) {
		USART2->CR1 |= 1;
	}

}

static uint_fast8_t open(uint32_t baud) {

	if (!isOpenFlag) {
		RCC->APB1ENR |= RCC_AHBENR_GPIOAEN;	// Enable the USART clock

		USART2->CR1 = 0;					// Clear the USART2 Register

		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;	// Enable the GPIO clock

		GPIOA->MODER &= ~(3 << 4); 			// Clear the PA2 MODER
		GPIOA->MODER |= (2 << 4);			// Set the PA2 MODER to Alternate Function

		GPIOA->MODER &= ~(3 << 6);
		GPIOA->MODER |= (2 << 6);			// Set the PA3 MODER to the alternate function

		GPIOA->AFR[0] &= ~(0xF << 8);		// Clear the PA2 Configuration
		GPIOA->AFR[0] |= (1 << 8);			// Set 'which' Alternate function mode. In this case "AF-1".

		GPIOA->AFR[0] &= ~(0xF << 12);
		GPIOA->AFR[0] |= (1 << 12);

		setBaudRate(baud);

		USART2->CR1 |= (1<<15)|   1     | (1<<3) | (1<<2);
		//              OS8     USART EN     Tx        Rx

		isOpenFlag = TRUE;
	}

	return TRUE;
}

static uint_fast8_t isWriteBusy() {
    if( USART2->ISR & (1<<7)) {
    	return FALSE;
    }
	return TRUE;
}

static uint_fast8_t sendByte(uint8_t source) {

	if( isOpenFlag ) {
		while(isWriteBusy());
		USART2->TDR = source;
		return TRUE;
	}
	return FALSE;

}

static int_fast8_t doesReceiveBufferHaveData(void) {
	if (isOpenFlag) {
		if (USART2->ISR & (1 << 5)) {
			return TRUE;
		}
		return FALSE;
	}
	return -1;
}

static int_fast8_t getByte(uint8_t *destination) {

	int_fast8_t result = doesReceiveBufferHaveData();

	if (result) {
		// DataConverter buffer;
		// buffer.ui16_t = USART2->RDR;
		//destination = buffer.ui8_t;
		*destination = USART2->RDR;
	}
	return result;
}

static uint_fast8_t sendString(const uint8_t *source) {
	if (isSerialOpen() && source) {
		while (*source) {
			if (!sendByte(*source)) {
				return FALSE;
			}
			source++;
		}
		return TRUE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Write an array of bytes
///
/// \param source pointer to the array to transmit.
/// \param length is the size of the array
///
/// \return true = success else either the port is not open or the pointer
/// to the array is invalid.
///////////////////////////////////////////////////////////////////////////////
static uint_fast8_t sendArray(const uint8_t *source, uint32_t length)
{
    if (isOpenFlag && source)
    {
        for ( ; length ; length--)
        {
            if ( !sendByte(*source) )
            {
                return FALSE;
            }
            source++;
        }
        return TRUE;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Defines the standard serial functions for usart 2
///
/// /sa SerialInterface
///////////////////////////////////////////////////////////////////////////////
SerialInterface SerialPort2 = {
                                    isSerialOpen,
                                    open,
                                    close,
                                    sendByte,
                                    sendString,
                                    sendArray,
                                    doesReceiveBufferHaveData,
                                    getByte
                                };



