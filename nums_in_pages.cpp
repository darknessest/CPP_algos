//
// Created by Alexey on 29/09/2019.
//

#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int steps[11] = {1, 1, 20, 300, 4000, 50000, 600000, 7000000, 80000000, 900000000};

const int steps_of_zeroes[11] = {1, 1, 11, 192, 2893, 38894, 488895, 5888896, 68888897, 788888898};

const int second_level_zeroes[11] = {1, 1, 11, 119, 1299, 13999, 149999, 1599999, 16999999, 179999999};

void optimizedCount(const string &N) {
    const int len = N.length();
    int base = 0;
    int storage[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    string huge;
    int another = 0;

    for (int l = 0; l < len - 2; ++l) {
        int x = *(N.begin() + l) - '0';
        another += x*(int) pow(10, len - l - 1);

        // base = a * 10^b + ...
        base += steps[len - l - 1]*(x);

        //for zeroes
        if (x > 0) {
            if (l > 0)
                storage[0] += second_level_zeroes[len - l] + steps[len - l - 1]*(x - 1);
            else
                storage[0] += steps_of_zeroes[len - l - 1] + steps[len - l - 1]*(x - 1);

            //correction for non-zero's
            storage[x] += 1;
        }

        //doing leading digits "multiplication"
        for (int k = 1; k < x; ++k) {
            storage[k] += (int) pow(10, len - 1 - l);
        }
        //correction for front digits
        for (int i = 0; i < l; ++i) {
            int z = *(N.begin() + i) - '0';
            storage[z] += (int) pow(10, len - 1 - l)*x;
        }
    }

    //for other digits
    for (int j = 1; j < 10; ++j) {
        storage[j] += base;
    }
    //adding last 100 numbers
    for (int i = another + 1; i <= stoi(N); ++i) {
        huge += to_string(i);
    }
    //final count of digits with last 100 numbers
    for (int i = 0; i < 10; ++i) {
        storage[i] += count(huge.begin(), huge.end(), '0' + i);
        cout << storage[i] << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int number = 0;
    cin >> number;

    optimizedCount(to_string(number));
}