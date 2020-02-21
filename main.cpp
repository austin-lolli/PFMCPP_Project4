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
struct FloatType;
struct DoubleType;
struct IntType;


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
    FloatType& add( const FloatType& operand );
    FloatType& add( const DoubleType& operand );
    FloatType& add( const IntType& operand );

    FloatType& subtract( float operand );
    FloatType& subtract( const FloatType& operand );
    FloatType& subtract( const DoubleType& operand );
    FloatType& subtract( const IntType& operand );

    FloatType& multiply( float operand );
    FloatType& multiply( const FloatType& operand );
    FloatType& multiply( const DoubleType& operand );
    FloatType& multiply( const IntType& operand );

    FloatType& divide( float operand );
    FloatType& divide( const FloatType& operand );
    FloatType& divide( const DoubleType& operand );
    FloatType& divide( const IntType& operand );
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
    DoubleType& add( const FloatType& operand );
    DoubleType& add( const DoubleType& operand );
    DoubleType& add( const IntType& operand );
        
    DoubleType& subtract( double operand );
    DoubleType& subtract( const FloatType& operand );
    DoubleType& subtract( const DoubleType& operand );
    DoubleType& subtract( const IntType& operand );

    DoubleType& multiply( double operand );
    DoubleType& multiply( const FloatType& operand );
    DoubleType& multiply( const DoubleType& operand );
    DoubleType& multiply( const IntType& operand );
    
    DoubleType& divide( double operand );
    DoubleType& divide( const FloatType& operand );
    DoubleType& divide( const DoubleType& operand );
    DoubleType& divide( const IntType& operand );
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
    IntType& add( const FloatType& operand );
    IntType& add( const DoubleType& operand );
    IntType& add( const IntType& operand );
        
    IntType& subtract( int operand );
    IntType& subtract( const FloatType& operand );
    IntType& subtract( const DoubleType& operand );
    IntType& subtract( const IntType& operand );

    IntType& multiply( int operand );
    IntType& multiply( const FloatType& operand );
    IntType& multiply( const DoubleType& operand );
    IntType& multiply( const IntType& operand );
    
    IntType& divide( int operand );
    IntType& divide( const FloatType& operand );
    IntType& divide( const DoubleType& operand );
    IntType& divide( const IntType& operand );
};

// float member functions 
FloatType& FloatType::add( float operand )
{
    *heapFloat += operand;
    return *this;
}

FloatType& FloatType::add( const FloatType& operand )
{
    return add(*operand.heapFloat);
}

FloatType& FloatType::add( const DoubleType& operand )
{
    return add(*operand.heapDub);
}

FloatType& FloatType::add( const IntType& operand )
{
    return add(*operand.heapInt);
}

FloatType& FloatType::subtract( float operand )
{
    *heapFloat -= operand;
    return *this;
}

FloatType& FloatType::subtract( const FloatType& operand )
{
    return subtract(*operand.heapFloat);
}

FloatType& FloatType::subtract( const DoubleType& operand )
{
    return subtract(*operand.heapDub);
}

FloatType& FloatType::subtract( const IntType& operand )
{
    return subtract(*operand.heapInt);  
}

FloatType& FloatType::multiply( float operand )
{
    *heapFloat *= operand;
    return *this;
}

FloatType& FloatType::multiply( const FloatType& operand )
{
    // *heapFloat *= *operand.heapFloat;
    // return *this;
    return multiply( *operand.heapFloat );
}

FloatType& FloatType::multiply( const DoubleType& operand )
{
    return multiply( *operand.heapDub );
}

FloatType& FloatType::multiply( const IntType& operand )
{
    return multiply( *operand.heapInt );
}

FloatType& FloatType::divide( float operand )
{
    *heapFloat /= operand;
    return *this;
}

FloatType& FloatType::divide( const FloatType& operand )
{
    return divide( *operand.heapFloat );
}

FloatType& FloatType::divide( const DoubleType& operand )
{
    return divide( *operand.heapDub );
}

FloatType& FloatType::divide( const IntType& operand )
{
    return divide( *operand.heapInt );
}

// double member functions
DoubleType& DoubleType::add( double operand )
{
    *heapDub += operand;
    return *this;
}

