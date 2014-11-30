#ifndef REF_COUNTER_H
#define REF_COUNTER_H

class ref_counter {
public:

	ref_counter();
	~ref_counter();

	void  increment() 
	{
		++_count;
	}

	int decrement()
	{
		return --_count;
	}

	const int& count() const { return _count; }

private:
	int _count;
};

ref_counter::ref_counter()
	: _count(0)
{}

ref_counter::~ref_counter() {}


#endif /* REF_COUNTER_H */