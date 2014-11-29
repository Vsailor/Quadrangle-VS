#include "Quadrangle.h"
#include <iostream>
using namespace std;


// Повертає 1, якщо відрізки ab і cd перетинаються
bool intersect(Segment a, Segment b, Point& p) {

	double x1 = a.A.x;
	double y1 = a.A.y;
	double x2 = a.B.x;
	double y2 = a.B.y;
	double x3 = b.A.x;
	double y3 = b.A.y;
	double x4 = b.B.x;
	double y4 = b.B.y;

	// прокції відрізків на осі
	double dx1 = x2 - x1;
	double dy1 = y2 - y1;
	double dx2 = x4 - x3;
	double dy2 = y4 - y3;

	p.x = dy1 * dx2 - dy2 * dx1;
	// відрізки не перетинаютсья
	if (p.x == 0)
		return false;
	
	p.y = x3 * y4 - y3 * x4;
	p.x = ((x1 * y2 - y1 * x2) * dx2 - p.y * dx1) / p.x;

	// якщо друга пряма не паралельна осі ОY
	if (dx2 != 0)
	{
		p.y = (dy2 * p.x - p.y) / dx2;
	}
	else {
		p.y = (x3 - x1)*(y2 - y1) / (x2 - x1) + y1;
	}

	if (
		((x1 <= p.x && x2 >= p.x) || (x2 <= p.x && x1 >= p.x)) && ((x3 <= p.x && x4 >= p.x) || (x4 <= p.x && x3 >= p.x))
		) {
		return true;
	}
	else return false;
}

Point Intersection(Segment a, Segment b, bool& exist)
{
	exist = true;
	Point p;
	if (intersect(a, b, p))
	{
		return p;
	}
	else {
		cout << "No intersections" << endl;
		exist = false;
	}
	return p;
}

Point Intersection(Line k, Line l, bool& exist)
{
	exist = true;
	Point p;
	if (l.a != 0 && l.b != 0 && k.a == l.a*k.b / l.b)
	{
		cout << "Lines are parallels" << endl;
		exist = false;
		return p;
	}
	else if (k.b == 0)
	{
		p.x = -k.c / k.a;
		p.y = (-l.c + l.a*(k.c / k.a)) / l.b;
		return p;
	}
	else
	{
		p.x = (-l.c + k.c*l.b / k.b) / (l.a - l.b*k.a / k.b);
		p.y = (-k.c - k.a*p.x) / k.b;
		return p;
	}
}

Point Intersection(Segment a, Line b, bool& exist)
{
	exist = true;
	Point p;
	// підставляємо кінці відрізку в рівняння прямої. Якщо по різні боки, то перетинаються
	if (
		(b.a*a.A.x + b.b*a.A.y + b.c >= 0 && b.a*a.B.x + b.b*a.B.y + b.c <= 0) ||
		(b.a*a.A.x + b.b*a.A.y + b.c <= 0 && b.a*a.B.x + b.b*a.B.y + b.c >= 0)
		)
	{
		// відрізок лежить на прямій y = a.B.y
		if (a.A.y == a.B.y)
		{
			Line l;
			l.a = 0;
			l.b = 1;
			l.c = -a.B.y;
			return Intersection(l, b, exist);
		}
		// відрізок не проходить перпендикулярно осі абсцис (загальний випадок)
		if (a.A.x != a.B.x)
		{
			double k = (a.B.y - a.A.y) / (a.B.x - a.A.x);
			double t = a.A.y - k*a.A.x;
			// -y + kx + b = 0
			Line l;
			l.a = -1;
			l.b = k;
			l.c = t;
			return Intersection(l, b, exist);
		}
		else
		{
			// відрізок перпендикулярний до осі абсцис
			if (b.b != 0) {
				p.x = a.A.x;
				p.y = -(b.a*p.x + b.c) / b.b;
				return p;
			}
			else
			{
				// відрізок і пряма співпадають
				exist = false;
				return p;
			}
		}
	}
	else
	{
		exist = false;
		// No intersections
		return p;
	}

}

// площа прямокутника
double Area(Rectangle r)
{
	double a, b;
	a = abs(r.C.x - r.A.x);
	b = abs(r.C.y - r.A.y);
	return a*b;
}

// площа трапеції
double Area(Trapeze t)
{
	double h = abs(t.GetTop().A.y - t.GetBottom().A.y);
	double a = abs(t.GetTop().B.x - t.GetTop().A.x);
	double b = abs(t.GetBottom().B.x - t.GetBottom().A.x);
	return h*(a + b) / 2;
}

