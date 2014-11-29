class Point
{
public:
	double x;
	double y;
	// конструктор, який дозволяє швидко виконати присвоєння при створенні об'єкта
	Point(double a, double b)
	{
		x = a;
		y = b;
	}
	// конструктор за замовчуванням
	Point(){}
};

class Segment
{
public:
	Point A;
	Point B;
};

class Rectangle
{
public:
	// нижня ліва вершина
	Point A;
	// верхня права вершина
	Point C;
};

// ax+by+c=0
class Line
{
public:
	double a;
	double b;
	double c;
};

class Trapeze
{
private:
	/*
	Верхня і нижня основи, які задаються відрізками.
	Ці поля є приватними, оскільки якщо напряму з файлу тесту присвоїти двом точкам
	відрізку Top, наприклад, різні значення Y, то це вже буде не трапеція
	*/
	Segment Top;
	Segment Bottom;
public:
	// Задати верхню основу трапеції
	void SetTop(Point A, Point B)
	{
		if (A.y == B.y && A.x < B.x)
		{
			Top.A = A;
			Top.B = B;
		}
	}
	// Дістати верхню основу трапеції
	Segment GetTop()
	{
		return Top;
	}
	void SetBottom(Point A, Point B)
	{
		if (A.y == B.y && A.x < B.x)
		{
			Bottom.A = A;
			Bottom.B = B;
		}
	}
	Segment GetBottom()
	{
		return Bottom;
	}
};

class Triangle
{
public:
	Point A;
	Point B;
	Point C;
};


extern Point Intersection(Segment a, Segment b, bool& exist);
extern Point Intersection(Line a, Line b, bool& exist);
extern Point Intersection(Segment a, Line b, bool& exist);
extern double Area(Rectangle r);
extern double Area(Trapeze t);
extern double Perimeter(Rectangle r);
extern double Perimeter(Trapeze t);
extern double Radius(Rectangle r);
extern double Radius(Trapeze t);
extern double radius(Rectangle r);
extern double radius(Trapeze t);
extern void Angle(Triangle t);
extern void Square(Rectangle r, Line l);
extern void Square(Trapeze r, Line l);
extern void Square(Triangle r, Line l);