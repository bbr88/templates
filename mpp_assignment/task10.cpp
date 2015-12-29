//
//  task10.cpp
//  mpp_assignment
//
//  Created by Игорь Бисарнов on 10.10.15.
//  Copyright (c) 2015 Игорь Бисарнов. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cassert>

template < int leftBorder, int rightBorder >
class Range {

private:
    //data
    int value;
    Range() {};
    
public:
    //constructors
    Range ( int range ) { //ctor
        assert( leftBorder < rightBorder && range >= leftBorder && range <= rightBorder ); //validate arguments
        value = range;
    }
    
    Range ( Range &range ) { //copy ctor
        value = range.value;
    }
    
    //operators
    // =
    Range &operator=( Range &range ) { //range = range1;
        value = range.value;
        return *this; //get the value and return it
    }
    // =
    Range &operator=( int v ) { //range = 1;
        assert( v >= leftBorder && v <= rightBorder ); //validate argument 'v'
        value = v;
        return *this;
    }
    // +
    Range &operator+ ( Range &range ) {
        assert( value + range.value >= leftBorder && value + range.value <= rightBorder );
        return Range(value + range.value);
    }
    
    // ++prefix
    Range &operator++ ( int ) {
        assert( ++value <= rightBorder) ;
        return *this;
    }
    // postfix++
    Range &operator++ ( void ) {
        assert( value + 1 <= rightBorder );
        Range *tempRange = this;
        ++(tempRange->value);
        return *tempRange;
    }
    // postfix--
    Range &operator-- ( void ) {
        assert( --value >= leftBorder );
        return *this;
    }
    // --prefix
    Range &operator-- ( int ) {
        assert( --value >= leftBorder );
        return *this;
    }
    
    //user defined conversion
    operator int() {
        return value;
    }
    operator long() {
        return static_cast<long>(value);
    }
    
    //-> for pointers, dot for objects
    // p->m == (*p).m
    // type casts... this is 'user defined conversion'

};

int main(int argc, const char* argv[]) {
    Range<-1, 30> range(28); //init
    Range<5, 20> range1(15); //init
    
    std::cout << (long)range << std::endl; //user defined conversion
    range = 14; // Range &operator=(int v)
    std::cout << (int)range << std::endl;
    
    range = range1; // it shouldn't work, since range and range1 are different types.
                    // But couse of operation Range &operator=(int v) and user defined conversion int()
                    // it works properly:
                    // range1 casts to int, so we have this expression range = 15;
    
    std::cout << (int)range << std::endl;
    
    //inc, dec
    int i = range;
    int j = ++range;
    int k = range++; //it doesn't work properly:(
    int m = --range;

    std::cout << "i = " << i << std::endl
              << "j = " << j << std::endl
              << "k = " << k << " :/" << std::endl
              << "m = " << m << std::endl;
    
    // +
    std::cout << "range = " << (int)range << "; range+1 = " << (int)range + 1 << std::endl;
    
    //copy
    Range<5, 20> copyRange(10);
    copyRange = range1;
    std::cout << "copy range = " << int(copyRange) << std::endl;
    
    return 0;
}