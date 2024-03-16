//
// Created by Zhiyang Lu on 15/03/24.
//

#ifndef KAITHANOS_HASHMAP_H
#define KAITHANOS_HASHMAP_H

#include <stdexcept>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include "Vector.h"
#include "Pair.h"

using namespace std;

template <typename T, typename U>
class HashMap {
private:
    Vector<Vector<Pair<T, U> > > hashmap;
    int buckets;
    int items;
    hash<T> hasher;

public:

    // Constructors and destructors

    HashMap() {
        Vector<Pair<T, U> > bucket;
        Vector<Vector<Pair<T, U> > > hm(16, bucket);
        hashmap = hm;
        buckets = 16;
        items = 0;
    }

    int hash_code(T key) {
        return hasher(key) % buckets;
    }

    // Accessors

    int size() {
        return items;
    }

    bool empty() {
        return items == 0;
    }

    bool contains_key(T key) {
        Vector<Pair<T, U> >& bucket = hashmap.get(hash_code(key));
        for (int i = 0; i < bucket.size(); i++) {
            if (bucket.get(i).get_first() == key) {
                return true;
            }
        }
        return false;
    }

    U& get(T key) {
        Vector<Pair<T, U> >& bucket = hashmap.get(hash_code(key));
        for (int i = 0; i < bucket.size(); i++) {
            if (bucket.get(i).get_first() == key) {
                return bucket.get(i).get_second();
            }
        }
        throw runtime_error("Could not retrieve item");
    }

    // Add & remove

    bool put(T key, U val) {
        bool added = false;
        Vector<Pair<T, U> >& bucket = hashmap.get(hash_code(key));
        for (int i = 0; i < bucket.size(); i++) {
            if (bucket.get(i).get_first() == key) {
                bucket.get(i).set_second(val);
                added = true;
            }
        }

        if (!added) {
            Pair<T, U> pair(key, val);
            bucket.push_back(pair);
            items++;
        }

        if (items > (3 * buckets) / 4) {
            Vector<Pair<T, U> > bucket;
            Vector<Vector<Pair<T, U> > > new_map(2 * buckets, bucket);
            for (int i = 0; i < buckets; i++) {
                Vector<Pair<T, U> >& curr = hashmap.get(i);
                for (int j = 0; j < curr.size(); j++) {
                    Pair<T, U> pair = curr.get(j);
                    new_map.get(hash_code(pair.get_first())).push_back(pair);
                }
            }
            hashmap = new_map;
            buckets *= 2;
        }
        return true;
    }

    bool remove(T key) {
        if (!contains_key(key)) {
            return false;
        } else if (items + 1 > (3 * buckets) / 4) {
            Vector<Pair<T, U> > bucket;
            Vector<Vector<Pair<T, U> > > new_map(buckets / 2, bucket);
            for (int i = 0; i < buckets; i++) {
                Vector<Pair<T, U> >& curr = hashmap.get(i);
                for (int j = 0; j < curr.size(); j++) {
                    Pair<T, U> pair = curr.get(j);
                    new_map.get(hash_code(pair.get_first())).push_back(pair);
                }
            }
            hashmap = new_map;
            buckets /= 2;
        }

        Vector<Pair<T, U> >& bucket = hashmap.get(hash_code(key));
        for (int i = 0; i < bucket.size(); i++) {
            if (bucket.get(i).get_first() == key) {
                bucket.remove(i);
            }
        }
        items--;
        return true;
    }

    // Override operators

    friend ostream& operator<<(ostream& os, HashMap<T, U>& map) {
        os << "[";
        for (int i = 0; i < map.buckets; i++) {
            Vector<Pair<T, U> >& curr = map.hashmap.get(i);
            for (int j = 0; j < curr.size(); j++) {
                os << curr.get(j) << ", ";
            }
        }
        os << "]";
        return os;
    }

    U& operator[](T key) {
        Vector<Pair<T, U> >& bucket = hashmap.get(hash_code(key));
        for (int i = 0; i < bucket.size(); i++) {
            if (bucket.get(i).get_first() == key) {
                return bucket.get(i).get_second();
            }
        }
        throw runtime_error("Could not retrieve item");
    }

    // Debugging output

    void debug() {
        for (int i = 0; i < hashmap.size(); i++) {
            cout << hashmap.get(i) << "\n";
        }
        cout << "size: " << items << "\n";
    }

};


#endif //KAITHANOS_HASHMAP_H
