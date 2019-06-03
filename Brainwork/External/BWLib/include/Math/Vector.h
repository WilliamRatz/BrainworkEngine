//
//  Vector.h
//  MathLibery
//
//  Created by William Ratz on 18.09.18.
//  Copyright © 2018 William Ratz. All rights reserved.
//
#ifndef Vector_H
#define Vector_H

#include <stdexcept>
#include <iostream>

#define typeVector template <typename T, std::size_t N>

typeVector class Vector {

private:
	T elements[N];

public:
	Vector();
	Vector(T value);
	Vector(const Vector<T, N>& vec);
	~Vector() {};

	std::size_t size() { return N; }

	T& operator[](const std::size_t index) {
		if (index >= N) {
			throw std::out_of_range("Index out of Range");
		}
		return elements[index];
	}

	const T& operator[](const std::size_t index) const{
		if (index > N) {
			throw std::out_of_range("Index out of Range");
		}
		return elements[index];
	}
};

typeVector Vector<T,N>::Vector() {
	for (std::size_t i = 0; i < N; ++i) {
		elements[i] = NULL;
	}
}

typeVector Vector<T, N>::Vector(T value)
	{
	for (std::size_t i = 0; i < N; ++i) {
		elements[i] = value;
	}
}

typeVector Vector<T, N>::Vector(const Vector<T,N>& vec)
	{
	for (std::size_t i = 0; i < N; ++i) {
		elements[i] = vec.elements[i];
	}
}
#endif