#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>

template <typename T>
class Vector
{
public:
	class ConstIterator;
	class Iterator;

	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type &;
	using const_reference = const value_type &;
	using pointer = value_type *;
	using const_pointer = const value_type *;
	using iterator = Vector::Iterator;
	using const_iterator = Vector::ConstIterator;

private:
	size_type sz;
	size_type max_sz;
	value_type *values;

	void allocate(size_type n)
	{
		if (n < sz)
			return;
		value_type *help = new value_type[n];
		for (size_t i{0}; i < sz; ++i)
			help[i] = values[i];
		delete[] values;
		values = help;
		max_sz = n;
	}

public:
	Vector(size_type n = 5) : sz{0}, max_sz{n}, values{max_sz ? new value_type[max_sz] : nullptr} {}
	Vector(std::initializer_list<value_type> init_list)
	{
		sz = init_list.size();
		max_sz = sz;
		values = new value_type[max_sz];
		size_t index = 0;
		for (auto value : init_list)
			values[index++] = value;
	}
	Vector(const Vector &cpy) : Vector(cpy.max_sz)
	{
		for (size_t i{0}; i < cpy.sz; ++i)
			values[i] = cpy.values[i];
		sz = cpy.sz;
	}
	~Vector()
	{
		delete[] values;
	}

	size_type size() const
	{
		return sz;
	}

	bool empty() const
	{
		if (sz == 0)
			return true;
		return false;
	}

	void clear()
	{
		value_type *help = new value_type[max_sz];
		delete[] values;
		values = help;
		sz = 0;
	}

	void reserve(size_type n)
	{
		allocate(n);
	}

	void shrink_to_fit()
	{
		value_type *help = new value_type[sz];
		for (size_t i{0}; i < sz; ++i)
			help[i] = values[i];
		delete[] values;
		values = help;
		max_sz = sz;
	}

	void push_back(value_type x)
	{
		if (sz == max_sz)
			allocate(2 * max_sz + 1);
		values[sz++] = x;
	}

	void pop_back()
	{
		if (sz == 0)
			throw std::runtime_error("Empty Vector");
		--sz;
	}

	value_type &operator[](size_type index)
	{
		if (index >= sz)
			throw std::runtime_error("out of bounds 1");
		return values[index];
	}
	const value_type &operator[](size_type index) const
	{
		if (index >= sz)
			throw std::runtime_error("out of bounds 2");
		return values[index];
	}

	size_type capacity() const
	{
		return max_sz;
	}

	Vector &operator=(Vector other)
	{
		std::swap(sz, other.sz);
		std::swap(max_sz, other.max_sz);
		std::swap(values, other.values);
		return *this;
	}

	friend std::ostream &operator<<(std::ostream &o, const Vector &v)
	{
		o << "[";
		bool first = true;
		for (size_t i = 0; i < v.size(); ++i)
		{
			if (first)
				first = false;
			else
				o << ",";
			o << v.values[i];
		}
		o << "]";

		return o;
	}

	iterator begin()
	{
		return iterator{values, values + sz};
	}

	iterator end()
	{
		return iterator{values + sz, values + sz};
	}

	const_iterator begin() const
	{
		return const_iterator{values, values + sz};
	}

	const_iterator end() const
	{
		return const_iterator{values + sz, values + sz};
	}

	iterator insert(const_iterator pos, const_reference val)
	{
		auto diff = pos - begin();
		if (diff < 0 || static_cast<size_type>(diff) > sz)
			throw std::runtime_error("Iterator out of bounds");
		size_type current{static_cast<size_type>(diff)};
		if (sz >= max_sz)
			reserve(max_sz * 2); // Achtung Sonderfall, wenn keine Mindestgroesze definiert ist
		for (auto i{sz}; i-- > current;)
			values[i + 1] = values[i];
		values[current] = val;
		++sz;
		return iterator{values + current};
	}

	iterator erase(const_iterator pos)
	{
		auto diff = pos - begin();
		if (diff < 0 || static_cast<size_type>(diff) >= sz)
			throw std::runtime_error("Iterator out of bounds");
		size_type current{static_cast<size_type>(diff)};
		for (auto i{current}; i < sz - 1; ++i)
			values[i] = values[i + 1];
		--sz;
		return iterator{values + current};
	}

	class Iterator
	{
	public:
		using value_type = Vector::value_type;
		using reference = Vector::reference;
		using pointer = Vector::pointer;
		using difference_type = Vector::difference_type;
		using iterator_category = std::forward_iterator_tag;

	private:
		pointer ptr;
		pointer end_ptr;

	public:
		Iterator() : ptr(nullptr), end_ptr(nullptr) {}
		Iterator(pointer ptr) : ptr(ptr ? ptr : nullptr), end_ptr(nullptr) {}
		Iterator(pointer ptr, pointer end_ptr) : ptr(ptr ? ptr : nullptr), end_ptr(end_ptr ? end_ptr : nullptr) {}

		reference operator*() const
		{
			if (ptr == end_ptr || ptr == nullptr)
				throw std::runtime_error("error range *");
			return *ptr;
		}
		pointer operator->() const
		{
			if (ptr == end_ptr || ptr == nullptr)
				throw std::runtime_error("error range ->");
			return ptr;
		}
		pointer get_ptr() const
		{
			return ptr;
		}
		bool operator==(const const_iterator &right) const
		{
			return ptr == right.get_ptr();
		}
		bool operator!=(const const_iterator &right) const
		{
			return !(*this == right);
			;
		}

		iterator &operator++()
		{
			if (ptr == end_ptr || ptr == nullptr)
				return *this;
			ptr++;
			return *this;
		}
		iterator operator++(int)
		{
			if (ptr == end_ptr || ptr == nullptr)
				return *this;
			++ptr;
			return *this;
		}
		operator const_iterator() const
		{
			return const_iterator{ptr};
		}
	};
	class ConstIterator
	{
	public:
		using value_type = Vector::value_type;
		using reference = Vector::const_reference;
		using pointer = Vector::const_pointer;
		using difference_type = Vector::difference_type;
		using iterator_category = std::forward_iterator_tag;

	private:
		pointer ptr;
		pointer end_ptr;

	public:
		ConstIterator() : ptr(nullptr), end_ptr(nullptr) {}
		ConstIterator(pointer ptr) : ptr(ptr ? ptr : nullptr), end_ptr(nullptr) {}
		ConstIterator(pointer ptr, pointer end_ptr) : ptr(ptr ? ptr : nullptr), end_ptr(end_ptr ? end_ptr : nullptr) {}

		reference operator*() const
		{
			if (ptr == end_ptr || ptr == nullptr)
				throw std::runtime_error("error range * const");
			return *ptr;
		}
		pointer operator->() const
		{
			if (ptr == end_ptr || ptr == nullptr)
				throw std::runtime_error("error range -> const");
			return ptr;
		}
		pointer get_ptr() const
		{
			return ptr;
		}
		bool operator==(const const_iterator &right) const
		{
			return ptr == right.get_ptr();
		}
		bool operator!=(const const_iterator &right) const
		{
			return !(*this == right);
			;
		}

		const_iterator &operator++()
		{
			if (ptr == end_ptr || ptr == nullptr)
				return *this;
			ptr++;
			return *this;
		}
		const_iterator operator++(int)
		{
			if (ptr == end_ptr || ptr == nullptr)
				return *this;
			++ptr;
			return *this;
		}
		friend Vector::difference_type operator-(const Vector::ConstIterator &lop, const Vector::ConstIterator &rop)
		{
			return lop.ptr - rop.ptr;
		}
	};
};

#endif
