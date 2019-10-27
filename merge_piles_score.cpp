#include <queue>
#include <iostream>
#include <list>

using namespace std;
class custom_pair {
 protected:
    int l;
    int r;
    list<int>::iterator addrL;
    list<int>::iterator addrR;
 public:
    [[nodiscard]] int getL() const {
        return l;
    }
    [[nodiscard]] int getR() const {
        return r;
    }
    [[nodiscard]] list<int>::iterator getAddrL() const {
        return addrL;
    }
    [[nodiscard]] list<int>::iterator getAddrR() const {
        return addrR;
    }
    explicit custom_pair(const int &a, const int &b, const list<int>::iterator &p1, const list<int>::iterator &p2) {
        l = a;
        r = b;
        addrL = p1;
        addrR = p2;
    }
};

class max_pair: public custom_pair {
 public:
    max_pair(const int &a,
             const int &b,
             const list<int>::iterator &p1,
             const list<int>::iterator &p2) : custom_pair(a, b, p1, p2) {}

    [[nodiscard]] string print() const {
        return string(to_string(l) + "\t-\t" + to_string(r));
    }

    friend bool operator<(const max_pair &one, const max_pair &two) {
        return (one.l + one.r) < (two.l + two.r);
    }
};
class min_pair: public custom_pair {
 public:
    min_pair(const int &a,
             const int &b,
             const list<int>::iterator &p1,
             const list<int>::iterator &p2) : custom_pair(a, b, p1, p2) {}

    [[nodiscard]] string print() const {
        return string(to_string(l) + "\t-\t" + to_string(r));
    }

    friend bool operator<(const min_pair &one, const min_pair &two) {
        return (one.l + one.r) > (two.l + two.r);
    }
};

template<typename PAIR>
void print_heap(priority_queue<PAIR> heap) {
    while (!heap.empty()) {
        cout << heap.top().print() << "\n";
        heap.pop();
    }
}
void print_list(list<int> &v) {
    for (auto x: v) {
        cout << x << " ";
    }
    cout << '\n';
}

template<typename PAIR>
void mergeAndUpdate(list<int> &elements, priority_queue<PAIR> &heap, int &counter) {

    // if only last two elements are left
    if (elements.size() == 2) {
        counter += (elements.front() + elements.back());
        elements.clear();
        return;
    }

    // deleting top pair
    // O(const)
    PAIR temp = heap.top();
    heap.pop();

    // check whether pair exist at all
    cout << temp.getL() << " " << temp.getR() << " " << *temp.getAddrL()
         << " " << *temp.getAddrR() << '\n';
    if (temp.getR() == *temp.getAddrR() && temp.getL() == *temp.getAddrL()) {
        list<int>::iterator newAddr, newAddrPrev, newAddrNext;

        // updating list
        // 'replacing' old two heaps with a new merged heap
        // replacing left value
        *temp.getAddrL() = temp.getL() + temp.getR();
        counter += *temp.getAddrL();

        // deleting left, O(const)
        *temp.getAddrR() = -1;
        elements.erase(temp.getAddrR());

        // inserting new pairs to the heap
        // O(log n)
        newAddr = temp.getAddrL();
        if (newAddr == elements.begin()) {
            newAddrPrev = --elements.end();                 //next iter
            newAddrNext = ++temp.getAddrL();       //prev iter

        } else if (newAddr == --elements.end()) {
            newAddrPrev = --temp.getAddrL();       //next iter
            newAddrNext = elements.begin();                 //prev iter
        } else {
            newAddrPrev = --temp.getAddrL();
            newAddrNext = ++temp.getAddrL();
        }
        heap.push(PAIR(*newAddrPrev, *newAddr, newAddrPrev, newAddr));
        heap.push(PAIR(*newAddr, *newAddrNext, newAddr, newAddrNext));
    }
}

template<typename PAIR>
void counting(list<int> &v, priority_queue<PAIR> &heap, int &counter) {
    while (!v.empty()) {
        print_list(v);
        mergeAndUpdate(copy, heap, counter);
    }
    print_list(v);
}

int main() {

    priority_queue<min_pair> minHeap;
    priority_queue<max_pair> maxHeap;

    list<int> original, copy;
    int n = 0, temp = 0;
    int minCounter = 0, maxCounter = 0;
    cin >> n;
    // O(n)
    for (int i = 0; i < n; ++i) {
        cin >> temp;
        original.push_back(temp);
        copy.push_back(temp);
    }

    for (auto x1 = original.begin(), x2 = ++original.begin(); x2 != original.end(); ++x1, ++x2) {
        // O(log n)
        // can be improved with copy + reverse instead of separate insertions
        if (x2 == --original.end()) {
            minHeap.push(min_pair(*x2, *original.begin(), x2, original.begin()));
            maxHeap.push(max_pair(*x2, *original.begin(), x2, original.begin()));
        }
        {
            minHeap.push(min_pair(*x1, *x2, x1, x2));
            maxHeap.push(max_pair(*x1, *x2, x1, x2));
        }
    }

//    print_list(original);
//    cout << "min heap:\n";
//    print_heap(minHeap);
//    cout << "max heap:\n";
//    print_heap(maxHeap);

//    counting(original, maxHeap, maxCounter);
//    counting(original, minHeap, minCounter);

    while (!copy.empty()) {
//        print_list(copy);
        mergeAndUpdate(copy, minHeap, minCounter);
    }

    int i = 0;
    while (!original.empty() && i < 10) {
//        print_list(original);
        mergeAndUpdate(copy, maxHeap, maxCounter);
        ++i;
    }
    cout << minCounter << '\n';
    cout << maxCounter << '\n';
}
/*
9
1
5
17
4
3
2
20
1
8
 */

/*
3
1 2 3333
 */