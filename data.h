struct ResourceTuple
{
	int timestamp;
	int resources;
	int nodeId;
};

struct JobTuple
{
	int timestamp;
	int resources;
	int duration;
};

inline std::istream& operator>>(std::istream& i, ResourceTuple& r)
{
	return i >> r.timestamp >> r.resources >> r.nodeId;
}

inline std::istream& operator>>(std::istream& i, JobTuple& j)
{
	return i >> j.timestamp >> j.resources >> j.duration;
}

template<typename T>
void readFile(const char* fname, std::queue<T>& q)
{
	LOG("loading file: " << fname);
	std::ifstream ifs(fname);
	VERIFY(ifs, "cannot open file");
	T t;
	int count = 0;
	while (ifs >> t)
	{
		++ count;
		q.emplace(std::move(t));
	}
	LOG("loaded items: " << count);
}

