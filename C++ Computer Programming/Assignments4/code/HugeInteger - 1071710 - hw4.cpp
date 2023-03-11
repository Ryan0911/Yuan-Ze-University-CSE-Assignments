#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
   : integer( 1, '0' )
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1, '0' )
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger& HugeInteger::operator=( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::operator==( const HugeInteger &right ) const
{
//   return operator==( integer, right.integer );
   return ( integer == right.integer );
} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::operator<( const HugeInteger &right ) const
{
	int size1 = integer.size();//buffer
	int	size2 = right.integer.size();//remainder
	//buffer <=remainder

	if (size1 > size2)
		return false;
	else if (size1 < size2)
		return true;
	else if (size1 == size2)
	{
		for (int i = size1 - 1; i >= 0; i--)
		{

			if (integer.begin()[i] < right.integer.begin()[i])
				return true;
			else if (integer.begin()[i] > right.integer.begin()[i])
				return false;
		}
	}
	if (*this ==right)
		return false;

	return true;

} // end function less

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::operator<=( const HugeInteger &right ) const
{
   return ( *this == right || *this < right );
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::operator+( HugeInteger &op2 )
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   string::iterator it1 = integer.begin();
   string::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   string::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 = ( *it3 - '0' ) + ( *it2 - '0' ) + '0';

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > '9' )
      {
         ( *it3 ) = ( *it3 - '0' ) - 10 + '0';
         ( *( it3 + 1 ) ) = ( *( it3 + 1 ) - '0' ) + 1 + '0';
      }

   if( *it3 == '0' )
      sum.integer.pop_back();

   return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::operator-( HugeInteger &op2 )
{
   HugeInteger zero;

   if( *this == op2 )
      return zero;

   HugeInteger difference( *this );


   unsigned int minuendSize = integer.size();
   unsigned int subtrahendSize = op2.integer.size();
   unsigned int differenceSize = (minuendSize >= subtrahendSize) ? minuendSize : subtrahendSize;

   for (int i = 0; i < subtrahendSize; i++)
   {
	   difference.integer.begin()[i] = (integer.begin()[i] - '0') - (op2.integer.begin()[i] - '0') + '0';
   }

   for (int i = 0; i < differenceSize; i++)
   {
	   if (difference.integer.begin()[i]-'0'<0)
	   {
		   difference.integer.begin()[i] = (difference.integer.begin()[i]-'0')+10+'0';
		   difference.integer.begin()[i + 1]= (difference.integer.begin()[i+1] - '0') -1 + '0';
	   }
   }
   for (int i = differenceSize - 1; i > 0; i--)
   {
	   if (difference.integer.begin()[i]=='0')
		   difference.integer.pop_back();
	   else
	   {
		   break;
	   }
   }

   return difference;
} // end function subtract

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::operator*( HugeInteger &op2 )
{
   HugeInteger zero;
   if( isZero() || op2.isZero() )
      return zero;
   unsigned int temp = 0;//紀錄
   unsigned int productSize = integer.size() + op2.integer.size();
   unsigned int multiplicandSize = integer.size(); 
   unsigned int multiplierSize = op2.integer.size(); //被乘
   HugeInteger product(productSize); //創空間
   for (int i = 0; i < multiplierSize; i++)
   {
	   for (int j = 0, start = i; j < multiplicandSize, start < multiplicandSize + i; j++, start++)
	   {


			   temp = (integer.begin()[j] - '0') *(op2.integer.begin()[i]-'0');
			   product.integer.begin()[start] = (product.integer.begin()[start] - '0') + (temp%10) + '0';
			   product.integer.begin()[start+1] = (product.integer.begin()[start+1] - '0') + (temp/10) + '0';
			   if (product.integer.begin()[start] > '9')
			   {
				   product.integer.begin()[start + 1] = (product.integer.begin()[start + 1] - '0') + ((product.integer.begin()[start] - '0') / 10) + '0';
				   product.integer.begin()[start] =((product.integer.begin()[start] - '0') % 10) + '0';

			   }
	   }
   }
   for (int i = productSize - 1; i >= 0; i--)//消'0'
   {
	   if (product.integer.begin()[i] == '0')
		   product.integer.pop_back();
	   else
		   break;
   }

   return product;
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::operator/( HugeInteger &op2 )
{
	int n = 0;
	int dividendSize = integer.size();
	int divisorSize = op2.integer.size();
	int quotientSize = 0;
   HugeInteger zero;
   if (isZero())
   {
	   return zero;
   }
   if( *this < op2 )
      return zero;
   HugeInteger remainder1(dividendSize);
   for (int i = 0; i < dividendSize; i++)
   {
	   remainder1.integer.begin()[i] = integer.begin()[i];
   }

	   n = dividendSize - divisorSize;
	   int bufferSize = divisorSize + n;
	   HugeInteger buffer(bufferSize);
	   for (int i = 0; i < divisorSize; i++)
		   buffer.integer.begin()[n + i] = op2.integer.begin()[i];
	   	quotientSize = dividendSize - divisorSize;	
	   if (*this<buffer)
		   buffer.divideByTen();
	   else
		   quotientSize++;
	   HugeInteger quotient(quotientSize);
	   for (int k = quotientSize - 1; k >= 0; k--)
	   {
		   while (buffer.operator<=(remainder1)) //buffer<=remainder
		   {
			   remainder1.operator=(remainder1.operator-(buffer));
			   quotient.integer.begin()[k]++;
			   if (remainder1.isZero())
				   return quotient;
		   }
		   buffer.divideByTen();
	   }
	   return quotient;


	   
   
} // end function divide

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::operator%( HugeInteger &op2 )
{
   HugeInteger quotient = ( *this ) / op2;
   HugeInteger product = quotient * op2;
   HugeInteger remainder = ( *this ) - product;
   return remainder;
}

// convert a string of decimal digits into a HugeInteger
void HugeInteger::convert( string &str )
{
   integer.resize( str.size() );
   string::iterator it1 = integer.end() - 1;
   string::iterator it2 = str.begin();
   for( ; it2 != str.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
   for( string::iterator it = integer.begin(); it != integer.end(); ++it )
      if( *it != '0' )
         return false;

   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   string::iterator it = integer.begin();
   string::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.pop_back();
}

// overloaded output operator
ostream& operator<<( ostream &output, const HugeInteger &hugeInteger )
{
   string::const_iterator it = hugeInteger.integer.end() - 1;

   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it <= '9' )
         output << *it;

   return output; // enables cout << x << y;
} // end function output
