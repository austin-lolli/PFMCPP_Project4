/*
Project 4: Part 4 / 9
 Chapter 4 Part 7
 Function/Constructor Overloading

 Create a branch named Part4
 
 Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add pow() functions, and a powInternal() function to each of your UDTs
     a) your pow() functions should call powInternal()
     b) add a pow() whose argument type is the primitive your UDT owns.  the argument should be passed by copy.
     c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
         the argument should be passed as const ref
         i.e. if you had UDTs named IntType, FloatType, DoubleType
             in your IntType class, you'd have:
                 pow(const IntType&),
                 pow(const FloatType&),
                 pow(const DoubleType&),
                 and pow(int)
     d) be sure to remember the rules about what member functions can be called on const objects.
             (const objects can only call their const member functions)
 
 2) your powInternal() function should do something like this in its body:    *val = std::pow( *val, arg );
         where 'arg' is the passed-in type, converted to whatever type your object is holding.
             if your UDT owns an int, then arg would be an int.
             if your UDT owns a float, then arg would be a float.
         std::pow's documentation is found here: https://en.cppreference.com/w/cpp/numeric/math/pow so be sure to include
             the proper header file listed there.
 
 3) modify the Point class below to have Constructors that accept your UDTs.
     a) make the Constructor's UDT arguments initialize the Point class's two member variables.
     b) overload the multiply() function so it can accept each of your UDTs.  I've added an implementation you can mimick for this function.
     c) add a toString() function to the Point class that prints out the x and y members via std::cout.
 
 4) Add to main()
     a) use your new pow() function in main for all of your types and print out the results.
     b) use the Point class in main and multiply some Point instances with your UDTs
     c) use the Point::toString() function to print out the results.
 
 
 5) make sure it compiles without errors.
 
 You will need to use Forward Declaration and out-of-class definitions to complete this.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

#include <cmath>

struct FloatType;
struct IntType;
struct DoubleType;

struct Point
{
    Point(float a, float b) : x(a), y(b) {}
    Point(FloatType& a, FloatType& b);
    Point(DoubleType& a, DoubleType& b);
    Point(IntType& a, IntType& b);

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
    
    Point& multiply( FloatType& m );
    Point& multiply( DoubleType& m );
    Point& multiply( IntType& m );

    void toString();

private:
    float x{0}, y{0};
};


// float UDT 
struct FloatType
{
    public:
        FloatType( float f ) : heapFloat( new float(f) ) {}
        ~FloatType()
        {
            delete heapFloat;
            heapFloat = nullptr;
        }

        operator float() const { return *heapFloat; }
    
        FloatType& add( float operand );
        FloatType& subtract( float operand );
        FloatType& multiply( float operand );
        FloatType& divide( float operand );

        FloatType& pow( const FloatType& operand );
        FloatType& pow( const DoubleType& operand );
        FloatType& pow( const IntType& operand );
        FloatType& pow( float operand );

    private:
        float* heapFloat = nullptr; 
        FloatType& powInternal( float x );

};

// double UDT
struct DoubleType
{
    public:
        DoubleType( double d ) : heapDub( new double(d) ) {}
        ~DoubleType()
        {
            delete heapDub;
            heapDub = nullptr;
        }

        operator double() const { return *heapDub; }
    
        DoubleType& add( double operand );
        DoubleType& subtract( double operand );
        DoubleType& multiply( double operand );
        DoubleType& divide( double operand );

        DoubleType& pow( const FloatType& operand );
        DoubleType& pow( const DoubleType& operand );
        DoubleType& pow( const IntType& operand );
        DoubleType& pow( double operand );

    private:
        double* heapDub = nullptr;
        DoubleType& powInternal( double x );

};

// int UDT
struct IntType
{
    public:
        IntType( int i ) : heapInt( new int(i) ) {}
        ~IntType()
        {
            delete heapInt;
            heapInt = nullptr;
        }

        operator int() const { return *heapInt; }

        IntType& add( int operand );
        IntType& subtract( int operand );
        IntType& multiply( int operand );  
        IntType& divide( int operand );

        IntType& pow( const FloatType& operand );
        IntType& pow( const DoubleType& operand );
        IntType& pow( const IntType& operand );
        IntType& pow( int operand );
    
    private:
        int* heapInt = nullptr;
        IntType& powInternal( int x );
};

//point constructor implementations
Point::Point(FloatType& a, FloatType& b) 
{ 
    Point( a, b);
}

Point::Point(DoubleType& a, DoubleType& b) 
{ 
    Point ( static_cast<float>(a), static_cast<float>(b) );
}

Point::Point(IntType& a, IntType& b)
{ 
    Point ( static_cast<float>(a), static_cast<float>(b) );
}

//point multiply UDT implementations
Point& Point::multiply( FloatType& m )
{
    x *= m;
    y *= m;
    return *this;
}

Point& Point::multiply( DoubleType& m )
{
    x *= static_cast<float>(m);
    y *= static_cast<float>(m);
    return *this;
}

Point& Point::multiply( IntType& m )
{
    x *= static_cast<float>(m);
    y *= static_cast<float>(m);
    return *this;
}

// point to string
#include <iostream>
void Point::toString()
{
    std::cout << "( " << x << ", " << y << " )" << std::endl;
}

// pow implementations for FloatType
FloatType& FloatType::pow( const FloatType& operand )
{
    return powInternal( static_cast<float>(operand) );
}

FloatType& FloatType::pow( const DoubleType& operand )
{
    return powInternal( static_cast<float>(operand) );
}

FloatType& FloatType::pow( const IntType& operand )
{
    return powInternal( static_cast<float>(operand) );
}

FloatType& FloatType::pow( float operand )
{
    return powInternal(operand);
}

// pow implementations for DoubleType
DoubleType& DoubleType::pow( const FloatType& operand )
{
    return powInternal( static_cast<double>(operand) );
}

DoubleType& DoubleType::pow( const DoubleType& operand )
{
    return powInternal( static_cast<double>(operand) );
}

DoubleType& DoubleType::pow( const IntType& operand )
{
    return powInternal( static_cast<double>(operand) );
}

DoubleType& DoubleType::pow( double operand )
{
    return powInternal(operand);
}

// pow implementations for IntType
IntType& IntType::pow( const FloatType& operand )
{
    return powInternal( static_cast<int>(operand) );
}

IntType& IntType::pow( const DoubleType& operand )
{
    return powInternal( static_cast<int>(operand) );
}

IntType& IntType::pow( const IntType& operand )
{
    return powInternal( static_cast<int>(operand) );
}

IntType& IntType::pow( int operand )
{
    return powInternal(operand);
}


// powInternal implementations
FloatType& FloatType::powInternal( float x )
{
    if( heapFloat != nullptr )
    {
        *heapFloat = std::pow( *heapFloat, x );
    }
    return *this;
}

DoubleType& DoubleType::powInternal( double x )
{
    if( heapDub != nullptr )
    {
        *heapDub = std::pow( *heapDub, x );
    }
    return *this;
}

IntType& IntType::powInternal( int x )
{
    if( heapInt != nullptr )
    {
        //static cast because pow returns a float or double
        *heapInt = static_cast<int>( std::pow( *heapInt, x ) );
    }
    return *this;
}

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
    
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    std::cout << "The result of FloatType^4 divided by IntType is: " << ft.multiply( ft ).multiply( ft ).divide( it ) << std::endl;
    std::cout << "The result of DoubleType times 3 plus IntType is : " << dt.multiply( 3 ).add( it ) << std::endl;
    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << it.divide( static_cast<int>(pi) ).multiply( static_cast<int>(dt) ).subtract( static_cast<int>(ft) ) << std::endl;
    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
    std::cout << it.multiply(it).divide(0).divide(0.0f).divide(0.0)<<std::endl;
    
    std::cout << "FloatType x IntType  =  " << it.multiply( static_cast<int>(ft) ) << std::endl;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << it.add( static_cast<int>(dt) ).add( static_cast<int>(ft) ).multiply( 24 ) << std::endl;
    
    std::cout << std::endl;
    std::cout << std::endl;

    FloatType powFloat( 2.4f );
    DoubleType powDub( 12.25 );
    IntType powInt( 2 );
    float a = 2.5f;
    double b = 1.89;
    int c = 5;

    std::cout << "Pow functions test: " << std::endl;
    std::cout << powFloat << " ^ " << a << " = " <<  powFloat.pow(a) << std::endl;
    std::cout << powDub << " ^ " << b << " = " << powDub.pow(b) << std::endl;
    std::cout << powInt << " ^ "<< c << " = " << powInt.pow(c) << std::endl;
    
    std::cout << std::endl;
    std::cout << "Resetting UDT's for Test 2..." << std::endl;
    powFloat.pow(1/a);
    powDub.pow(1/b);
    powInt.divide(16);
    std::cout << std::endl;
    
    std::cout << "Test 2, one UDT ^ another UDT: " << std::endl;
    std::cout << powFloat << " ^ " << powInt << " = " <<  powFloat.pow(powInt) << std::endl;
    std::cout << powDub << " ^ " << powFloat << " = " << powDub.pow(powFloat) << std::endl;
    std::cout << powInt << " ^ "<< powDub << " = " << powInt.pow(powDub) << std::endl;   

    FloatType xFloat( 1.3f );
    FloatType yFloat( 2.9f );
    DoubleType xDouble( 3.33 );
    DoubleType yDouble( 1.75 );
    IntType xInt( 4 );
    IntType yInt( -2 );

    std::cout << std::endl;
    std::cout << std::endl;

    Point pFloat( xFloat, yFloat);
    Point pDouble( xDouble, yDouble);
    Point pInt( xInt, yInt);

    std::cout << "Initial Point Values: " << std::endl;
    std::cout << "pFloat: ";
    pFloat.toString();
    std::cout << "pDouble: ";
    pDouble.toString();
    std::cout << "pInt: ";
    pInt.toString();

    std::cout << std::endl;

    std::cout << "pFloat x 2.1f = ";
    pFloat.multiply(2.1f).toString();
    std::cout << "pDouble x -1.4f = ";
    pDouble.multiply(-1.4f).toString();
    std::cout << "pInt x .75f = ";
    pInt.multiply(.75f).toString();

    std::cout << "good to go!" << std::endl;
}
