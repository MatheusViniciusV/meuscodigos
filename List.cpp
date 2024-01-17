#include <cstddef>
#include <stdexcept>
#include <iostream>

#define COEFICIENT 1.5

template <class T>
class List
{
	private:
		T* data;
		size_t size;
		int reserve;
	public:
	    List();
		List(int);
		~List();
		void add(T);
		void add(int, T);
		T remove(int);
		T get(int);
		void set(int, T);
		size_t len();
		void display();
};

template <class T>
List<T>::List()
{
	this->size = 0;
	this->reserve = 10;
	this->data = new T[10];
}

template <class T>
List<T>::List(int initial)
{
	this->size = 0;
	this->reserve = initial;
	this->data = new T[initial];
}

template <class T>
List<T>::~List()
{
	delete this->data;
}

template <class T>
void List<T>::add(T element)
{
	this->add(this->size, element);
}

template <class T>
void List<T>::add(int position, T element)
{
	if(position > this->size || position < 0)
	{
		throw std::out_of_range("Invalid position");
	}
	
	if(this->size < this->reserve)
	{
		for(size_t i = this->size; i > position; i--)
		{
			this->data[i] = this->data[i - 1];
		}
		
		this->data[position] =  element;
		this->size++;
	}
	else
	{
		T *temp = this->data;
		this->reserve *= COEFICIENT;
		this->data = new T[this->reserve];
		this->size++;
		
		for(int i = 0; i < position; i++)
		{
			this->data[i] = temp[i];
		}
		
		this->data[position] = element;
		
		for(int i = position + 1; i < this->size; i++)
		{
			this->data[i] = temp[i - 1];
		}
		
		delete temp;
	}
}

template <class T>
T List<T>::remove(int position)
{
	if(position > this->size || position < 0)
	{
		throw std::out_of_range("Invalid position");
	}
	if(this->size == 0)
	{
		throw std::length_error("The list is empty");
	}
	
	T value = this->data[position];
	
	this->size--;
	
	for(int i = position; i < this->size; i++)
	{
		this->data[i] = this->data[i + 1];
	}
	
	return value;
}

template <class T>
T List<T>::get(int position)
{
	if(position > this->size || position < 0)
	{
		throw std::out_of_range("Invalid position");
	}
	
	return this->data[position];
}

template <class T>
void List<T>::set(int position, T element)
{
	if(position > this->size || position < 0)
	{
		throw std::out_of_range("Invalid position");
	}
	
	this->data[position] = element;
}

template <class T>
size_t List<T>::len()
{
	return this->size;
}

template <class T>
void List<T>::display()
{
    std::cout << '[';

    for (size_t i = 0; i < this->size; ++i)
    {
        std::cout << this->data[i];
    
        if (i < this->size - 1) {
            std::cout << ", ";
        }
    }
    
    std::cout << ']';
}
