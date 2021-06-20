#pragma once
#include <string>
#include <typeinfo>
#include <iostream>

template <typename T>
class MyVector {	
	size_t m_size = 1;
	size_t m_index = 0;
	T* m_ptr = nullptr;
	
public:
	//desturctor
	~MyVector() {
		if (m_size > 0) {
			if(m_ptr) delete[] m_ptr;
			m_ptr = nullptr;
		}
		else
			m_ptr = nullptr;
	}
	//constructor
	MyVector(size_t size)	{
		m_index = 0;
		if (size > 1) {
			m_size = size;
			memoryAllction(m_size);
		}
	}
	//Insert a data on last array
	int push(T& data) {
		if ((&data) && (m_index < m_size)) {
			m_ptr[m_index] = data;
			if (m_index < (m_size - 1))
				m_index++;
			return 0;
		}
		else return -1;

	}
	//delete a data on last array
	int pop() {
		if(m_index < m_size) {
			m_ptr[m_index] = NULL;
			m_index--;
			return 0;
		}
		else return -1;
	}
	// copy constructor
	MyVector(MyVector& ptr) {
		this = ptr;
	}
	// copy assignment
	MyVector& operator=(MyVector& mVec)  {
		if (this != &mVec) {
			m_size = mVec.size();
			m_index = mVec.index();

			if (m_ptr != nullptr) delete[] m_ptr;
			if (m_size > 1) {
				m_ptr = new T[m_size];

				for (size_t i = 0; i < m_index; i++)
					m_ptr[i] = mVec[i];
			}
			else
				m_ptr = mVec.address();			
		}
		return *this;
	}
	// Move Contructor
	MyVector(MyVector&& ptr) noexcept {
		*this = std::move(ptr);
	}
	// Move Operator
	MyVector& operator=(MyVector&& mptr) noexcept {
		if (this != &mptr) {
			if (m_ptr != nullptr)	delete m_ptr;
			else if (m_size == 0) m_ptr = nullptr;
			m_ptr = mptr.m_ptr;
			m_size = mptr.m_size;

			mptr.m_ptr = nullptr;
			mptr.m_size = 0;
		}
		return *this;
	}
	// allocate memory
	void memoryAllction(size_t size) {
		if (m_ptr) delete m_ptr;
		if (size > 0) {
			m_ptr = new T[size];
			if (!m_ptr) throw "Error: failed to allocate memory";
		}
	}
	// resize memory 
	bool resize(size_t newSize) {
		bool isResizedPointer = false;
		T* temp = nullptr;
		
		if (newSize == 0) throw "Error: failed to resized memory";
		else {
			temp = new T[m_size];
			m_index = 0;
			
			if (m_size == 0)
				temp = m_ptr;
			else {
				for (size_t i = 0; i < m_size; i++)
					temp[i] = m_ptr[i];
			}

			memoryAllction(newSize);
			if (newSize <= m_size) {
				m_index = newSize;
				for (size_t j = 0; j < newSize; j++)
					m_ptr[j] = temp[j];
			}
			else {
				m_index = m_size;
				for (size_t k = 0; k < m_size; k++)
					m_ptr[k] = temp[k];
			}
			m_size = newSize;
			if(temp) delete[] temp;
		}
		
		return isResizedPointer;
	}
	/*T& operator + (const T t1, const T t2) {
		return t1 + t2;
	}*/
	//get a value
	T val() {	return *m_ptr;	}
	size_t size() {	return m_size;	}
	size_t index() { return m_index; }
	T* address() { return m_ptr; }
	T& operator[] (size_t index) {
		if (m_size > index)		return m_ptr[index];
		else	throw "Error: This pointer has an only one data.";
	}
	
};



