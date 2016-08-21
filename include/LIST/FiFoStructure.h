//////////////////////////////////////////////////////////////////////////////
///	\file FiFoStructure.h
///
///	\brief	FIFO Library API structure
///
///	\author	Steve Mayze
///
//////////////////////////////////////////////////////////////////////////////

#ifndef _FIFO_STRUCTURE_H_LIST_
#define _FIFO_STRUCTURE_H_LIST_

	#include "../common.h"


#ifdef _FIFO_TEST_
#define MAXQUEUESIZE 3	///< defines the FIFO buffer maximum size
#else
#define MAXQUEUESIZE 256	///< defines the FIFO buffer maximum size
#endif

//////////////////////////////////////////////////////////////////////////////
/// \brief The structure for the FIFO queue as an array of uint8_t
//////////////////////////////////////////////////////////////////////////////
	typedef struct {


		uint8_t items[MAXQUEUESIZE];	///<	The FIFO buffer of uint8_t

		uint8_t front;	///<	The front or read/remove point of the queue

		uint8_t rear;	///<	The rear or insert point of the queue

	} FIFOQueue;


	//////////////////////////////////////////////////////////////////////////
	/// \brief Define the interface for the FIFO list.
	//////////////////////////////////////////////////////////////////////////
	typedef struct {

		uint_fast8_t (*Initialize)( FIFOQueue *queue );	///<	\brief Initialize the queue

		uint_fast8_t (*Insert)(FIFOQueue *queue, const uint8_t byte);	///<	\brief	Insert an item at the end of the queue

		uint_fast8_t (*Remove)(FIFOQueue *queue, uint8_t *dest);	///<	\brief Remove an item from the front of the queue


	} FIFOInterface;

#endif // _FIFO_STRUCTURE_H_LIST_
