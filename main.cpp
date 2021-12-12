#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <cstdlib>
#include <ctime>

using namespace std::chrono_literals;
using namespace std;

struct Point {
	long int x;

	long int y;
};

void PointsCoord(int n, Point** points, int* v) {

	srand(time(0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			points[i][j].x = j + 1 + rand() % 20;

			points[i][j].y = j + 1 + rand() % 20;

			v[i] = 1 + rand() % 5;
		}
	}

	for (int i = 0; i < n; i++) {
		int max0 = max(points[i][0].y, points[i][1].y);

		int max1 = max(points[i][1].y, points[i][2].y);

		int max3 = max(max0, max1);

		for (int j = i + 1; j < n; j++) {
			if (j == 1 + 1) {
				if (max3 > points[j][0].y)
					points[j][0].y += max3;
				if (max3 > points[j][1].y)
					points[j][1].y += max3;
				if (max3 > points[j][2].y)
					points[j][2].y += max3;

			}
		}
	}
}

void CorrectPoints(int n, Point** points) {
	for (int i = 0; i < n; i++) {
		if (((points[i][0].x == points[i][1].x) &&
			(points[i][0].y == points[i][1].y)) ||
			((points[i][1].x == points[i][2].x) && 
			(points[i][1].y == points[i][2].y)) ||
			((points[i][0].x == points[i][2].x) &&
			(points[i][0].y == points[i][2].y)) ||
			(points[i][0].x > 1000) || 
			(points[i][1].x > 1000) ||
			(points[i][2].x > 1000) ||
			(points[i][0].y > 1000) ||
			(points[i][1].y > 1000) ||
			(points[i][2].y > 1000)){

			points[i][0].x = 1;
			points[i][0].y = 1;
			points[i][1].x = 2;
			points[i][1].y = 5;
			points[i][2].x = 1;
			points[i][2].y = 5;

		}
	}
}

class Triangle {
public:

	Triangle(Point a, Point b, Point c, int v) {
		m_v = v;
		m_a = a;
		m_b = b;
		m_c = c;

		int max0 = max(a.x, b.x);
		int max1 = max(b.x, c.x);
		int max3 = max(max0, max1);

		m_posx = max3;

		if (max3 == a.x)
			m_posy = a.y;
		if (max3 == b.x)
			m_posy = b.y;
		if (max3 == c.x)
			m_posy = c.y;

		m_shape = new sf::ConvexShape;
		m_shape->setPointCount(3);
		m_shape->setOrigin(m_posx, m_posy);
		m_shape->setPosition(m_posx, m_posy);
		m_shape->setPoint(0, sf::Vector2f(m_a.x, m_a.y));
		m_shape->setPoint(1, sf::Vector2f(m_b.x, m_b.y));
		m_shape->setPoint(2, sf::Vector2f(m_c.x, m_c.y));
		m_shape->setFillColor(sf::Color::White);
	}

	~Triangle() {
		delete m_shape;
	}

	void ChangeSpeed(int v) {
		m_v = v;
	}

	void Move(Point a, Point b, Point c) {

		if (m_posx < 1000) {
			m_posx += m_v;
			m_shape->setPosition(m_posx, m_posy);
		}

		else {
			if (m_posx == m_a.x)
				m_a.x = 1000;
			if (m_posx == m_b.x)
				m_b.x = 1000;
			if (m_posx == m_c.x)
				m_c.x = 1000;
		}
	}

	void Stop() {
		if (m_a.x >= 1000)
			m_a.x = 1000;
		if (m_b.x >= 1000)
			m_b.x = 1000;
		if (m_c.x >= 1000)
			m_c.x = 1000;
	}

	int GetMax_X(Point a, Point b, Point c) {
		int max0 = max(m_a.x, m_b.x);
		int max1 = max(m_b.x, m_c.x);

		return max(max0, max1);
	}

	sf::ConvexShape* Get() {
		return m_shape;
	}

private:
	Point m_a;
	Point m_b;
	Point m_c;

	int m_v;
	int m_posx;
	int m_posy;

	sf::ConvexShape* m_shape;
};

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 700), L"Лаба №10 работает.");

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	const int n = 10;
	int* v;
	v = new int[n];

	Point** points;
	points = new Point * [n];

	for (int i = 0; i < n; i++)
		points[i] = new Point[3];

	PointsCoord(n, points, v);
	CorrectPoints(n, points);

	vector<Triangle*> triangles;

	for (int i = 0; i < n; i++)
		triangles.push_back(new Triangle(points[i][0], points[i][1], points[i][2], v[i]));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (int i = 0; i < n; i++)
			triangles[i]->Move(points[i][0], points[i][1], points[i][2]);

		window.clear();

		for (const auto& triangle : triangles)
			window.draw(*triangle->Get());

		window.display();
		this_thread::sleep_for(40ms);
	}

	for (int i = 0; i < n; i++)
		delete[] points[i];

	delete[] points;

	for (const auto& triangle : triangles)
		delete triangle;

	return 0;
}