DoubleType& DoubleType::add( const FloatType& operand )
{
    return add( *operand.heapFloat );
}

DoubleType& DoubleType::add( const DoubleType& operand )
{
    return add( *operand.heapDub );
}

DoubleType& DoubleType::add( const IntType& operand )
{
    return add( *operand.heapInt );
}

DoubleType& DoubleType::subtract( double operand )
{
    *heapDub -= operand;
    return *this;
}

DoubleType& DoubleType::subtract( const FloatType& operand )
{
    return subtract( *operand.heapFloat );
}

DoubleType& DoubleType::subtract( const DoubleType& operand )
{
    return subtract( *operand.heapDub );
}

DoubleType& DoubleType::subtract( const IntType& operand )
{
    return subtract( *operand.heapInt );
}

DoubleType& DoubleType::multiply( double operand )
{
    *heapDub *= operand;
    return *this;
}

DoubleType& DoubleType::multiply( const FloatType& operand )
{
    return multiply( *operand.heapFloat );
}

DoubleType& DoubleType::multiply( const DoubleType& operand )
{
    return multiply( *operand.heapDub );
}

DoubleType& DoubleType::multiply( const IntType& operand )
{
    return multiply( *operand.heapInt );
}

DoubleType& DoubleType::divide( double operand )
{
    *heapDub /= operand;
    return *this;
}

DoubleType& DoubleType::divide( const FloatType& operand )
{
    return divide( *operand.heapFloat );
}

DoubleType& DoubleType::divide( const DoubleType& operand )
{
    return divide( *operand.heapDub );
}

DoubleType& DoubleType::divide( const IntType& operand )
{
    return divide( *operand.heapInt );
}

// int member functions
IntType& IntType::add( int operand )
{
    *heapInt += operand;
    return *this;
}

IntType& IntType::add( const FloatType& operand )
{
    return add( *operand.heapFloat );
}

IntType& IntType::add( const DoubleType& operand )
{
    return add( *operand.heapDub );
}

IntType& IntType::add( const IntType& operand )
{
    return add( *operand.heapInt );
}

IntType& IntType::subtract( int operand )
{
    *heapInt -= operand;
    return *this;
}

IntType& IntType::subtract( const FloatType& operand )
{
    return subtract( *operand.heapFloat );
}

IntType& IntType::subtract( const DoubleType& operand )
{
    return subtract( *operand.heapDub );
}

IntType& IntType::subtract( const IntType& operand )
{
    return subtract( *operand.heapInt );
}

IntType& IntType::multiply( int operand )
{
    *heapInt *= operand;
    return *this;
}

IntType& IntType::multiply( const FloatType& operand )
{
    return multiply( *operand.heapFloat);
}

IntType& IntType::multiply( const DoubleType& operand )
{
    return multiply( *operand.heapDub );
}

IntType& IntType::multiply( const IntType& operand )
{
    return multiply( *operand.heapInt );
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

IntType& IntType::divide( const FloatType& operand )
{
    return divide( *operand.heapFloat );
}

IntType& IntType::divide( const DoubleType& operand )
{
    return divide( *operand.heapDub );
}

IntType& IntType::divide( const IntType& operand )
{
    return divide( *operand.heapInt );
}

int main()
{
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    std::cout << "The result of ft^4 divided by it is: " << *ft.multiply( ft ).multiply( ft ).divide( it ).heapFloat << std::endl;
    std::cout << "The result of dt times 3 plus it is : " << *dt.multiply( 3 ).add( it ).heapDub << std::endl;
    std::cout << "The result of it divided by 3.14 multiplied by dt minus ft is: " << *it.divide( pi ).multiply( dt ).subtract( ft ).heapInt << std::endl;
    std::cout << "A couple operations followed by a divide by 0, which gets ignored and warns user: " << *it.multiply(it).divide(0).divide(0.0f).divide(0.0).heapInt <<std::endl;
    /*
    std::cout << "ft x it  =  " << *it.multiply( ft ).heapInt << std::endl;
    std::cout << "(it + dt + ft) x 24 = " << *it.add( dt ).add( ft ).multiply( 24 ).heapInt << std::endl;
    */


    std::cout << "good to go!" << std::endl;
}
