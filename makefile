all : ellipse_fit

clean :
	rm ellipse_fit *.o

run : ellipse_fit
	./ellipse_fit data.txt

ellipse_fit : main.o translate.o run.o
	g++ -std=c++17 $^ -lboost_program_options -o $@

%.o : %.cpp
	g++ -std=c++17 -c $<
