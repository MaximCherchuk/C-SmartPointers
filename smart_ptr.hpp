/*
 * @Compiler: g++ 4.8.2 (C++11 standard)
 */

#ifndef SMART_PTR_HPP
#define	SMART_PTR_HPP

#include "ref_counter.hpp"

namespace htop {

template<typename value_t, typename counter_t = unsigned int>
class smart_ptr {
public:
    smart_ptr(value_t*);
    smart_ptr(value_t*, std::function<void(value_t*)>);
    smart_ptr(const smart_ptr<value_t, counter_t>& copy);
    ~smart_ptr();
    smart_ptr& operator = (const smart_ptr<value_t, counter_t>& other);
    value_t& operator *  ();
    value_t* operator -> ();
    value_t& operator [] (const size_t index);
private:
    smart_ptr() = delete;
    value_t *pointer;
    ref_counter<counter_t> counter;
    std::function<void(value_t*)> deleter;
};

template<typename value_t, typename counter_t> 
smart_ptr<value_t, counter_t>::smart_ptr(value_t *value) 
        : pointer(value), counter(ref_counter<counter_t>())
{
    counter.add_ref();
    deleter = [&] (value_t *point = pointer) -> void { 
        delete pointer; 
    };
}

template<typename value_t, typename counter_t> 
smart_ptr<value_t, counter_t>::
    smart_ptr(value_t *value, std::function<void(value_t*)> deleter) 
        : pointer(value), counter(ref_counter<counter_t>())
{
    counter.add_ref();
    this->deleter = deleter;
}

template<typename value_t, typename counter_t> 
smart_ptr<value_t, counter_t>::
    smart_ptr(const smart_ptr<value_t, counter_t>& smart_pointer) 
    : pointer(smart_pointer.pointer), counter(smart_pointer.counter),
      deleter(smart_pointer.deleter)
{
    counter.add_ref();
}

template<typename value_t, typename counter_t> 
smart_ptr<value_t, counter_t>::~smart_ptr() {
    if(counter.delete_ref() == 0) {
        deleter(pointer);
    }
}

template<typename value_t, typename counter_t> 
value_t& smart_ptr<value_t, counter_t>::operator *() {
    return *pointer;
}

template<typename value_t, typename counter_t> 
value_t* smart_ptr<value_t, counter_t>::operator -> () {
    return pointer;
}

template<typename value_t, typename counter_t> 
smart_ptr<value_t, counter_t>& smart_ptr<value_t, counter_t>::
    operator = (const smart_ptr<value_t, counter_t>& other) 
{
    if(this == &other) return *this;
    if(counter.delete_ref() == 0) {
        deleter(pointer);
    }
    pointer = other.pointer;
    counter = other.counter;
    deleter = other.deleter;
    counter.add_ref();
    return *this;
}

template<typename value_t, typename counter_t> 
value_t& smart_ptr<value_t, counter_t>::
    operator [] (const size_t index)
{
        return pointer[index];
}

}
#endif	/* SMART_PTR_HPP */
