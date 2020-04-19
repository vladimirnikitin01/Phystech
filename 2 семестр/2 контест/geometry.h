/*�������� �������� ������� ��� ������ � ��������������� �������� �� ���������.
��������� Point - ����� �� ���������. ����� ����� ������ ����� ������� ���� double. ������ ���� ������� ���� x � y. ����� ����� ���������� ����������� == � !=.
����� Line - ������. ������ ����� ������ ����� �������, ����� ����� ������� (������� ����������� � �����), ����� ������ � ������ (������� �����������).
����� ����� ���������� ����������� == � !=.
����������� ����� Shape - ������.
����� Polygon - �������������. ������������� - ������� ������ ������.
� �������������� ����� �������� verticesCount() - ���������� ������ - � std::vector<Point> getVertices - ���� ������� ��� ����������� ���������.
������������ � �������� ���������� ����� ������� (�.�. ����������� ����� ����������). ��� �������� ����� �������,
��� �������������� � ����������������� ������� �� ��������� (�������������, ��� � ������ ������� ����� �������������).
����� Ellipse - ������. ������ - ������� ������ ������. � ������� ����� �������� std::pair<Point,Point> focuses() - ��� ������;
std::pair<Line, Line> directrices() - ���� ��� ���������; double eccentricity() - ��� ��������������, Point center() - ��� �����.
������ ����� ��������������� �� ���� ����� � double (��� ������ � ����� ���������� �� ������� �� ���);
����� Circle - ����. ���� - ������� ������ �������. � ����� ����� �������� double radius() - ������. ���� ����� ������ ������ � ������ (����� � ������).
����� Rectangle - �������������. ������������� - ������� ������ ��������������. � �������������� ����� �������� Point center() - ��� �����;
std::pair<Line, Line> diagonals() - ���� ��� ����������.
������������� ����� ��������������� �� ���� ������ (��� ��������������� ��������) � ����� (��������� ������� ������),
������ �� ���� ����� ��������������� ���������� ���, � �������� ����� �������� ������� ����������� �� ����� ������� �� ���������, ���� �������� �� ������ �������� ����� � ����������� ������.
����� Square - �������. ������� - ������� ������ ��������������. � �������� ����� �������� Circle circumscribedCircle(), Circle inscribedCircle().
������� ����� ������ ����� ������� - ���������������� ���������.
����� Triangle - �����������. ����������� - ������� ������ ��������������. � ������������ ����� �������� Circle circumscribedCircle(), Circle inscribedCircle(),
Point centroid() - ��� ����� ����, Point orthocenter() - ��� ���������, Line EulerLine() - ��� ������ ������, Circle ninePointsCircle() - ��� ���������� ������.
� ����� ������ ����� ��������:
double perimeter() - ��������;
double area() - �������;
operator==(const Shape& another) - ��������� �� ��� ������ � ������;
isCongruentTo(const Shape& another) - ����� �� ��� ������ ������ � �������������� ������;
isSimilarTo(const Shape& another) - ������� �� ��� ������ ������;
containsPoint(Point point) - ��������� �� ����� ������ ������.
� ����� ������� ����� �������:
rotate(Point center, double angle) - ������� �� ���� (� ��������, ������ ������� �������) ������������ �����;
reflex(Point center) - ��������� ������������ �����;
reflex(Line axis) - ��������� ������������ ������;
scale(Point center, double coefficient) - ��������� � ������������� coefficient � ������� center.

*/


#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

const double PI = 3.1415926535897932384626;
const double EPSILON = 0.000000001;

struct Point {
    double x;
    double y;

    Point(double a, double b) {
        x = a;
        y = b;
    }

    Point() {
        x = 0;
        y = 0;
    }
};

double Distance(Point a, Point b) {
    double s = sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
    return (s);
}

struct Corner {
    double x;

    Corner(double a) {
        x = a;
    }

    Corner() {
        x = 0;
    }
};


struct Len {
    double x;

    Len(double a) {
        x = a;
    }

    Len() {
        x = 0;
    }
};


bool operator==(const Len& a, const Len& b) {
    return std::abs(a.x - b.x) < EPSILON;
}

bool operator!=(const Len& a, const Len& b) {
    return (!(a == b));
}


