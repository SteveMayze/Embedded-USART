#include "LIST/fifo.h"


//////////////////////////////////////////////////////////////////////
/// \brief	Inserts a data item into the FIFO queue
///
/// \param	FIFOQueue* 	A pointer to the queue to hold the data
///			uint_fast8_t	The data to store in the queue
///
/// \return	TRUE Successful insertion
///			FALSE Overflow occurred
//////////////////////////////////////////////////////////////////////
static uint_fast8_t Insert(FIFOQueue *queue, const uint_fast8_t byte){
	uint_fast8_t tempData = queue->rear;
	if(queue->rear == MAXQUEUESIZE-1)
		queue->rear = 0;
	else
		(queue->rear)++;

	// Check of overflow
	if(queue->rear == queue->front) {
		queue->rear = tempData; // Roll-back the insert
		return FALSE;	// Overflow
	}

	queue->items[queue->rear] = byte;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
/// \brief	Removes a data item from the FIFO queue and inserts into
///			dest.
///
/// \param	FIFOQueue*	The queue to remove the data from
///			uint_fast8_t	The data to receive the information
///
///	\return	TRUE The data was successfully removed from the queue
//////////////////////////////////////////////////////////////////////
static uint_fast8_t Remove( FIFOQueue *queue, uint_fast8_t *dest ){

	if( queue->front == queue->rear )
		return FALSE;	// Underflow

	if( queue->front == MAXQUEUESIZE-1)
		queue->front = 0;
	else
		(queue->front)++;
	*dest = queue->items[queue->front];

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
/// \brief Defines the standard implementation for the FIFO queue
//////////////////////////////////////////////////////////////////////////
FIFOInterface FIFO = {
		Insert,
		Remove
};
