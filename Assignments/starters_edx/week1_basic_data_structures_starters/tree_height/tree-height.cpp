#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class Node;

class Node
{
public:
  int key;
  Node *parent;
  std::vector<Node *> children;

  Node()
  {
    this->parent = NULL;
  }

  void setParent(Node *theParent)
  {
    parent = theParent;
    parent->children.push_back(this);
  }
};

int getTreeHeight(vector<Node> &nodes, int root)
{
  Node *rootNode = &nodes[root];
  if (rootNode == NULL)
    return 0;

  int childSize = rootNode->children.size();
  vector<int> childs;  
  childs.resize(childSize);
  int count = 0;
  while(count < childSize)
  {
    childs[count] = rootNode->children[count]->key;
    count ++;
  }
  count = 0;
  int maxHeight = 0;
  while(count < childSize)
  {
    int height = getTreeHeight(nodes, childs[count]);
    maxHeight = max(height, maxHeight);
    count ++;
  }

  return 1 + maxHeight;
}

vector<Node> makeTree(int& root, int size, vector<int> parentIndexVec)
{ 
  std::vector<Node> nodes;
  nodes.resize(size);
  for (int child_index = 0; child_index < size; child_index++)
  {
    if (parentIndexVec[child_index] >= 0)
        nodes[child_index].setParent(&nodes[parentIndexVec[child_index]]);
    else
    {
      root = child_index;
    }        
      nodes[child_index].key = child_index;
  }
  return nodes;
}

void testAllTreeHeight(int testcase)
{
  string path = "C:/Users/CSK/git/UCSanDiegoX-ALGS201x-Data-Structures-Fundamentals-Assignments/Assignments/starters_edx/week1_basic_data_structures_starters/tree_height/tests/";
  ifstream myTestFile;
  ifstream myAnswerFile;
  stringstream ss;
  int testSize = 0;  
  int answerHeight = 0;
  vector<int> parentIndexVec;
  vector<Node> nodes;
  int count = 1;

  while (count <= testcase)
  {
    ss << setfill('0') << setw(2) << to_string(count);
    string testFileName = path + ss.str();
    //cout << testFileName << endl;
    myTestFile.open(testFileName);
    string answerFileName = path + ss.str() + ".a";
    myAnswerFile.open(answerFileName);
    ss.str("");    

    if (myTestFile.is_open() && myAnswerFile.is_open())
    {
      int lineCount = 0;
      while (myTestFile)
      {
        if(lineCount == 0)
          myTestFile >> testSize;
        else
        {
          int value = 0;
          while(myTestFile >> value)
          {
            parentIndexVec.push_back(value);
          }
        }
        lineCount ++; 
      }        
      
      while (myAnswerFile)
        myAnswerFile >> answerHeight;

      myTestFile.close();
      myAnswerFile.close();
    }

    // cout << answerString << endl;
    // cout << testString << endl;
    int root = 0;
    nodes = makeTree(root, testSize, parentIndexVec);
    //cout << root << " " << testSize << " " << parentIndexVec[1] << endl;
    int result = getTreeHeight(nodes, root);
    //cout << result << " " << answerHeight << endl;
    if (result != answerHeight)
      break;
    else
    {
      count ++;
      parentIndexVec.clear();
      nodes.clear();
    }      
  }

  if (count > testcase)
    cout << "Pass" << endl;
  else
    cout << "fail at: " << count << endl;
}


int main_with_large_stack_space()
{
  std::ios_base::sync_with_stdio(0);
  int n;
  // cout << "input size: " << endl;
  std::cin >> n;

  int root = 0;
  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++)
  {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else
      root = child_index;
    nodes[child_index].key = child_index;
  }

  /*Replace this code with a faster implementation
  int maxHeight = 0;
  for (int leaf_index = 0; leaf_index < n; leaf_index++)
  {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
      height++;
    maxHeight = std::max(maxHeight, height);
  }
  */

  int maxHeight = getTreeHeight(nodes, root);

  // cout << "height: " << endl;
  std::cout << maxHeight << std::endl;
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
  //gcc -Wl,--stack,16777216 -o file.exe file.cpp for larger stack size
  testAllTreeHeight(24);
  return main_with_large_stack_space();
}