bool operator==(const Corner& a, const Corner& b) {
    return std::abs(a.x - b.x) < EPSILON;
}

bool operator!=(const Corner& a, const Corner& b) {
    return (!(a == b));
}

bool operator==(const Point& a, const Point& b) {
    return std::abs(a.x - b.x) < EPSILON && std::abs(a.y - b.y) < EPSILON;
}

bool operator!=(const Point& a, const Point& b) {
    return (!(a == b));
}

struct VECTOR {
    double x;
    double y;

    VECTOR() {
        x = 0;
        y = 0;
    }

    VECTOR(Point start, Point end) {
        x = end.x - start.x;
        y = end.y - start.y;
    }
};

double Scalar_product(const VECTOR a, const VECTOR b) {
    double res = a.x * b.x + a.y * b.y;
    return (res);
}

bool Vector_product(const VECTOR a, const VECTOR b) {
    //double res = a.x * b.y - a.y * b.x;
    bool sign = (a.x * b.y >= a.y * b.x);
    return (sign);
}

VECTOR from_point_to_VECTOR(const Point a) {
    VECTOR b;
    b.x = a.x;
    b.y = a.y;
    return (b);
}

VECTOR give_normal_front_vector(const VECTOR& a) {
    VECTOR now;
    now.x = -a.y;
    now.y = a.x;
    return (now);
}

std::vector<Corner> Corner_from_vertex(const std::vector<Point>& a) {
    std::vector<Corner> now;
    for (size_t i = 0; i < a.size(); ++i) {
        if (i == a.size() - 2) {
            now.push_back(acos(Scalar_product(VECTOR(a[i], a[i + 1]), VECTOR(a[0], a[i + 1])) /
                (Distance(a[i], a[i + 1]) * Distance(a[0], a[i + 1]))));
        }
        else if (i == a.size() - 1) {
            now.push_back(acos(Scalar_product(VECTOR(a[i], a[0]), VECTOR(a[1], a[0])) /
                (Distance(a[i], a[0]) * Distance(a[1], a[0]))));
        }
        else {
            now.push_back(acos(Scalar_product(VECTOR(a[i], a[i + 1]), VECTOR(a[i + 2], a[i + 1])) /
                (Distance(a[i], a[i + 1]) * Distance(a[i + 2], a[i + 1]))));
        }
    }
    return (now);
}

std::vector<Len> Distance_from_vertex(const std::vector<Point>& a) {
    std::vector<Len> now;
    for (size_t i = 0; i < a.size(); ++i) {
        if (i == a.size() - 1) {
            now.push_back(Len(Distance(a[i], a[0])));
        }
        else {
            now.push_back(Len(Distance(a[i], a[i + 1])));
        }
    }
    return (now);
}

class Line {
private:
    double vector_x = 0;
    double vector_y = 0;
    Point point_0;

public:
    Line(Point a, Point b) {
        point_0 = a;
        vector_x = b.x - a.x;
        vector_y = b.y - a.y;
    }

    Line(double k, double b) {
        vector_x = 1;
        vector_y = k;
        point_0.x = 0;
        point_0.y = b;
    }

    Line(Point a, double k) {
        vector_x = 1;
        vector_y = k;
        point_0 = a;
    }

    Line(Point a, VECTOR b) {
        vector_x = b.x;
        vector_y = b.y;
        point_0 = a;
    }

    Line() = default;

    bool operator==(const Line& b) {
        if (std::abs(vector_x * b.vector_y - vector_y * b.vector_x) < EPSILON) {
            return std::abs(((point_0.x - b.point_0.x) * b.vector_y) - ((point_0.y - b.point_0.y) * b.vector_x)) <
                EPSILON;
        }
        else {
            return (false);
        }
    }

    bool operator!=(const Line& b) {
        return (!(*this == b));
    }

    double give_vx() const {
        return (vector_x);
    }

    double give_vy() const {
        return (vector_y);
    }

    double give_px() const {
        return (point_0.x);
    }

    double give_py() const {
        return (point_0.y);
    }

    Point give_p() const {
        return (point_0);
    }

    VECTOR give_normal() const {
        VECTOR now;
        now.x = -vector_y;
        now.y = vector_x;
        return (now);
    }
};

