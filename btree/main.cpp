#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
//#include <algorithm>
using namespace std;

struct Tree {
  int data;
  Tree *left;
  Tree *right;
};

int height(Tree *node) {
  if (node == NULL) {
    return -1;
  } else {
    int lh = height(node->left);
    int rh = height(node->right);
    return max(lh, rh) + 1;
  }
}
Tree *NewTree(int data) {
  Tree *newNode = new Tree();
  newNode->data = data;
  newNode->left = newNode->right = NULL;
  return newNode;
}

int getBalanceFactor(Tree *root) {
  if (root == NULL) {
    return -1;
  } else {
    return (height(root->left) - height(root->right));
  }
}

Tree *rightRotate(Tree *node) {
  Tree *l = node->left;
  Tree *t = l->right;
  l->right = node;
  node->left = t;
  return l;
}

Tree *leftRotate(Tree *node) {
  Tree *l = node->right;
  Tree *t = l->left;
  l->left = node;
  node->right = t;
  return l;
}

Tree *add(int data, Tree *root) {
  if (NULL == root) {
    root = NewTree(data);
  } else if (root->data > data) {
    if (root->left != NULL) {
      root->left = add(data, root->left);
    } else {
      root->left = new Tree;
      root->left->left = root->left->right = NULL;
      root->left->data = data;
    }
  } else {
    if (root->right != NULL) {
      root->right = add(data, root->right);
    } else {
      root->right = new Tree;
      root->right->left = root->right->right = NULL;
      root->right->data = data;
    }
  }
  int bf = getBalanceFactor(root);
  if (bf > 1 && data < root->left->data) {
    return rightRotate(root);
  } else if (bf < -1 && data > root->right->data) {
    return leftRotate(root);
  } else if (bf > 1 && data > root->left->data) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  } else if (bf < -1 && data < root->right->data) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

void PrintTime(const int k, bool is_sorted, const string &filename) {
  ofstream outf(filename, ios::app);
  int num[k];
  for (int j = 0; j < k; j++) {
    num[j] = j;
  }
  Tree *root = NULL;
  if (!is_sorted) {
    default_random_engine rng;
    shuffle(num, num + k, rng);
  }
  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < k; i++) {
    //int *a = new int[i];
    root = add(num[i], root);
  }
  auto end = std::chrono::system_clock::now();
  auto t = chrono::duration_cast<chrono::milliseconds>(end - start).count();
  cout << t << std::endl;
  outf << k << " " << t << "\n";

  //del(root);
}

int main() {
  const int k = 10000;
  const int step = 100;
  for (int i = 0; step * i < k + 1; i++) {
    PrintTime(step * i, false, "unsorted2.txt");
    PrintTime(step * i, true, "sorted2.txt");
  }

}
