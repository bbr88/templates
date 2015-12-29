//
//  task5.cpp
//  mpp_assignment
//
//  Created by Игорь Бисарнов on 10.10.15.
//  Copyright (c) 2015 Игорь Бисарнов. All rights reserved.
//


#include <stdio.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

using namespace::std;

//Array list
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
        size = 0;
    }
    MyArrayList(int capacity) { //with particular capacity
        if (capacity > 0) {
            this->capacity = capacity;
            mass = new T[this->capacity];
            size = 0;
        } else {
            throw runtime_error("Capacity should be greater than 0.");
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
            //mass[idx] = NULL; //remove element with i = idx
            for (int i = idx; i < size - idx; i++) {
                mass[i] = mass[i+1]; //move elements rightward
            }
            size--; //decrement array's size
            return result;
        } else {
            throw std::runtime_error("Wrong index.");
        }
        
    }
    
    T getLast() { //return the last element
        if (!isEmpty()) {
            return mass[size-1];
        } else {
            return NULL;
        }
    }
    
    T removeLast() { //remove the last element
        if (!isEmpty()) {
            
            T result = mass[size--];
            
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
    mass = new T[capacity * 2]; //declare mass with doubled capacity
    
    for (int i = 0; i < capacity; i++) { //fill the array with previous values
        mass[i] = tempMass[i];
    }
    delete tempMass; //delete temporary array to avoid memory leak;
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
        //std::cout<<"size:= " <<size<<std::endl;
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





//Stack
template <typename T>
class Stack {
private: MyArrayList<T> elements = MyArrayList<T>(); //elements of the stack

public:
    void push(T const&); 	//push element
    T& pop();		//pop element
    T peek(); 	//return top element
    bool isEmpty() {
        return elements.isEmpty();
    }
    
    Stack<T>() {} //default constructor
    Stack<T>(Stack<T> &other) { //copy constructor
        this->elements = other.elements;
    }
};

//implementation
template <typename T>
void Stack<T>::push (T const &element) {
    elements.addElement(element);
}

template <typename T>
T& Stack<T>::pop() {
    if (elements.isEmpty()) {
        throw std::out_of_range("There's nothing to pop out. Stack is empty.");
    }
    T result = peek(); //get the last element of the stack;
    elements.removeLast(); //removes last element from the stack;
    return result;
}

template <typename T>
T Stack<T>::peek() {
    if (elements.isEmpty()) {
        return NULL;
    }
    return elements.getLast(); //gets the last element of the vector.
};


int main(int argc, const char * argv[]) {
    try {
        Stack<int> intStack; //int stack
        Stack<std::string> stringStack; //sting stack
        Stack<int> copiedIntStack; //copied int stack
        
        //pop/push tests
        std::cout<<intStack.isEmpty() << std::endl;
        intStack.push(100);
        std::cout<<intStack.isEmpty() << std::endl;
        intStack.push(140);
        intStack.push(130);

        std::cout << intStack.peek() << std::endl;
        intStack.push(123);
        std::cout << intStack.pop() << std::endl;
        
        stringStack.push("some string");
        std::cout << stringStack.peek() << std::endl;
        stringStack.push("yet another string");
        std::cout << (string)stringStack.pop() << std::endl;
        std::cout << stringStack.peek() << std::endl;
        
        //copy tests
        std::cout << "Is it empty? " << copiedIntStack.isEmpty() << std::endl;
        copiedIntStack = (intStack);
        std::cout << "Is it empty? " << copiedIntStack.isEmpty() << std::endl;
        std::cout << copiedIntStack.peek() << std::endl;
    }
    catch (std::exception &ex) {
        std::cout << "Something went wrong:( " << ex.what() << std::endl;
    }
    return 0;
}