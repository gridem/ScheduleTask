struct Distribution
{
	void add(double val);
	void toStream(std::ostream& o) const;
	
private:
	int count = 0;
	double sum = 0.;
	double sum2 = 0.;
	std::map<int, int> values;
};

struct TimedDistribution
{
	void add(int ts, double val);
	void toStream(std::ostream& o) const;

private:
	struct Mean
	{
		int count = 0;
		double value = 0.;

		double mean() const { return value/count; }
	};

	Distribution distribution;
	std::map<int, Mean> dependency;
};
