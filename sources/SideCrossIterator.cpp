#include "MagicalContainer.hpp"

#include <algorithm>
#include <vector>

using namespace std;

// Returns the iterator pointing to the beginning of the side cross elements
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const {
    return SideCrossIterator(container);
}

// Returns the iterator pointing to the end of the side cross elements
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const {
    return SideCrossIterator(container, container.mysticalElements.size());
}

// Moves to the next side cross element
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    if (index >= container.mysticalElements.size()) {
        throw std::runtime_error("Reached end of container");
    }
    ++index;
    if (index % 2 == 0) {
        sideindex = index / 2;
    } else {
        sideindex = container.mysticalElements.size() - 1 - (index / 2);
    }
    return *this;
}

// Assigns the iterator to another iterator
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
    if (&container != &other.container) {
        throw std::runtime_error("Containers aren't the same");
    }
    if (this != &other) {
        index = other.index;
    }
    return *this;
}

// Returns the value of the side cross element at the current position
int MagicalContainer::SideCrossIterator::operator*() const {
    return container.mysticalElements[sideindex];
}

// Compares two iterators
bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
    return index == other.index;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
    return index > other.index;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
    return index < other.index;
}