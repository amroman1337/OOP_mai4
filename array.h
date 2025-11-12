#pragma once
#include <iostream>
#include <memory>
#include <assert.h>
#include <stdexcept>

template <class T>
class Array {
public:
    Array() : _size(0), _capacity(10) {
        std::cout << "Default constructor" << std::endl;
        _array = std::shared_ptr<T[]>(new T[_capacity]);
    }

    Array(size_t initial_capacity) : _size(0), _capacity(initial_capacity) {
        std::cout << "Capacity constructor" << std::endl;
        _array = std::shared_ptr<T[]>(new T[_capacity]);
    }

    Array(const std::initializer_list<T> &t) {
        std::cout << "Initializer list constructor" << std::endl;
        _size = t.size();
        _capacity = _size * 2;
        _array = std::shared_ptr<T[]>(new T[_capacity]);
        
        size_t i{0};
        for (auto &c : t) {
            _array[i++] = c;
        }
    }

    Array(const Array &other) {
        std::cout << "Copy constructor" << std::endl;
        _size = other._size;
        _capacity = other._capacity;
        _array = std::shared_ptr<T[]>(new T[_capacity]);

        for (size_t i{0}; i < _size; ++i){
            _array[i] = other._array[i];
        }
    }

    Array(Array &&other) noexcept {
        std::cout << "Move constructor" << std::endl;
        _size = other._size;
        _capacity = other._capacity;
        _array = std::move(other._array);
        other._size = 0;
        other._capacity = 0;
    }

    Array& operator=(const Array &other) {
        std::cout << "Copy assignment" << std::endl;
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            _array = std::shared_ptr<T[]>(new T[_capacity]);

            for (size_t i{0}; i < _size; ++i)
                _array[i] = other._array[i];
        }
        return *this;
    }

    Array& operator=(Array &&other) noexcept {
        std::cout << "Move assignment" << std::endl;
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            _array = std::move(other._array);
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    void push_back(const T& value) {
        if (_size >= _capacity) {
            resize(_capacity * 2);
        }
        _array[_size++] = value;
    }

    void push_back(T&& value) {
        if (_size >= _capacity) {
            resize(_capacity * 2);
        }
        _array[_size++] = std::move(value);
    }

    void remove(size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < _size - 1; ++i) {
            _array[i] = std::move(_array[i + 1]);
        }
        --_size;
    }

    T& operator[](size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _array[index];
    }

    const T& operator[](size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _array[index];
    }

    size_t size() const {
        return _size;
    }

    size_t capacity() const {
        return _capacity;
    }

    bool empty() const {
        return _size == 0;
    }

    void clear() {
        _size = 0;
    }

    class Iterator {
    public:
        Iterator(std::shared_ptr<T[]> data, size_t index) : _data(data), _index(index) {}
        T& operator*() { return _data[_index]; }
        T* operator->() { return &_data[_index]; }
        
        Iterator& operator++() { 
            ++_index; 
            return *this; 
        }
        
        Iterator operator++(int) {
            Iterator temp = *this;
            ++_index;
            return temp;
        }
        
        bool operator==(const Iterator& other) const { return _index == other._index; }
        bool operator!=(const Iterator& other) const { return _index != other._index; }
    private:
        std::shared_ptr<T[]> _data;
        size_t _index;
    };

    Iterator begin() {
        return Iterator(_array, 0);
    }

    Iterator end() {
        return Iterator(_array, _size);
    }
private:
    size_t _size;
    size_t _capacity;
    std::shared_ptr<T[]> _array;
    void resize(size_t new_capacity) {
        std::cout << "Resizing from " << _capacity << " to " << new_capacity << std::endl;
        std::shared_ptr<T[]> new_array = std::shared_ptr<T[]>(new T[new_capacity]);
        
        for (size_t i = 0; i < _size; ++i) {
            new_array[i] = std::move(_array[i]);
        }
        
        _array = std::move(new_array);
        _capacity = new_capacity;
    }
};