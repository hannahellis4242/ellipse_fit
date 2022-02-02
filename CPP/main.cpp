#include "run.h"

#include <iostream>
#include <boost/program_options.hpp>

//for testing
#include "simplex.h"


namespace test
{
double func(double x)
{
return 20*sin(x)+x*x;
}

void run()
{
std::cout << std::string(10,'-') << "test" << std::string(10,'-')<<std::endl;
const auto out = simplex(func,Range(6,5),1e-6);
std::cout << "Range : " << out.first << " - " << out.second << std::endl ;
std::cout << std::string(10,'=') << "test" << std::string(10,'=')<<std::endl;
}

}

int main(int argc, char *argv[])
{
	boost::program_options::options_description desc("ellipse_fit");
	desc.add_options()
	        ("help", "produce help message")
	        ("input,f", boost::program_options::value<std::string>(), "input data file");

	boost::program_options::positional_options_description p;
	p.add("input", -1);

	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
	boost::program_options::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 1;
	}

	if (vm.count("input"))
	{
		const std::string filename = vm["input"].as<std::string>();
		run(filename);
		test::run();
	}
	else
	{
		std::cout << "please spesify a data file" <<std::endl;
		std::cout << desc << std::endl;
		return 1;
	}

}
