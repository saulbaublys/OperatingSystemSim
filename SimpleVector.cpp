// Program Information ////////////////////////////////////////////////////////
/**
 * @file SimpleVector.cpp
 * 
 * @author Michael Leverington
 *
 * @brief Implementation file for SimpleVector class
 * 
 * @details Implements all member methods of the SimpleVector class
 *
 * @version 1.00 (30 August 2015)
 *
 * @Note Requires SimpleVector.h
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef CLASS_SIMPLEVECTOR_CPP
#define CLASS_SIMPLEVECTOR_CPP

// Header files ///////////////////////////////////////////////////////////////

#include "SimpleVector.h"

/**
 * @brief Default constructor
 *
 * @details Constructs vector capacity to default and vector size to zero
 *          creates default size data array
 *          
 * @param None
 *
 * @note None
 */
template <class DataType>
SimpleVector<DataType>::SimpleVector
       (
        // data loaded via initializers
       )
    : vectorCapacity( DEFAULT_CAPACITY ), vectorSize( 0 ), 
      vectorData( new DataType[ DEFAULT_CAPACITY ] )
   {
    // data loaded via initializers
   }

/**
 * @brief Initialization constructor
 *
 * @details Constructs vector capacity to given capacity 
 *          and vector size to zero
 *          creates array of given capacity size
 *          
 * @param in: capacity with which to initialize vector
 *
 * @note None
 */
template <class DataType>
SimpleVector<DataType>::SimpleVector
       ( 
        int newCapacity // in: new vector capacity
       )
     : vectorCapacity( newCapacity ), vectorSize( 0 ), 
       vectorData( new DataType[ newCapacity ] )
   {
    // data loaded via initializers
   }

/**
 * @brief Initialization constructor
 *
 * @details Constructs vector to given capacity and zero size
 *          and sets each element to given fill value
 *          
 * @param in: capacity with which to initialize vector
 * @param in: fill value with which to initialize each element
 *
 * @note None
 */
template <class DataType>
SimpleVector<DataType>::SimpleVector
       ( 
        int newCapacity,          // in: new vector capacity
        const DataType &fillValue // in: fill value for all elements
       )
     : vectorCapacity( newCapacity ), vectorSize( 0 ), 
       vectorData( new DataType[ newCapacity] )
   {
    int index;

    for( index = 0; index < vectorCapacity; index++ )
       {
        vectorData[ index ] = fillValue;
       }
   }

/**
 * @brief Copy constructor
 *
 * @details Constructs vector capacity to default and vector size to zero
 *          creates default size data array
 *          
 * @param in: Other vector with which this vector is constructed
 *
 * @note Uses copyVector to move data into this vector
 */
template <class DataType>
SimpleVector<DataType>::SimpleVector
       ( 
        const SimpleVector<DataType> & copiedVector // in: vector to copy
       )
     : vectorCapacity( copiedVector.vectorCapacity ),
       vectorSize( copiedVector.vectorSize ),
       vectorData( new DataType[ vectorCapacity ] )
   {
    copyVector( vectorData, copiedVector.vectorData );
   }

/**
 * @brief object destructor
 *
 * @details If capacity is greater than zero, releases memory to system
 *          
 * @param None
 *
 * @note None
 */
template <class DataType>
SimpleVector<DataType>::~SimpleVector
       (
        // no parameters
       )
   {
    if( vectorCapacity > 0 )
       {
        delete [] vectorData;
       }
   }

/**
 * @brief assignment operation overload
 *
 * @details Assigns data from right-hand object to this object
 *          
 * @param in: right-hand vector object
 *
 * @note Uses copyVector to move data into this vector
 */
template <class DataType>
const SimpleVector<DataType> &
SimpleVector<DataType>::operator = 
       (
        const SimpleVector<DataType> & rhVector // in: assigned right side
       )
   {
    if( this != &rhVector )
       {
        if( vectorCapacity > 0 )
           {
            delete [] vectorData;
           }

        vectorCapacity = rhVector.vectorCapacity;
        vectorSize =     rhVector.vectorSize;
        vectorData = new DataType [ vectorCapacity ];

        copyVector( vectorData, rhVector.vectorData );
       }

    return *this; 
   }

/**
 * @brief vector capacity accessor
 *
 * @details returns capacity of this vector
 *          
 * @param None
 *
 * @note None
 */
template <class DataType>
int SimpleVector<DataType>::getCapacity
       (
        // no parameters
       ) const
   {
    return vectorCapacity;
   }

/**
 * @brief vector size accessor
 *
 * @details returns size of this vector
 *          
 * @param None
 *
 * @note None
 */
template <class DataType>
int SimpleVector<DataType>::getSize
       (
        // no parameters
       ) const
   {
    return vectorSize;
   }

template <class DataType>
bool SimpleVector<DataType>::isEmpty
       (
        // no paramters
       ) 
   {
    if(getSize() == 0)
      {
       return true;
      }
    return false;
   }


/**
 * @brief vector overloaded bracket operation
 *
 * @details allows assignment of data to element in this vector
 *          
 * @param in: index of element to be assigned
 *
 * @note throws logic error if index is out of bounds
 */
template <class DataType>
DataType &SimpleVector<DataType>::operator [] 
       ( 
        int index // in: index for array element
       ) 
     throw ( logic_error )
   {
    if ( index >= 0 && index < vectorCapacity )
       {
        return vectorData[ index ];
       }

    throw logic_error( "ERROR: Array index out of bounds" );
   }

