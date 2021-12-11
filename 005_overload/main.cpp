#include<iostream>

class Point {
    public:
    double x = 0;
    double y = 0;

    // 默认构造器
    Point() {}

    Point(double a, double b) :
        x(a),
        y(b) {  }

    Point operator+(const Point& rhs) const;

    Point& operator+=(const Point& rhs);
};

Point Point::operator+(const Point& rhs) const {
    return Point(x+rhs.x, y+rhs.y);
}

Point& Point::operator+=(const Point& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

int main() {
    Point up (0, 1);
    Point right (1, 0);
    Point res = up + right;
    std::cout << res.x << ", " << res.y << std::endl;
    return 0;
}
