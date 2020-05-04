/*
Project 4 - Part 6 / 9
Video: Chapter 5 Part 3
 
Create a branch named Part6
 
 Lambdas
 
    Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add two member functions named "apply()" to each of your Heap-Allocated Numeric Type wrappers.
         both apply() functions should work with chaining
 
 2) One of the apply() functions should takes a std::function<> object as the function argument.
    the std::function<> object should return *this;
 
 3) the other apply() function should take a function pointer. 
    the function pointer should return void.
 
 4) Make both of the member functions's Callable Function Parameter use your owned object as it's single parameter.
         e.g. if you manage your owned object via std::unique_ptr<T>, you'd use this for your std::function argument:
             std::function< OwnedT&(std::unique_ptr<T>&)>
             
         if you managed your owned object via a raw pointer, you'd use this for your std::function argument:
             std::function<OwnedT&(T&)>    
 
 5) call that Callable Function Parameter in the apply() member function.
         be sure to practice safe std::function usage (make sure it's not a nullptr function being called)
 
 6) Using one instance of each of your Heap-Allocated Numeric Type wrappers: Call your apply() member function twice in main()
         a) once with a lambda as the argument
         b) once with a free function as the argument.
         c) there will be a total of 6 calls to apply() in main(), 2x per HeapType, IntType, DoubleType instance.
         If this confuses you, rewatch the video where I pass a free function in to a function that wants a function pointer
 
 8) Make your lambda & free function update the value of your held object
 
 9) use std::cout statements to print out the results of calling apply()
 
build/run to make sure you don't have any errors

Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 
 If you need to see an example, look at https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part6Example.cpp
 */






#include <cmath>
#include <functional>

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
        FloatType() : FloatType(0) {}

        ~FloatType()
        {
            delete heapFloat;
            heapFloat = nullptr;
        }

        operator float() const { return *heapFloat; }

        FloatType& operator+=( const float y )
        {
            *heapFloat += y;
            return *this;
        }

        FloatType& operator-=( const float y )
        {
            *heapFloat -= y;
            return *this;
        }

        FloatType& operator*=( const float y )
        {
            *heapFloat *= y;
            return *this;
        }

        FloatType& operator/=( const float y )
        {
            *heapFloat /= y;
            return *this;
        }

        FloatType& pow( const FloatType& operand );
        FloatType& pow( const DoubleType& operand );
        FloatType& pow( const IntType& operand );
        FloatType& pow( float operand );

        FloatType& apply(std::function<FloatType&()>){ return *this; }
        void apply( void(*funcPtr)()){}

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

        DoubleType& operator+=( const double y )
        {
            *heapDub += y;
            return *this;
        }

        DoubleType& operator-=( const double y )
        {
            *heapDub -= y;
            return *this;
        }

        DoubleType& operator*=( const double y )
        {
            *heapDub *= y;
            return *this;
        }

        DoubleType& operator/=( const double y )
        {
            *heapDub /= y;
            return *this;
        }
    
        DoubleType& pow( const FloatType& operand );
        DoubleType& pow( const DoubleType& operand );
        DoubleType& pow( const IntType& operand );
        DoubleType& pow( double operand );
    
        DoubleType& apply(std::function<DoubleType&()>){ return *this; }
        void apply( void(*funcPtr)()){}

    private:
        double* heapDub = nullptr;
        DoubleType& powInternal( double x );

};

// int UDT
#include <iostream>
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

        IntType& operator+=( const int y )
        {
            *heapInt += y;
            return *this;
        }

        IntType& operator-=( const int y )
        {
            *heapInt -= y;
            return *this;
        }

        IntType& operator*=( const int y )
        {
            *heapInt *= y;
            return *this;
        }

        IntType& operator/=( const int y )
        {
            if( y == 0 )
            {
                std::cout << "Can't divide by 0! Cancelling divide operation."  << std::endl;       
                return *this;
            }
    
            *heapInt /= y;
            return *this;
        }

        IntType& pow( const FloatType& operand );
        IntType& pow( const DoubleType& operand );
        IntType& pow( const IntType& operand );
        IntType& pow( int operand );

        IntType& apply(std::function<IntType&()>){ return *this; }
        void apply( void(*funcPtr)()){}

    
    private:
        int* heapInt = nullptr;
        IntType& powInternal( int x );
};