/**
 * @brief vector overloaded bracket operation
 *
 * @details allows assignment of data from element in this vector
 *          
 * @param in: index of element to be assigned
 *
 * @note throws logic error if index is out of bounds
 */
template <class DataType>
const DataType &SimpleVector<DataType>::operator [] 
       ( 
        int index // in: index for array element
       ) const 
         throw ( logic_error )
   {
    if ( index >= 0 && index < vectorCapacity )
       {
        return vectorData[ index ];
       }

    throw logic_error( "ERROR: Array index out of bounds" );
   }

/**
 * @brief vector resize larger operation
 *
 * @details increases vector capacity by amount given in parameter
 *          
 * @param in: delta size for growth of vector
 *
 * @note creates new data list, copies using copyVector,
 *       then deletes old list
 */
template <class DataType>
void SimpleVector<DataType>::grow
       ( 
        int growBy // in: grow by amount
       )
   {
    DataType *newData;

    vectorCapacity += growBy;

    newData = new DataType[ vectorCapacity ];

    if( vectorCapacity > growBy )
       {
        copyVector( newData, vectorData );

        delete [] vectorData;  
       }

    vectorData = newData;
   }

/**
 * @brief vector resize smaller operation
 *
 * @details decreases vector capacity by amount given in parameter
 *          
 * @param in: delta size for reduction of vector
 *
 * @note creates new data list, copies using copyVector,
 *       then deletes old list
 *
 * @note vector does not check size before capacity reduction;
 *       if capacity is reduced to less than size, data will be lost
 */
template <class DataType>
void SimpleVector<DataType>::shrink
       ( 
        int shrinkBy // in: shrink by amount
       )
     throw ( logic_error )
   {
    DataType *newData;

    if( shrinkBy < vectorCapacity )
       {
        vectorCapacity -= shrinkBy;

        newData = new DataType[ vectorCapacity ];

        copyVector( newData, vectorData );

        delete [] vectorData;  

        vectorData = newData;

        if( vectorSize > vectorCapacity )
           {
            vectorSize = vectorCapacity;
           } 
       }

    else if( shrinkBy == vectorCapacity )
       {
        delete [] vectorData;

        vectorCapacity = 0;

        vectorSize = 0;
       }

    else
       {
        throw logic_error
                  ( "ERROR: Attempt to shrink vector by more than capacity" );
       }
   }

/**
 * @brief vector size mutator - increase
 *
 * @details increases vector size count
 *          
 * @param None
 *
 * @note has no effect on operation of vector;
 *       provided as convenience to user/programmer
 *       
 */
template <class DataType>
void SimpleVector<DataType>::incrementSize
       (
        // no parameters
       )
   {
    vectorSize++;
   }

/**
 * @brief vector size mutator - decrease
 *
 * @details decreases vector size count
 *          
 * @param None
 *
 * @note has no effect on operation of vector;
 *       provided as convenience to user/programmer
 *       
 */
template <class DataType>
void SimpleVector<DataType>::decrementSize
       (
        // no parameters
       )
   {
    vectorSize--;
   }

/**
 * @brief array/vector copy tool
 *
 * @details private element by element copy operation
 *          
 * @param in: destination vector/array
 * @param in: source vector/array
 *
 * @note copies data from source array/vector to destination array/vector
 *       element by element
 *       
 */
template<class DataType>
void SimpleVector<DataType>::removeAtIndex
        (
         int atIndex
        )
  {
   if(vectorSize >= 0 && atIndex < vectorSize)
      {
       while(atIndex < vectorSize-1)
          {
           vectorData[atIndex] = vectorData[atIndex+1];
           atIndex++;
          }       
      }

   decrementSize();
  }


/**
 * @brief array/vector copy tool
 *
 * @details private element by element copy operation
 *          
 * @param in: destination vector/array
 * @param in: source vector/array
 *
 * @note copies data from source array/vector to destination array/vector
 *       element by element
 *       
 */
template<class DataType>
int SimpleVector<DataType>::findItem
        (
         int itemID
        )
  {
   int index = 0;
   while(index < vectorSize)
      { 
//cout << endl << "BLOCKED ID: " << vectorData[0].getProcessID() << endl;
//cout << "itemID: " << itemID << endl << endl;
       if(vectorData[index].getProcessID() == itemID)
          {   
//cout << "BLOCKED ID: " << vectorData[0].getProcessID() << endl << endl << endl;
           return index;
          }
       index++;
      }
   return -1;
  }
/**
 * @brief array/vector copy tool
 *
 * @details private element by element copy operation
 *          
 * @param in: destination vector/array
 * @param in: source vector/array
 *
 * @note copies data from source array/vector to destination array/vector
 *       element by element
 *       
 */
template <class DataType>
void SimpleVector<DataType>::copyVector
       ( 
        DataType *dest, // out: copied vector, destination
        DataType *src   // in: vector coped, source
       )
   {
    int index;

    for( index = 0; index < vectorSize; index++ )
       {
        dest[ index ] = src[ index ];
       }
   }

// Terminating precompiler directives  ////////////////////////////////////////

#endif		// #ifndef CLASS_SIMPLEVECTOR_CPP







