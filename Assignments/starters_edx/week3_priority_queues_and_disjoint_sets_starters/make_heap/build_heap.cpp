#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void MinHeapToSortedArr() {
    swaps_.clear();
    int size = data_.size();
    vector<int> sortedArr;
    for(int i = 0; i < size; i++) {
      sortedArr.push_back(data_[0]);
      swap(data_[0], data_[data_.size() - 1]);
      data_.pop_back();
      siftDown(data_, 0, swaps_);
    }

    for(auto d : sortedArr) {
      cout << d << " ";
    }
    cout << endl;
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    /* TODO: replace by a more efficient implementation
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
    */
    
    // Build Min Heap in-place
    for(int i = (data_.size() / 2) - 1; i >= 0; i--) {
      siftDown(data_, i, swaps_);
    }

  }

  //use zero based
  void siftDown(vector<int>& data, int index, vector<pair<int,int>>& swapPairs) {
    int size = data.size() - 1;
    int maxIndex = index;
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;

    if(leftIndex <= size && data[leftIndex] < data[maxIndex]) {
      maxIndex = leftIndex;
    }
    if(rightIndex <= size && data[rightIndex] < data[maxIndex]) {
      maxIndex = rightIndex;
    }

    if(index != maxIndex) {
      swap(data[index], data[maxIndex]);
      swapPairs.push_back(make_pair(index, maxIndex));
      siftDown(data, maxIndex, swapPairs);
    }


  }


 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
    MinHeapToSortedArr();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}

/*redirect cin to files
void f()
{
    std::string line;
    while(std::getline(std::cin, line))  //input from the file in.txt
    {
        std::cout << line << "\n";   //output to the file out.txt
    }
}

    std::ifstream in("in.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    std::ofstream out("out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    std::string word;
    std::cin >> word;           //input from the file in.txt
    std::cout << word << "  ";  //output to the file out.txt

    f(); //call function


    std::cin.rdbuf(cinbuf);   //reset to standard input again
    std::cout.rdbuf(coutbuf); //reset to standard output again

    std::cin >> word;   //input from the standard input
    std::cout << word;  //output to the standard input

/*
auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save and redirect
Here std::cin.rdbuf(in.rdbuf()) sets std::cin's buffer to in.rdbuf() 
and then returns the old buffer associated with std::cin. 
The very same can be done with std::cout — or any stream for that matter.
*/