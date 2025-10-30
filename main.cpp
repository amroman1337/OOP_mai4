#include "figure.h"
#include "array.h"
#include <iostream>
#include <memory>
#include <string>
#include <windows.h>

template<typename T>
std::shared_ptr<Figure<T>> createFigure(int choice) {
    switch (choice) {
        case 1: 
            return std::make_shared<Rhombus<T>>();
        case 2:
            return std::make_shared<Pentagon<T>>();
        case 3:
            return std::make_shared<Hexagon<T>>();
        default: 
            return nullptr;
    }
}

template<typename T>
void demoFigurePointers() {
    std::cout << "\nДемонстрация Array<Figure*>" << std::endl;
    
    Array<Figure<T>*> figure_pointers;
    auto* rhombus = new Rhombus<T>(0.0, 0.0, 2.0, 1.0, 4.0, 0.0, 2.0, -1.0);
    auto* pentagon = new Pentagon<T>(0.0, 0.0, 1.0, 2.0, 3.0, 2.0, 4.0, 0.0, 2.0, -1.0);
    
    figure_pointers.push_back(rhombus);
    figure_pointers.push_back(pentagon);

    for (size_t i = 0; i < figure_pointers.size(); ++i) {
        std::cout << "Фигура " << i + 1 << ":" << std::endl;
        auto center = figure_pointers[i]->getCenter();
        std::cout << "Центр: (" << center.x() << ", " << center.y() << ")" << std::endl;
        std::cout << "Площадь: " << figure_pointers[i]->getArea() << std::endl;
        std::cout << *figure_pointers[i] << std::endl;
    }
    for (size_t i = 0; i < figure_pointers.size(); ++i) {
        delete figure_pointers[i];
    }
}

void demoConcreteFigures() {
    std::cout << "\nДемонстрация Array<Rhombus<int>>" << std::endl;
    
    Array<Rhombus<int>> rhombuses_int;
    rhombuses_int.push_back(Rhombus<int>(0, 0, 2, 1, 4, 0, 2, -1));
    rhombuses_int.push_back(Rhombus<int>(1, 1, 3, 2, 5, 1, 3, 0));
    
    for (size_t i = 0; i < rhombuses_int.size(); ++i) {
        std::cout << "Ромб " << i + 1 << " площадь: " << rhombuses_int[i].getArea() << std::endl;
    }
    
    std::cout << "\nДемонстрация Array<Hexagon<double>>" << std::endl;
    
    Array<Hexagon<double>> hexagons_double;
    hexagons_double.push_back(Hexagon<double>(0.0, 0.0, 1.0, 1.0, 2.0, 1.0, 3.0, 0.0, 2.0, -1.0, 1.0, -1.0));
    hexagons_double.push_back(Hexagon<double>(1.0, 1.0, 2.0, 2.0, 3.0, 2.0, 4.0, 1.0, 3.0, 0.0, 2.0, 0.0));
    
    for (size_t i = 0; i < hexagons_double.size(); ++i) {
        std::cout << "Шестиугольник " << i + 1 << " площадь: " << hexagons_double[i].getArea() << std::endl;
    }
}

template<typename T>
void demoSharedPtrFigures() {
    std::cout << "\nДемонстрация Array<std::shared_ptr<Figure<T>>>" << std::endl;
    
    Array<std::shared_ptr<Figure<T>>> figures;
    
    figures.push_back(std::make_shared<Rhombus<T>>(0.0, 0.0, 2.0, 1.0, 4.0, 0.0, 2.0, -1.0));
    figures.push_back(std::make_shared<Pentagon<T>>(0.0, 0.0, 1.0, 2.0, 3.0, 2.0, 4.0, 0.0, 2.0, -1.0));
    figures.push_back(std::make_shared<Hexagon<T>>(0.0, 0.0, 1.0, 1.0, 2.0, 1.0, 3.0, 0.0, 2.0, -1.0, 1.0, -1.0));
    
    std::cout << "Информация о всех фигурах:" << std::endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Фигура " << i + 1 << ":" << std::endl;
        auto center = figures[i]->getCenter();
        std::cout << "Центр: (" << center.x() << ", " << center.y() << ")" << std::endl;
        std::cout << "Площадь: " << figures[i]->getArea() << std::endl;
        std::cout << *figures[i] << std::endl;
    }

    double total_area = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_area += figures[i]->getArea();
    }
    std::cout << "Общая площадь: " << total_area << std::endl;
    
    std::cout << "\nУдаление фигуры с индексом 1..." << std::endl;
    figures.remove(1);
    std::cout << "Осталось фигур: " << figures.size() << std::endl;
}