template<class T>
bool equality_of_arrays(const std::vector<T> a, const std::vector<T> b) {
    bool status = false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[0] == b[i] && !status) {
            bool status1 = true;
            bool status2 = true;
            size_t k1 = 0;
            size_t k2 = 0;
            for (size_t j = (i + 1) % a.size(); k1 < a.size() - 1; ++j) {
                if (a[1 + k1] != b[(j) % (a.size())]) {
                    status1 = false;
                    break;
                }
                ++k1;
            }
            for (int j = static_cast<int>(i - 1); k2 < a.size() - 1; --j) {
                if (j == -1) {
                    j = a.size() - 1;
                }
                if (a[1 + k2] != b[(j) % (a.size())]) {
                    status2 = false;
                    break;
                }
                ++k2;
            }
            if (status1 || status2) {
                status = true;
            }
        }
    }
    return (status);
}

void my_rotate(Point& a, Point b, double z) {
    double& x = a.x;
    double& x0 = b.x;
    double& y = a.y;
    double& y0 = b.y;
    double c = z / 180 * PI;
    double x_now = x0 + (x - x0) * cos(c) - (y - y0) * sin(c);
    y = y0 + (y - y0) * cos(c) + (x - x0) * sin(c);
    x = x_now;
}

void my_rotateRADIAN(Point& a, Point b, double z) {
    double& x = a.x;
    double& x0 = b.x;
    double& y = a.y;
    double& y0 = b.y;
    double& c = z;
    double x_now = x0 + (x - x0) * cos(c) - (y - y0) * sin(c);
    y = y0 + (y - y0) * cos(c) + (x - x0) * sin(c);
    x = x_now;
}

void my_reflexp(Point& F1, Point center) {
    F1.x = 2 * center.x - F1.x;
    F1.y = 2 * center.y - F1.y;
}

void my_reflexl(Point& F1, Line axis) {
    VECTOR n, r0;
    n.x = -axis.give_vy();
    n.y = axis.give_vx();
    r0 = from_point_to_VECTOR(axis.give_p());
    double d = Scalar_product(r0, n);
    double k = 2 * (d - Scalar_product(n, from_point_to_VECTOR(F1))) / (Scalar_product(n, n));
    double x, y;
    x = F1.x + k * n.x;
    y = F1.y + k * n.y;
    F1.x = x;
    F1.y = y;
}


Point
Inter_line(const double& A1, const double& B1, const double& C1, const double& A2, const double& B2, const double& C2) {
    double DET = A1 * B2 - B1 * A2;
    double x = (-C1 * B2 + B1 * C2) / DET;
    double y = (-A1 * C2 + A2 * C1) / DET;
    return (Point(x, y));
}

class Shape {
public:
    virtual double perimeter() const = 0;

    virtual double area() const = 0;

    virtual bool operator==(const Shape& another) const = 0;

    virtual bool operator!=(const Shape& another) const = 0;

    virtual bool isCongruentTo(const Shape& another) const = 0;

    virtual bool isSimilarTo(const Shape& another) const = 0;

    virtual bool containsPoint(Point point) const = 0;

    virtual void rotate(Point center, double angle) = 0;

    virtual void reflex(Point center) = 0;

    virtual void reflex(Line axis) = 0;

    virtual void scale(Point center, double coefficient) = 0;

    virtual ~Shape() {};
};


class Ellipse : public Shape {
private:
    Point F1;
    Point F2;
    double s;//s=2*a
    double b;
    double c;
    double e = 0;
protected:
    double a;
public:
    Ellipse(Point a1, Point b1, double c1) {
        F1 = a1;
        F2 = b1;
        s = c1;//s=2*a
        a = c1 / 2;
        c = Distance(a1, b1) / 2;
        b = sqrt(a * a - c * c);
    }

    double perimeter() const override {
        return (PI * (3 * (a + b) - sqrt((3 * a + b) * (a + 3 * b))));
    }

    double area() const override {
        return (a * b*PI);
    }

