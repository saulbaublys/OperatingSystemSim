// Program Information ////////////////////////////////////////////////////////
/**
 * @file PriorityQueue.h
 *
 * @brief Definition file for PriorityQueue class
 * 
 * @details Specifies all member methods of the PriorityQueue class,
 *          which is derived from the SimpleVector class
 *
 * @version 1.00 (07 September 2015)
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_PRIORITYQUEUE_H
#define CLASS_PRIORITYQUEUE_H

// Header files ///////////////////////////////////////////////////////////////

#include <stdexcept>
#include <iostream>
#include "SimpleVector.h"

using namespace std;

// Class constants ////////////////////////////////////////////////////////////

   // None

// Class definition ///////////////////////////////////////////////////////////

template <class ProcessControlBlock>
class PriorityQueue
   {
    public:

       // class constants
       static const int MIN_CAPACITY_SET = 1;
       static const int DEFAULT_NUM_PRIORITIES = 5;
       static const char SPACE = ' ';

       // constructors
       PriorityQueue();
       PriorityQueue( const PriorityQueue &copiedQueue ); 

       // destructor
       ~PriorityQueue();

       // assignment
       const PriorityQueue &operator = 
                                   ( const PriorityQueue<ProcessControlBlock> &rhPQueue );

       // modifiers
       void enqueue( int priorityVal, ProcessControlBlock &process ) throw ( logic_error );

       // accessors
       void dequeue( ProcessControlBlock &process ) throw ( logic_error );
       void peekAtFront( ProcessControlBlock &process ) throw ( logic_error );
       bool isEmpty() const;

    private:

       void insertAtIndex( int insertIndex, const ProcessControlBlock &process );
       void removeAtIndex( int removeIndex, ProcessControlBlock &process );

       SimpleVector<ProcessControlBlock> qData;
   };

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_PRIORITYQUEUE_H