void demoMoveSemantics() {
    std::cout << "\nДемонстрация move-семантики" << std::endl;
    
    Array<std::string> strings;

    for (int i = 0; i < 15; ++i) {
        strings.push_back("Строка " + std::to_string(i));
        std::cout << "Добавлена строка, размер: " << strings.size() 
        << ", вместимость: " << strings.capacity() << std::endl;
    }
    
    std::cout << "Содержимое массива:" << std::endl;
    for (size_t i = 0; i < strings.size(); ++i) {
        std::cout << strings[i] << std::endl;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Array<std::shared_ptr<Figure<double>>> figure_array;
    int choice;
    std::cout << "Программа для работы с геометрическими фигурами" << std::endl;

    demoFigurePointers<double>(); // Array<Figure*>
    demoConcreteFigures(); // Array<Rhombus<int>>, Array<Hexagon<double>>
    demoSharedPtrFigures<double>(); // Array<std::shared_ptr<Figure>>
    demoMoveSemantics();

    while (true) {
        std::cout << "\nМеню:" << std::endl;
        std::cout << "1. Добавить фигуру" << std::endl;
        std::cout << "2. Удалить фигуру по индексу" << std::endl;
        std::cout << "3. Показать все фигуры" << std::endl;
        std::cout << "4. Вычислить общую площадь" << std::endl;
        std::cout << "5. Запустить все демонстрации" << std::endl;
        std::cout << "6. Выход" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                int figure_type;
                std::cout << "Выберите тип фигуры: " << std::endl;
                std::cout << "1) Ромб" << std::endl;
                std::cout << "2) Пятиугольник" << std::endl;
                std::cout << "3) Шестиугольник" << std::endl;
                std::cout << "Ваш выбор: ";
                std::cin >> figure_type;
                
                auto figure = createFigure<double>(figure_type);
                if (figure) {
                    std::cin >> *figure;
                    figure_array.push_back(figure);
                    std::cout << "Фигура добавлена" << std::endl;
                } else {
                    std::cout << "error: неверный тип фигуры" << std::endl;
                }
                break;
            }
            
            case 2: {
                if (figure_array.empty()) {
                    std::cout << "error: массив пуст!" << std::endl;
                    break;
                }
                
                std::cout << "Bведите индекс для удаления (1-" << figure_array.size() << "): ";
                size_t index;
                std::cin >> index;
                
                if (index >= 1 && index <= figure_array.size()) {
                    figure_array.remove(index - 1);
                    std::cout << "Фигура удалена" << std::endl;
                } else {
                    std::cout << "error: неверный индекс!" << std::endl;
                }
                break;
            }
            
            case 3: {
                if (figure_array.empty()) {
                    std::cout << "error: массив пуст" << std::endl;
                } else {
                    for (size_t i = 0; i < figure_array.size(); ++i) {
                        std::cout << "Фигура " << i + 1 << ":" << std::endl;
                        auto center = figure_array[i]->getCenter();
                        std::cout << "Центр: (" << center.x() << ", " << center.y() << ")" << std::endl;
                        std::cout << "Площадь: " << figure_array[i]->getArea() << std::endl;
                        std::cout << *figure_array[i] << std::endl;
                    }
                }
                break;
            }
            
            case 4: {
                double total_area = 0;
                for (size_t i = 0; i < figure_array.size(); ++i) {
                    total_area += figure_array[i]->getArea();
                }
                std::cout << "Общая площадь всех фигур: " << total_area << std::endl;
                break;
            }
            
            case 5: {
                demoFigurePointers<double>();
                demoConcreteFigures();
                demoSharedPtrFigures<double>();
                demoMoveSemantics();
                break;
            }
            
            case 6:
                std::cout << "Программа завершена" << std::endl;
                return 0;
            
            default:
                std::cout << "error: неверный выбор" << std::endl;
        }
    }
    
    return 0;
}