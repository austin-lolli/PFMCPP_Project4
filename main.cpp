/*
 Project 4 - Part 3 / 9
 Video: Chapter 4 Part 3 
 Casting

 Create a branch named Part3
 
    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.

 1) remove your functions that accepted a User-Defined Type
 
 2) remove any getValue() functions if you added them
 
 3) move all of your add/subtract/multiply/divide implementations out of the class.
  
 4) add user-defined conversion functions that convert to the numeric type your object holds.
        i.e. if your type holds an int, you'll need an operator int() function.
 
 5) make your member variable private.
         this conversion function should be the ONLY WAY to access the held value.
 
 6) clean up any forward declaration that you might have.
 
 7) make sure it compiles & runs without errors.
 
 8) use your knowledge of casting to remove any conversion warnings. 
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */


//forward declarations
/*
//no longer needed... 
struct FloatType;
struct DoubleType;
struct IntType;
*/


// float UDT 
struct FloatType
{
    float* heapFloat = nullptr; 

    FloatType( float f ) : heapFloat( new float(f) ) {}

    ~FloatType()
    {
        delete heapFloat;
        heapFloat = nullptr;
    }
    
    FloatType& add( float operand );
    FloatType& subtract( float operand );
    FloatType& multiply( float operand );
    FloatType& divide( float operand );
};

// double UDT
struct DoubleType
{
    double* heapDub = nullptr;

    DoubleType( double d ) : heapDub( new double(d) ) {}

    ~DoubleType()
    {
        delete heapDub;
        heapDub = nullptr;
    }
    
    DoubleType& add( double operand );
    DoubleType& subtract( double operand );
    DoubleType& multiply( double operand );
    DoubleType& divide( double operand );
};

// int UDT
struct IntType
{
    int* heapInt = nullptr;

    IntType( int i ) : heapInt( new int(i) ) {}

    ~IntType()
    {
        delete heapInt;
        heapInt = nullptr;
    }

    IntType& add( int operand );
    IntType& subtract( int operand );
    IntType& multiply( int operand );  
    IntType& divide( int operand );
};

// float member functions 
FloatType& FloatType::add( float operand )
{
    *heapFloat += operand;
    return *this;
}

FloatType& FloatType::subtract( float operand )
{
    *heapFloat -= operand;
    return *this;
}

FloatType& FloatType::multiply( float operand )
{
    *heapFloat *= operand;
    return *this;
}

FloatType& FloatType::divide( float operand )
{
    *heapFloat /= operand;
    return *this;
}

// double member functions
DoubleType& DoubleType::add( double operand )
{
    *heapDub += operand;
    return *this;
}

DoubleType& DoubleType::subtract( double operand )
{
    *heapDub -= operand;
    return *this;
}

DoubleType& DoubleType::multiply( double operand )
{
    *heapDub *= operand;
    return *this;
}

DoubleType& DoubleType::divide( double operand )
{
    *heapDub /= operand;
    return *this;
}

// int member functions
IntType& IntType::add( int operand )
{
    *heapInt += operand;
    return *this;
}

IntType& IntType::subtract( int operand )
{
    *heapInt -= operand;
    return *this;
}

IntType& IntType::multiply( int operand )
{
    *heapInt *= operand;
    return *this;
}

#include <iostream>
IntType& IntType::divide( int operand )
{
    if( operand == 0 )
    {
        std::cout << "Can't divide by 0! Cancelling divide operation."  << std::endl;       
        return *this;
    }
    
    *heapInt /= operand;
    return *this;
}

int main()
{
    /*
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    std::cout << "The result of ft^4 divided by it is: " << *ft.multiply( ft ).multiply( ft ).divide( it ).heapFloat << std::endl;
    std::cout << "The result of dt times 3 plus it is : " << *dt.multiply( 3 ).add( it ).heapDub << std::endl;
    std::cout << "The result of it divided by 3.14 multiplied by dt minus ft is: " << *it.divide( pi ).multiply( dt ).subtract( ft ).heapInt << std::endl;
    std::cout << "A couple operations followed by a divide by 0, which gets ignored and warns user: " << *it.multiply(it).divide(0).divide(0.0f).divide(0.0).heapInt <<std::endl;
    
    std::cout << "ft x it  =  " << *it.multiply( ft ).heapInt << std::endl;
    std::cout << "(it + dt + ft) x 24 = " << *it.add( dt ).add( ft ).multiply( 24 ).heapInt << std::endl;
    */


    std::cout << "good to go!" << std::endl;
}
