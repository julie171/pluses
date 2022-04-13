#include <iostream>

using namespace std;

class Figure {
public: 
	Figure(int w, int h) : h(h), w(w) {};
	int h;
	int w;
};

class Rectangle : public Figure {
public:
	Rectangle(int w, int h) : Figure(w, h) {};
	virtual int Area() const {
		return h * w;
	};
	virtual void Print() const {
		cout << "W:" << w << ", H:" << h << endl;
	};
	virtual void Draw() const {
		for (int i = 1; i <= h; ++i) {
			for (int j = 1; j <= w; ++j)
				cout << "#";
			cout << endl;
		}
	}
};

class Square: public Rectangle {
public: 
	Square(int a) : Rectangle (a, a) {};
	void Print() const {
		cout << "W:" << w << ", H:" << h <<endl;
	}
	void Draw() const {
		for (int i = 1; i <= h; ++i) {
			for (int j = 1; j <= h; ++j)
				cout << "#";
			cout << endl;
		}
	}
};

int main() {
	Square X(3);
	X.Draw();
	X.Print();
	Rectangle Y(2, 3);
	Y.Draw();
	Y.Print();
	return 0;
}