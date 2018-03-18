#include <iostream>
#include "library.h"
int main(){
    Vec v0 = {23.4,12.5,144.56,90.56};
    Vec v1 = {67.12,34.8,90.34,89.30};
    Vec v2 = {34.90,111.9,45.12,90.5};
    // Following assignment will call the ctor of Vec which accept type of
    // `VecExpression<E> const&`. Then expand the loop body to
    // a.elems[i] + b.elems[i] + c.elems[i]
    Vec sum_of_vec_type = v0+v1+v2;
    for(int i=0;i<sum_of_vec_type.size();++i)
        std::cout << sum_of_vec_type[i] << std::endl;
}
