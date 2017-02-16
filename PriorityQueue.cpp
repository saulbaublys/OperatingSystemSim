// Program Information ////////////////////////////////////////////////////////
/**
 * @file PriorityQueue.cpp
 *
 * @brief Implementation file for PriorityQueue class
 * 
 * @details Implements all member methods of the PriorityQueue class
 *
 * @version 1.00 (07 September 2015)
 *
 * @Note Requires PriorityQueue.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_PRIORITYQUEUE_CPP
#define CLASS_PRIORITYQUEUE_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "SimpleVector.h"
#include "PriorityQueue.h"

/**
 * @brief Default constructor
 *
 * @details Constructs SimpleVector data as default
 *          and sets number of priorities to default
 *          
 * @param None
 *
 * @note None
 */
template <class ProcessControlBlock>
PriorityQueue<ProcessControlBlock>::PriorityQueue
       (
        // data loaded via initializers
       )
    : qData()
   {
    // data loaded via initializers
   }

/**
 * @brief Copy constructor
 *
 * @details Constructs SimpleVector data as copy of given data
 *          and sets number of priorities to copied queue quantity
 *
 * @param in: PriorityQueue object to be copied
 *
 * @note None
 */
template <class ProcessControlBlock>
PriorityQueue<ProcessControlBlock>::PriorityQueue
       ( 
        const PriorityQueue<ProcessControlBlock> &copiedQueue // in: queue to copy
       )
     : qData( copiedQueue.qData )
   {
    // data loaded via initializers
   }

/**
 * @brief Class destructor
 *
 * @details Defaults to SimpleVector destructor
 *
 * @param None
 *
 * @note None
 */
template <class ProcessControlBlock>
PriorityQueue<ProcessControlBlock>::~PriorityQueue
       (
        // no parameters
       )
   {
    // destructor implicitly called for SimpleVector
   }

/**
 * @brief Assignment operator
 *
 * @details Assigns PriorityQueue object into this object
 *
 * @param in: PriorityQueue object to be assigned
 *
 * @note None
 */
template <class ProcessControlBlock>
const PriorityQueue<ProcessControlBlock> &
PriorityQueue<ProcessControlBlock>::operator = 
       (
        const PriorityQueue<ProcessControlBlock> & rhPQueue // in: assigned right side
       )
   {
    if( this != &rhPQueue )
       {
        qData = rhPQueue.qData;
       }

    return *this; 
   }

/**
 * @brief Enqueue operation
 *
 * @details Checks to make sure priority value is within range;
 *          if so, sets data into ProcessControlBlock form,
 *          seeks end of the list of priorities it is at,
 *          and enqueues
 *
 * @param in: priority value
 * @param in: process string (data)
 *
 * @note throws logic error if priority value is not within range
 */
template <class ProcessControlBlock>
void PriorityQueue<ProcessControlBlock>::enqueue
       (
        int priorityVal,  // in: priority value to be enqueued
        ProcessControlBlock &process
       ) throw ( logic_error )
   {
    int index;

    if( priorityVal > 0 )
       {
        for( index = 0; index < qData.getSize() &&
                     qData[ index ].getPriority() <= priorityVal; index++ );

        insertAtIndex( index, process );
       }

    else
       {
        throw logic_error( "Attempt to enqueue with negative priority" );
       }
   }

/**
 * @brief Dequeue operation
 *
 * @details If list is not empty, removes item at front of queue
 *          (which is at first element of the vector) and passes it back
 *
 * @param out: data item
 *
 * @note throws logic error if attempt to dequeue from empty list
 */
template <class ProcessControlBlock>
void PriorityQueue<ProcessControlBlock>::dequeue 
       (
        ProcessControlBlock &dQData // data returned from dequeue
       ) throw ( logic_error )
   {
    if( !isEmpty() )
       {
        removeAtIndex( 0, dQData );
       }

    else
       {
        throw logic_error( "Attempt to dequeue from empty list" );
       }
   }

/**
 * @brief Peek at front operation
 *
 * @details If list is not empty, returns data from the front of the queue
 *          (which is at first element of the vector) and passes it back
 *
 * @param out: data item
 *
 * @note throws logic error if attempt to peek at an empty list
 */
template <class ProcessControlBlock>
void PriorityQueue<ProcessControlBlock>::peekAtFront 
       (
        ProcessControlBlock &pkData // data returned from peek
       ) throw ( logic_error )
   {
    if( !isEmpty() )
       {
        pkData = qData[ 0 ];
       }

    else
       {
        throw logic_error( "Attempt to peek at front of empty list" );
       }
   }

/**
 * @brief check for empty list operation
 *
 * @details Checks with vector to see if list is empty, returns results
 *
 * @param None
 *
 * @note None
 */
template <class ProcessControlBlock>
bool PriorityQueue<ProcessControlBlock>::isEmpty
       (
        // no parameters
       ) const
   {
    return ( qData.getSize() == 0 );
   }

/**
 * @brief Insert at specified index operation
 *
 * @details Checks for full list; if full, grows by default amount,
 *          moves all items up from selected index, then inserts value
 *          then increments size
 *
 * @param out: data item
 *
 * @note throws logic error if attempt to dequeue from empty list
 */
template <class ProcessControlBlock>
void PriorityQueue<ProcessControlBlock>::insertAtIndex
       (
        int insertIndex,       // in: index at which to insert
        const ProcessControlBlock &dQData // in: data to insert at index
       )
   {
    int index;

    if( qData.getSize() == qData.getCapacity() )
      {
       // for case of empty capacity
       if( qData.getCapacity() > 0 )
          {
           qData.grow( qData.getCapacity() ); // double capacity
          }

       else
          {
           qData.grow( qData.DEFAULT_CAPACITY );
          }
      }

    for( index = qData.getSize(); index > insertIndex; index-- )
       {
        qData[ index ] = qData[ index - 1 ];
       }

    qData[ insertIndex ] = dQData;

    qData.incrementSize();
   }

/**
 * @brief Remove at index operation
 *
 * @details Retrieves value at given index, then copies all items down
 *          by one starting at removed index
 *          (which is at first element of the vector) and passes it back;
 *          then decrements size; then checks for vector capacity 4 * size;
 *          if so, shrinks capacity by half
 *
 * param in: index at which to remove item
 * @param out: data item found at index
 *
 * @note self-managing capacity
 */
template <class ProcessControlBlock>
void PriorityQueue<ProcessControlBlock>::removeAtIndex
       (
        int removeIndex,  // in: index at which to remove
        ProcessControlBlock &dQData  // in: data to found at index
       )
   {
    double quarterQueueCapacity = .25;
    double reduceQueueCapacityBy = .50;
    int index;

    dQData = qData[ removeIndex ];

    for( index = 0; index < qData.getSize() - 1; index++ )
       {
        qData[ index ] = qData[ index + 1 ];
       }

    qData.decrementSize();

    if( qData.getSize() < ( qData.getCapacity() * quarterQueueCapacity ) )
       {
        qData.shrink( qData.getCapacity() * reduceQueueCapacityBy );
       }
   }

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_PRIORITYQUEUE_CPP







