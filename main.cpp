#include <iostream>
#include <algorithm>
#include <limits>
#include <string>
#include <ctime>
#include <random>
#include <chrono>
#include <fstream>
using namespace std;

struct Tree {
  int data;
  Tree *left;
  Tree *right;
};

void del(Tree *&t) {
  if (t != NULL) {
    del(t->left);
    del(t->right);
    delete t;
    t = NULL;
  }
}

Tree *NewTree(int data) {
  Tree *newNode = new Tree();
  newNode->data = data;
  newNode->left = newNode->right = NULL;
  return newNode;
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
  return root;
}

void PrintTime(const int k, bool is_sorted, string filename) {
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
  const int k = 40000;
  const int step = 100;
  for (int i = 0; step * i < k; i++) {
    PrintTime(step * i, false, "unsorted1.txt");
    PrintTime(step * i, true, "sorted1.txt");
  }
}
