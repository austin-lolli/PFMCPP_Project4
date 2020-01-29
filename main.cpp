/*
 Project 4 - Part 1 / 9
 video: Chapter 2 Part 7
 Returning Values tasks 

 Create a branch named Part1
 
 1) write 3 UDTs named FloatType, DoubleType, IntType.
 
 2) give each UDT the following member functions:
        add( lhs, rhs );
        subtract( lhs, rhs );
        multiply( lhs, rhs );
        divide( lhs, rhs );
 
 3) make them return the correct primitive type. e.g. if you're implementing the FloatType::add function, your implementation would start like this:
        float FloatType::add( float lhs, float rhs )
 
 4) declare a few instances of each class in main() and call the member functions with the appropriate arguments.
        FloatType ft;
        auto result = ft.add(3.2f, 23.f );
 
 5) print out those results using std::cout:
        std::cout "result of ft.add(): " << result << std::endl;
 
 6) After you finish defining each type/function, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */

// float UDT 
struct FloatType
{
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

int IntType::divide( int lhs, int rhs )
{
    if( rhs == 0 )
    {
        return 0;
    }
    else
    {
    return lhs / rhs;
    }
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
