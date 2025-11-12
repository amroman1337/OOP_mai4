#include "Figure.h"

Figure::operator double() const {
    return getArea();
}

bool Figure::operator==(const Figure& other) const {
    return equals(&other);
}

Triangle::Triangle() : side(0), centerX(0), centerY(0) {}

Triangle::Triangle(double SIDE, double x, double y): side(SIDE), centerX(x), centerY(y) {}

Triangle::Triangle(const Triangle& other):
    side(other.side), centerX(other.centerX), centerY(other.centerY) {}

Triangle::Triangle(Triangle&& other) noexcept:
    side(std::move(other.side)), 
    centerX(std::move(other.centerX)), 
    centerY(std::move(other.centerY)) {}

Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        side = other.side;
        centerX = other.centerX;
        centerY = other.centerY;
    }
    return *this;
}

Triangle& Triangle::operator=(Triangle&& other) noexcept {
    if (this != &other) {
        side = std::move(other.side);
        centerX = std::move(other.centerX);
        centerY = std::move(other.centerY);
    }
    return *this;
}

std::pair<double, double> Triangle::getCenter() const {
    double height = (sqrt(3)/2)*side;
    double r = height*2/3;

    double x1 = centerX, y1 = centerY + r;
    double x2 = centerX - side/2, y2 = centerY - r/2;
    double x3 = centerX + side/2, y3 = centerY - r/2;
    double sumX = x1 + x2 + x3;
    double sumY = y1 + y2 + y3;
    return {sumX / 3, sumY / 3};
}

double Triangle::getArea() const {
    return (sqrt(3)/4)*pow(side, 2);
}

void Triangle::printCoords(std::ostream& output) const {
    double height = (sqrt(3)/2)*side;
    double r = height*2/3;
    output << "Bершины треугольника: " << std::endl;
    output << "1 (" << centerX << ", " << centerY + r << ")" << std::endl;
    output << "2 (" << centerX - side/2 << ", " << centerY - r/2 << ")" << std::endl;
    output << "3 (" << centerX + side/2 << ", " << centerY - r/2 << ")" << std::endl;
}

void Triangle::readCoords(std::istream& input) {
    std::cout << "Введите сторону треугольника ";
    input >> side;
    std::cout << "Введите координаты центра (x;y) ";
    input >> centerX >> centerY;
}

std::unique_ptr<Figure> Triangle::copyFig() const {
    return std::make_unique<Triangle>(*this);
}

bool Triangle::equals(const Figure* other) const {
    const Triangle* t = dynamic_cast<const Triangle*>(other);
    if (!t) {
        return false;
    }
    return side == t->side && centerX == t->centerX && centerY == t->centerY;
}




Square::Square() : side(0), centerX(0), centerY(0) {}

Square::Square(double SIDE, double x, double y) : side(SIDE), centerX(x), centerY(y) {}

Square::Square(const Square& other):
    side(other.side), centerX(other.centerX), centerY(other.centerY) {}

Square::Square(Square&& other) noexcept:
    side(std::move(other.side)), 
    centerX(std::move(other.centerX)), 
    centerY(std::move(other.centerY)) {}

Square& Square::operator=(const Square& other) {
    if (this != &other) {
        side = other.side;
        centerX = other.centerX;
        centerY = other.centerY;
    }
    return *this;
}

Square& Square::operator=(Square&& other) noexcept {
    if (this != &other) {
        side = std::move(other.side);
        centerX = std::move(other.centerX);
        centerY = std::move(other.centerY);
    }
    return *this;
}

std::pair<double, double> Square::getCenter() const {
    double hS = side / 2;

    double x1 = centerX - hS, y1 = centerY - hS;
    double x2 = centerX + hS, y2 = centerY - hS;
    double x3 = centerX + hS, y3 = centerY + hS;
    double x4 = centerX - hS, y4 = centerY + hS;
    double sumX = x1 + x2 + x3 + x4;
    double sumY = y1 + y2 + y3 + y4;

    return {sumX / 4, sumY / 4};
}

double Square::getArea() const {
    return side * side;
}

void Square::printCoords(std::ostream& output) const {
    double hS = side / 2;
    output << "Вершины квадрата:" << std::endl;
    output << "1 (" << centerX - hS << ", " << centerY - hS << ")" << std::endl;
    output << "2 (" << centerX + hS << ", " << centerY - hS << ")" << std::endl;
    output << "3 (" << centerX + hS << ", " << centerY + hS << ")" << std::endl;
    output << "4 (" << centerX - hS << ", " << centerY + hS << ")" << std::endl;
}