double Perimeter(Rectangle r)
{
	double a = abs(r.C.x - r.A.x);
	double b = abs(r.C.y - r.A.y);
	return a*b;
}

double Perimeter(Trapeze t)
{
	double a, b, c, d;
	a = abs(t.GetTop().B.x - t.GetTop().A.x);
	b = abs(t.GetBottom().B.x - t.GetBottom().A.x);
	c = sqrt(pow((t.GetTop().B.x - t.GetBottom().B.x), 2) + pow((t.GetTop().B.y - t.GetBottom().B.y), 2));
	d = sqrt(pow((t.GetTop().A.x - t.GetBottom().A.x), 2) + pow((t.GetTop().A.y - t.GetBottom().A.y), 2));
	return a + b + c + d;
}

double Radius(Rectangle r)
{
	double a = abs(r.A.y - r.C.y);
	double b = abs(r.A.x - r.C.x);
	double d = sqrt(a*a + b*b);
	return d / 2;
}

double Radius(Trapeze t)
{
	double a, b, c, d;
	a = abs(t.GetTop().B.x - t.GetTop().A.x);
	b = abs(t.GetBottom().B.x - t.GetBottom().A.x);
	c = sqrt(pow((t.GetTop().B.x - t.GetBottom().B.x), 2) + pow((t.GetTop().B.y - t.GetBottom().B.y), 2));
	d = sqrt(pow((t.GetTop().A.x - t.GetBottom().A.x), 2) + pow((t.GetTop().A.y - t.GetBottom().A.y), 2));
	if (c == d)
	{
		double diagonal = sqrt(pow((t.GetTop().B.x - t.GetBottom().A.x), 2) + pow((t.GetTop().B.y - t.GetBottom().A.y), 2));
		double p = (b + c + diagonal) / 2;
		return a*b*c / (4 * sqrt(p*(p - c)*(p - diagonal)*(p - b)));
	}
	else
	{
		cout << "Trapeze isn't isosceles" << endl;
		return 0;
	}
}

double radius(Rectangle r)
{
	double a = abs(r.A.y - r.C.y);
	double b = abs(r.A.x - r.C.x);
	if (a == b)
	{
		return a / 2;
	}
	else {
		cout << "Rectangle isn't isosceles" << endl;
		return 0;
	}
}

double radius(Trapeze t)
{
	double a, b, c, d;
	a = abs(t.GetTop().B.x - t.GetTop().A.x);
	b = abs(t.GetBottom().B.x - t.GetBottom().A.x);
	c = sqrt(pow((t.GetTop().B.x - t.GetBottom().B.x), 2) + pow((t.GetTop().B.y - t.GetBottom().B.y), 2));
	d = sqrt(pow((t.GetTop().A.x - t.GetBottom().A.x), 2) + pow((t.GetTop().A.y - t.GetBottom().A.y), 2));
	if (a + b == c + d)
	{
		return abs(t.GetTop().A.y - t.GetBottom().A.y)/2;
	}
	else
	{
		cout << "Can not inscribe a circle" << endl;
		return 0;
	}
}

void Angle(Triangle t)
{
	double a = sqrt(pow((t.B.x - t.A.x), 2) + pow((t.B.y - t.A.y), 2));
	double b = sqrt(pow((t.B.x - t.C.x), 2) + pow((t.B.y - t.C.y), 2));
	double c = sqrt(pow((t.C.x - t.A.x), 2) + pow((t.C.y - t.A.y), 2));
	cout << "alpha = " << (180 / 3.14)*acos((b*b + c*c - a*a) / (2 * b*c)) << endl;
	cout << "beta = " << (180 / 3.14)*acos((a*a + b*b - c*c) / (2 * a*b)) << endl;
	cout << "gamma = " << (180 / 3.14)*acos((a*a + c*c - b*b) / (2 * a*c)) << endl;
}

