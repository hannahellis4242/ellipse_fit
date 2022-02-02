#ifndef MAKE_VECTOR
#define MAKE_VECTOR
#include <boost/numeric/ublas/vector.hpp>
#include <vector>


template < class T >
boost::numeric::ublas::vector<T> make_vector(const std::vector<T> &x)
{
	boost::numeric::ublas::vector<T> v(x.size());
	for(unsigned int i =0, end = x.size(); i < end; ++i)
	{
		v(i)=x[i];
	}
	return v;
}
#endif
