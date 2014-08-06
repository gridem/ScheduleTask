//void verifyTimestamps()

template<typename T>
std::vector<T> getFor(int timestamp, std::queue<T>& stream)
{
	std::vector<T> result;
	while (!stream.empty())
	{
		const T& t = stream.front();
		if (t.timestamp != timestamp)
			break;
		result.push_back(t);
		stream.pop();
	}
	return result;
}

struct Emulator
{
	void start();
	
private:
	void readData();
	void execute();

	void executeStep();
	void collectStatistics();
	void outStatistics();
	void outSchedule();

	int timestamp = 0;
	std::queue<ResourceTuple> resourcesStream;
	std::queue<JobTuple> jobsStream;
	std::vector<JobTuple> scheduled;
	
	Scheduler scheduler;
	std::map<int, std::vector<JobTuple>> jobsSchedule;

	TimedDistribution workDoneDistrib;
	TimedDistribution workDoneLatencyDistrib;
	TimedDistribution resourceAllocatedLatencyDistrib;
	
	// nodes
	std::map<int, TimedDistribution> nodesDistrib;
	TimedDistribution totalNodesDistrib;
};
