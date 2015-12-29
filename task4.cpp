//
//  task4.cpp
//  mpp_assignment
//
//  Created by Игорь Бисарнов on 09.10.15.
//  Copyright (c) 2015 Игорь Бисарнов. All rights reserved.
//

#include <stdio.h>
#include <stdexcept>
#include <string>
#include <iostream>

template <typename T>
class MyArrayList {

private:
    //data
    const static int DEFAULT_CAPACITY = 10;
    T *mass;
    int size = 0;
    int capacity = 0;
    
    //methods
    void resize();
    //void resize(int newSize);
    bool checkSize() const;
    
public:
    //constructors
    MyArrayList() { //default ctor
        mass = new T[DEFAULT_CAPACITY];
        capacity = DEFAULT_CAPACITY;
    }
    MyArrayList(int capacity) { //with particular capacity
        if (capacity > 0) {
            this->capacity = capacity;
            mass = new T[this->capacity];
            
        } else {
            throw std::runtime_error("Capacity should be greater than 0.");
        }
    }
    
    //operations
    
    bool addElement(T const &element); //add an element to the end of the array
    bool addByIndex(int idx, T const &element); //add an element by the idx
    bool addAll(MyArrayList<T> &otherList); //add all the elements to the array
    
    bool isEmpty() {//check if the array is empty;
        return size == 0;
    }

    int getCapacity() { //returns current capacity of the array
        return capacity;
    }
    int getSize() { //returns current size of the array
        return size;
    }
    
    T get(int idx) { //get element by its idx
        if (idx >= 0 && idx <= this->size) {
            return this->mass[idx];
        } else {
            throw std::runtime_error("Index should be less or equal to array's size.");
        }
    }
    
    T remove(int idx) { //remove element by its idx
        if (idx >= 0 && idx <= size) {
            T result = mass[idx];
            mass[idx] = NULL; //remove element with i = idx
            size--; //decrement array's size
            for (int i = idx; i < size - idx; i++) {
                mass[i] = mass[i+1]; //move elements rightward
            }
            return result;
        } else {
            throw std::runtime_error("Wrong index.");
        }
        
    }
    
    T getLast() { //return the last element
        if (!isEmpty()) {
            return mass[size];
        } else {
            return NULL;
        }
    }
    
    T removeLast() { //remove the last element
        if (!isEmpty()) {
            T result = mass[size];
            mass[size--] = NULL;
            return result;
        } else {
            return NULL;
        }
    }
    
    void printIt() { //print all the elements
        if (!isEmpty()) {
            std::cout << "{ ";
            for (int i = 0; i < size; i++) {
                if (i == size - 1) {
                    std::cout << mass[i] << " }" << std::endl << std::endl;
                    return;
                }
                std::cout << mass[i] << ", ";
            }
        }
        return;
    }
    void clear() { //clear the array
        if (!isEmpty()) {
            mass = new T[DEFAULT_CAPACITY];
        }
    }
};


//implementation
template <typename T>
void MyArrayList<T>::resize () { //doubles array's size
    T *tempMass = new T[capacity]; //new temporary array
    for (int i = 0; i < capacity; i++) {
        tempMass[i] = mass[i];
    }
    //mass = nullptr;
    mass = new T[capacity * 2]; //declare mass with doubled capacity
    
    for (int i = 0; i < capacity; i++) { //fill the array with previous values
        mass[i] = tempMass[i];
    }
    capacity *= 2; //double the capacity
}

template <typename T>
bool MyArrayList<T>::checkSize () const{ //check if we can add another element into array
    if (size < capacity) {
        return true;
    }
    return false;
}

template <typename T>
bool MyArrayList<T>::addElement(T const &element) {
    if (checkSize()) { //check size, if its okay then insert new item
        mass[size++] = element;
        return true;
    } else { //double array's size
        this->resize();
        mass[size++] = element; //insert new item, increment the size
        return true;
    }
    return false;
}

template <typename T>
bool MyArrayList<T>::addByIndex (int idx, T const &element) {
    if (idx >= 0 && idx <= size) {
        mass[idx] = element; //replace element
        return true;
    } else {
        throw std::runtime_error("Wrong index."); //throw an exception if idx is not valid
    }
    return false;
}

template <typename T>
bool MyArrayList<T>::addAll(MyArrayList<T> &otherList) {
    if (!otherList.isEmpty()) { //if array is not empty
        while (this->capacity <= this->size + otherList.getSize()) { //check the size and resize it if nessasry
            resize();
        }
        for (int i = 0; i < otherList.getSize(); i++) { //add elements to the initial array
            this->mass[size++] = otherList.get(i);
        }
        return true;
    } else {
        throw std::runtime_error("The other array is empty.");
    }
    //return false;
};

int main(int argc, const char * argv[]) {
    //delcaration
    MyArrayList<int> myIntList = MyArrayList<int>(); //initial int array
    MyArrayList<int> copiedIntList = MyArrayList<int>(); //coppied int array
    MyArrayList<double> doubleList = MyArrayList<double>(100); //double array
    MyArrayList<std::string> myStringList = MyArrayList<std::string>(15);//string array
    
    //tests
    std::cout << "Is it empty? " << myIntList.isEmpty() << std::endl;
    std::cout << "Is it epmty? " << myStringList.isEmpty() << std::endl;
    
    try {
        
        doubleList.addElement(1.4);
        doubleList.printIt();
        
        myIntList.addElement(123);
        for (int i = 0; i < 35; i++) {
            myIntList.addElement(i);
        }
        myIntList.printIt();
        myIntList.addElement(1);
        myIntList.printIt(); //print all the elements
        
        myIntList.addByIndex(4, 999); //add '999' instead of '4' to the array
        myIntList.printIt(); //print all the elements
        std::cout << "Current capacity: " << myIntList.getCapacity() << " Current size: " << myIntList.getSize() << std::endl;
        
        std::cout << std::endl << "============copy tests============" << std::endl;
        std::cout << "Is it empty? " << copiedIntList.isEmpty() << std::endl << std::endl;
        copiedIntList.addElement(123);
        copiedIntList.addAll(myIntList); //add all the elements of myIntList to the copiedIntList;
        copiedIntList.printIt();
        std::cout << "Current capacity: " << copiedIntList.getCapacity() << " Current size: " << copiedIntList.getSize() << std::endl << std::endl;
        
        //copy empty array
        MyArrayList<int> emptyArray;
        copiedIntList.addAll(emptyArray);
        
    } catch (std::exception &ex) {
        std::cout << "Something went wrong, exception's been catched: " << ex.what() << std::endl;
    }
    return 0;
}

