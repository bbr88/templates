//
//  task7.cpp
//  mpp_assignment
//
//  Created by Игорь Бисарнов on 10.10.15.
//  Copyright (c) 2015 Игорь Бисарнов. All rights reserved.
//

#include <stdio.h>
#include <iostream>

template < unsigned N >
unsigned long long fibonacci( void ) {
    return fibonacci<N-1>() + fibonacci<N-2>();
}

template <> //explicit specialization for '1'
unsigned long long fibonacci<1> ( void ) {
    return 1;
}

template <> //explicit specialization for '2'
unsigned long long fibonacci<2> ( void ) {
    return 1;
}

template <> //explicit specialization for '0'
unsigned long long fibonacci<0> ( void ) {
    return 0;
}

template <typename N>
class Fibonnaci {

public:
    N fib (N value) {
        if (value >= 0) {
            switch (value) {
                case 0:
                    return 0;
                    break;
                case 1:
                    return 1;
                    break;
                case 2:
                    return 1;
                    break;
                default:
                    return fib(value -1) + fib(value -2);
                    break;
            }
        } else {
            throw std::runtime_error("Value should be more or equal to 0.");
        }
    }
};

int main(int argc, const char * argv[]) {
    // explicit
    std::cout << fibonacci<0>() << std::endl;
    std::cout << fibonacci<1>() << std::endl;
    std::cout << fibonacci<2>() << std::endl;
    
    //implicit
    std::cout << fibonacci<10>() << std::endl;
    std::cout << fibonacci<40>() << " O_O" << std::endl;
    
    //class
    Fibonnaci<long> fibonacci;
    std::cout << fibonacci.fib(1) << std::endl;
    std::cout << fibonacci.fib(10) << std::endl;
    return 0;
}
