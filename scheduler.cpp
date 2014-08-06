#include "task.h"

std::vector<JobTuple> Scheduler::newEvent(
		const std::vector<ResourceTuple>& resources,
		const std::vector<JobTuple>& jobs)
{
	for (const auto& r: resources)
		nodeResources[r.nodeId] += r.resources;
	for (const auto& j: jobs)
		sortedJobs.insert(j);
	return schedule();
}

std::vector<JobTuple> Scheduler::schedule()
{
	std::vector<JobTuple> scheduled;
	for (const JobTuple& j : sortedJobs)
	{
		int node = findNode(j.resources);
		if (node >= 0)
		{
			nodeResources[node] -= j.resources;
			scheduled.push_back(j);
		}
	}
	for (const JobTuple& j : scheduled)
		sortedJobs.erase(j);
	return scheduled;
}

int Scheduler::findNode(int resources) // returns -1 on empty result (not found)
{
	int node = -1;
	int delta = 0;
	for (const auto& nr : nodeResources)
	{
		int nrNode = nr.first;
		int nrResources = nr.second;
		int nrDelta = nrResources - resources;
		if (nrDelta >= 0 && (node == -1 || delta > nrDelta))
		{
			delta = nrDelta;
			node = nrNode;
		}
	}
	return node;
}
