//////////////////////////////////////////////////////////////////////////////
///	\file fifo.c
///
///	\brief	FIFO Library
///
///	\Author	Steve Mayze
///
//////////////////////////////////////////////////////////////////////////////

#include "LIST/fifo.h"

//////////////////////////////////////////////////////////////////////
/// \brief	Inserts a data item into the FIFO queue
///
/// \param	FIFOQueue *queue	The queue data to use
///
/// \return	TRUE	The initialization completed OK
///			ERROR	The queue is not defined
//////////////////////////////////////////////////////////////////////
static uint_fast8_t Initialize( FIFOQueue *queue ) {

	if( queue ) {
	    queue->front = queue->rear = MAXQUEUESIZE-1;

	    for(int i = 0; i < MAXQUEUESIZE; i++){
	    	queue->items[i] = 0;
	    }
	    return TRUE;
	}
	return ERROR;

}

//////////////////////////////////////////////////////////////////////
/// \brief	Inserts a data item into the FIFO queue
///
/// \param	FIFOQueue *queue 	A pointer to the queue to hold the data
///			uint8_t byte	The data to store in the queue
///
/// \return	TRUE	Successful insertion
///			FALSE	Overflow occurred
///			ERROR	The queue is not defined.
//////////////////////////////////////////////////////////////////////
static uint_fast8_t Insert(FIFOQueue *queue, const uint8_t byte){
	if( queue ){ // Check that the queue is valid
		uint_fast8_t tempData = queue->rear;
		if(MAXQUEUESIZE-1 == queue->rear)
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
	return ERROR;
}

//////////////////////////////////////////////////////////////////////
/// \brief	Removes a data item from the FIFO queue and inserts into
///			dest.
///
/// \param	FIFOQueue *queue	The queue to remove the data from
///			uint8_t *dest	The data to receive the information
///
///	\return	TRUE	The data was successfully removed from the queue
///			FALSE	The queue is empty
///			ERROR	The queue or destination are not defined.
//////////////////////////////////////////////////////////////////////
static uint_fast8_t Remove( FIFOQueue *queue, uint8_t *dest ){

	if( queue && dest ){ // Check that the pointer to the destination is valid
		if( queue->front == queue->rear )
			return FALSE;	// Underflow

		if( MAXQUEUESIZE-1 == queue->front )
			queue->front = 0;
		else
			(queue->front)++;
		*dest = queue->items[queue->front];
		return TRUE;
	}

	return ERROR;
}


//////////////////////////////////////////////////////////////////////////
/// \brief Defines the standard implementation for the FIFO queue
//////////////////////////////////////////////////////////////////////////
FIFOInterface FIFO = {
		Initialize,
		Insert,
		Remove
};
