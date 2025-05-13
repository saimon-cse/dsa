// Hash Table Implementation in C++
// This implementation uses separate chaining to handle collisions

#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <string>

using namespace std;

// Template Hash Table class
template<typename K, typename V>
class HashTable {
private:
    // Hash table size (number of buckets)
    int tableSize;
    
    // Vector of lists to store key-value pairs
    vector<list<pair<K, V>>> table;
    
    // Hash function
    int hashFunction(const K& key) {
        // Use the standard hash function
        size_t hashValue = hash<K>{}(key);
        return hashValue % tableSize;
    }
    
public:
    // Constructor
    HashTable(int size = 10) : tableSize(size) {
        table.resize(tableSize);
    }
    
    // Insert a key-value pair
    void insert(const K& key, const V& value) {
        // Find the bucket for this key
        int index = hashFunction(key);
        
        // Check if key already exists
        for (auto& kv : table[index]) {
            if (kv.first == key) {
                // Update value if key exists
                kv.second = value;
                return;
            }
        }
        
        // Add new key-value pair to the bucket
        table[index].push_back(make_pair(key, value));
    }
    
    // Remove a key-value pair
    bool remove(const K& key) {
        // Find the bucket for this key
        int index = hashFunction(key);
        
        // Iterate through the bucket
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                // Remove key-value pair if found
                table[index].erase(it);
                return true;
            }
        }
        
        // Key not found
        return false;
    }
    
    // Search for a key and return its value
    bool search(const K& key, V& value) {
        // Find the bucket for this key
        int index = hashFunction(key);
        
        // Iterate through the bucket
        for (const auto& kv : table[index]) {
            if (kv.first == key) {
                // Key found, return the value
                value = kv.second;
                return true;
            }
        }
        
        // Key not found
        return false;
    }
    
    // Get all keys in the hash table
    vector<K> getKeys() {
        vector<K> keys;
        
        // Iterate through all buckets
        for (int i = 0; i < tableSize; i++) {
            for (const auto& kv : table[i]) {
                keys.push_back(kv.first);
            }
        }
        
        return keys;
    }
    
    // Get all values in the hash table
    vector<V> getValues() {
        vector<V> values;
        
        // Iterate through all buckets
        for (int i = 0; i < tableSize; i++) {
            for (const auto& kv : table[i]) {
                values.push_back(kv.second);
            }
        }
        
        return values;
    }
    
    // Print the hash table
    void display() {
        for (int i = 0; i < tableSize; i++) {
            cout << "Bucket " << i << ": ";
            for (const auto& kv : table[i]) {
                cout << "(" << kv.first << ", " << kv.second << ") ";
            }
            cout << endl;
        }
    }
    
    // Get the current load factor
    float loadFactor() {
        int itemCount = 0;
        
        // Count total number of elements
        for (int i = 0; i < tableSize; i++) {
            itemCount += table[i].size();
        }
        
        return static_cast<float>(itemCount) / tableSize;
    }
    
    // Get the size of the largest bucket
    int maxBucketSize() {
        int maxSize = 0;
        
        for (int i = 0; i < tableSize; i++) {
            int bucketSize = table[i].size();
            if (bucketSize > maxSize) {
                maxSize = bucketSize;
            }
        }
        
        return maxSize;
    }
    
    // Resize the hash table
    void resize(int newSize) {
        // Save old table
        vector<list<pair<K, V>>> oldTable = table;
        
        // Reset table with new size
        tableSize = newSize;
        table.clear();
        table.resize(tableSize);
        
        // Rehash all elements
        for (const auto& bucket : oldTable) {
            for (const auto& kv : bucket) {
                insert(kv.first, kv.second);
            }
        }
    }
};

// Example usage with string keys and int values
int main() {
    HashTable<string, int> ht(7);
    
    // Insert some key-value pairs
    ht.insert("apple", 5);
    ht.insert("banana", 8);
    ht.insert("cherry", 12);
    ht.insert("date", 15);
    ht.insert("elderberry", 20);
    ht.insert("fig", 3);
    ht.insert("grape", 7);
    
    // Display the hash table
    cout << "Hash Table Contents:" << endl;
    ht.display();
    
    // Search for keys
    int value;
    if (ht.search("apple", value)) {
        cout << "\nFound apple with value: " << value << endl;
    } else {
        cout << "\napple not found" << endl;
    }
    
    if (ht.search("orange", value)) {
        cout << "Found orange with value: " << value << endl;
    } else {
        cout << "orange not found" << endl;
    }
    
    // Remove a key
    if (ht.remove("banana")) {
        cout << "\nRemoved banana successfully" << endl;
    } else {
        cout << "\nCouldn't find banana to remove" << endl;
    }
    
    // Display updated hash table
    cout << "\nAfter removal:" << endl;
    ht.display();
    
    // Get all keys and values
    vector<string> keys = ht.getKeys();
    vector<int> values = ht.getValues();
    
    cout << "\nAll keys: ";
    for (const auto& key : keys) {
        cout << key << " ";
    }
    cout << endl;
    
    cout << "All values: ";
    for (const auto& val : values) {
        cout << val << " ";
    }
    cout << endl;
    
    // Get load factor and max bucket size
    cout << "\nLoad factor: " << ht.loadFactor() << endl;
    cout << "Max bucket size: " << ht.maxBucketSize() << endl;
    
    // Resize the hash table
    cout << "\nResizing hash table to size 15..." << endl;
    ht.resize(15);
    
    // Display after resizing
    cout << "After resizing:" << endl;
    ht.display();
    cout << "New load factor: " << ht.loadFactor() << endl;
    
    // Example with integer keys
    HashTable<int, string> ht2(5);
    ht2.insert(1, "one");
    ht2.insert(2, "two");
    
    ht2.insert(3, "three");
    ht2.insert(11, "eleven"); // Should hash to the same bucket as 1
    ht2.insert(22, "twenty-two"); // Should hash to the same bucket as 2
    
    cout << "\nHash Table with Integer Keys:" << endl;
    ht2.display();
    
    return 0;
}