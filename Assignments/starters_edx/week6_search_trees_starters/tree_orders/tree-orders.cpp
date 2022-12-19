#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::cin;
using std::cout;
using std::ios_base;
using std::vector;

class TreeOrders
{
  int n;
  vector<int> key;
  vector<int> left;
  vector<int> right;

public:
  void read()
  {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++)
    {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  vector<int> in_order()
  {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    inorderDFS(0, key, left, right, result);
    return result;
  }

  void inorderDFS(int root, const vector<int> &key, const vector<int> &left, const vector<int> &right, vector<int>& result)
  {
    if(left[root] == -1 && right[root] == -1)
    {
      result.push_back(key[root]);
      return;
    }     

    if(left[root] != -1)
      inorderDFS(left[root], key, left, right, result);

    result.push_back(key[root]);

    if(right[root] != -1)
      inorderDFS(right[root], key, left, right, result);    
  }

  vector<int> pre_order()
  {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    preorderDFS(0, key, left, right, result);
    return result;
  }

  void preorderDFS(int root, const vector<int> &key, const vector<int> &left, const vector<int> &right, vector<int>& result)
  {
    if(left[root] == -1 && right[root] == -1)
    {
      result.push_back(key[root]);
      return;
    }     

    result.push_back(key[root]);

    if(left[root] != -1)
      preorderDFS(left[root], key, left, right, result);

    if(right[root] != -1)
      preorderDFS(right[root], key, left, right, result);   
  }

  vector<int> post_order()
  {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    postorderDFS(0, key, left, right, result);
    return result;
  }

  void postorderDFS(int root, const vector<int> &key, const vector<int> &left, const vector<int> &right, vector<int>& result)
  {
    if(left[root] == -1 && right[root] == -1)
    {      
      result.push_back(key[root]);
      return;
    }         

    if(left[root] != -1)
      postorderDFS(left[root], key, left, right, result);

    if(right[root] != -1)
      postorderDFS(right[root], key, left, right, result);  

    result.push_back(key[root]);  
  }
  
};

void print(vector<int> a)
{
  for (size_t i = 0; i < a.size(); i++)
  {
    if (i > 0)
    {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space()
{
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main(int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024; // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
    if (rl.rlim_cur < kStackSize)
    {
      rl.rlim_cur = kStackSize;
      result = setrlimit(RLIMIT_STACK, &rl);
      if (result != 0)
      {
        std::cerr << "setrlimit returned result = " << result << std::endl;
      }
    }
  }
#endif

  return main_with_large_stack_space();
}
