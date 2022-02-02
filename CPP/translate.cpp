#include "translate.h"
#include "make_matrix.h"
#include "make_vector.h"
//for debug
#include <boost/numeric/ublas/io.hpp>

static const auto translateForm2DMatrix = *(make_matrix(3,2,std::vector<double>{1.0,0.0,0.0,1.0,0.0,0.0}));
static const auto translateForm2DAdd = make_vector(std::vector<double>{0,0,1});
static const auto translateForm2DInverseMatrix = *(make_matrix(2,3,std::vector<double>{1,0,0,0,1,0}));

static boost::numeric::ublas::vector<double> toTranslate2DForm(const boost::numeric::ublas::vector<double> &x)
{
	return prod(translateForm2DMatrix,x)+translateForm2DAdd;
}

static boost::numeric::ublas::matrix<double > makeTranslation2DMatrix(const boost::numeric::ublas::vector<double> &x)
{
	return *(make_matrix(3,3,std::vector<double>{1,0,x[0],0,1,x[1],0,0,1}));
}

boost::numeric::ublas::matrix<double> translate( const boost::numeric::ublas::matrix<double> &x, const boost::numeric::ublas::vector<double> &y)
{
	std::cout << std::string(10, '-') << std::endl;
	boost::numeric::ublas::matrix<double> translateForm = prod(translateForm2DMatrix,x);
	for(unsigned int i = 0,end = x.size2(); i < end; ++i)
	{
		translateForm(2,i)=1.0;
	}
	std::cout << "translate form :  " << translateForm << std::endl;
	const auto op = makeTranslation2DMatrix(y);
	std::cout << "op : " << op << std::endl;
	const boost::numeric::ublas::matrix<double> result = prod(op,translateForm);
	std::cout << "result : " << result << std::endl;
	const auto ret = prod(translateForm2DInverseMatrix,result);
	std::cout << "return : " << ret << std::endl;
	std::cout << std::string(10,'=')<<std::endl;
	return ret;
}
