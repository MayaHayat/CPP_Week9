#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <algorithm>
#include <vector>

using namespace std;
namespace ariel{};


// Starting with the magicalContainer class which includes the iterators
class MagicalContainer {
private:
    std::vector<int> mysticalElements;
    std::vector<int*> primeElements; // will be soon explained

public:
    MagicalContainer() = default;
    ~MagicalContainer() = default;


    void addElement(int element);
    void removeElement(int element);

    int size() const;
    std::vector<int> getElements() const;

    bool isPrime(int number);

    


    // ------------------ tidy -------------------
    MagicalContainer(const MagicalContainer& other) = default;
    MagicalContainer& operator=(const MagicalContainer& other) = default;
    MagicalContainer(MagicalContainer&& other) = default;
    MagicalContainer& operator=(MagicalContainer&& other) = default;


    // 4 6 2 8 3 8 0 1 -> 0 1 2 3 4  6 8
    class AscendingIterator {
    public:
        MagicalContainer& container;
        std::vector<int>::size_type index; // current place

        AscendingIterator(MagicalContainer& container): container(container), index(0){} // constructor
        AscendingIterator(const AscendingIterator& other): container(other.container), index(other.index){} // copy
        ~AscendingIterator() = default; // destructor

        // Constructor
        AscendingIterator(MagicalContainer& container, size_t index) : container(container), index(index) {
            if (index > container.mysticalElements.size()) {
                throw invalid_argument("Index out of bound");
            }
        }

        // returns first number in the container
        AscendingIterator begin() const{
            return AscendingIterator(container);
        }

        // returns the end of the container
        AscendingIterator end() const{
            return AscendingIterator (container, container.mysticalElements.size());
        }

        // if hasn't reached the end go to the next element
        AscendingIterator& operator++(){
            if (this ->index >= this->container.size()){
                throw std :: runtime_error("Reached end of container.");
            }
            index++;
            return *this;
        }

        // assigns the iterator to another iterator.
        AscendingIterator& operator=(const AscendingIterator& other){
            // makes sure it is the same type
            if(&this->container != &other.container){
                throw std :: runtime_error("Containers aren't the same");
            }
            // if they're not the same one
            if(this != &other) {
                this->index = other.index;
            }
            return *this;
        }

        // returns the value of the element we're at
        int operator*() const{ 
            return container.mysticalElements[(index)];
        }

        // compares 2 iterators
        bool operator==(const AscendingIterator& other) const{
            return this->index == other.index;
        }

        bool operator!=(const AscendingIterator& other) const{
            return  !(*this == other);
        }

        
        bool operator>(const AscendingIterator& other) const{
            return this ->index > other.index;
        }
        bool operator<(const AscendingIterator& other) const{
            return this ->index < other.index;
        }



        // ------------------ tidy -------------------

        AscendingIterator(AscendingIterator&& other) = default;
        AscendingIterator& operator=(AscendingIterator&& other) = delete;

    };

    class PrimeIterator {
    private:
        MagicalContainer& container;
        std::vector<int>::size_type index;

    public:
        PrimeIterator(MagicalContainer& container): container(container), index(0){}
        PrimeIterator(const PrimeIterator& other) : container(other.container), index(other.index){}
        ~PrimeIterator() = default; // destructor

        // Constructor
        PrimeIterator(MagicalContainer& container, size_t index) : container(container), index(index) {
            if (index > container.mysticalElements.size()) {
                throw invalid_argument("Index out of bound");
            }
        }

        // Uses default constructor -> index = 0
        PrimeIterator begin() const{
            return PrimeIterator(container);
        }

        // Note that we're looking at the end of the primeElements vector here
        PrimeIterator end() const{
            return PrimeIterator((this->container), (container).primeElements.size());
        }

        // Moves to the next prime in container
        PrimeIterator& operator++(){
            // checks if not empty first
            if(this->container.primeElements.empty()){
                throw std::runtime_error("No primes found");
            }
            // checks if hasn't reached the end
            if (this ->index >= this->container.primeElements.size()){
                throw std :: runtime_error("Reached end of container");
            }
            index++;
            return *this;
        }

        // Assigns the iterator to another one
        PrimeIterator& operator=(const PrimeIterator& other){
            if(&container != &other.container){
                throw std :: runtime_error("Containers aren't the same");
            }
            if(this != &other) {
                this->index = other.index;
            }
            return *this;
        }

        // returns the value of number in that index(need to use * as it's a vectors of pointers)
        int operator*() const{
            return *container.primeElements[(index)];
        }

        //
        bool operator==(const PrimeIterator& other) const{
            return this->index == other.index;
        }
        bool operator!=(const PrimeIterator& other) const{
            return !(*this == other);
        }
        bool operator>(const PrimeIterator& other) const{
            return this ->index > other.index;
        }
        bool operator<(const PrimeIterator& other) const{
            return this ->index < other.index;
        }


        // ------------------ tidy -------------------

        PrimeIterator(PrimeIterator&& other) = default;
        PrimeIterator& operator=(PrimeIterator&& other) = delete;
    };

    class SideCrossIterator {
    private:
        MagicalContainer& container;
        // Normal index is in a way to count number of steps, sideIndex for current location
        std::vector<int>::size_type index;
        std::vector<int>::size_type sideindex;


    public:
        SideCrossIterator(MagicalContainer& container) : container(container), index(0), sideindex(0){}
        SideCrossIterator(const SideCrossIterator& other) : container(other.container), index(other.index), sideindex(other.sideindex){}
        ~SideCrossIterator() = default;

        SideCrossIterator(MagicalContainer& container, size_t index) : container(container), index(index), sideindex(0) {
            if (index > container.mysticalElements.size()) {
                throw invalid_argument("Index out of bound");
            }
        }

        SideCrossIterator begin() const{
            return SideCrossIterator(container);
        }

        SideCrossIterator end() const{
            return SideCrossIterator(container, container.mysticalElements.size());

        }

        SideCrossIterator& operator++(){
            if(index >= (container).mysticalElements.size()){
                throw std::runtime_error("Reached end of container");
            }
            ++index;
            // index/2 from the left side
            if (index%2 == 0){
                sideindex = index/2;
            }
            else{
                // index/2 from the end of the container aka right size
                sideindex = (container).mysticalElements.size()-1-(index/2) ;
            }
            return *this;
        }
        

        SideCrossIterator& operator=(const SideCrossIterator& other){
            if(&this->container != &other.container){
                throw std :: runtime_error("Containers aren't the same");
            }
            if(this != &other) {
                this->index = other.index;
            }
            return *this;
        }

        // Note that we're returning the specialIndex used
        int operator*() const{
            return container.mysticalElements[(sideindex)];
        }
        
        bool operator==(const SideCrossIterator& other) const{
            return this->index == other.index;
        }
        bool operator!=(const SideCrossIterator& other) const{
            return !(*this == other);
        }
        bool operator>(const SideCrossIterator& other) const{
            return this ->index > other.index;
        }
        bool operator<(const SideCrossIterator& other) const{
            return this ->index < other.index;
        }
        

        // ------------------ tidy -------------------

        SideCrossIterator(SideCrossIterator&& other) = default;
        SideCrossIterator& operator=(SideCrossIterator&& other) = delete;
    };
};



#endif