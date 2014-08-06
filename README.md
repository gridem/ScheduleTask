ScheduleTask
============
# Overview
Repository contains scheduler emulator with simplest yet suitable scheduler as a first approximation to the emulator model. To compare different emulators several statistics are used.

# Input data
Input data has 2 streams:
- Node resources stream. It uses the following notation in the file:
  - *timestamp* of the resource arrival
  - amount of available *resources*
  - *node id*
- Jobs stream. It uses the following notation in the file:
  - *timestamp* of job arrival
  - needed *resources*
  - job *duration* in time steps

# Output data
- Statistics. The corresponding file contains different statistics to describe the scheduler algorithm. See details later.
- Schedule. The file contains schedule strategy at each timestamp. Unfortunately, I forgot to add the node id for each scheduled job in output, but it can be fixed easily (doesn’t affect algorithms and statistics).

# Statistics
Statistics is needed to provide better understanding what’s going on inside the scheduling algorithm and make a conclusion after comparison statistics for different schedulers. Detailed statistics data allows further improving the algorithms.

## Distribution: general description
Each statistics contains the same set of data:
- Values distribution, including mean and standard deviation values.
- Dependency of averaged values.

## Emulator Distributions
Emulator contains a set of distributions:
- *Work done distribution*. Work is amount of work needed to complete particular job and is equal to job resources times job duration.
- *Work done vs latency distribution*. Each job has the latency: difference between arrival time and scheduled time. The less latency means better scheduler.
- *Resource needed vs latency distribution*. The same as previous but uses job resource instead of amount of work.
- *Nodes distribution*. Contains distribution of available resources for each particular node and for sum of all nodes.
