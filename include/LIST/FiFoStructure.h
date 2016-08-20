//////////////////////////////////////////////////////////////////////////////
///	\file FifoStructure.h
///
///	\brief	FIFO Library API structure
///
///	\Author	Steve Mayze
///
//////////////////////////////////////////////////////////////////////////////

#ifndef _FIFO_STRUCTURE_H_LIST_
#define _FIFO_STRUCTURE_H_LIST_

	#include "../common.h"

//////////////////////////////////////////////////////////////////////////////
// \brief defines the FIFO buffer maximum size
//////////////////////////////////////////////////////////////////////////////
#ifdef _FIFO_TEST_
#define MAXQUEUESIZE 3
#else
#define MAXQUEUESIZE 100
#endif

//////////////////////////////////////////////////////////////////////////////
// \brief The structure for the FIFO queue as an array of uint8_t
//////////////////////////////////////////////////////////////////////////////
	typedef struct {

		/// \brief The FIFO buffer of uint8_t
		uint8_t items[MAXQUEUESIZE];

		/// \brief The front and rear track the insert and remove point
		int front, rear;

	} FIFOQueue;


	//////////////////////////////////////////////////////////////////////////
	/// \brief Define the interface for the FIFO list.
	//////////////////////////////////////////////////////////////////////////
	typedef struct {

		uint_fast8_t (*Initialize)( FIFOQueue *queue );

		uint_fast8_t (*Insert)(FIFOQueue *queue, const uint8_t byte);

		uint_fast8_t (*Remove)(FIFOQueue *queue, uint8_t *dest);


	} FIFOInterface;

#endif // _FIFO_STRUCTURE_H_LIST_
