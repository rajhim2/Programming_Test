#include <iostream>
#include <vector>
#include <assert.h>
template <typename E>
class VecExpression {
  public:
    double operator[](size_t i) const { return static_cast<E const&>(*this)[i];     }

    size_t size()               const { return static_cast<E const&>(*this).size(); }


    // The following overload conversions to E, the template argument type;
    // e.g., for VecExpression<VecSum>, this is a conversion to VecSum.
     operator E& () { return static_cast<E&>(*this); }
     operator const E& () const { return static_cast<const E&>(*this); }
};
class Vec : public VecExpression<Vec> {
    std::vector<double> elems;
  public:
    double operator[](size_t i) const { return elems[i]; }
    double &operator[](size_t i)      { return elems[i]; }
    size_t size() const               { return elems.size(); }

    Vec(size_t n) : elems(n) {}
    // construct vector using initializer list
    Vec(std::initializer_list<double>init){
        for(auto i:init)
            elems.push_back(i);
    }
    // A Vec can be constructed from any VecExpression, forcing its evaluation.
    template <typename E>
    Vec(VecExpression<E> const& vec) : elems(vec.size()) {
        for (size_t i = 0; i != vec.size(); ++i) {
            elems[i] = vec[i];
        }
    }
};
template <typename E1, typename E2>

class VecSum : public VecExpression<VecSum<E1, E2> > {
    E1 const& _u;
    E2 const& _v;
public:
    VecSum(E1 const& u, E2 const& v) : _u(u), _v(v) {
        assert(u.size() == v.size());
        }
    double operator[](size_t i) const { return _u[i] + _v[i]; }

    size_t size()               const { return _v.size(); }

};

template <typename E1, typename E2>
VecSum<E1,E2> const
operator+(E1 const& u, E2 const& v) {
   return VecSum<E1, E2>(u, v);
}
