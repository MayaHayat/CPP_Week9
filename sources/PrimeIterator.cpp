#include "MagicalContainer.hpp"

#include <algorithm>
#include <vector>

using namespace std;

// Returns the iterator pointing to the beginning of the prime elements
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
    return PrimeIterator(container);
}

// Returns the iterator pointing to the end of the prime elements
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
    return PrimeIterator(container, container.primeElements.size());
}

// Moves to the next prime element
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
    if (container.primeElements.empty()) {
        throw std::runtime_error("No primes found");
    }
    if (index >= container.primeElements.size()) {
        throw std::runtime_error("Reached end of container");
    }
    index++;
    return *this;
}

// Assigns the iterator to another iterator
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
    if (&container != &other.container) {
        throw std::runtime_error("Containers aren't the same");
    }
    if (this != &other) {
        index = other.index;
    }
    return *this;
}

// Returns the value of the prime element at the current position
int MagicalContainer::PrimeIterator::operator*() const {
    return *container.primeElements[index];
}

// Compares two iterators
bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
    return index == other.index;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
    return index > other.index;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
    return index < other.index;
}