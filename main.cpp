
#include <iostream>
/*
Project 4: Part 5 / 9
 video: Chapter 5 Part 2
 Operator Overloading.

Do not delete your previous main. 

 Create a branch named Part5

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) replace the add/subtract/multiply/etc functions with overloaded math operators 
        e.g. add() would become operator+=() because it modifies the internal heap-allocated object.
 
 2) Your overloaded operators should only take primitives, passed by value.
 
 3) don't delete your conversion functions.
         if you removed them in Chapter 4 Part 7, put them back in.
         uncomment them if you commented them in Chapter 4 Part 7
 
 4) your main() function should be the same as Chapter 4 Part 7.  
     
 5) if your Chapter4 Part7 task didn't use any [+ - * or /], 
         add some in and fix the build errors that might result via the techniques you have learned in the previous weeks (hint: casting)
         i.e.
 */
#if false
namespace Example
{
    int main()
    {
        FloatType floatNum(4.3f);
        IntType intNum(2);
        IntType intNum2(6);

        /* 
        if you previously had a line like this demonstrating chaining:
            
            intNum.add(3).add(4.5f).divide(floatNum); 

        it should become:
        */
        intNum += 3;
        intNum += 4.5f;
        intNum /= floatNum;
        std::cout << "intNum: " << intNum << std::endl;
        
        return 0;
    }
}
#endif
 /*
 6) compile/link/run to make sure you don't have any errors
 
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

        /*
        FloatType& add( int operand );
        FloatType& subtract( int operand );
        FloatType& multiply( int operand );  
        FloatType& divide( int operand );
        */

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

        /*
        DoubleType& add( int operand );
        DoubleType& subtract( int operand );
        DoubleType& multiply( int operand );  
        DoubleType& divide( int operand );
        */
    
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
            *heapInt /= y;
            return *this;
        }

        /*
        IntType& add( int operand );
        IntType& subtract( int operand );
        IntType& multiply( int operand );  
        IntType& divide( int operand );
        */

        IntType& pow( const FloatType& operand );
        IntType& pow( const DoubleType& operand );
        IntType& pow( const IntType& operand );
        IntType& pow( int operand );
    
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

/*
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
*/

int main()
{
    
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    float x = 3.1f;


    std::cout << ft << " + " << x << std::endl;
    ft+=x;
    std::cout << ft << std::endl;

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

    std::cout << "Pow functions test: " << std::endl;
    std::cout << powFloat << " ^ " << a << " = " <<  powFloat.pow(a) << std::endl;
    std::cout << powDub << " ^ " << b << " = " << powDub.pow(b) << std::endl;
    std::cout << powInt << " ^ "<< c << " = " << powInt.pow(c) << std::endl;
    
    std::cout << std::endl;
    std::cout << "Resetting UDT's for Test 2..." << std::endl;
    powFloat.pow(1/a);
    powDub.pow(1/b);
    powInt/=16; // changed value reset from divide function to operator
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
