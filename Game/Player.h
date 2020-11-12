#pragma once


struct Player {
	Vector3D<float> pos;
	Vector3D<float> face;
	int id;
	int role;
	int status;

};

template <class T>
struct Vector3D {
	T x;
	T y;
	T z;

	Vector3D(T val1, T val2, T val3) {
		x = val1;
		y = val2;
		z = val3;
	}
};
