#include <iostream>
#include <chrono>
#include <algorithm>  
#include <cstddef>    

class Buffer {
private:
    int* data;
    size_t size;

public:
    Buffer(size_t s) : size(s), data(new int[s]) {
        std::cout << "Constructor called\n";
    }

    ~Buffer() {
        delete[] data;
        std::cout << "Destructor called\n";
    }

    // Copy constructor
    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + other.size, data);
        std::cout << "Copy constructor called\n";
    }

    // Copy assignment
    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
            std::cout << "Copy assignment called\n";
        }
        return *this;
    }

    // Move constructor
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Move constructor called\n";
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "Move assignment called\n";
        }
        return *this;
    }
};

int main() {
    const size_t bigSize = 10000000;

    std::cout << "--- Testing Copy ---\n";
    Buffer original(bigSize);
    
    auto start_copy = std::chrono::high_resolution_clock::now();
    Buffer copy = original;  // Copy constructor
    auto end_copy = std::chrono::high_resolution_clock::now();
    
    std::cout << "Copy Duration: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_copy - start_copy).count()
              << " ms\n";

    std::cout << "\n--- Testing Move ---\n";
    auto start_move = std::chrono::high_resolution_clock::now();
    Buffer moved = std::move(original);  // Move constructor
    auto end_move = std::chrono::high_resolution_clock::now();

    std::cout << "Move Duration: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_move - start_move).count()
              << " ms\n";

    return 0;
}
