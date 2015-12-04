#ifndef REF_COUNTER_HPP
#define	REF_COUNTER_HPP

template<typename type>
class ref_counter {
public:
    ref_counter();
    ref_counter(const ref_counter<type> &cnt);
    ref_counter(const ref_counter<type> &&cnt);
    inline void add_ref();
    inline int delete_ref();
    ~ref_counter();
private:
    type count;
};

template<typename type>
ref_counter<type>::ref_counter() : count(type()) {
}

template<typename type>
ref_counter<type>::ref_counter(const ref_counter<type> &cnt) 
    : count(cnt.count) {
}

template<typename type>
ref_counter<type>::ref_counter(const ref_counter<type> &&cnt)
    : count(std::move(cnt.count)) {}

template<typename type>
inline void ref_counter<type>::add_ref() {
    ++count;
}

template<typename type>
inline int ref_counter<type>::delete_ref() {
    return --count;
}

template<typename type>
ref_counter<type>::~ref_counter() {
}

#endif	/* REF_COUNTER_HPP */