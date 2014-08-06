#include "task.h"

const char* const fileResources = "resources.txt";
const char* const fileJobs = "jobs.txt";
const char* const fileStatistics = "statistics.txt";
const char* const fileSchedule = "schedule.txt";

template<typename T>
void outStat(std::ostream& o, const std::string& name, const T& distrib)
{
	o << "=== stat: " << name << "\n";
	distrib.toStream(o);
}

void Emulator::start()
{
	readData();
	execute();
	outStatistics();
	outSchedule();
}

void Emulator::readData()
{
	readFile(fileResources, resourcesStream);
	readFile(fileJobs, jobsStream);
}

void Emulator::execute()
{
	while (!resourcesStream.empty())
	{
		LOG("timestamp: " << timestamp);
		executeStep();
		collectStatistics();
		++ timestamp;
	}
}

void Emulator::executeStep()
{
	std::vector<ResourceTuple> resources = getFor(timestamp, resourcesStream);
	std::vector<JobTuple> jobs = getFor(timestamp, jobsStream);
	scheduled = std::move(
			(!resources.empty() || !jobs.empty()) ? scheduler.newEvent(resources, jobs) : std::vector<JobTuple>());
	LOG("scheduled jobs: " << scheduled.size());
	jobsSchedule[timestamp] = scheduled;
}

void Emulator::collectStatistics()
{
	int workDone = 0;
	for(const JobTuple& j: scheduled)
	{
		int work = j.resources * j.duration;
		workDone += work;
		workDoneLatencyDistrib.add(work, timestamp - j.timestamp);
		resourceAllocatedLatencyDistrib.add(j.resources, timestamp - j.timestamp);
	}
	workDoneDistrib.add(timestamp, workDone);
	const auto& nodes = scheduler.nodes();
	int totalResources = 0;
	for (const auto& n: nodes)
	{
		int nNode = n.first;
		int nResources = n.second;
		totalResources += nResources;
		nodesDistrib[nNode].add(timestamp, nResources);
	}
	totalNodesDistrib.add(timestamp, totalResources);
}

void Emulator::outStatistics()
{
	LOG("saving statistics");
	std::ofstream o(fileStatistics);
	VERIFY(o, "cannot open file");
	outStat(o, "work done", workDoneDistrib);
	outStat(o, "work done vs latency", workDoneLatencyDistrib);
	outStat(o, "resource allocated vs latency", resourceAllocatedLatencyDistrib);
	for (const auto& d: nodesDistrib)
		outStat(o, "node: " + std::to_string(d.first), d.second);
	outStat(o, "overall nodes (total)", totalNodesDistrib);
	o << "unscheduled jobs: " << scheduler.unscheduledJobs() << std::endl;
	o.close();
}

void Emulator::outSchedule()
{
	LOG("saving schedule");
	std::ofstream o(fileSchedule);
	VERIFY(o, "cannot open file");
	for (const auto& s: jobsSchedule)
	{
		o << "timestamp: " << s.first;
		for (const JobTuple& j: s.second)
			o << "\n    " << j.timestamp << " " << j.resources << " " << j.duration;
		o << std::endl;
	}
	o.close();
}
