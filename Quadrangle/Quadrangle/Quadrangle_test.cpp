#include "Quadrangle.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void showPoint(Point p)
{
	cout << "(" << p.x << "; " << p.y << ")";
}

void showLine(Line l)
{
	cout << "(" << l.a << ")x + (" << l.b << ")y + (" << l.c << ") = 0";
}

void showSegment(Segment s)
{
	cout << "A(" << s.A.x << "; " << s.A.y << "), B(" << s.B.x << "; " << s.B.y << ")";
}

void inputLine(Line& l)
{
	cout << "Enter line coefficients:" << endl;
	cout << "a = ";
	cin >> l.a;
	cout << "b = ";
	cin >> l.b;
	cout << "c = ";
	cin >> l.c;
}

void inputSegment(Segment& s)
{
	cout << "Enter segment points:" << endl;
	cout << "A: x = ";
	cin >> s.A.x;
	cout << "A: y = ";
	cin >> s.A.y;
	cout << "B: x = ";
	cin >> s.B.x;
	cout << "B: y = ";
	cin >> s.B.y;
}

void inputRectangle(Rectangle& r)
{
	cout << "Enter A and C rectangle points:" << endl;
	cout << "A: x = ";
	cin >> r.A.x;
	cout << "A: y = ";
	cin >> r.A.y;
	do
	{
		cout << "C: x = ";
		cin >> r.C.x;
		cout << "C : y = ";
		cin >> r.C.y;
		if (r.C.x < r.A.x || r.C.y < r.A.y)
		{
			cout << "Point C must be heigter than point A. Try again." << endl;
		}
	} while (r.C.x < r.A.x || r.C.y < r.A.y);
}

void inputTrapeze(Trapeze& t)
{
	Point A, B, C, D;
	do{
		cout << "Enter trapeze top:" << endl;
		cout << "Top: A: x = ";
		cin >> A.x;
		cout << "Top: A,B: y = ";
		cin >> A.y;
		cout << "Top: B: x = ";
		cin >> B.x;
		B.y = A.y;
		t.SetTop(A, B);
		cout << "Enter trapeze bottom:" << endl;
		cout << "Bottom: C: x = ";
		cin >> C.x;
		cout << "Bottom: C,D: y = ";
		cin >> C.y;
		cout << "Bottom D: x = ";
		cin >> D.x;
		D.y = C.y;
		t.SetBottom(C, D);
		if (A.y <= C.y)
		{
			cout << "Wrong trapeze set. Try again." << endl;
		}
	} while (A.y <= C.y);
}

