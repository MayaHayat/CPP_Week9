#include "MagicalContainer.hpp"

#include <algorithm>
#include <vector>

using namespace std;

// Returns the first number in the container
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const {
    return AscendingIterator(container);
}

// Returns the end of the container
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const {
    return AscendingIterator(container, container.mysticalElements.size());
}

// Moves to the next element if not reached the end
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    if (index >= container.size()) {
        throw std::runtime_error("Reached end of container.");
    }
    index++;
    return *this;
}

// Assigns the iterator to another iterator
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
    if (&container != &other.container) {
        throw std::runtime_error("Containers aren't the same");
    }
    if (this != &other) {
        index = other.index;
    }
    return *this;
}

// Returns the value of the element at the current position
int MagicalContainer::AscendingIterator::operator*() const {
    return container.mysticalElements[index];
}

// Compares two iterators
bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
    return index == other.index;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
    return index > other.index;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
    return index < other.index;
}