//float type operators


//point constructor implementations
Point::Point(FloatType& a, FloatType& b) : Point(static_cast<float>(a), static_cast<float>(b) ) { } 

Point::Point(DoubleType& a, DoubleType& b) : Point ( static_cast<float>(a), static_cast<float>(b) ) { }


Point::Point(IntType& a, IntType& b) : Point ( static_cast<float>(a), static_cast<float>(b) ) { }

//point multiply UDT implementations
Point& Point::multiply( FloatType& m )
{
    return multiply(static_cast<float>(m));
}

Point& Point::multiply( DoubleType& m )
{
    return multiply(static_cast<float>(m));
}

Point& Point::multiply( IntType& m )
{
    return multiply(static_cast<float>(m));
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


int main()
{
    
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

/*
    std::cout << "The result of FloatType^4 divided by IntType is: " << ft.multiply( ft ).multiply( ft ).divide( it ) << std::endl;
    std::cout << "The result of DoubleType times 3 plus IntType is : " << dt.multiply( 3 ).add( it ) << std::endl;
    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << it.divide( static_cast<int>(pi) ).multiply( static_cast<int>(dt) ).subtract( static_cast<int>(ft) ) << std::endl;
    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
    std::cout << it.multiply(it).divide(0).divide(0.0f).divide(0.0)<<std::endl;
    
    std::cout << "FloatType x IntType  =  " << it.multiply( static_cast<int>(ft) ) << std::endl;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << it.add( static_cast<int>(dt) ).add( static_cast<int>(ft) ).multiply( 24 ) << std::endl;
    
    std::cout << std::endl;
    std::cout << std::endl;
    */

    FloatType powFloat( 2.4f );
    DoubleType powDub( 12.25 );
    IntType powInt( 2 );
    float a = 2.5f;
    double b = 1.89;
    int c = 5;

    std::cout << "New tests added for Project 4 Part 5 (Operator Overloading):" << std::endl;
    std::cout << powFloat << " + " << b << " = " << (powFloat += static_cast<float>(b)) << std::endl;
    std::cout << powFloat << " * " << it << " = " << (powFloat *= static_cast<float>(it)) << std::endl;
    std::cout << dt << " * " << powDub << " = " << (dt *= powDub) << std::endl;
    std::cout << dt << " / " << powFloat << " = " << (dt /= static_cast<double>(powFloat)) << std::endl;
    std::cout << powInt << " - " << ft << " = " << (powInt -= static_cast<int>(ft)) << std::endl;
    std::cout << powDub << " * " << c << " = " << (powDub *= static_cast<double>(c)) << std::endl;

    std::cout << std::endl;

    std::cout << "Pow functions test: " << std::endl;
    std::cout << powFloat << " ^ " << a << " = " <<  powFloat.pow(a) << std::endl;
    std::cout << powDub << " ^ " << b << " = " << powDub.pow(b) << std::endl;
    std::cout << powInt << " ^ "<< c << " = " << powInt.pow(c) << std::endl;
    
    std::cout << std::endl;
    std::cout << "Resetting UDT's for Test 2..." << std::endl;
    powFloat.pow(1.f / a);
    powDub.pow(1.0 / b);
    powInt /= 16; // changed value reset from divide function to operator
    std::cout << std::endl;
    
    std::cout << "Test 2, one UDT ^ another UDT: " << std::endl;
    std::cout << powFloat << " ^ " << powInt << " = " <<  powFloat.pow(powInt) << std::endl;
    std::cout << powDub << " ^ " << powFloat << " = " << powDub.pow(powFloat) << std::endl;
    std::cout << powInt << " ^ "<< powFloat << " = " << powInt.pow(powFloat) << std::endl;

    FloatType xFloat( 1.3f );
    FloatType yFloat( 2.9f );
    DoubleType xDouble( 3.33 );
    DoubleType yDouble( 1.75 );
    IntType xInt( 4 );
    IntType yInt( -2 );

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
