#include "point.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

template<typename T>
class Figure {
public:
    virtual Point<T> getCenter() const = 0;
    virtual double getArea() const = 0;
    virtual void printVertices(std::ostream& os) const = 0;
    virtual void readData(std::istream& is) = 0;
    virtual std::vector<std::unique_ptr<Point<T>>> getVertices() const = 0;
    
    virtual explicit operator double() const { return getArea(); }
    virtual std::unique_ptr<Figure<T>> clone() const = 0;
    virtual bool equals(const Figure<T>* other) const = 0;
    
    bool operator==(const Figure<T>& other) const {
        return equals(&other);
    }
    virtual ~Figure() = default;
};

template<typename T>
class Rhombus : public Figure<T> {
public:
    Rhombus() : p1(0, 0), p2(0, 0), p3(0, 0), p4(0, 0) {}

    Rhombus(T x1, T y1, T x2, T y2, T x3, T y3, T x4, T y4) 
        :p1(x1, y1), p2(x2, y2), p3(x3, y3), p4(x4, y4) {}

    Point<T> getCenter() const override {
        T center_x = (p1.x() + p2.x() + p3.x() + p4.x()) / 4;
        T center_y = (p1.y() + p2.y() + p3.y() + p4.y()) / 4;
        return Point<T>(center_x, center_y);
    }

    double getArea() const override {
        T d1 = std::sqrt(std::pow(p2.x() - p4.x(), 2) + std::pow(p2.y() - p4.y(), 2));
        T d2 = std::sqrt(std::pow(p1.x() - p3.x(), 2) + std::pow(p1.y() - p3.y(), 2));
        return (d1 * d2) / 2.0;
    }

    void printVertices(std::ostream& output) const override {
        output << "Вершины ромба:\n";
        output << "1: (" << p1.x() << ", " << p1.y() << ")\n";
        output << "2: (" << p2.x() << ", " << p2.y() << ")\n";
        output << "3: (" << p3.x() << ", " << p3.y() << ")\n";
        output << "4: (" << p4.x() << ", " << p4.y() << ")\n";
    }

    std::vector<std::unique_ptr<Point<T>>> getVertices() const override {
        std::vector<std::unique_ptr<Point<T>>> vertices;
        vertices.push_back(std::make_unique<Point<T>>(p1));
        vertices.push_back(std::make_unique<Point<T>>(p2));
        vertices.push_back(std::make_unique<Point<T>>(p3));
        vertices.push_back(std::make_unique<Point<T>>(p4));
        return vertices;
    }

    void readData(std::istream& input) override {
        std::cout << "Введите координаты 4 вершин ромба (x1 y1 x2 y2 x3 y3 x4 y4): ";
        T x1, y1, x2, y2, x3, y3, x4, y4;
        input >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        p1 = Point<T>(x1, y1);
        p2 = Point<T>(x2, y2);
        p3 = Point<T>(x3, y3);
        p4 = Point<T>(x4, y4);
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Rhombus<T>>(*this);
    }

    bool equals(const Figure<T>* other) const override {
        auto r = dynamic_cast<const Rhombus<T>*>(other);
        if (!r) return false;
        return p1 == r->p1 && p2 == r->p2 && p3 == r->p3 && p4 == r->p4;
    }
private:
    Point<T> p1, p2, p3, p4;
};

template<typename T>
class Pentagon : public Figure<T> {
public:
    Pentagon() : p1(0, 0), p2(0, 0), p3(0, 0), p4(0, 0), p5(0, 0) {}
    
    Pentagon(T x1, T y1, T x2, T y2, T x3, T y3, T x4, T y4, T x5, T y5) 
        : p1(x1, y1), p2(x2, y2), p3(x3, y3), p4(x4, y4), p5(x5, y5) {}

    Point<T> getCenter() const override {
        T center_x = (p1.x() + p2.x() + p3.x() + p4.x() + p5.x()) / 5;
        T center_y = (p1.y() + p2.y() + p3.y() + p4.y() + p5.y()) / 5;
        return Point<T>(center_x, center_y);
    }

    double getArea() const override {
        T sum1 = p1.x() * p2.y() + p2.x() * p3.y() + p3.x() * p4.y() + p4.x() * p5.y() + p5.x() * p1.y();
        T sum2 = p1.y() * p2.x() + p2.y() * p3.x() + p3.y() * p4.x() + p4.y() * p5.x() + p5.y() * p1.x();
        return std::abs(sum1 - sum2) / 2.0;
    }

    void printVertices(std::ostream& output) const override {
        output << "Вершины пятиугольника:\n";
        output << "1: (" << p1.x() << ", " << p1.y() << ")\n";
        output << "2: (" << p2.x() << ", " << p2.y() << ")\n";
        output << "3: (" << p3.x() << ", " << p3.y() << ")\n";
        output << "4: (" << p4.x() << ", " << p4.y() << ")\n";
        output << "5: (" << p5.x() << ", " << p5.y() << ")\n";
    }

