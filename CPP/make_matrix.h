#ifndef MAKE_MATRIX
#define MAKE_MATRIX
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include <optional>

template < class T >
std::optional<boost::numeric::ublas::matrix<T> > make_matrix(const unsigned int rows, const unsigned int columns, const std::vector<T> &x)
{
	if( rows * columns <= x.size())
	{
		boost::numeric::ublas::matrix<T> m(rows,columns);
		for( unsigned int i = 0; i < rows; ++i)
		{
			for( unsigned int j = 0; j < columns; ++j)
			{
				m(i,j)=x[i*columns+j];
			}
		}
		return m;
	}
	return std::optional<boost::numeric::ublas::matrix<T> >();
}
#endif