void Square::readCoords(std::istream& input) {
    std::cout << "Введите значение стороны квадрата: ";
    input >> side;
    std::cout << "Введите координаты центра (x;y): ";
    input >> centerX >> centerY;
}

std::unique_ptr<Figure> Square::copyFig() const {
    return std::make_unique<Square>(*this);
}

bool Square::equals(const Figure* other) const {
    const Square* s = dynamic_cast<const Square*>(other);
    if (!s){
        return false;
    }
    return side == s->side && centerX == s->centerX && centerY == s->centerY;
}





Rectangle::Rectangle() : width(0), height(0), centerX(0), centerY(0) {}

Rectangle::Rectangle(double w, double h, double x, double y):
    width(w), height(h), centerX(x), centerY(y) {}

Rectangle::Rectangle(const Rectangle& other):
    width(other.width), height(other.height), 
    centerX(other.centerX), centerY(other.centerY) {}

Rectangle::Rectangle(Rectangle&& other) noexcept:
    width(std::move(other.width)), 
    height(std::move(other.height)),
    centerX(std::move(other.centerX)), 
    centerY(std::move(other.centerY)) {}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        centerX = other.centerX;
        centerY = other.centerY;
    }
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        width = std::move(other.width);
        height = std::move(other.height);
        centerX = std::move(other.centerX);
        centerY = std::move(other.centerY);
    }
    return *this;
}

std::pair<double, double> Rectangle::getCenter() const {
    double hW = width/2;
    double hH = height/2;

    double x1 = centerX - hW, y1 = centerY - hH;
    double x2 = centerX + hW, y2 = centerY - hH;
    double x3 = centerX + hW, y3 = centerY + hH;
    double x4 = centerX - hW, y4 = centerY + hH;
    double sumX = x1 + x2 + x3 + x4;
    double sumY = y1 + y2 + y3 + y4;
    
    return {sumX / 4, sumY / 4};
}
double Rectangle::getArea() const {
    return width * height;
}

void Rectangle::printCoords(std::ostream& output) const {
    double hW = width/2;
    double hH = height/2;
    output << "вершины прямоугольника:" << std::endl;
    output << "1 (" << centerX - hW << ", " << centerY - hH << ")" << std::endl;
    output << "2 (" << centerX + hW << ", " << centerY - hH << ")" << std::endl;
    output << "3 (" << centerX + hW << ", " << centerY + hH << ")" << std::endl;
    output << "4 (" << centerX - hW << ", " << centerY + hH << ")" << std::endl;
}

void Rectangle::readCoords(std::istream& input) {
    std::cout << "введите ширину прямоугольника ";
    input >> width;
    std::cout << "введите высоту прямоугольника ";
    input >> height;
    std::cout << "введите координаты центра (x;y) ";
    input >> centerX >> centerY;
}

std::unique_ptr<Figure> Rectangle::copyFig() const {
    return std::make_unique<Rectangle>(*this);
}

bool Rectangle::equals(const Figure* other) const {
    const Rectangle* r = dynamic_cast<const Rectangle*>(other);
    if (!r) {
        return false;
    }
    return width == r->width && height == r->height && centerX == r->centerX && centerY == r->centerY;
}

void FigureArray::addFig(std::unique_ptr<Figure> figure) {
    figures.push_back(std::move(figure));
}

void FigureArray::removeFig(int index) {
    if (index > -1 && index < figures.size()) {
        figures.erase(figures.begin() + index);
    }
}

size_t FigureArray::size() const {
    return figures.size();
}

Figure* FigureArray::getFig(int index) {
    if (index > -1 && index < figures.size()) {
        return figures[index].get();
    }
    return nullptr;
}

double FigureArray::getTotalArea() const {
    double res = 0;
    for (const auto& figure : figures) {
        res += figure->getArea();
    }
    return res;
}

void FigureArray::printAll() const {
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "фигура " << i + 1 << ":" << std::endl;
        auto center = figures[i]->getCenter();
        std::cout << "центр: (" << center.first << ", " << center.second << ")" << std::endl;
        std::cout << "площадь: " << figures[i]->getArea() << std::endl;
        std::cout << *figures[i]<< std::endl;
    }
}

std::ostream& operator<<(std::ostream& output, const Figure& figure) {
    figure.printCoords(output);
    return output;
}

std::istream& operator>>(std::istream& input, Figure& figure) {
    figure.readCoords(input);
    return input;
}

std::unique_ptr<Figure> createFig(int key) {
    switch (key) {
        case 1:
            return std::make_unique<Triangle>();
        case 2:
            return std::make_unique<Square>();
        case 3:
            return std::make_unique<Rectangle>();
        default:
            return nullptr;
    }
}