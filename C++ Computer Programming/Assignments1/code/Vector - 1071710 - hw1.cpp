#include "Vector.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
{
   myFirst = myLast = myEnd = nullptr;
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector(const size_type count)
{
	myFirst = new value_type[count]();
	myEnd = myFirst + count;
	myLast = myEnd;
	
}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector( const vector &right )
{

		value_type SizeLen = right.myLast - right.myFirst; //RightSize
		value_type CapaLen = right.myEnd - right.myFirst; // RightCapacity
		myFirst = new value_type[SizeLen](); //宣告一個RightCapacity大小空間
		for (value_type i = 0; i < SizeLen; i++)
		{
			*(myFirst + i) = *(right.myFirst + i);
		}
		myLast = myFirst + SizeLen;
		myEnd = myLast;

}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

// Adds a new element at the end of the vector, after its current last element.
// The content of val is copied to the new element.
// This effectively increases the vector size by one,
// which causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
void vector::push_back( const value_type &val )
{
	size_type originalSize = size();
	resize(originalSize + 1);
	myFirst[originalSize] = val;
}

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign( const vector &right )
{
   if( this != &right ) // avoid self-assignment
   {
	   value_type rightSize = right.myLast - right.myFirst;	
		   resize(rightSize);
		   for (int i = 0; i < rightSize; i++)
		   {
			   *(myFirst + i) = *(right.myFirst + i);
		   }
	   
   }
   return *this; // enables x = y = z, for example
}
// Resizes the vector so that it contains newSize elements.
// If newSize is smaller than the current vector size,
// the content is reduced to its first newSize elements, removing those beyond.
// If newSize is greater than the current vector size,
// the content is expanded by inserting at the end
// as many elements as needed to reach a size of newSize.
// The new elements are initialized as 0.
// If newSize is also greater than the current vector capacity,
// an automatic reallocation of the allocated storage space takes place.
void vector::resize(const size_type newSize)
{
	value_type sizeLen = size();
	value_type capaLen = capacity();
	value_type capaNum = capacity()/2;
	value_type capaLen2 = capaLen + capaNum;
	if (newSize < sizeLen) 
	{
		for (int i = 0; i < sizeLen - newSize; i++)
		{
			myLast--;
		}
	}
	else if (newSize > sizeLen && newSize <= capaLen)
	{
	
		for (int i = 0; i < newSize-sizeLen; i++)
		{
			*(myLast) = 0;
			myLast++;
		}
		
	}
	else if (newSize > capaLen )
	{

		if (capaLen2 > newSize)
		{
			value_type *temp = nullptr;
			temp = myFirst;
			myFirst = new int[capaLen2](); //宣告一個新的空間
			myLast = myFirst;
			for (int i = 0; i < sizeLen; i++)
			{
				*(myFirst + i) = *(temp + i);
			}
			myLast = myFirst + newSize;
			myEnd = myFirst + capaLen2;
			delete[] temp;
			temp = nullptr;
		}
		else
		{
			value_type *temp = nullptr;
			temp = myFirst;
			myFirst = new int[newSize](); //宣告一個新的空間
			for (int i = 0; i < sizeLen; i++)
			{
				*(myFirst + i) = *(temp +i);
				myLast++;
			}
			myLast = myFirst + newSize;
			myEnd = myFirst + newSize;
			delete[] temp;
			temp = nullptr; 
		}
	}
}

// Removes the last element in the vector,
// effectively reducing the container size by one.
void vector::pop_back()
{
   if( size() > 0 )
      --myLast;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear()
{
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::pointer vector::begin()
{
   return myFirst;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size()
{
   return ( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity()
{
   return ( myEnd - myFirst );
}

// Returns a reference to the element at position "pos" in the vector container.
vector::value_type& vector::element( const size_type pos )
{
   return myFirst[ pos ];
}