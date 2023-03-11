#include "String.h" // include definition of class String

string::string() noexcept
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
}
// from buffer constructor
// Copies the first "count" characters from the array of characters pointed by ptr.
string::string( const char *const ptr, const size_type count )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
	if (count > myRes)
	{
		int myRes2 = myRes / 2;
		myRes = myRes +myRes2;
		if (myRes < (count / 16) * 16 + 15)
		{
			myRes = (count / 16) * 16 + 15;
		}
		mySize = count;
		value_type *Record = new char[count]; //新增一塊動態char空間
		for (int i = 0; i < count; i++)//將ptr內容放到動態陣列
		{
			Record[i] = ptr[i];
		}
		bx.ptr = &Record[0]; //再將原靜態陣列　指標指到新增的動態陣列

	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			bx.buf[i] = ptr[i];
		}
		mySize = count;
	}
	
}

// fill constructor
// Fills the string with "count" consecutive copies of character ch.
string::string( const size_type count, const char ch )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
	if (count > myRes) 
	{
		int myRes2 = myRes / 2;
		myRes = myRes + myRes2;
		if (myRes < (count / 16) * 16 + 15)
		{
			myRes = (count / 16) * 16 + 15;
		}
		mySize = count;
		value_type *Record = new char[myRes]; //新增一塊動態char空間
		for (int i = 0; i < count; i++)//將ptr內容放到動態陣列
		{
			Record[i] = ch;
		}
		bx.ptr = &Record[0]; //再將原靜態陣列　指標指到新增的動態陣列
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			myPtr()[i] = ch;
		}
		mySize = count;

	}

}

// copy constructor
// Constructs a copy of "right".
string::string( const string &right )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
	
	if (right.myRes > myRes) //新增複製容量
	{
		int mySize2 = mySize / 2;
		myRes = mySize +mySize2;
		if (myRes < (right.mySize / 16) * 16 + 15)
		{
			myRes = (right.mySize / 16) * 16 + 15;
		}
	}
	mySize = right.mySize;//要right的size
	if (myRes >= 16)
	{
		pointer temp = new value_type[myRes]();
		for (int i = 0;i<right.mySize ;i++ )
		{
			temp[i] = right.bx.ptr[i];
		}
		bx.ptr = &temp[0];
	}
	else
	{
		for (int i = 0;i<right.mySize ;i++)
		{
			bx.buf[i] = right.bx.buf[i];
		}
	}
}

string::~string() noexcept
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

const string::value_type* string::myPtr() const
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}
// String assignment
// Assigns a new value to the string, replacing its current contents.
string& string::assign( const string &right )
{
   if( this != &right )
   {

	   resize(right.mySize);
	   if (myRes >= 16)
	   {
		   if (right.myRes >= 16)
		   {
			   for (int i = 0; i < right.mySize; i++)
			   {
				   bx.ptr[i] = right.bx.ptr[i];
			   }
		   }
		   else
		   {
			   for (int i = 0; i < right.mySize; i++)
			   {
				   bx.ptr[i] = right.bx.buf[i];
			   }
		   }
	   }
	   else
	   {
		   if (right.myRes >= 16)
		   {
			   for (int i = 0; i < right.mySize; i++)
			   {
				   bx.buf[i] = right.bx.ptr[i];
			   }
		   }
		   else
		   {
			   for (int i = 0; i < right.mySize; i++)
			   {
				   bx.buf[i] = right.bx.buf[i];
			   }
		   }
	   }
	   


   }

   return *this;
}

void string::clear() noexcept
{
   mySize = 0;
   myPtr()[ 0 ] = value_type();
}

string::iterator string::begin() noexcept
{
   return iterator( myPtr() );
}

string::const_iterator string::begin() const noexcept
{
   return const_iterator( myPtr() );
}

string::iterator string::end() noexcept
{
   return iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::const_iterator string::end() const noexcept
{
   return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::reference string::element( const size_type off ) noexcept
{
   return myPtr()[ off ];
}

string::const_reference string::element( const size_type off ) const noexcept
{
   return myPtr()[ off ];
}

void string::push_back( char ch )
{
	resize(mySize + 1);
	myPtr()[mySize - 1] = ch;
}

void string::pop_back() noexcept
{
   if( mySize > 0 )
      --mySize;
}

string::reference string::front() noexcept
{
   return myPtr()[ 0 ];
}

string::const_reference string::front() const noexcept
{
   return myPtr()[ 0 ];
}

string::reference string::back() noexcept
{
   return myPtr()[ mySize - 1 ];
}

string::const_reference string::back() const noexcept
{
   return myPtr()[ mySize - 1 ];
}

const char* string::c_str() const noexcept
{
   return myPtr();
}

string::size_type string::size() const noexcept
{
   return mySize;
}

// Resizes the string to a length of "newSize" characters.
// If "newSize" is smaller than the current string length,
// the current value is shortened to its first "newSize" character,
// removing the characters beyond the "newSize"th.
// If "newSize" is greater than the current string length,
// the current content is extended by inserting at the end
// as many characters as needed to reach a size of "newSize".
// The new elements are initialized as copies of ch,
void string::resize( const size_type newSize, const char ch )
{
	
	if (newSize > myRes) //當newSize大於現在容量　新增空間
	{
		size_type newMyRes = myRes + myRes / 2;
		if (newMyRes < (newSize / 16) * 16 + 15)
		{
			newMyRes = (newSize / 16) * 16 + 15;
		}
		pointer temp = new value_type[newMyRes+1]();//新增一個動態空間

		if(myRes>=16)//ptr
		{
			for (int i = 0; i < mySize; i++)
			{
				temp[i] = bx.ptr[i];
			}
			delete[]bx.ptr;
		}
		else //buffer
		{
			for (int i = 0; i < mySize; i++)
			{
				temp[i] = bx.buf[i];
			}
		}
		for (int i = mySize; i < newSize; i++)
		{
			temp[i] = ch;
		}
		bx.ptr = &temp[0];
		temp = nullptr;
		myRes = newMyRes;
	}
	else if (newSize > mySize) //當newSize不大於現在容量　但需要用的空間加長
	{
		if(myRes<16) //buffer
		{
			for (int i = mySize; i < newSize; i++)
			{
				bx.buf[i] = ch;
			}
		}
		else if(myRes>=16)//ptr
		{
			for (int i = mySize; i < newSize; i++)
			{
				bx.ptr[i] = ch;
			}
		}
	}


	mySize = newSize;
}

string::size_type string::capacity() const noexcept
{
   return myRes;
}

bool string::empty() const noexcept
{
   return mySize == 0;
}