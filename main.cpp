/*
Prject 4: Part 8 / 9
 video: Chapter 5 Part 6 Task 

Create a branch named Part8

 R-Values L-Values Move Semantics.

 This Task is going to demonstrate R-Values and writing Generic Code

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 
 
 Edit your Chapter 5 Part 4 Task and replace its instructions with these instructions
 
 Your job is to replace the owned type (the primitive specified by your template argument) from the 
     Templated Class you created in Ch5 p04 with a struct named Temporary that can behave ENTIRELY as a temporary object.
 
 That means you must use conversion functions to interact with what it owns.
 
 You need to figure out how to use conversion functions to be able to GET and SET the 'value' member variable.
    hint: conversion functions can return by value and also by ___...
  
 1) Here is a starting point for how to implement your Temporary struct.
 */
#include <iostream>
#include <cmath>
#include <functional>
#include <memory>
#include <typeinfo>

template<typename NumericType>
struct Temporary
{
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }
    /*
     revise these conversion functions to read/write to 'v' here
     hint: what qualifier do read-only functions usually have?
     */
     //dont need to dereference v becuase Numeric's conversion function already does this
    operator NumericType&() const { /* read-only function */ return v; }
    operator NumericType&() { /* read/write function */ return v; }
private:
    static int counter;
    NumericType v;
};

/*
 2) add the definition of Temporary::counter here, which is a static variable and must be defined outside of the class.
    Remember the rules about how to define a Template member variable/function outside of the class.
*/
template<typename NumericType>
int Temporary<NumericType>::counter { 0 };
/*
 3) You'll need to template your overloaded math operator functions in your Templated Class from Ch5 p04
    use static_cast to convert whatever type is passed in to your template's NumericType before performing the +=, -=, etc.  here's an example implementation:

namespace example
{
template<typename NumericType>
struct Numeric
{
    //snip
    template<typename OtherType>
    Numeric& operator-=(const OtherType& o) 
    { 
        *value -= static_cast<NumericType>(o); 
        return *this; 
    }
    //snip
};
}
 */
/*
 4) remove your specialized <double> template of your Numeric<T> class from the previous task (ch5 p04)
    replace the 2 apply() functions in your Numeric<T> with the single templated apply() function from the specialized <double> template.
 */

/*
 5) Template your pow() function the same way you templated the overloaded math operators
    Remove the call to powInternal() and just call std::pow() directly.
    you'll need to static_cast<> the pow() argument the same way you did in the overloaded math operators, when you pass it to std::pow()
 */
/*
 
 6) Finally, your conversion function in your templated class is going to be returning this Temporary, 
        so you should probably NOT return by copy if you want your templated class's owned object to be modified by any math operation.
    See the previous hint for implementing the conversion functions for the Temporary if you want to get the held value
*/


