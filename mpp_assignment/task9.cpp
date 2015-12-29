//
//  task9.cpp
//  mpp_assignment
//
//  Created by Игорь Бисарнов on 10.10.15.
//  Copyright (c) 2015 Игорь Бисарнов. All rights reserved.
//

#include <stdio.h>
#include <iostream>

template < typename T > //generic form
T less (T v1, T v2) {
    return v1 < v2 ? v1 : v2;
}

template <> //explicit specialization
const char* less(const char* v1, const char* v2) {
    return strcmp(v1, v2) < 0 ? v2 : v1;
}

template <typename T> //partial specialization
T less(T* v1, T* v2) {
    return *v1 < *v2 ? *v1: *v2;
}

int main(int argc, const char* argv[]) {
    int x = 25;
    int* pX = &x;
    int y = 30;
    int* pY = &y;
    
    std::cout << less(pY, pX) << std::endl; //partial
    std::cout << less(10,2) << std::endl; //generic
    std::cout << less(2.8, 2.9) << std::endl; //generic
    std::cout << less("qwe", "asd123") << std::endl; //explicit
    
    return 0;
}