    bool operator==(const Shape& another) const override {
        bool status = false;
        try {
            const Ellipse& my_b = dynamic_cast<const Ellipse&>(another);
            std::pair<Point, Point> FOCUSES = my_b.focuses();
            if ((F1 == FOCUSES.first && F2 == FOCUSES.second) || (F2 == FOCUSES.first && F1 == FOCUSES.second)) {
                if (std::abs(s - my_b.give_s()) < EPSILON) {
                    status = true;
                }
            }
        }
        catch (...) {
        }
        return (status);
    }

    bool operator!=(const Shape& another) const override {
        return (!(*this == another));
    }

    bool isCongruentTo(const Shape& another) const override {
        bool status = false;
        try {
            const auto& my_b = dynamic_cast<const Ellipse&>(another);
            double k = s / my_b.give_s();
            auto FOCUSES = my_b.focuses();
            double k1 = Distance(F1, F2) / (Distance(FOCUSES.first, FOCUSES.second));
            if ((std::abs(k1 - 1) < EPSILON) && (std::abs(k - 1) < EPSILON)) {
                status = true;
            }
        }
        catch (...) {

        }
        return (status);
    }

    bool isSimilarTo(const Shape& another) const override {
        bool status = false;
        try {
            const auto& my_b = dynamic_cast<const Ellipse&>(another);
            double k = s / my_b.give_s();
            auto FOCUSES = my_b.focuses();
            double k1 = Distance(F1, F2) / (Distance(FOCUSES.first, FOCUSES.second));
            if (std::abs(k1 - k) < EPSILON) {
                status = true;
            }
        }
        catch (...) {

        }
        return (status);
    }

    bool containsPoint(const Point point) const override {
        double s1 = Distance(point, F1) + Distance(point, F2);
        return s1 <= s;
    }

    void rotate(const Point center, const double angle) override {
        my_rotate(F1, center, angle);
        my_rotate(F2, center, angle);
    }

    void reflex(const Point center) override {
        my_reflexp(F1, center);
        my_reflexp(F2, center);
    }

    void reflex(const Line axis) override {
        my_reflexl(F1, axis);
        my_reflexl(F2, axis);
    }

    void scale(const Point center, const double coefficient) override {
        F1.x = (F1.x - center.x) * coefficient + center.x;
        F1.y = (F1.y - center.y) * coefficient + center.y;
        F2.x = (F2.x - center.x) * coefficient + center.x;
        F2.y = (F2.y - center.y) * coefficient + center.y;
        s *= std::abs(coefficient);
        a = s / 2;
        c = Distance(F1, F2) / 2;
        b = sqrt(a * a - c * c);
    }

    std::pair<Point, Point> focuses() const {
        return { F1, F2 };
    }

    double eccentricity() {
        return (c / a);
    }

    Point center() {
        Point now;
        now.x = (F1.x + F2.x) / 2;
        now.y = (F1.y + F2.y) / 2;
        return (now);
    }

    double give_s() const {
        return (s);
    }

    std::pair<Line, Line> directrices() {
        Point nowR(a / eccentricity(), 0);
        Point nowL(-a / eccentricity(), 0);
        nowR.x += center().x;
        nowR.y += center().y;
        nowL.x += center().x;
        nowL.y += center().y;
        Line Between_focus(F1, F2);
        VECTOR between_focus = Between_focus.give_normal();
        if (F2.x < F1.x) {
            Point F3 = F2;
            F2 = F1;
            F1 = F3;
        }
        Point o(0, 0);
        my_rotateRADIAN(nowR, o, atan(F2.y / F2.x));
        my_rotateRADIAN(nowL, o, atan(F2.y / F2.x));
        Line first = Line(nowR, between_focus);
        Line second = Line(nowL, between_focus);
        return { first, second };
    }
};

class Circle : public Ellipse {
public:
    Circle(Point a1, double R) : Ellipse(a1, a1, 2 * R) {
    }

    double radius() {
        return (a);
    }
};

class Polygon : public Shape {
protected:
    std::vector<Point> vertices;
public:
    void f() {}

    template<typename Head, typename... Tail>
    void f(Head x, Tail... t) {
        vertices.push_back(x);
        if (sizeof...(t) > 0) {
            f(t...);
        }
    }

    template<typename... Tail>
    Polygon(Tail... t) {
        f(t...);
    }

    Polygon(std::vector<Point> s) {
        vertices = s;
    }

