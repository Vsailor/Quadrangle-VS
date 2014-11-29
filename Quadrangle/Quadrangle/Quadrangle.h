class Point
{
public:
	double x;
	double y;
	// �����������, ���� �������� ������ �������� ��������� ��� �������� ��'����
	Point(double a, double b)
	{
		x = a;
		y = b;
	}
	// ����������� �� �������������
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
	// ����� ��� �������
	Point A;
	// ������ ����� �������
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
	������ � ����� ������, �� ��������� ��������.
	ֳ ���� � ����������, ������� ���� ������� � ����� ����� �������� ���� ������
	������ Top, ���������, ��� �������� Y, �� �� ��� ���� �� ��������
	*/
	Segment Top;
	Segment Bottom;
public:
	// ������ ������ ������ ��������
	void SetTop(Point A, Point B)
	{
		if (A.y == B.y && A.x < B.x)
		{
			Top.A = A;
			Top.B = B;
		}
	}
	// ĳ����� ������ ������ ��������
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