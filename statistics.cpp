#include "task.h"

void Distribution::add(double val)
{
	++count;
	sum += val;
	sum2 += val * val;
	++values[int(val)];
}

void Distribution::toStream(std::ostream& o) const
{
	double mean = sum/count;
	double mean2 = sum2/count;
	o
		<< "count: " << count << "\n"
		<< "mean: " << mean << "\n"
		<< "deviation: " << std::sqrt(mean2 - mean*mean) << "\n"
		<< "distribution:\n";
	for (const auto& e: values)
		o << e.first << " " << e.second << "\n";
	o << std::endl;
}

void TimedDistribution::add(int ts, double val)
{
	distribution.add(val);
	dependency[ts].value += val;
	++ dependency[ts].count;
}

void TimedDistribution::toStream(std::ostream& o) const
{
	distribution.toStream(o);
	o << "dependency:\n";
	for (const auto& d : dependency)
		o << d.first << " " << d.second.mean() << "\n";
	o << std::endl;
}
