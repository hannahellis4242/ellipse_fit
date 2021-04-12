#include "run.h"
#include "translate.h"
#include "make_matrix.h"
#include "make_vector.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <optional>

static boost::numeric::ublas::matrix<double> parse(const std::string & filename)
{
	unsigned int line_count = 0;
	{
		std::ifstream file(filename.c_str());
		if( file.good() )
		{
			//step 1 find out how many lines the file has
			std::string line;
			while(std::getline(file,line))
			{
				++line_count;
			}
		}
		file.close();
	}
	std::cout << "number of lines :  " << line_count << std::endl;
	{
		boost::numeric::ublas::matrix<double> m(line_count,3);
		std::ifstream file(filename.c_str());
		std::cout << "reopening file" << std::endl;
		if(file.good())
		{
			std::cout << "is open " << std::endl;
			for( unsigned int i=0; i < line_count; ++i)
			{
				std::string first, second;
				std::getline(file,first,',');
				std::getline(file,second);
				std::cout << first << " , "  << second << std::endl;
				m(i,0)=boost::lexical_cast<double>(first);
				m(i,1)=boost::lexical_cast<double>(second);
				m(i,2)=1.0;
			}
		}
		file.close();
		return m;

	}
	return boost::numeric::ublas::matrix<double> ();
}

class EllipseParams
{
public:
double major;
double minor;
double angle;
double centre_x;
double centre_y;

EllipseParams(const double A, const double B, const double alpha, const double px, const double py )
	: major(A), minor(B),angle(alpha),centre_x(px),centre_y(py){
}
};

static boost::numeric::ublas::matrix<double> transform(const EllipseParams & p)
{
	boost::numeric::ublas::matrix<double> T1 = boost::numeric::ublas::identity_matrix(3,3);
	T1(2,0)=-p.centre_x;
	T1(2,1)=-p.centre_y;
	std::cout << "T1 : " << T1 << std::endl ;
	
	boost::numeric::ublas::matrix<double> T2 = boost::numeric::ublas::identity_matrix(3,3);
	T2(0,0)=T2(1,1)=cos(p.angle);
	T2(1,0)=sin(p.angle);
	T2(0,1)=-T2(1,0);
	std::cout << "T2 : " << T2 << std::endl ;
	
	boost::numeric::ublas::matrix<double> T3 = boost::numeric::ublas::identity_matrix(3,3);
	T3(0,0)=1.0/p.major;
	T3(1,1)=1/p.minor;
	std::cout << "T3 : " << T3 << std::endl ;
	
	boost::numeric::ublas::matrix<double> out = prod(T1,T2);
	out = prod(out, T3);
	std::cout << "product : " << out << std::endl ;
	return out;
}

class Point {
public:
double x, y;
Point(const double a, const double b ) : x(a),y(b){
}
};

static double distance( const Point & a, const Point & b )
{
	const double dx = a.x - b.x;
	const double dy = a.y - b.y;
	return sqrt(dx*dx+dy*dy);
}

static double score( const boost::numeric::ublas::matrix<double> & xs, const EllipseParams &p)
{
	const auto trans = transform(p);
	const boost::numeric::ublas::matrix<double> ys = prod(xs,trans);
	
	const boost::numeric::ublas::matrix<double> ys_trans = boost::numeric::ublas::trans(ys);
	//trace by hand...annoyingly
	const size_t rows = ys.size1();
	double sum = 0 ;
	const boost::numeric::ublas::matrix<double> yProd = prod(ys,ys_trans);
	std::cout << "yProd : " << yProd << std::endl ;
	for( size_t row = 0 ; row != rows ; ++row )
	{
		sum += yProd(row,row);
	}
	const double diff = sum - 2*rows;
	return diff*diff;
}

void run(const std::string & filename)
{
	const boost::numeric::ublas::matrix<double> input = parse(filename);
	std::cout << "input : "<< input << std::endl;
	EllipseParams params(2,1,45*boost::math::constants::pi<double>()/180.0,1,1);
	const auto s = score(input,EllipseParams(2,1,45*boost::math::constants::pi<double>()/180.0,1,1));
	std::cout << "score : " << s << std::endl ;
}

