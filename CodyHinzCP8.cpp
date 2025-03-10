class MKAverage {
public:
    MKAverage(int m, int k) {
        this->m = m;
        this->k = k;
    }

    void addElement(int num) {
        // Insert the new element into the appropriate multiset based on its value
        if (lo.empty() || num <= *lo.rbegin()) {
            lo.insert(num);
        } else if (hi.empty() || num >= *hi.begin()) {
            hi.insert(num);
        } else {
            mid.insert(num);
            s += num;
        }

        // Add the new element to the queue
        q.push(num);

        // If the queue size exceeds m, remove the oldest element
        if (q.size() > m) {
            int x = q.front();
            q.pop();
            if (lo.find(x) != lo.end()) {
                lo.erase(lo.find(x));
            } else if (hi.find(x) != hi.end()) {
                hi.erase(hi.find(x));
            } else {
                mid.erase(mid.find(x));
                s -= x;
            }
        }

        // Adjust the multisets to maintain the size constraints
        while (lo.size() > k) {
            int x = *lo.rbegin();
            lo.erase(prev(lo.end()));
            mid.insert(x);
            s += x;
        }
        while (hi.size() > k) {
            int x = *hi.begin();
            hi.erase(hi.begin());
            mid.insert(x);
            s += x;
        }
        while (lo.size() < k && mid.size()) {
            int x = *mid.begin();
            mid.erase(mid.begin());
            s -= x;
            lo.insert(x);
        }
        while (hi.size() < k && mid.size()) {
            int x = *mid.rbegin();
            mid.erase(prev(mid.end()));
            s -= x;
            hi.insert(x);
        }
    }

    int calculateMKAverage() {
        // If the queue size is less than m, return -1
        // Otherwise, calculate the average of the elements in the mid multiset
        return q.size() < m ? -1 : s / (q.size() - k * 2);
    }

private:
    int m, k;
    long long s = 0;  // Sum of elements in the mid multiset
    queue<int> q;  // Queue to maintain the order of elements
    multiset<int> lo, mid, hi;  // Multisets to store elements in sorted order
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */