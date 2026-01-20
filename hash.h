#include <iostream>
#include <string>
#include <cmath>
// You are free to use additional libraries as long as it's not PROHIBITED per instruction.

using namespace std;

struct Node {
    string token;
    Node* next;
    Node(const string& t) : token(t), next(nullptr) {}
};

int hash_function(string text, int k);