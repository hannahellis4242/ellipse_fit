#ifndef SIMPLEX_H
#define SIMPLEX_H
#include <utility>
#include <function>

using Range=std::pair<double,double>;

Range simplex(const std::function<double(double)> & f , const Range & r , const double tol);

#endif
