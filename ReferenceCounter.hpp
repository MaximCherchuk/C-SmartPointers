#ifndef REFERENCECOUNTER_HPP
#define	REFERENCECOUNTER_HPP

template<typename type>
class ReferenceCounter {
public:
    ReferenceCounter();
    ReferenceCounter(const ReferenceCounter<type> &cnt);
    ReferenceCounter(const ReferenceCounter<type> &&cnt);
    inline void addReference();
    inline int deleteReference();
    ~ReferenceCounter();
private:
    type count;
};

template<typename type>
ReferenceCounter<type>::ReferenceCounter() : count(type()) {
}

template<typename type>
ReferenceCounter<type>::ReferenceCounter(const ReferenceCounter<type> &cnt) 
    : count(cnt.count) {
}

template<typename type>
ReferenceCounter<type>::ReferenceCounter(const ReferenceCounter<type> &&cnt)
    : count(std::move(cnt.count)) {}

template<typename type>
inline void ReferenceCounter<type>::addReference() {
    ++count;
}

template<typename type>
inline int ReferenceCounter<type>::deleteReference() {
    return --count;
}

template<typename type>
ReferenceCounter<type>::~ReferenceCounter() {
}

#endif	/* REFERENCECOUNTER_HPP */