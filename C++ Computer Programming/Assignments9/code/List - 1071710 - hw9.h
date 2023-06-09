// list standard header

#ifndef LIST
#define LIST

#include "XUtility.h"

// CLASS TEMPLATE ListConstIterator
template< typename MyList >
class ListConstIterator
{
public:
   using nodePtr = typename MyList::nodePtr;
   using value_type = typename MyList::value_type;
   using difference_type = typename MyList::difference_type;
   using pointer = typename MyList::const_pointer;
   using reference = const value_type &;

   ListConstIterator()
      : ptr()
   {
   }

   ListConstIterator( nodePtr pNode )
      : ptr( pNode )
   {
   }

   reference operator*() const
   {
      return ptr->myVal;
   }

   ListConstIterator& operator++()
   {
      ptr = ptr->next;
      return *this;
   }

   ListConstIterator operator++( int )
   {
      ListConstIterator temp = *this;
      ptr = ptr->next;
      return temp;
   }

   ListConstIterator& operator--()
   {
      ptr = ptr->prev;
      return *this;
   }

   ListConstIterator operator--( int )
   {
      ListConstIterator temp = *this;
      ptr = ptr->prev;
      return temp;
   }

   bool operator==( const ListConstIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const ListConstIterator &right ) const
   {
      return !( *this == right );
   }

   nodePtr ptr; // pointer to node
};


// CLASS TEMPLATE ListIterator
template< typename MyList >
class ListIterator : public ListConstIterator< MyList >
{
public:
   using MyBase = ListConstIterator< MyList >;

   using nodePtr = typename MyList::nodePtr;
   using value_type = typename MyList::value_type;
   using difference_type = typename MyList::difference_type;
   using pointer = typename MyList::pointer;
   using reference = value_type &;

   using MyBase::MyBase;

   reference operator*() const
   {

      return const_cast< reference >( MyBase::operator*() );
   }

   ListIterator& operator++()
   {
      MyBase::operator++();
      return *this;
   }

   ListIterator operator++( int )
   {
      ListIterator temp = *this;
      MyBase::operator++();
      return temp;
   }

   ListIterator& operator--()
   {
      MyBase::operator--();
      return *this;
   }

   ListIterator operator--( int )
   {
      ListIterator temp = *this;
      MyBase::operator--();
      return temp;
   }
};

template< typename ValueType >
struct ListNode // list node
{
   using nodePtr = ListNode *;

   nodePtr next; // successor node, or first element if head
   nodePtr prev; // predecessor node, or last element if head
   ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
   using node = ListNode< Ty >;
   using nodePtr = node *;

   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   ListVal() // initialize data
      : myHead(),
        mySize( 0 )
   {
   }

   nodePtr myHead; // pointer to head node
   size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
   using node = ListNode< Ty >;
   using nodePtr = node *;
   using ScaryVal = ListVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = ListIterator< ScaryVal >;
   using const_iterator = ListConstIterator< ScaryVal >;
   using reverse_iterator = ReverseIterator< iterator >;
   using const_reverse_iterator = ReverseIterator< const_iterator >;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   list()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   explicit list( size_type count ) // construct list from count * Ty()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;

