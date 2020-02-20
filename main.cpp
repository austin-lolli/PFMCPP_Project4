/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 Create a branch named Part2

New/This/Pointers/References conclusion

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 0) in the blank space below, declare/define an empty struct named 'A' on a single Line. 
     on the lines below it, write a struct named 'HeapA' that correctly shows how to own an instance of 'A' 
         on the heap without leaking, without using smart pointers. 
 */
struct A { };

struct HeapA
{
    A *aOfA = nullptr;

    HeapA() : aOfA(new A) {}
    ~HeapA()
    {
        delete aOfA;
        aOfA = nullptr;
    }
};



 /*
 1) Edit your 3 structs so that they own a heap-allocated primitive type without using smart pointers  
         IntType should own a heap-allocated int, for example.
 
 2) give it a constructor that takes the appropriate primitive
    this argument will initialize the owned primitive's value.
         i.e. if you're owning an int on the heap, your ctor argument will initialize that heap-allocated int's value.
 
 3) modify those add/subtract/divide/multiply member functions from chapter 2 on it
         a) make them modify the owned numeric type
         b) set them up so they can be chained together.
             i.e.
             DoubleType dt(3.5);
             dt.add(3.0).multiply(-2.5).divide(7.2); //an example of chaining
 
 4) write some add/subtract/divide/multiply member functions for each type that take your 3 UDTs
         for example, IntType::divide(const DoubleType& dt);
 
 5) print out the results with some creative couts 
    i.e.
         FloatType ft(0.1f);
         IntType it(3);
         std::cout << "adding 3 and subtracting 'it' from 'ft' results in the following value: " << *ft.add(2.f).subtract( it ).value << std::endl;  //note the dereference of the `value` member of `ft`
 
 6) Don't let your heap-allocated owned type leak!
 
 7) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

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

    FloatType() : heapFloat( new float ) {}
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

    DoubleType() : heapDub( new double ) {}
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

    IntType() : heapInt( new int ) {}
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
    *heapFloat += *operand.heapFloat;
    return *this;
}

FloatType& FloatType::add( const DoubleType& operand )
{
    *heapFloat += *operand.heapDub;
    return *this;
}

FloatType& FloatType::add( const IntType& operand )
{
    *heapFloat += *operand.heapInt;
    return *this;
}

FloatType& FloatType::subtract( float operand )
{
    *heapFloat -= operand;
    return *this;
}

FloatType& FloatType::subtract( const FloatType& operand )
{
    *heapFloat -= *operand.heapFloat;
    return *this;
}

FloatType& FloatType::subtract( const DoubleType& operand )
{
    *heapFloat -= *operand.heapDub;
    return *this;
}

FloatType& FloatType::subtract( const IntType& operand )
{
    *heapFloat -= *operand.heapInt;
    return *this;
}

FloatType& FloatType::multiply( float operand )
{
    *heapFloat *= operand;
    return *this;
}

FloatType& FloatType::multiply( const FloatType& operand )
{
    *heapFloat *= *operand.heapFloat;
    return *this;
}

FloatType& FloatType::multiply( const DoubleType& operand )
{
    *heapFloat *= *operand.heapDub;
    return *this;
}

FloatType& FloatType::multiply( const IntType& operand )
{
    *heapFloat *= *operand.heapInt;
    return *this;
}

FloatType& FloatType::divide( float operand )
{
    *heapFloat /= operand;
    return *this;
}

FloatType& FloatType::divide( const FloatType& operand )
{
    *heapFloat /= *operand.heapFloat;
    return *this;
}

FloatType& FloatType::divide( const DoubleType& operand )
{
    *heapFloat /= *operand.heapDub;
    return *this;
}

FloatType& FloatType::divide( const IntType& operand )
{
    *heapFloat /= *operand.heapInt;
    return *this;
}

// double member functions
DoubleType& DoubleType::add( double operand )
{
    *heapDub += operand;
    return *this;
}

DoubleType& DoubleType::add( const FloatType& operand )
{
    *heapDub += *operand.heapFloat;
    return *this;
}

DoubleType& DoubleType::add( const DoubleType& operand )
{
    *heapDub += *operand.heapDub;
    return *this;
}

DoubleType& DoubleType::add( const IntType& operand )
{
    *heapDub += *operand.heapInt;
    return *this;
}

DoubleType& DoubleType::subtract( double operand )
{
    *heapDub -= operand;
    return *this;
}

DoubleType& DoubleType::subtract( const FloatType& operand )
{
    *heapDub -= *operand.heapFloat;
    return *this;
}

DoubleType& DoubleType::subtract( const DoubleType& operand )
{
    *heapDub -= *operand.heapDub;
    return *this;
}

DoubleType& DoubleType::subtract( const IntType& operand )
{
    *heapDub -= *operand.heapInt;
    return *this;
}

DoubleType& DoubleType::multiply( double operand )
{
    *heapDub *= operand;
    return *this;
}

DoubleType& DoubleType::multiply( const FloatType& operand )
{
    *heapDub *= *operand.heapFloat;
    return *this;
}

DoubleType& DoubleType::multiply( const DoubleType& operand )
{
    *heapDub *= *operand.heapDub;
    return *this;
}

DoubleType& DoubleType::multiply( const IntType& operand )
{
    *heapDub *= *operand.heapInt;
    return *this;
}

DoubleType& DoubleType::divide( double operand )
{
    *heapDub /= operand;
    return *this;
}

DoubleType& DoubleType::divide( const FloatType& operand )
{
    *heapDub /= *operand.heapFloat;
    return *this;
}

DoubleType& DoubleType::divide( const DoubleType& operand )
{
    *heapDub /= *operand.heapDub;
    return *this;
}

DoubleType& DoubleType::divide( const IntType& operand )
{
    *heapDub /= *operand.heapInt;
    return *this;
}

// int member functions
IntType& IntType::add( int operand )
{
    *heapInt += operand;
    return *this;
}

IntType& IntType::add( const FloatType& operand )
{
    *heapInt += *operand.heapFloat;
    return *this;
}

IntType& IntType::add( const DoubleType& operand )
{
    *heapInt += *operand.heapDub;
    return *this;
}

IntType& IntType::add( const IntType& operand )
{
    *heapInt += *operand.heapInt;
    return *this;
}

IntType& IntType::subtract( int operand )
{
    *heapInt -= operand;
    return *this;
}

IntType& IntType::subtract( const FloatType& operand )
{
    *heapInt -= *operand.heapFloat;
    return *this;
}

IntType& IntType::subtract( const DoubleType& operand )
{
    *heapInt -= *operand.heapDub;
    return *this;
}

IntType& IntType::subtract( const IntType& operand )
{
    *heapInt -= *operand.heapInt;
    return *this;
}

IntType& IntType::multiply( int operand )
{
    *heapInt *= operand;
    return *this;
}

IntType& IntType::multiply( const FloatType& operand )
{
    *heapInt *= *operand.heapFloat;
    return *this;
}

IntType& IntType::multiply( const DoubleType& operand )
{
    *heapInt *= *operand.heapDub;
    return *this;
}

IntType& IntType::multiply( const IntType& operand )
{
    *heapInt *= *operand.heapInt;
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

#include <iostream>
IntType& IntType::divide( const FloatType& operand )
{
    if( *operand.heapFloat == 0.0f)
    {
        std::cout << "Can't divide by 0! Cancelling divide operation."  << std::endl;       
        return *this;
    }
    
    *heapInt /= *operand.heapFloat;
    return *this;
}

#include <iostream>
IntType& IntType::divide( const DoubleType& operand )
{
    if( *operand.heapDub == 0.0 )
    {
        std::cout << "Can't divide by 0! Cancelling divide operation."  << std::endl;       
        return *this;
    }
    
    *heapInt /= *operand.heapDub;
    return *this;
}

#include <iostream>
IntType& IntType::divide( const IntType& operand )
{
    if( *operand.heapInt == 0 )
    {
        std::cout << "Can't divide by 0! Cancelling divide operation."  << std::endl;       
        return *this;
    }
    
    *heapInt /= *operand.heapInt;
    return *this;
}

#include <iostream>
int main()
{
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    std::cout << "The result of ft^4 divided by it is: " << *ft.multiply( ft ).multiply( ft ).divide( it ).heapFloat << std::endl;
    std::cout << "The result of dt times 3 plus it is : " << *dt.multiply( 3 ).add( it ).heapDub << std::endl;
    std::cout << "The result of it divided by 3.14 multiplied by dt minus ft is: " << *it.divide( pi ).multiply( dt ).subtract( ft ).heapInt << std::endl;
    /*
    std::cout << "ft x it  =  " << *it.multiply( ft ).heapInt << std::endl;
    std::cout << "(it + dt + ft) x 24 = " << *it.add( dt ).add( ft ).multiply( 24 ).heapInt << std::endl;
    */


    std::cout << "good to go!" << std::endl;
}
