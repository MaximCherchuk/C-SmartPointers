/*
 * @Compiler: g++ 4.8.2 (C++11 standard)
 */

#ifndef SMARTPOINTER_HPP
#define	SMARTPOINTER_HPP

#include "ReferenceCounter.hpp"

template<typename value_type, typename counter_type = unsigned int>
class SmartPointer {
public:
    SmartPointer(value_type*);
    SmartPointer(value_type*, std::function<void(value_type*)>);
    SmartPointer(const SmartPointer<value_type, counter_type>& copy);
    ~SmartPointer();
    SmartPointer& operator = (const SmartPointer<value_type, counter_type>& another);
    value_type& operator * ();
    value_type* operator -> ();
private:
    SmartPointer() = delete;
    value_type *pointer;
    ReferenceCounter<counter_type> counter;
    std::function<void(value_type*)> deleter;
};

template<typename value_type, typename counter_type> 
SmartPointer<value_type, counter_type>::SmartPointer(value_type *value) 
        : pointer(value), counter(ReferenceCounter<counter_type>())
{
    counter.addReference();
    deleter = [&] (value_type *point = pointer) -> void { 
        delete pointer; 
    };
}

template<typename value_type, typename counter_type> 
SmartPointer<value_type, counter_type>::
SmartPointer(value_type *value, std::function<void(value_type*)> deleter) 
        : pointer(value), counter(ReferenceCounter<counter_type>())
{
    counter.addReference();
    this->deleter = deleter;
}

template<typename value_type, typename counter_type> 
SmartPointer<value_type, counter_type>::
    SmartPointer(const SmartPointer<value_type, counter_type>& smart_pointer) 
    : pointer(smart_pointer.pointer), counter(smart_pointer.counter),
      deleter(smart_pointer.deleter)
{
    counter.addReference();
}

template<typename value_type, typename counter_type> 
SmartPointer<value_type, counter_type>::~SmartPointer() {
    if(counter.deleteReference() == 0) {
        deleter(pointer);
    }
}

template<typename value_type, typename counter_type> 
value_type& SmartPointer<value_type, counter_type>::operator *() {
    return *pointer;
}

template<typename value_type, typename counter_type> 
value_type* SmartPointer<value_type, counter_type>::operator -> () {
    return pointer;
}

template<typename value_type, typename counter_type> 
SmartPointer<value_type, counter_type>& SmartPointer<value_type, counter_type>::
               operator = (const SmartPointer<value_type,counter_type>& another) 
{
    if(this == &another) return *this;
    if(counter.deleteReference() == 0) {
        deleter(pointer);
    }
    pointer = another.pointer;
    counter = another.counter;
    deleter = another.deleter;
    counter.addReference();
    return *this;
}
#endif	/* SMARTPOINTER_HPP */