      if( count > 0 )
         for( size_type i = 0; i < count; ++i )
            push_back( Ty() );
   }

   // copy constructor
   // Constructs a container with a copy of each of the elements in "right",
   // in the same order.
   list( const list &right )
      : myData()
   {
	   nodePtr temp = right.myData.myHead;
	   myData.myHead = new node;
	   myData.myHead->myVal = Ty();
	   myData.myHead->prev = myData.myHead->next = myData.myHead;

	   int listSize = right.myData.mySize;
	   if (right.myData.mySize > 0)
		   for (int i = 0; i < listSize; i++)
		   {
			   temp = temp->next;
			   push_back(temp->myVal);
		   }
   }

   // List destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the list container.
   ~list()
   {
      clear();
      delete myData.myHead;
   }

   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the container
   // (with "right" preserving its contents).
   list& operator=( const list &right )
   {
	   if (this != &right)
	   {
		   nodePtr temp = myData.myHead;
		   nodePtr temp2 = right.myData.myHead;
		   int listSize = right.myData.mySize;
		   resize(listSize);
		   if (right.myData.mySize > 0)
		   {
			   for (int i = 0; i < listSize; i++)
			   {
				   temp = temp->next;
				   temp2 = temp2->next;
				   temp->myVal = temp2->myVal;

			   }
		   }
	  }

      return *this;
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return iterator( myData.myHead->next );
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myHead->next );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   iterator end()
   {
      return iterator( myData.myHead );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myHead );
   }

   // Returns a reverse iterator pointing to the last element in the container
   // ( i.e., its reverse beginning ).
   // rbegin points to the element right before the one
   // that would be pointed to by member end.
   reverse_iterator rbegin()
   {
      return reverse_iterator( end() );
   }

   // Returns a reverse iterator pointing to the last element in the container
   // ( i.e., its reverse beginning ).
   // rbegin points to the element right before the one
   // that would be pointed to by member end.
   const_reverse_iterator rbegin() const
   {
      return const_reverse_iterator( end() );
   }

   // Returns a reverse iterator pointing to the theoretical element
   // preceding the first element in the list container
   // (which is considered its reverse end).
   reverse_iterator rend()
   {
      return reverse_iterator( begin() );
   }

   // Returns a reverse iterator pointing to the theoretical element
   // preceding the first element in the list container
   // (which is considered its reverse end).
   const_reverse_iterator rend() const
   {
      return const_reverse_iterator( begin() );
   }

   // Resizes the container so that it contains "newSize" elements.
   // If "newSize" is smaller than the current container size,
   // the content is reduced to its first "newSize" elements,
   // removing those beyond( and destroying them ).
   // If "newSize" is greater than the current container size,
   // the content is expanded by inserting at the end
   // as many elements as needed to reach a size of "newSize".
   // The new elements are initialized as 0.
   void resize( size_type newSize )
   {
      if( myData.mySize < newSize ) // pad to make larger
      {
         size_type difference = newSize - myData.mySize;
         for( size_type i = 0; i < difference; i++ ) // create newSize - myData.mySize elements
            push_back( Ty() );
      }
      else
      {
         while( newSize < myData.mySize )
            pop_back();
      }
   }

   // Returns the number of elements in the list container.
   size_type size() const
   {
      return myData.mySize;
   }

   // Returns whether the list container is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference front()
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference front() const
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference back()
   {
      return myData.myHead->prev->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference back() const
   {
      return myData.myHead->prev->myVal;
   }

   // Inserts a new element at the beginning of the list,
   // right before its current first element.
   // The content of val is copied (or moved) to the inserted element.
   // This effectively increases the container size by one.
   void push_front( const Ty &val )
   {
	   nodePtr newNode = new  node;
	   newNode->myVal = val;
	   newNode->next = myData.myHead->next;
	   newNode->prev = myData.myHead;
	   newNode->next->prev = newNode;
	   newNode->prev->next = newNode;

	   myData.mySize++;
   }

   // Removes the first element in the list container,
   // effectively reducing its size by one.
   // This destroys the removed element.
   void pop_front()
   {
      if( myData.mySize > 0 )
      {
		  nodePtr temp = myData.myHead->next;

		  myData.myHead->next = myData.myHead->next->next;
		  myData.myHead->next->prev = myData.myHead;
		  delete temp;
		  myData.mySize--;
      }
   }

   // Adds a new element at the end of the list container,
   // after its current last element.
   // The content of val is copied (or moved) to the new element.
   // This effectively increases the container size by one.
   void push_back( const Ty &val )
   {
	   nodePtr newNode = new  node;
	   newNode->myVal = val;
	   newNode->prev = myData.myHead->prev;
	   newNode->next = myData.myHead;
	   myData.myHead->prev->next = newNode;
	   myData.myHead->prev = newNode;

	   myData.mySize++;
   }

   // Removes the last element in the list container,
   // effectively reducing the container size by one.
   void pop_back()
   {
      if( myData.mySize > 0 )
      {
		  nodePtr temp = myData.myHead->prev;
		  myData.myHead->prev = temp->prev;
		  myData.myHead->prev->next = myData.myHead;
		  myData.mySize--;
		  delete temp;
      }
   }

   // Removes all elements from the list container (which are destroyed),
   // and leaving the container with a size of 0.
   void clear() // erase all
   {
      if( myData.mySize != 0 ) // the list is not empty
      {
         while( myData.myHead->next != myData.myHead )
         {
            myData.myHead->next = myData.myHead->next->next;
            delete myData.myHead->next->prev;
         }

         myData.myHead->prev = myData.myHead;
         myData.mySize = 0;
      }
   }

private:
   ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==( const list< Ty > &left, const list< Ty > &right )
{
	int listSize = left.size();
	int listSize2 = right.size();
	typename list<Ty>::const_iterator leftNum = left.begin();
	typename list<Ty>::const_iterator rightNum = right.begin();

	if (listSize != listSize2)
		return false;
	else
	{
		for (int i = 0; i < listSize; i++)
		{
			if (*leftNum != *rightNum)
				return false;
			else
			{
				rightNum++;
				leftNum++;
			}
		}
	}
	return true;
}
#endif // LIST