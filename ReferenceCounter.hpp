#ifndef REFERENCECOUNTER_HPP
#define	REFERENCECOUNTER_HPP

template<typename type>
class ReferenceCounter {
public:
    ReferenceCounter() : count(type()) {}
    ReferenceCounter(const ReferenceCounter<type> &cnt) : count(cnt.count) {}
    ReferenceCounter(const ReferenceCounter<type> &&cnt) : count(std::move(cnt.count)) {}
    inline void addReference() { ++count; }
    inline int deleteReference() { return --count; }
    ~ReferenceCounter() {}
private:
    type count;
};

#endif	/* REFERENCECOUNTER_HPP */