    double perimeter() const override {
        double sum = 0;
        for (size_t i = 0; i < vertices.size() - 1; ++i) {
            sum += Distance(vertices[i], vertices[i + 1]);
        }
        sum += Distance(vertices[vertices.size() - 1], vertices[0]);
        return (sum);
    }

    double area() const override {
        double sum = 0;
        for (size_t i = 0; i < vertices.size() - 1; ++i) {
            sum += vertices[i].x * vertices[i + 1].y;
        }
        sum += vertices[vertices.size() - 1].x * vertices[0].y;
        sum -= vertices[vertices.size() - 1].y * vertices[0].x;
        for (size_t i = 0; i < vertices.size() - 1; ++i) {
            sum -= vertices[i].y * vertices[i + 1].x;
        }
        return (std::abs(sum) / 2);

    }

    bool operator==(const Shape& another) const override {
        bool status = false;
        try {
            const auto& my_b = dynamic_cast<const Polygon&>(another);
            if (vertices.size() == my_b.verticesCount()) {
                std::vector<Point> v = my_b.getVertices();
                status = equality_of_arrays(vertices, v);
            }
        }
        catch (...) {

        }
        return (status);
    }

    bool operator!=(const Shape& another) const override {
        return (!(*this == another));
    }

    bool isCongruentTo(const Shape& another) const override {
        bool status = false;
        try {
            const auto& my_b = dynamic_cast<const Polygon&>(another);
            if (isSimilarTo(another)) {
                std::vector<Point> v = my_b.getVertices();
                status = equality_of_arrays(Distance_from_vertex(v), Distance_from_vertex(vertices));
            }
        }
        catch (...) {

        }
        return (status);
    }

    bool isSimilarTo(const Shape& another) const override {
        bool status = false;
        try {
            const auto& my_b = dynamic_cast<const Polygon&>(another);
            if (vertices.size() == my_b.verticesCount()) {
                std::vector<Point> v = my_b.getVertices();
                status = equality_of_arrays(Corner_from_vertex(vertices), Corner_from_vertex(v));
            }
        }
        catch (...) {
        }
        return (status);
    }

    bool containsPoint(const Point point) const override {
        bool status = false;
        double min_x = vertices[0].x;
        double max_x = min_x;
        double min_y = vertices[0].y;
        double max_y = min_y;
        for (size_t i = 1; i < vertices.size(); ++i) {
            if (min_x > vertices[i].x) {
                min_x = vertices[i].x;
            }
            if (max_x < vertices[i].x) {
                max_x = vertices[i].x;
            }
            if (min_y > vertices[i].y) {
                min_y = vertices[i].y;
            }
            if (max_y < vertices[i].y) {
                max_y = vertices[i].y;
            }
        }
        if (!((point.y < min_y || point.y > max_y) || (point.x < min_x || point.x > max_x))) {
            for (size_t i = 0; i < vertices.size() - 1; ++i) {
                if (std::min(vertices[i].y, vertices[i + 1].y) <= point.y && point.y <
                    std::max(vertices[i].y,
                        vertices[i + 1].y) &&
                        (std::max(vertices[i].y, vertices[i + 1].y) != std::min(vertices[i].y, vertices[i + 1].y))) {
                    double d = (vertices[i + 1].x - vertices[i].x) * (point.y - vertices[i].y) /
                        (vertices[i + 1].y - vertices[i].y) + vertices[i].x - point.x;
                    if (0 < d) {
                        status = !status;
                    }
                }
            }
            size_t end = vertices.size() - 1;
            if (std::min(vertices[end].y, vertices[0].y) <= point.y &&
                point.y < std::max(vertices[end].y, vertices[0].y) &&
                (std::max(vertices[end].y, vertices[0].y) != std::min(vertices[end].y, vertices[0].y))) {
                double d = (vertices[0].x - vertices[end].x) * (point.y - vertices[end].y) /
                    (vertices[0].y - vertices[end].y) + vertices[end].x - point.x;
                if (0 < d) {
                    status = !status;
                }
            }
        }
        return (status);
    }

    void rotate(const Point center, const double angle) override {
        for (size_t i = 0; i < vertices.size(); ++i) {
            my_rotate(vertices[i], center, angle);
        }
    }