void Square(Rectangle r, Line l)
{
	Point A, B, C, D;
	A = r.A;
	C = r.C;
	B.x = A.x;
	B.y = C.y;
	D.x = C.x;
	D.y = A.y;
	Segment a, b, c, d;
	a.A = A;
	a.B = B;
	b.A = B;
	b.B = C;
	c.A = C;
	c.B = D;
	d.A = A;
	d.B = D;
	bool e1;
	bool e2;
	bool e3;
	bool e4;
	Point i1 = Intersection(a, l, e1);
	Point i2 = Intersection(b, l, e2);
	Point i3 = Intersection(c, l, e3);
	Point i4 = Intersection(d, l, e4);
	// одна з площ
	double area;
	if (e1 == true || e2 == true || e3 == true || e4 ==true)
	{
		if (e1 && e2)
		{
			area = 0.5*(abs(B.x - i2.x))*(abs(B.y - i1.y));
		}
		if (e1 && e3)
		{
			area = (abs(B.x - C.x))*(abs(C.y - i3.y) + abs(B.y - i1.y)) / 2;
		}
		if (e1 && e4)
		{
			area = 0.5*(abs(i1.y - A.y))*(abs(i4.x - A.x));
		}
		if (e2 && e3)
		{
			area = 0.5*(abs(C.x - i2.x))*(abs(C.y - i3.y));
		}
		if (e2 && e4)
		{
			area = (abs(B.y - A.y))*(abs(B.x - i2.x) + abs(A.x - i4.x)) / 2;
		}
		if (e3 && e4)
		{
			area = 0.5*(abs(i3.y - D.y))*(abs(D.x - i4.x));
		}
		cout << area << " and " << Area(r) - area << endl;
	}
	else
	{
		cout << "No intersections" << endl;
	}
}

double P(double a, double b, double c)
{
	return (a + b + c);
}

double Distance(Point a, Point b)
{
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

double S(Point a, Point b, Point c)
{
	double p = P(Distance(a, b), Distance(b, c), Distance(a, c)) / 2;
	return sqrt(p*(p - Distance(a, b))*(p - Distance(b, c))*(p - Distance(a, c)));
}

void Square(Trapeze r, Line l)
{
	Point A, B, C, D;
	A = r.GetBottom().A;
	C = r.GetTop().B;
	B = r.GetTop().A;
	D = r.GetBottom().B;
	Segment a, b, c, d;
	a.A = A;
	a.B = B;
	b.A = B;
	b.B = C;
	c.A = C;
	c.B = D;
	d.A = A;
	d.B = D;
	bool e1;
	bool e2;
	bool e3;
	bool e4;
	Point i1 = Intersection(a, l, e1);
	Point i2 = Intersection(b, l, e2);
	Point i3 = Intersection(c, l, e3);
	Point i4 = Intersection(d, l, e4);
	// одна з площ
	double area;
	if (e1 == true || e2 == true || e3 == true || e4 == true)
	{
		if (e1 && e2)
		{
			area = Area(r) - S(i1, B, i2);
		}
		if (e1 && e3)
		{
			// Розбиваємо чотирикутник на два трикутники і трапецію
			area = 0.5*(abs(i1.y - A.y))*abs(i1.x - A.x) + 0.5*(abs(i3.y - D.y))*abs(i3.x - D.x) + (abs(i3.x - i1.x))*(abs(i3.y - D.y) + abs(i1.y - A.y)) / 2;
		}
		if (e1 && e4)
		{
			area = Area(r) - S(i1, A, i4);
		}
		if (e2 && e3)
		{
			area = Area(r) - S(i2, C, i3);
		}
		if (e2 && e4)
		{
			area = (abs(B.x - i2.x) + abs(A.x - i4.x))*0.5*abs(B.y - A.y);
		}
		if (e3 && e4)
		{
			area = Area(r) - S(i3, D, i4);
		}
		cout << area << " and " << Area(r) - area << endl;
	}
	else
	{
		cout << "No intersections" << endl;
	}

}

void Square(Triangle r, Line l)
{
	bool e1;
	bool e2;
	bool e3;
	Segment s1, s2, s3;
	s1.A = r.A;
	s1.B = r.B;
	s2.A = r.B;
	s2.B = r.C;
	s3.A = r.A;
	s3.B = r.C;
	Point i1 = Intersection(s1, l, e1);
	Point i2 = Intersection(s2, l, e2);
	Point i3 = Intersection(s3, l, e3);
	double area = 0;
	if (e1 == true || e2 == true || e3 == true) 
	{
		if (e1 && e2)
		{
			area = S(i1, i2, r.B);
		}
		if (e1 && e3)
		{
			area = S(i1, i3, r.A);
		}
		if (e2 && e3)
		{
			area = S(i2, i3, r.C);
		}
		cout << S(r.A, r.B, r.C) - area << " and " << area << endl;
	}
	else
	{
		cout << "No intersections" << endl;
	}
}