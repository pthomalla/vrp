#ifndef INTERFACE_ENUM
#define INTERFACE_ENUM

#include <string>
using namespace std;

template<class Type>
struct Adapter: public Type{
	typename Type::Enum value;
	typedef  Type Base_Type;
	Adapter();
	Adapter(typename Type::Enum);
	Adapter(const string&);

	operator string();
    inline string to_string(){ return operator string(); }
	Adapter& operator =(typename Type::Enum);
	Adapter& operator =(string);

	operator typename Type::Enum (){ return value;}
};


template<class Type>
Adapter<Type>::Adapter() :value( Type::Enum::INVALID){}

template<class Type>
Adapter<Type>::Adapter(typename Type::Enum type) : value(type){}

template<class Type>
Adapter<Type>::Adapter(const string &type)
{ 
    value = Type::to_Enum(type);
}

template<class Type>
Adapter<Type>::operator string()
{
    return Type::to_string(value);
}

template<class Type>
Adapter<Type>& Adapter<Type>::operator =(typename Type::Enum type)
{
	value = type;
	return *this;
}

template<class Type>
Adapter<Type>& Adapter<Type>::operator =(string type)
{
    value = Type::to_Enum(type);
	return *this;
}


template<class Stream, typename Type>
Stream& operator >>(Stream& input, Adapter<Type>& value)
{
    string tmp;
    input >> tmp;
    value = tmp;
    return input;
}


template<class Stream, typename Type>
Stream& operator <<(Stream& output, const Adapter<Type> &value)
{
    output << Adapter<Type>::Base_Type::to_string(value.value);
    return output;
}

#endif
