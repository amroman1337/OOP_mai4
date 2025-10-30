#pragma once
#include <memory>

template<typename T>
class Point {
public:
    Point() : x_(0), y_(0) {}
    Point(T x, T y) : x_(x), y_(y) {}

    T x() const { 
        return x_; 
    }
    T y() const { 
        return y_; 
    }

    void setX(T x) {
        x_ = x;
    }
    void setY(T y) {
        y_ = y;
    }

    bool operator==(const Point& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }
private:
    T x_, y_;
};