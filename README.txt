Aaron Shih and Benjamin Reichler
main.cpp tokenizes the input file and stores each line in texts[] one at a time. 
main.cpp then constructs the hash table by calling hashFunction() on each token in texts[] and pushing the new node onto the linked list in hashTable. Finally main.cpp loops through hashTable to print the first 5 slots, each slot length, and the standard deviation of all slots. 
hash.cpp calculates hash values in hash_function() by summing integer representations of each letter, and then using the modulo of the number of slots.
