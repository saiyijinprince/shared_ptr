#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include "ref_counter.h"

template <class T>
class shared_ptr {
public:
	shared_ptr();
	shared_ptr(T* p);
	shared_ptr(const shared_ptr<T>& p);
	shared_ptr& operator=(const shared_ptr<T>& p);

	~shared_ptr();

	T* operator->();
	T& operator*();

	void reset();
	void reset(T* p);
private:
	T* _ptr;
	ref_counter* _ref;
};

template <class T> 
shared_ptr<T>::shared_ptr()
	: _ptr(nullptr),
	  _ref(new ref_counter())
{}

template <class T> 
shared_ptr<T>::shared_ptr(T* ptr)
	: _ptr(ptr),
	  _ref(new ref_counter())
{
	_ref->increment();
}

template <class T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& p) 
{
	_ptr = p._ptr;
	_ref = p._ref;
	_ref->increment();
}

template <class T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& p)
{
	if (this == &p) 
		return *this;

	//Handle what the current pointer is pointing to by decrementing and if necessary, deleting, 
	//and then assign the new shared_ptr to this one.
	if (_ref->count() > 0 && _ref->decrement() == 0){
		delete _ptr;
		delete _ref;
	}

	_ptr = p._ptr;
	_ref = p._ref;
	_ref->increment();

	return *this;
}

template <class T> 
shared_ptr<T>::~shared_ptr()
{
	if (_ref->decrement() == 0){
		delete _ptr;
		_ptr = nullptr;

		delete _ref;
		_ref = nullptr;
	}
}

template <class T>
T* shared_ptr<T>::operator->()
{
	return _ptr;
}

template <class T>
T& shared_ptr<T>::operator*()
{
	return *_ptr;
}

#endif /* SHARED_PTR_H */