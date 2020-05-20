
/*
Project 4: Part 7 / 9
Video: Chapter 5 Part 4

Create a branch named Part7

Do not delete your previous main. you will be adding to it.

Templates and Containers

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 

#1) if you're not using std::unique_ptr to own your heap-allocated type as a member variable, 
    replace your manual memory management techniques with a private std::unique_ptr member variable.

#2) replace your Heap-Allocated Numeric Type-owning class with a templated class called Numeric.
        replace all of your previous instances of your separate classes with this templated class.

#3) add a 'using <some name> = <your class template parameter>;' 
        treat this type declaration via 'using' as a static member variable
        use this Type alias as the argument everywhere you previously used the template argument.
        this will make it very easy to change the type if needed.
            i.e. if you have 'std::unique_ptr<Numeric> value;' before
                you'd replace Numeric in that variable declaration with '<some name>'
        
#4) you'll need to pair it with decltype() to help the compiler figure out the type of the object 
    your class owns when you make your lambda and free function that takes your unique_ptr.  
    i.e. like this for determining the template parameter of the unique_ptr function argument to your class's apply() function
        std::unique_ptr< decltype( <instance of class> )::<some name> >
    
#5) template your free function for the apply() that takes a function pointer so it can be used with your Wrapper class's apply() function

#6) add an explicit template specialization for 'double' of your wrapper class
        this template specialization will have one apply() function instead of 2. 

#7) this apply() function will be templated, and expect a Callable object, not std::function<>. 
        the function should allow for chaining.  
        the callable object should return void, like the function pointer-based apply() function in the primary class template

#8) instantiate your explicit template specialization

#9) call the apply function twice, once with a lambda and once with the free function
        the free function is templated, so you might need to call it including the template arguments.
        
#10) in addition to using the lambda argument to modify the owned object:  (your previous task's lambdas did this same thing) 
        make the lambda use your explicit template instance (maybe via a std::cout), 

#11) now that your class is templated, you'll need to adjust your logic in your division function to handle if your input is a zero or not, based on your templated type.  
        - look up how to use std::is_same<>::value on cppreference to determine the type of your template parameter.
        
        - look up how to use std::numeric_limits<>::epsilon() to determine if you're dividing by a floating point 0
        
        - read about Knuth's algorithm here: https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/

        - in plain-english, you'll need to implement logic like this:
        if your template type is an int
                if your parameter's type is also an int
                        if your parameter is 0
                                don't do the division
                else if it's less than epsilon
                        dont do the divison
        else if it's less than epsilon
                warn about doing the division

        - to make these checks work during compilation, your if() statements will need to be 'constexpr':  if constexpr (expression)

compile/link/run to make sure you don't have any errors

If you need to view an example, see: https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part7Example.cpp
*/

#include <iostream>
#include <cmath>
#include <functional>
#include <memory>

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

    Numeric& operator+=( const Type y )
    {
        *heapNumber += y;
        return *this;
    }

    Numeric& operator-=( const Type y )
    {
        *heapNumber -= y;
        return *this;
    }

    Numeric& operator*=( const Type y )
    {
        *heapNumber *= y;
        return *this;
    }
  
    Numeric& operator/=( const Type y )
    {
        if constexpr ( std::is_same<Type, int>::value )
        {
            // self note: int is not the same as const int and your comparison must reflect that!
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
            
        *heapNumber /= y;
        return *this;
    }


    Numeric& pow( const Numeric& operand )
    {
        return powInternal( operand );
    }

    Numeric& apply(std::function<Numeric&(std::unique_ptr<Type>&)> callable)
    {
        if(callable)
        {
            return callable(heapNumber); 
        }

        return *this;
    }

    Numeric& apply( void(*funcPtr)(std::unique_ptr<Type>&) )
    {
        if(funcPtr)
        {
            funcPtr(heapNumber); 
        }

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

template<>
struct Numeric<double>
{
    using Type = double;

    Numeric( Type n ) : heapNumber( new Type(n) ) {}
    Numeric() : Numeric(0) {}

    ~Numeric()
    {
        heapNumber = nullptr;
    }

    operator Type() const { return *heapNumber; }

    Numeric& operator+=( const Type y )
    {
        *heapNumber += y;
        return *this;
    }

    Numeric& operator-=( const Type y )
    {
        *heapNumber -= y;
        return *this;
    }

    Numeric& operator*=( const Type y )
    {
        *heapNumber *= y;
        return *this;
    }

    Numeric& operator/=( const Type y )
    {
        if( y == 0.0 ) 
        {
            std::cout << "Can't divide by 0! Cancelling operation." << std::endl;
            return *this;
        }

        *heapNumber /= y;
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
    std::cout << "Float Type x 3 using Function Pointer: " << ft.apply(triple) << "\n" << std::endl;   
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
    std::cout << "Int Type x 3 using Function Pointer: " << it.apply(triple) << "\n" << std::endl;

    std::cout << std::endl;
    std::cout << "Additional tests on divide by 0." << std::endl;

    ft/=0;
    std::cout << "ft: " << ft << std::endl;
    it/=0; 
    std::cout << "it: " << it << std::endl;

    std::cout << "good to go!" << std::endl;

    dt.pow(dt);

}