/*
 7)   replace main() with the main below

 If you did everything correctly, this is the output you should get:
 
I'm a Temporary<f> object, #0
I'm a Temporary<i> object, #0
I'm a Temporary<d> object, #0
f: -1.89
d: -3.024
i: -9
Point { x: -1.89, y: -9 }
d: 3.024
I'm a Temporary<d> object, #1
I'm a Temporary<d> object, #2
d: 1.49519e+08
Point { x: -2.82591e+08, y: -1.34567e+09 }
I'm a Temporary<f> object, #1
I'm a Temporary<i> object, #1
I'm a Temporary<i> object, #2
I'm a Temporary<i> object, #3
intNum: 5
I'm a Temporary<f> object, #2
f squared: 3.5721
I'm a Temporary<f> object, #3
f cubed: 45.5796
I'm a Temporary<d> object, #3
d squared: 2.2356e+16
I'm a Temporary<d> object, #4
d cubed: 1.11733e+49
I'm a Temporary<i> object, #4
i squared: 81
I'm a Temporary<i> object, #5
i cubed: 531441

Use a service like https://www.diffchecker.com/diff to compare your output. 


#include <iostream>
int main()
{
    Numeric<float> f(0.1f);
    Numeric<int> i(3);
    Numeric<double> d(4.2);
    
    f += 2.f;
    f -= i;
    f *= d;
    f /= 2.f;
    std::cout << "f: " << f << std::endl;
    
    d += 2.f;
    d -= i;
    d *= f;
    d /= 2.f;
    std::cout << "d: " << d << std::endl;
    
    i += 2.f; i -= f; i *= d; i /= 2.f;
    std::cout << "i: "<< i << std::endl;
    
    Point p(f, i);
    p.toString();
    
    d *= -1;
    std::cout << "d: " << d << std::endl;
    
    p.multiply(d.pow(f).pow(i));
    std::cout << "d: " << d << std::endl;
    
    p.toString();
    
    Numeric<float> floatNum(4.3f);
    Numeric<int> intNum(2);
    Numeric<int> intNum2(6);
    intNum = 2 + (intNum2 - 4) + static_cast<double>(floatNum) / 2.3;
    std::cout << "intNum: " << intNum << std::endl;
    
    {
        using Type = decltype(f)::Type;
        f.apply([&f](std::unique_ptr<Type>&value) -> decltype(f)&
                {
                    auto& v = *value;
                    v = v * v;
                    return f;
                });
        std::cout << "f squared: " << f << std::endl;
        
        f.apply( cube<Type> );
        std::cout << "f cubed: " << f << std::endl;
    }
    
    {
        using Type = decltype(d)::Type;
        d.apply([&d](std::unique_ptr<Type>&value) -> decltype(d)&
                {
                    auto& v = *value;
                    v = v * v;
                    return d;
                });
        std::cout << "d squared: " << d << std::endl;
        
        d.apply( cube<Type> );
        std::cout << "d cubed: " << d << std::endl;
    }
    
    {
        using Type = decltype(i)::Type;
        i.apply([&i](std::unique_ptr<Type>&value) -> decltype(i)&
                {
                    auto& v = *value;
                    v = v * v;
                    return i;
                });
        std::cout << "i squared: " << i << std::endl;
        
        i.apply( cube<Type> );
        std::cout << "i cubed: " << i << std::endl;
    }
}
*/

struct Point
{
    Point(float a, float b) : x(a), y(b) {}
    
    //constructor to take numeric types
    template<typename T>
    Point(T& a, T& b) : Point(static_cast<float>(a), static_cast<float>(b) ) { }

    template<typename T> 
    Point& multiply( T& m)
    {
        return multiply(static_cast<float>(m));
    }

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }

    void toString()
    {
        std::cout << "( " << x << ", " << y << " )" << std::endl;
    }

private:
    float x{0}, y{0};
};

//template class
template<typename T>
struct Numeric
{
    using Type = T;

    Numeric( Type n ) : heapNumber( new Type(n) ) {}
    Numeric() : Numeric(0) {}

    ~Numeric()
    {
        heapNumber = nullptr;
    }

    operator Type() const { return *heapNumber; }

