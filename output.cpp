#ifndef COMPLEXHEADER_H
#define COMPLEXHEADER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <algorithm>
#include <functional>
#include <cmath>

// Namespace to encapsulate all code
namespace ComplexLib
{
    enum class Color
    {
        Red,
        Green,
        Blue,
        Yellow,
        White,
        Black
    };

    enum class ShapeType
    {
        Circle,
        Square,
        Triangle
    };

    struct Point
    {
        double x, y;

        Point() : x(0), y(0) {}
        Point(double x, double y) : x(x), y(y) {}

        double distance(const Point& other) const
        {
            return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
        }
    };

    class Shape
    {
    public:
        virtual ~Shape() {}
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
        virtual void draw() const = 0;
    };

    class Circle : public Shape
    {
    private:
        Point center;
        double radius;

    public:
        Circle(Point center, double radius) : center(center), radius(radius) {}

        double area() const override
        {
            return M_PI * radius * radius;
        }

        double perimeter() const override
        {
            return 2 * M_PI * radius;
        }

        void draw() const override
        {
            std::cout << "Drawing Circle at (" << center.x << ", " << center.y << ") with radius " << radius << std::endl;
        }
    };

    class Square : public Shape
    {
    private:
        Point topLeft;
        double side;

    public:
        Square(Point topLeft, double side) : topLeft(topLeft), side(side) {}

        double area() const override
        {
            return side * side;
        }

        double perimeter() const override
        {
            return 4 * side;
        }

        void draw() const override
        {
            std::cout << "Drawing Square at (" << topLeft.x << ", " << topLeft.y << ") with side " << side << std::endl;
        }
    };

    class Triangle : public Shape
    {
    private:
        Point a, b, c;

        double sideLength(const Point& p1, const Point& p2) const
        {
            return p1.distance(p2);
        }

    public:
        Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {}

        double area() const override
        {
            double s1 = sideLength(a, b);
            double s2 = sideLength(b, c);
            double s3 = sideLength(c, a);
            double s = (s1 + s2 + s3) / 2;
            return std::sqrt(s * (s - s1) * (s - s2) * (s - s3));
        }

        double perimeter() const override
        {
            return sideLength(a, b) + sideLength(b, c) + sideLength(c, a);
        }

        void draw() const override
        {
            std::cout << "Drawing Triangle with vertices at (" << a.x << ", " << a.y << "), (" 
                      << b.x << ", " << b.y << "), and (" << c.x << ", " << c.y << ")" << std::endl;
        }
    };

    class ShapeFactory
    {
    public:
        static std::unique_ptr<Shape> createShape(ShapeType type)
        {
            switch (type)
            {
            case ShapeType::Circle:
                return std::make_unique<Circle>(Point(0, 0), 5.0);
            case ShapeType::Square:
                return std::make_unique<Square>(Point(0, 0), 4.0);
            case ShapeType::Triangle:
                return std::make_unique<Triangle>(Point(0, 0), Point(3, 0), Point(1.5, 2.6));
            default:
                return nullptr;
            }
        }
    };

    template <typename T>
    class Stack
    {
    private:
        std::vector<T> elements;

    public:
        void push(const T& elem)
        {
            elements.push_back(elem);
        }

        void pop()
        {
            if (elements.empty())
            {
                throw std::out_of_range("Stack<>::pop(): empty stack");
            }
            elements.pop_back();
        }

        T top() const
        {
            if (elements.empty())
            {
                throw std::out_of_range("Stack<>::top(): empty stack");
            }
            return elements.back();
        }

        bool empty() const
        {
            return elements.empty();
        }
    };

    template <typename K, typename V>
    class Dictionary
    {
    private:
        std::map<K, V> data;

    public:
        void add(const K& key, const V& value)
        {
            data[key] = value;
        }

        V get(const K& key) const
        {
            auto it = data.find(key);
            if (it != data.end())
            {
                return it->second;
            }
            throw std::out_of_range("Key not found");
        }

        bool contains(const K& key) const
        {
            return data.find(key) != data.end();
        }
    };

    class Scene
    {
    private:
        std::vector<std::unique_ptr<Shape>> shapes;
        Color backgroundColor;

    public:
        Scene(Color backgroundColor = Color::White) : backgroundColor(backgroundColor) {}

        void addShape(std::unique_ptr<Shape> shape)
        {
            shapes.push_back(std::move(shape));
        }

        void render() const
        {
            std::cout << "Rendering scene with background color: " << static_cast<int>(backgroundColor) << std::endl;
            for (const auto& shape : shapes)
            {
                shape->draw();
            }
        }
    };

    template <typename T>
    class Math
    {
    public:
        static T add(T a, T b)
        {
            return a + b;
        }

        static T subtract(T a, T b)
        {
            return a - b;
        }

        static T multiply(T a, T b)
        {
            return a * b;
        }

        static T divide(T a, T b)
        {
            if (b == 0)
            {
                throw std::invalid_argument("Division by zero");
            }
            return a / b;
        }

        static T power(T base, int exponent)
        {
            return std::pow(base, exponent);
        }
    };

    class Logger
    {
    public:
        static void log(const std::string& message)
        {
            std::cout << "[LOG] " << message << std::endl;
        }

        static void warn(const std::string& message)
        {
            std::cout << "[WARN] " << message << std::endl;
        }

        static void error(const std::string& message)
        {
            std::cerr << "[ERROR] " << message << std::endl;
        }
    };

    // Function to simulate complex calculations
    double complexCalculation(double input)
    {
        Logger::log("Starting complex calculation...");
        double result = input;
        for (int i = 0; i < 100; ++i)
        {
            result = Math<double>::add(result, Math<double>::power(result, 2));
        }
        Logger::log("Complex calculation finished.");
        return result;
    }

    class Resource
    {
    private:
        int* data;

    public:
        Resource(int value) : data(new int(value)) {}
        
        ~Resource()
        {
            delete data;
        }

        int getValue() const
        {
            return *data;
        }

        void setValue(int value)
        {
            *data = value;
        }
    };

    class ResourceManager
    {
    private:
        std::vector<std::unique_ptr<Resource>> resources;

    public:
        void createResource(int value)
        {
            resources.push_back(std::make_unique<Resource>(value));
        }

        Resource* getResource(size_t index) const
        {
            if (index < resources.size())
            {
                return resources[index].get();
            }
            throw std::out_of_range("Invalid resource index");
        }
    };
}

#endif  // COMPLEXHEADER_H

#include <iostream>

using namespace ComplexLib;

int main()
{
    Square triangle = Square(Point(), 5.0);
    std::cout << triangle.area() << std::endl;
}