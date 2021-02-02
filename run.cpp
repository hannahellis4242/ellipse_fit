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
		if( file.is_open() )
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
		boost::numeric::ublas::matrix<double> m(2,line_count);
		std::ifstream file(filename.c_str());
		std::cout << "reopening file" << std::endl;
		if(file.is_open())
		{
			std::cout << "is open " << std::endl;
			for( unsigned int i=0; i < line_count; ++i)
			{
				std::string first, second;
				std::getline(file,first,',');
				std::getline(file,second);
				std::cout << first << " , "  << second << std::endl;
				m(0,i)=boost::lexical_cast<double>(first);
				m(1,i)=boost::lexical_cast<double>(second);
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

static double score( const boost::numeric::ublas::matrix<double> & xs, const EllipseParams &p)
{
//step 1 translate
	const auto translated = translate(xs,make_vector(std::vector<double>{-p.centre_x,-p.centre_y}));
	std::cout<<"translated : " <<translated<<std::endl;
	const auto s = sin(p.angle);
	const auto c = cos(p.angle);
	const auto R = *make_matrix(2,2,std::vector<double>{c,s,-s,c});
	std::cout << "R : " << R << std::endl;
	const boost::numeric::ublas::matrix<double> pointsInEllipseFrame = prod(R,translated);
	std::cout << pointsInEllipseFrame << std::endl;
	return 1000000.0;
}

void run(const std::string & filename)
{
	const boost::numeric::ublas::matrix<double> input = parse(filename);
	std::cout << "input : "<< input << std::endl;
	score(input,EllipseParams(2,1,45*boost::math::constants::pi<double>()/180.0,1,1));
}