    template<typename OtherType>
    Numeric& operator+=( const OtherType y )
    {
        *heapNumber += static_cast<Type>(y);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator-=( const OtherType y )
    {
        *heapNumber -= static_cast<Type>(y);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator*=( const OtherType y )
    {
        *heapNumber *= static_cast<Type>(y);
        return *this;
    }
  
    template<typename OtherType>
    Numeric& operator/=( const OtherType y )
    {
        if constexpr ( std::is_same<Type, int>::value )
        {
            if constexpr ( std::is_same<decltype(y), const int>::value )
            {
                if ( y == 0 ) 
                {
                    std::cout << "Can't divide by integer 0! Cancelling operation." << std::endl;
                    return *this; 
                }
            }
            else if ( y < std::numeric_limits<Type>::epsilon() )
            {
                std::cout << "Can't divide by non-int 0! Cancelling operation." << std::endl;
                return *this;
            }
                
        }
        else if ( y < std::numeric_limits<Type>::epsilon() )
        {
            std::cout << "Warning! Dividing by 0." << std::endl;
        }
            
        *heapNumber /= static_cast<Type>(y);
        return *this;
    }


    Numeric& pow( const Numeric& operand )
    {
        return powInternal( operand );
    }

    template<typename Callable>
    auto apply(Callable callable) ->  Numeric&
    {
        callable(heapNumber);
        return *this;
    }

private:
    std::unique_ptr<Type> heapNumber{ new Type() };
    Numeric& powInternal( Type x )
    {
        if( heapNumber != nullptr )
        {
            *heapNumber = static_cast<Type>( std::pow( *heapNumber, x ) );
        }
        return *this;
    }

};

// free functions to pass to apply
template<typename T>
void triple(std::unique_ptr<T> &heapNumber)
{
    *heapNumber *= 3;
}


int main()
{
    
    Numeric<float> ft( 5.5f );
    Numeric<double> dt( 11.1 );
    Numeric<int> it( 34 );
    Numeric<double> pi( 3.14 );

    Numeric<float> powFloat( 2.4f );
    Numeric<double> powDub( 12.25 );
    Numeric<int> powInt( 2 );
    float a = 2.5f;
    double b = 1.89;
    int c = 5;

    std::cout << "New tests added for Project 4 Part 5 (Operator Overloading):" << std::endl;
    std::cout << powFloat << " + " << b << " = " << (powFloat += static_cast<float>(b)) << std::endl;
    std::cout << powFloat << " * " << it << " = " << (powFloat *= static_cast<float>(it)) << std::endl;
    std::cout << dt << " * " << powDub << " = " << (dt *= static_cast<double>(powDub)) << std::endl;
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
    std::cout << powFloat << " ^ " << powInt << " = " <<  powFloat.pow(static_cast<float>(powInt)) << std::endl;
    std::cout << powDub << " ^ " << powFloat << " = " << powDub.pow(static_cast<double>(powFloat)) << std::endl;
    std::cout << powInt << " ^ "<< powFloat << " = " << powInt.pow(static_cast<int>(powFloat)) << std::endl;

    Numeric<float> xFloat( 1.3f );
    Numeric<float> yFloat( 2.9f );
    Numeric<double> xDouble( 3.33 );
    Numeric<double> yDouble( 1.75 );
    Numeric<int> xInt( 4 );
    Numeric<int> yInt( -2 );

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

    std::cout << std::endl;
    std::cout << std::endl;

    using FloatType = decltype(ft);
    using DoubleType = decltype(dt);
    using IntType = decltype(it);
    std::cout << "Float Type Initial Valule: " << ft << std::endl;

    ft.apply( [&ft](std::unique_ptr<FloatType::Type>& heapFloat) -> FloatType&
    {
        *heapFloat += 2.f;
        return ft;
    });

    std::cout << "Float Type + 2 using Lambda: " << ft << std::endl;
    std::cout << "Float Type x 3 using Function Pointer: " << ft.apply(triple<float>) << "\n" << std::endl;   
    std::cout << "Double Type Initial Valule: " << dt << std::endl;

    dt.apply( [&dt](std::unique_ptr<DoubleType::Type>& heapDub) -> DoubleType&
    {
        *heapDub += 2.0;
        return dt;
    });

    std::cout << "Double Type + 2 using Lambda: " << dt << std::endl;
    std::cout << "Double Type x 3 using Function Pointer: " << dt.apply(triple<double>) << "\n" << std::endl;
    std::cout << "Int Type Initial Valule: " << it << std::endl;

    it.apply( [&it](std::unique_ptr<IntType::Type>& heapInt) -> IntType&
    {
        *heapInt += 2;
        return it;
    });

    std::cout << "Int Type + 2 using Lambda: " << it << std::endl;
    std::cout << "Int Type x 3 using Function Pointer: " << it.apply(triple<int>) << "\n" << std::endl;

    std::cout << std::endl;
    std::cout << "Additional tests on divide by 0." << std::endl;

    ft/=0;
    std::cout << "ft: " << ft << std::endl;
    it/=0; 
    std::cout << "it: " << it << std::endl;

    std::cout << "good to go!" << std::endl;

    dt.pow(dt);

}
