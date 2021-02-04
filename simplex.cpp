#include "simplex.h"
#include <vector>
#include <algorithm>

Range simplex(const std::function<double(double)> & f , const Range & r , const double tol)
{
if(std::max(r.first - r.second , r.second -r.first) < tol)
{
return r;
}
//otherwise we calculate a new range using trail points
using PointAndValue = std::pair<double,double>;
const PointAndValue x1( r.first ,f(r.first));
const PointAndValue x2(r.second,f(r.second));
const auto compareSecond = [](const PointAndValue & a ,const PointAndValue &b){ return a.second < b.second ;};
const double best = std::min( x1 , x2 , compareSecond).first;
const double worst = std::max( x1, x2 , compareSecond).first ;

//trial points
std::vector<double> trialPoints;
//middle
trialPoints.push_back((best+worst)/2.0);
//one step along the line
trialPoints.push_back(2*best-worst);
//two steps along the line
trialPoints.push_back(3*best-2*worst);
//three steps along the line (being optimisic)
trialPoints.push_back(4*best-3*worst);

//find the smallest
const auto it = std::min_element(trialPoints.begin(),trialPoints.end(),[&](const double a , const double b){return f(a)<f(b);});
const Range newRange(best,*it);
//now do it again
return simplex(f,newRange,tol);
}