    std::vector<std::unique_ptr<Point<T>>> getVertices() const override {
        std::vector<std::unique_ptr<Point<T>>> vertices;
        vertices.push_back(std::make_unique<Point<T>>(p1));
        vertices.push_back(std::make_unique<Point<T>>(p2));
        vertices.push_back(std::make_unique<Point<T>>(p3));
        vertices.push_back(std::make_unique<Point<T>>(p4));
        vertices.push_back(std::make_unique<Point<T>>(p5));
        return vertices;
    }

    void readData(std::istream& input) override {
        std::cout << "Введите координаты 5 вершин пятиугольника (x1 y1 x2 y2 x3 y3 x4 y4 x5 y5): ";
        T x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;
        input >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5;
        p1 = Point<T>(x1, y1);
        p2 = Point<T>(x2, y2);
        p3 = Point<T>(x3, y3);
        p4 = Point<T>(x4, y4);
        p5 = Point<T>(x5, y5);
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Pentagon<T>>(*this);
    }

    bool equals(const Figure<T>* other) const override {
        auto p = dynamic_cast<const Pentagon<T>*>(other);
        if (!p) return false;
        return p1 == p->p1 && p2 == p->p2 && p3 == p->p3 && p4 == p->p4 && p5 == p->p5;
    }
private:
    Point<T> p1, p2, p3, p4, p5;  
};

template<typename T>
class Hexagon : public Figure<T> {
public:
    Hexagon() : p1(0, 0), p2(0, 0), p3(0, 0), p4(0, 0), p5(0, 0), p6(0, 0) {}
    
    Hexagon(T x1, T y1, T x2, T y2, T x3, T y3, T x4, T y4, T x5, T y5, T x6, T y6) 
        : p1(x1, y1), p2(x2, y2), p3(x3, y3), p4(x4, y4), p5(x5, y5), p6(x6, y6) {}

    Point<T> getCenter() const override {
        T center_x = (p1.x() + p2.x() + p3.x() + p4.x() + p5.x() + p6.x()) / 6;
        T center_y = (p1.y() + p2.y() + p3.y() + p4.y() + p5.y() + p6.y()) / 6;
        return Point<T>(center_x, center_y);
    }

    double getArea() const override {
        T sum1 = p1.x() * p2.y() + p2.x() * p3.y() + p3.x() * p4.y() + 
                 p4.x() * p5.y() + p5.x() * p6.y() + p6.x() * p1.y();
        T sum2 = p1.y() * p2.x() + p2.y() * p3.x() + p3.y() * p4.x() + 
                 p4.y() * p5.x() + p5.y() * p6.x() + p6.y() * p1.x();
        return std::abs(sum1 - sum2) / 2.0;
    }

    void printVertices(std::ostream& output) const override {
        output << "Вершины шестиугольника:\n";
        output << "1: (" << p1.x() << ", " << p1.y() << ")\n";
        output << "2: (" << p2.x() << ", " << p2.y() << ")\n";
        output << "3: (" << p3.x() << ", " << p3.y() << ")\n";
        output << "4: (" << p4.x() << ", " << p4.y() << ")\n";
        output << "5: (" << p5.x() << ", " << p5.y() << ")\n";
        output << "6: (" << p6.x() << ", " << p6.y() << ")\n";
    }

    std::vector<std::unique_ptr<Point<T>>> getVertices() const override {
        std::vector<std::unique_ptr<Point<T>>> vertices;
        
        vertices.push_back(std::make_unique<Point<T>>(p1));
        vertices.push_back(std::make_unique<Point<T>>(p2));
        vertices.push_back(std::make_unique<Point<T>>(p3));
        vertices.push_back(std::make_unique<Point<T>>(p4));
        vertices.push_back(std::make_unique<Point<T>>(p5));
        vertices.push_back(std::make_unique<Point<T>>(p6));
        return vertices;
    }

    void readData(std::istream& input) override {
        std::cout << "Введите координаты 6 вершин шестиугольника (x1 y1 x2 y2 x3 y3 x4 y4 x5 y5 x6 y6): ";
        T x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
        input >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5 >> x6 >> y6;
        p1 = Point<T>(x1, y1);
        p2 = Point<T>(x2, y2);
        p3 = Point<T>(x3, y3);
        p4 = Point<T>(x4, y4);
        p5 = Point<T>(x5, y5);
        p6 = Point<T>(x6, y6);
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Hexagon<T>>(*this);
    }

    bool equals(const Figure<T>* other) const override {
        auto h = dynamic_cast<const Hexagon<T>*>(other);
        if (!h) return false;
        return p1 == h->p1 && p2 == h->p2 && p3 == h->p3 && 
               p4 == h->p4 && p5 == h->p5 && p6 == h->p6;
    }
private:
    Point<T> p1, p2, p3, p4, p5, p6;
};

template<typename T>
std::ostream& operator<<(std::ostream& output, const Figure<T>& figure) {
    figure.printVertices(output);
    return output;
}

template<typename T>
std::istream& operator>>(std::istream& input, Figure<T>& figure) {
    figure.readData(input);
    return input;
}