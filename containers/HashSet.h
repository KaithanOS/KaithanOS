//
// Created by Zhiyang Lu on 12/03/24.
//

#ifndef KAITHANOS_HASHSET_H
#define KAITHANOS_HASHSET_H

#include <stdexcept>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include "Vector.h"

using namespace std;

template <typename T>
class HashSet {
private:
    Vector<Vector<T> > hashset;
    int buckets;
    int items;
    hash<T> hasher;

public:

    // Constructors and destructors

    HashSet() {
        Vector<T> bucket;
        Vector<Vector<T> > hs(16, bucket);
        hashset = hs;
        buckets = 16;
        items = 0;
    }

    int hash_code(T val) {
        return hasher(val) % buckets;
    }

    // Accessors

    int size() {
        return items;
    }

    bool empty() {
        return items == 0;
    }

    bool contains(T val) {
        return hashset.get(hash_code(val)).index(val) != -1;
    }

    // Add & remove

    bool add(T val) {
        if (contains(val)) {
            return false;
        } else if (items + 1 > (3 * buckets) / 4) {
            Vector<T> bucket;
            Vector<Vector<T> > new_set(2 * buckets, bucket);
            for (int i = 0; i < buckets; i++) {
                Vector<T> curr = hashset.get(i);
                for (int j = 0; j < curr.size(); j++) {
                    T item = curr.get(j);
                    new_set.get(hash_code(item)).push_back(item);
                }
            }
            hashset = new_set;
            buckets *= 2;
        }

        Vector<T>& bucket = hashset.get(hash_code(val));
        bucket.push_back(val);
        cout << hashset.get(hash_code(val)) << "\n";
        items++;
        return true;
    }

    bool remove(T val) {
        if (!contains(val)) {
            return false;
        } else if (buckets > 16 && items - 1 < buckets / 4) {
            Vector<T> bucket;
            Vector<Vector<T> > new_set(buckets / 2, bucket);
            for (int i = 0; i < buckets; i++) {
                Vector<T> curr = hashset.get(i);
                for (int j = 0; j < curr.size(); j++) {
                    T item = curr.get(j);
                    new_set.get(hash_code(item)).push_back(item);
                }
            }
            hashset = new_set;
            buckets /= 2;
        }

        Vector<T>& bucket = hashset.get(hash_code(val));
        bucket.remove(&val);
        items--;
        return true;
    }

    // Override operators



    // Debugging output


};


#endif //KAITHANOS_HASHSET_H
