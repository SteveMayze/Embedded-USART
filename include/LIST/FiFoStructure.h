#ifndef _FIFO_STRUCTURE_H_LIST_
#define _FIFO_STRUCTURE_H_LIST_

	#include "../common.h"
#ifdef _FIFO_TEST_
#define MAXQUEUESIZE 5
#else
#define MAXQUEUESIZE 100
#endif

	typedef struct {

		uint_fast8_t items[MAXQUEUESIZE];
		int front, rear;

	} FIFOQueue;


	//////////////////////////////////////////////////////////////////////////
	/// \brief Define the interface for the FIFO list.
	//////////////////////////////////////////////////////////////////////////
	typedef struct {

		//////////////////////////////////////////////////////////////////////
		/// \brief	Inserts a data item into the FIFO queue
		///
		/// \param	FIFOQueue* 	A pointer to the queue to hold the data
		///			uint_fast8_t	The data to store in the queue
		///
		/// \return	TRUE Successful insertion
		///			FALSE Overflow occurred
		//////////////////////////////////////////////////////////////////////
		uint_fast8_t (*Insert)(FIFOQueue *queue, const uint_fast8_t byte);

		//////////////////////////////////////////////////////////////////////
		/// \brief	Removes a data item from the FIFO queue and inserts into
		///			dest.
		///
		/// \param	FIFOQueue*	The queue to remove the data from
		///			uint_fast8_t	The data to receive the information
		///
		///	\return	TRUE The data was successfully removed from the queue
		//////////////////////////////////////////////////////////////////////
		uint_fast8_t (*Remove)(FIFOQueue *queue, uint_fast8_t *dest);


	} FIFOInterface;

#endif
