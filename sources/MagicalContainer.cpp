#include <iostream>
#include <algorithm>

#include "MagicalContainer.hpp"



void MagicalContainer :: addElement(int element){
    auto it = std::lower_bound(mysticalElements.begin(), mysticalElements.end(), element);
    mysticalElements.insert(it, element);
    if(isPrime(element)){
        int *pointer = new int(element);
        auto it2 = std::lower_bound(this->primeElements.begin(), this->primeElements.end(), pointer , [](const int* a, const int* b) {return *a < *b; });
        primeElements.insert(it2, pointer);
    }
}

void MagicalContainer :: removeElement(int element){
    auto it = std::find(mysticalElements.begin(), mysticalElements.end(), element);
    if (it == mysticalElements.end())
        throw std:: runtime_error ("Element not found in the vector.");
    this -> mysticalElements.erase(std::remove(mysticalElements.begin(), mysticalElements.end(), element), mysticalElements.end());
    if(isPrime(element)){
        for (auto it2 = primeElements.begin(); it2 != primeElements.end(); ++it2) {
            if (**it2 == element) {
                primeElements.erase(it2);
                break;
            }
        }

    }
}

int MagicalContainer :: size()const{
    return this -> mysticalElements.size();
}

std::vector<int>  MagicalContainer :: getElements()const{
    return this ->mysticalElements;
}

bool MagicalContainer :: isPrime(int number){
    if (number <2){
        return false;
    }
    if (number == 2){
        return true;
    }
    for (int i = 2; i < number ; i++){
        if (number%i == 0){
            return false;
        }
    }
    return true;
}