    void reflex(const Point center) override {
        for (size_t i = 0; i < vertices.size(); ++i) {
            my_reflexp(vertices[i], center);
        }
    }

    void reflex(const Line axis) override {
        for (size_t i = 0; i < vertices.size(); ++i) {
            my_reflexl(vertices[i], axis);
        }
    }

    void scale(const Point center, const double coefficient) override {
        for (size_t i = 0; i < vertices.size(); ++i) {
            vertices[i].x = (vertices[i].x - center.x) * coefficient + center.x;
            vertices[i].y = (vertices[i].y - center.y) * coefficient + center.y;
        }
    }

    size_t verticesCount() const {
        return (vertices.size());
    }

    std::vector<Point> getVertices() const {
        return (vertices);
    }

    bool isConvex() {
        bool status = true;
        bool povorot_napravlenie = Vector_product(VECTOR(vertices[0], vertices[1]), VECTOR(vertices[1], vertices[2]));
        for (size_t i = 1; i < vertices.size() - 1; ++i) {
            if (i == vertices.size() - 2) {
                if (povorot_napravlenie !=
                    Vector_product(VECTOR(vertices[i], vertices[i + 1]), VECTOR(vertices[i + 1], vertices[0]))) {
                    status = false;
                }
            }
            else {
                if (povorot_napravlenie !=
                    Vector_product(VECTOR(vertices[i], vertices[i + 1]), VECTOR(vertices[i + 1], vertices[i + 2]))) {
                    status = false;
                }
            }
            if (!status) {
                break;
            }
        }
        return (status);
    }
};

class Rectangle : public Polygon {

public:
    Rectangle() {}

    Rectangle(Point a, Point b, double k) {
        vertices.resize(4);
        vertices[0] = a;
        vertices[2] = b;
        VECTOR diag(a, b);
        double L = Distance(a, b);
        double size_one_side = L / (sqrt(1 + k * k));
        if (k < 1) {
            size_one_side *= k;
        }
        diag.x = diag.x / L * size_one_side;
        diag.y = diag.y / L * size_one_side;
        Point Third_vertex;
        Third_vertex.x = a.x + diag.x;
        Third_vertex.y = a.y + diag.y;
        my_rotateRADIAN(Third_vertex, a, acos((size_one_side / L)));
        vertices[1] = Third_vertex;
        vertices[3] = Third_vertex;
        my_reflexp(vertices[3], center());
    }

    Point center() const {
        return (Point((vertices[0].x + vertices[2].x) / 2, (vertices[0].y + vertices[2].y) / 2));
    }

    std::pair<Line, Line> diagonals() const {
        return { Line(vertices[0], vertices[2]), Line(vertices[1], vertices[3]) };
    }

    std::vector<Point>& give_vertices() {
        return (vertices);
    }
};

class Square : public Rectangle {
public:
    std::vector<Point>& v = give_vertices();

    Square() {}

    Square(Point a, Point b) {
        v.resize(4);
        v[0] = a;
        v[2] = b;
        VECTOR diag(a, b);
        double L = Distance(a, b);
        double size_one_side = L / (sqrt(2));
        diag.x = diag.x / L * size_one_side;
        diag.y = diag.y / L * size_one_side;
        Point Third_vertex;
        Third_vertex.x = a.x + diag.x;
        Third_vertex.y = a.y + diag.y;
        my_rotate(Third_vertex, a, 45);
        v[1] = Third_vertex;
        v[3] = Third_vertex;
        my_reflexp(v[3], center());
    }

    Circle circumscribedCircle() {
        Circle now(center(), Distance(v[0], v[2]));
        return (now);
    }

    Circle inscribedCircle() {
        Circle now(center(), Distance(v[0], v[1]));
        return (now);
    }
};

class Triangle : public Polygon {
public:
    Triangle(Point a, Point b, Point c) {
        vertices.resize(3);
        vertices[0] = a;
        vertices[1] = b;
        vertices[2] = c;
    }

