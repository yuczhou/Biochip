/*
 * Coordinate.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef COORDINATE_H_
#define COORDINATE_H_
#include "Global.h"

namespace BioChip {

typedef int Position;
typedef int Capacity;
typedef int Direction;

template<class T>
struct CoordTemplate {
private:
	T array[3]; // as to make directions cheaply "indexable"

public:
	T& x;
	T& y;
	T& z;

	CoordTemplate() :
			x(array[0]), y(array[1]), z(array[2]) {
		x = y = z = 0;
	}
	CoordTemplate(T _x_, T _y_, T _z_) :
			x(array[0]), y(array[1]), z(array[2]) {
		x = _x_;
		y = _y_;
		z = _z_;
	}
	CoordTemplate(const CoordTemplate<T>& c) :
			x(array[0]), y(array[1]), z(array[2]) {
		x = c.x;
		y = c.y;
		z = c.z;
	}
	inline void add(const CoordTemplate<T>& c) {
		x += c.x;
		y += c.y;
		z += c.z;
	}
	inline T& operator ()(int i) {
		return array[i];
	}
	inline CoordTemplate& operator =(const CoordTemplate<T>& c) {
		x = c.x;
		y = c.y;
		z = c.z;
		return *this;
	}
	inline bool operator ==(const CoordTemplate<T>& c) const {
		return x == c.x && y == c.y && z == c.z;
	}
	inline bool operator !=(const CoordTemplate<T>& c) const {
		return !(*this == c);
	}
	inline bool operator <(const CoordTemplate<T>& c) const {
		if (x != c.x)
			return (x < c.x);
		if (y != c.y)
			return (y < c.y);
		if (z != c.z)
			return (z < c.z);
		return false;
	}
	inline bool operator >(const CoordTemplate<T>& c) const {
		if (x != c.x)
			return (x > c.x);
		if (y != c.y)
			return (y > c.y);
		if (z != c.z)
			return (z > c.z);
		return false;
	}
	inline Position operator -(const CoordTemplate<T>& c) const {
		return std::abs(x - c.x) + std::abs(y - c.y) + std::abs(z - c.z);
	}
	std::ostream& operator <<(std::ostream& os) const {
		os << "(" << x << "," << y << "," << z << ")";
		return os;
	}

	static CoordTemplate<T> origin;
};

template<class T>
std::ostream& operator <<(std::ostream& os, const CoordTemplate<T> & c) {
	os << "(" << c.x << "," << c.y << "," << c.z << ")";
	return os;
}

typedef CoordTemplate<Position> Coord;
typedef CoordTemplate<double> dblTriple;
template<class T> CoordTemplate<T> CoordTemplate<T>::origin(0, 0, 0);

}
#endif /* COORDINATE_H_ */
