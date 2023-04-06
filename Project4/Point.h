#pragma once
#include "Vector2D.h"
#include <iostream>
#include <string>
class Point
{
public: 
	float X, Y;
	Point(float X = 0, float Y = 0) :X(X), Y(Y){}
	inline Point operator+(const Point& p2) const {
		return Point(X + p2.X,Y + p2.Y);
	}
	inline friend Point operator+= (Point& p1, const Point& p2) {
		p1.X += p2.X;
		p1.Y += p2.Y;
		return p1;
	}
	inline Point operator-(const Point& p2) const {
		return Point(X - p2.X, Y - p2.Y);
	}
	inline friend Point operator-= (Point& p1, const Point& p2) {
		p1.X -= p2.X;
		p1.Y -= p2.Y;
		return p1;
	}
	inline Point operator*(const float temp) const {
		return Point(X* temp, Y* temp);

	}
	void log(std::string msg = "") {
		std::cout << msg << "(X Y) = (" << X << " " << Y << ")" << std::endl;
	}
};