    Circle circumscribedCircle() const {
        double r = Distance(vertices[0], vertices[1]) * Distance(vertices[1], vertices[2]) *
            Distance(vertices[0], vertices[2]) / 4.0 / area();
        VECTOR tox2(vertices[0], vertices[2]);
        VECTOR tox1(vertices[0], vertices[1]);
        VECTOR from_x2 = give_normal_front_vector(tox2);
        VECTOR from_x1 = give_normal_front_vector(tox1);
        double x1 = tox1.x / 2 + vertices[0].x;
        double y1 = tox1.y / 2 + vertices[0].y;
        double x2 = tox2.x / 2 + vertices[0].x;
        double y2 = tox2.y / 2 + vertices[0].y;
        double A1 = from_x1.y;
        double B1 = -1 * from_x1.x;
        double C1 = -x1 * from_x1.y + from_x1.x * y1;
        double A2 = from_x2.y;
        double B2 = -1 * from_x2.x;
        double C2 = -x2 * from_x2.y + from_x2.x * y2;
        return (Circle(Inter_line(A1, B1, C1, A2, B2, C2), r));
    }

    Circle inscribedCircle() const {
        double r = 2 * area() / (Distance(vertices[0], vertices[1]) + Distance(vertices[2], vertices[1]) +
            Distance(vertices[0], vertices[2]));
        double k1 = Distance(vertices[0], vertices[1]) / Distance(vertices[0], vertices[2]);
        VECTOR CD(vertices[2], vertices[1]);
        CD.x /= (k1 + 1);
        CD.y /= (k1 + 1);
        Point D(CD.x + vertices[2].x, CD.y + vertices[2].y);

        double k2 = Distance(vertices[1], vertices[2]) / Distance(vertices[0], vertices[1]);
        VECTOR AE(vertices[0], vertices[2]);
        AE.x /= (k2 + 1);
        AE.y /= (k2 + 1);
        Point E(AE.x + vertices[0].x, AE.y + vertices[0].y);

        const double& x1 = vertices[0].x;
        const double& y1 = vertices[0].y;
        const double& x2 = vertices[1].x;
        const double& y2 = vertices[1].y;
        VECTOR from_x1 = VECTOR(D, vertices[0]);
        VECTOR from_x2 = VECTOR(E, vertices[1]);
        double A1 = from_x1.y;
        double B1 = -1 * from_x1.x;
        double C1 = -x1 * from_x1.y + from_x1.x * y1;
        double A2 = from_x2.y;
        double B2 = -1 * from_x2.x;
        double C2 = -x2 * from_x2.y + from_x2.x * y2;
        return (Circle(Inter_line(A1, B1, C1, A2, B2, C2), r));
    }

    Point centroid() const {
        double x = (vertices[0].x + vertices[1].x + vertices[2].x) / 3;
        double y = (vertices[0].y + vertices[1].y + vertices[2].y) / 3;
        return (Point(x, y));
    }

    Point orthocenter() const {
        const double& x1 = vertices[1].x;
        const double& y1 = vertices[1].y;
        const double& x2 = vertices[2].x;
        const double& y2 = vertices[2].y;
        VECTOR tox2(vertices[0], vertices[1]);
        VECTOR tox1(vertices[0], vertices[2]);
        VECTOR from_x2 = give_normal_front_vector(tox2);
        VECTOR from_x1 = give_normal_front_vector(tox1);
        double A1 = from_x1.y;
        double B1 = -1 * from_x1.x;
        double C1 = -x1 * from_x1.y + from_x1.x * y1;
        double A2 = from_x2.y;
        double B2 = -1 * from_x2.x;
        double C2 = -x2 * from_x2.y + from_x2.x * y2;
        double DET = A1 * B2 - B1 * A2;
        double x = (-C1 * B2 + B1 * C2) / DET;
        double y = (-A1 * C2 + A2 * C1) / DET;
        return (Point(x, y));
    }

    Line EulerLine() {
        return (Line(centroid(), orthocenter()));
    }

    Circle ninePointsCircle() const {
        double r = Distance(vertices[0], vertices[1]) * Distance(vertices[1], vertices[2]) *
            Distance(vertices[0], vertices[2]) / 8.0 / area();
        auto around_focus = circumscribedCircle().focuses();
        Point around = around_focus.first;
        VECTOR a(around, orthocenter());
        a.x /= 2.0;
        a.y /= 2.0;
        Point center_nine(a.x + around.x, a.y + around.y);
        return (Circle(center_nine, r));
    }
};
