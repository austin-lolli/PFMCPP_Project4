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

    float add( float lhs, float rhs );
    float subtract( float lhs, float rhs );
    float multiply( float lhs, float rhs );
    float divide( float lhs, float rhs );
};

// float member functions 
float FloatType::add( float lhs, float rhs )
{
    return lhs + rhs;
}

float FloatType::subtract( float lhs, float rhs )
{
    return lhs - rhs;
}

float FloatType::multiply( float lhs, float rhs )
{
    return lhs * rhs; 
}

float FloatType::divide( float lhs, float rhs )
{
    return lhs / rhs;
}

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
    
    double add( double lhs, double rhs );
    double subtract( double lhs, double rhs );
    double multiply( double lhs, double rhs );
    double divide( double lhs, double rhs );
};

// double member functions
double DoubleType::add( double lhs, double rhs )
{
    return lhs + rhs;
}

double DoubleType::subtract( double lhs, double rhs )
{
    return lhs - rhs;
}

double DoubleType::multiply( double lhs, double rhs )
{
    return lhs * rhs; 
}

double DoubleType::divide( double lhs, double rhs )
{
    return lhs / rhs;
}

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

    int add( int lhs, int rhs );
    int subtract( int lhs, int rhs );
    int multiply( int lhs, int rhs );
    int divide( int lhs, int rhs );
};

// int member functions
int IntType::add( int lhs, int rhs )
{
    return lhs + rhs;
}

int IntType::subtract( int lhs, int rhs )
{
    return lhs - rhs;
}

int IntType::multiply( int lhs, int rhs )
{
    return lhs * rhs; 
}

#include <iostream>
int IntType::divide( int lhs, int rhs )
{
    if( rhs == 0 )
    {
        std::cout << "Can't divide by 0! "  << std::endl;       
        return 0;
    }
    
    return lhs / rhs;
}

#include <iostream>
int main()
{
    FloatType ft;
    auto resultA = ft.add( 21.4f, 7.1f );
    std::cout << "result of ft.add(): " << resultA << std::endl;
    resultA = ft.subtract( 21.4f, 7.1f );
    std::cout << "result of ft.subtract(): " << resultA << std::endl;
    resultA = ft.multiply( 21.4f, 7.1f );
    std::cout << "result of ft.multiply(): " << resultA << std::endl;
    resultA = ft.divide( 21.4f, 7.1f );
    std::cout << "result of ft.divide(): " << resultA << std::endl;

    DoubleType dt;
    auto resultB = dt.add( 7.343, 3.278 );
    std::cout << "result of dt.add(): " << resultB << std::endl;
    resultB = dt.subtract( 7.343, 3.278 );
    std::cout << "result of dt.subtract(): " << resultB << std::endl;
    resultB = dt.multiply( 7.343, 3.278 );
    std::cout << "result of dt.multiply(): " << resultB << std::endl;
    resultB = dt.divide( 7.343, 3.278 );
    std::cout << "result of dt.divide(): " << resultB << std::endl;

    IntType it;
    auto resultC = it.add( 50, 25 );
    std::cout << "result of it.add(): " << resultC << std::endl;
    resultC = it.subtract( 50, 25 );
    std::cout << "result of it.subtract(): " << resultC << std::endl;
    resultC = it.multiply( 50, 25 );
    std::cout << "result of it.multiply(): " << resultC << std::endl;
    resultC = it.divide( 50, 25 );
    std::cout << "result of it.divide(): " << resultC << std::endl;

    it.divide(1, 0);

    std::cout << "good to go!" << std::endl;
}
