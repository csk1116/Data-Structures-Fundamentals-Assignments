#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::swap;

class JobQueue
{
private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const
  {
    for (int i = 0; i < jobs_.size(); ++i)
    {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData()
  {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for (int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs()
  {
    /* TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
    */
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<int> trackWorkers;
    vector<long long> taskMinHeap(num_workers_, 0);
    for (int i = 0; i < num_workers_; i++)
    {
      trackWorkers.push_back(i);
    }

    for(int i = 0; i < jobs_.size(); i++)
    {
      int duration = jobs_[i];
      assigned_workers_[i] = trackWorkers[0];
      start_times_[i] = taskMinHeap[0];
      taskMinHeap[0] += duration;
      siftDown(taskMinHeap, 0, trackWorkers);     
    }

  }

  void siftDown(vector<long long> &data, int index, vector<int>& track)
  {
    int size = data.size() - 1;
    int maxIndex = index;
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;

    if (leftIndex <= size && data[leftIndex] < data[maxIndex])
    {
      maxIndex = leftIndex;
    }
    else if(leftIndex <= size && data[leftIndex] == data[maxIndex] && track[leftIndex] < track[maxIndex])
    {
      maxIndex = leftIndex;
    }
    if (rightIndex <= size && data[rightIndex] < data[maxIndex])
    {
      maxIndex = rightIndex;
    }
    else if(rightIndex <= size && data[rightIndex] == data[maxIndex] && track[rightIndex] < track[maxIndex])
    {
      maxIndex = rightIndex;
    }

    if (index != maxIndex)
    {
      swap(data[index], data[maxIndex]);
      swap(track[index], track[maxIndex]);
      siftDown(data, maxIndex, track);
    }
  }

public:
  void Solve()
  {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
