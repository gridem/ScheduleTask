struct Scheduler
{
	std::vector<JobTuple> newEvent(
			const std::vector<ResourceTuple>& resources,
			const std::vector<JobTuple>& jobs);
	std::vector<JobTuple> schedule();
	const std::map<int, int>& nodes() const { return nodeResources; }
	int unscheduledJobs() const { return sortedJobs.size(); }
	
private:
	int findNode(int resources);

	struct Comparator
	{
		bool operator()(const JobTuple& j1, const JobTuple& j2) const
		{
			return j1.resources > j2.resources ||
					(j1.resources == j2.resources && (j1.timestamp < j2.timestamp ||
							(j1.timestamp == j2.timestamp && j1.duration > j2.duration)));
		}
	};

	// pair: nodeId -> resources
	std::map<int, int> nodeResources;
	std::set<JobTuple, Comparator> sortedJobs;
};
