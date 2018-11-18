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

template <typename T, int N>
class Vector {

public:
	//Standart Constructor
	Vector();
	Vector(T value);
	~Vector() {};
	//Copie Construcktor
	Vector(const Vector<T, N>& vec);

	std::size_t size() { return N; }

	T& operator[](std::size_t index) {
		if (index > N) {
			throw std::out_of_range("Indexüberschreitung!");
		}
		return elements[index];
	}

	const T& operator[](std::size_t index) const{
		if (index > N) {
			throw std::out_of_range("Indexüberschreitung!");
		}
		return elements[index];
	}

	T* begin() { return elements; }
	T* end() { return elements + N; }
	const T* begin() const { return elements; }
	const T* end() const { return elements + N; }

private:
	T elements[N];
};

template <typename T, int N>
Vector<T,N>::Vector() {
}

template <typename T, int N>
Vector<T, N>::Vector(T value)
	: Vector() {
	for (std::size_t i = 0; i < N; ++i) {
		elements[i] = value;
	}
}

template <typename T, int N>
Vector<T, N>::Vector(const Vector<T,N>& vec)
	: Vector() {
	for (std::size_t i = 0; i < N; ++i) {
		elements[i] = vec.elements[i];
	}
}
#endif