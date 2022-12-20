#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node
{
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

static bool isFirstNode = true;

void dfs(const vector<Node> &tree, const Node &root, bool &isValid, int &prev, int parent, bool isLeft)
{
  if (root.left == -1 && root.right == -1)
  {
    if (!isFirstNode)
    {
      if (root.key > prev)
      {
        isValid = false;
        return;
      }
      else if (root.key == prev)
      {
        if (isLeft && root.key >= parent)
        {
          isValid = false;
          return;
        }
      }
    }
    else
    {
      prev = root.key;
      isFirstNode = false;
      return;
    }
  }

  if (root.right != -1)
    dfs(tree, tree[root.right], isValid, prev, parent, isLeft);

  if (!isFirstNode)
  {
    if (root.key > prev)
    {
      isValid = false;
      return;
    }
    else if (root.key == prev)
    {
      if (isLeft && root.key >= parent)
      {
        isValid = false;
        return;
      }
    }
    else
    {
      prev = root.key;
    }
  }
  else
  {
    isFirstNode = false;
    prev = root.key;
  }

  if (root.left != -1)
  {
    int leftParent = root.key;
    bool isLeft = true;
    dfs(tree, tree[root.left], isValid, prev, leftParent, isLeft);    
  }
}

bool IsBinarySearchTree(const vector<Node> &tree)
{
  // Implement correct algorithm here
  if (tree.empty())
    return true;
  bool isValid = true;
  int prev = -1;
  dfs(tree, tree[0], isValid, prev, -1, false);
  return isValid;
}

int main()
{
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i)
  {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree))
  {
    cout << "CORRECT" << endl;
  }
  else
  {
    cout << "INCORRECT" << endl;
  }
  return 0;
}

