/*
CSE 310 Hash Function DIY Contest
Instructor: Yiran "Lawrence" Luo
Your name(s):
Your team alias: 
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "hash.h"
using namespace std;

int main() {

    int k = 0;
    int n = 0;
    string texts[500];

    // WARNING: Start of the tokenizer that loads the input from std::cin, DO NOT change this part!
    cin >> k;
    string line;
    getline(cin, line);

    while (getline(cin, line)) {
        texts[n] = line;
        n++;
    }
    // WARNING: End of the tokenizer, DO NOT change this part!

    // By this point, k is the # of slots, and n is the # of tokens to fit in
    // texts[] stores the input sequence of tokens/keys to be inserted into your hash table

    // The template is able to be compiled by running 
    //   make
    //   ./encoder < inputs/sample_input.txt
    // which puts out the placeholders only.

    // Your time to shine starts now
    Node* hashTable[100] = {nullptr}; 
    for (int i = 0; i < n; i++) {
        int slot = hash_function(texts[i], k);
        if (slot < 0 || slot >= k) slot = 0; // safety check

        Node* newNode = new Node(texts[i]);
        if (!hashTable[slot]) {
            hashTable[slot] = newNode;
        } else {
            Node* curr = hashTable[slot];
            while (curr->next) curr = curr->next;
            curr->next = newNode;
        }
    }
    cout << "==== Printing the contents of the first 5 slots ====" << endl;
    for (int i = 0; i < 5 && i < k; ++i) {
        cout << "Slot " << i << ":";
        Node* curr = hashTable[i];
        while (curr) {
            cout << " " << curr->token;
            curr = curr->next;
        }
        cout << endl;
    }

    cout << "==== Printing the slot lengths ====" << endl;
    int lengths[100] = {0};
    for (int i = 0; i < k; ++i) {
        Node* curr = hashTable[i];
        while (curr) {
            lengths[i]++;
            curr = curr->next;
        }
        cout << "Slot " << i << ": " << lengths[i] << endl;
    }
    cout << "==== Printing the standard deviation =====" << endl;

    double sum = 0.0;
    for (int i = 0; i < k; ++i) sum += lengths[i];
    double mean = sum / k;

    double sq_diff = 0.0;
    for (int i = 0; i < k; ++i) sq_diff += (lengths[i] - mean) * (lengths[i] - mean);

    double stddev = sqrt(sq_diff / k);
    cout << fixed << setprecision(4) << stddev << endl;

    for (int i = 0; i < k; ++i) {
        Node* curr = hashTable[i];
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
    }
    return 0;
}