void inputTriangle(Triangle& t)
{
	cout << "Enter triangle top:" << endl;
	cout << "A: x = ";
	cin >> t.A.x;
	cout << "A: y = ";
	cin >> t.A.y;
	cout << "B: x = ";
	cin >> t.B.x;
	cout << "B: y = ";
	cin >> t.B.y;
	cout << "C: x = ";
	cin >> t.C.x;
	cout << "C: y = ";
	cin >> t.C.y;
}
void inputFromFile(Line& l1, Line& l2, Segment& s1, Segment& s2, Rectangle& r, Trapeze& t, Triangle& tr)
{
	ifstream f;
	f.open("input.txt", ios::out);
	string s;
	f >> s;
	f >> l1.a;
	f >> l1.b;
	f >> l1.c;
	f >> s;
	f >> l2.a;
	f >> l2.b;
	f >> l2.c;
	f >> s;
	f >> s1.A.x;
	f >> s1.A.y;
	f >> s1.B.x;
	f >> s1.B.y;
	f >> s;
	f >> s2.A.x;
	f >> s2.A.y;
	f >> s2.B.x;
	f >> s2.B.y;
	f >> s;
	f >> r.A.x;
	f >> r.A.y;
	f >> r.C.x;
	f >> r.C.y;
	f >> s;
	Point a, b;
	f >> a.x;
	f >> a.y;
	f >> b.x;
	f >> b.y;
	t.SetTop(a, b);
	f >> s;
	f >> a.x;
	f >> a.y;
	f >> b.x;
	f >> b.y;
	t.SetBottom(a, b);
	f >> s;
	f >> tr.A.x;
	f >> tr.A.y;
	f >> tr.B.x;
	f >> tr.B.y;
	f >> tr.C.x;
	f >> tr.C.y;

	// out

	/// перетин прямихl1 i l2
	cout << "Intersection ";
	showLine(l1);
	cout << " and ";
	showLine(l2);
	cout << endl;
	bool exist = false;
	showPoint(Intersection(l1, l2, exist));
	cout << endl;
	/// перетин відрізків s1 i s2

	cout << "Intersection ";
	showSegment(s1);
	cout << " and ";
	showSegment(s2);
	cout << endl;
	showPoint(Intersection(s1, s2,exist));
	cout << endl;
	// перетин відрізку s1 і прямої l1
	cout << "Intersection ";
	showSegment(s1);
	cout << " and ";
	showLine(l1);
	cout << endl;
	Point p = Intersection(s1, l1, exist);
	if (exist)
	{
		showPoint(p);
	}
	else
	{
		cout << "No intersections" << endl;
	}
	// Rectangle
	cout << endl;
	cout << "Rectangle area = " << Area(r) << endl;
	cout << "Rectangle perimeter = " << Perimeter(r) << endl;
	cout << "R = " << Radius(r) << endl;
	cout << "r = " << radius(r) << endl;
	cout << "Squares: ";
	Square(r, l1);
	// Trapeze
	
	cout << "Trapeze area = " << Area(t) << endl;
	cout << "Trapeze perimeter = " << Perimeter(t) << endl;
	cout << "R = " << Radius(t) << endl;
	cout << "r = " << radius(t) << endl;
	cout << "Squares: ";
	Square(t, l1);
	// Triangle
	Angle(tr);
	cout << "Squares: ";
	Square(tr, l1);
}

int inputMode()
{
	cout << "Choose input mode:\n1. Console\n2. File\n";
	int m;
	do{
		cin >> m;
		if (m == 1)
		{
			return 1;
		}
		else if (m == 2)
		{
			return 2;
		}
		else {
			cout << "Wrong mode. Try again" << endl;
		}
	} while (m != 1 || m != 2);
	return 0;
}

void main()
{
	int mode = inputMode();
	Line l1, l2;
	Segment s1, s2;
	Rectangle r;
	Trapeze t;
	Triangle tr;
	bool exist = false;
	if (mode == 1)
	{
		inputLine(l1);
		inputLine(l2);
		
		/// перетин прямихl1 i l2
		cout << "Intersection ";
		showLine(l1);
		cout << " and ";
		showLine(l2);
		cout << endl;
		showPoint(Intersection(l1, l2, exist));
		cout << endl;
		/// перетин відрізків s1 i s2
		inputSegment(s1);
		inputSegment(s2);
		cout << "Intersection ";
		showSegment(s1);
		cout << " and ";
		showSegment(s2);
		cout << endl;
		showPoint(Intersection(s1, s2, exist));
		cout << endl;
		// перетин відрізку s1 і прямої l1
		cout << "Intersection ";
		showSegment(s1);
		cout << " and ";
		showLine(l1);
		cout << endl;
		bool exist = true;
		Point p = Intersection(s1, l1, exist);
		if (exist)
		{
			showPoint(p);
		}
		else
		{
			cout << "No intersections" << endl;
		}
		// Rectangle
		cout << endl;

		inputRectangle(r);
		cout << "Rectangle area = " << Area(r) << endl;
		cout << "Rectangle perimeter = " << Perimeter(r) << endl;
		cout << "R = " << Radius(r) << endl;
		cout << "r = " << radius(r) << endl;
		cout << "Squares: ";
		Square(r, l1);
		// Trapeze
		

		inputTrapeze(t);
		cout << "Trapeze area = " << Area(t) << endl;
		cout << "Trapeze perimeter = " << Perimeter(t) << endl;
		cout << "R = " << Radius(t) << endl;
		cout << "r = " << radius(t) << endl;
		cout << "Squares: ";
		Square(t, l1);
		// Triangle

		inputTriangle(tr);
		Angle(tr);
		cout << "Squares: ";
		Square(tr, l1);
	}
	else if (mode == 2)
	{
		inputFromFile(l1, l2, s1, s2, r, t, tr);
	}
	system("pause");
}