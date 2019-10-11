#include <iostream>

using std::cin;
using std::cout;

#define N 100

const int prime[N] =
    {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109,
     113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
     241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379,
     383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521,
     523, 541};

const int numbers[] = {
    1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260, 1680, 2520, 5040, 7560, 10080,
    15120, 20160, 25200, 27720, 45360, 50400, 55440, 83160, 110880, 166320, 221760, 277200,
    332640, 498960, 554400, 665280, 720720, 1081080, 1441440, 2162160, 2882880, 3603600,
    4324320, 6486480, 7207200, 8648640, 10810800, 14414400, 17297280, 21621600, 32432400,
    36756720, 43243200, 61261200, 73513440, 110270160, 122522400, 147026880, 183783600,
    245044800, 294053760, 367567200, 551350800, 698377680, 735134400
};

//local maximums of divisors
const int divisors_of_numbers[] = {
    1, 2, 3, 4, 6, 8, 9, 10, 12, 16, 18, 20, 24, 30, 32, 36, 40, 48, 60, 64, 72, 80, 84, 90, 96, 100, 108, 120, 128,
    144, 160, 168, 180, 192, 200, 216, 224, 240, 256, 288, 320, 336, 360, 384, 400, 432, 448, 480, 504, 512,
    576, 600, 640, 672, 720, 768, 800, 864, 896, 960, 1008, 1024, 1152, 1200, 1280, 1344
};

int the_last_mid = 0;

unsigned int Count(unsigned int a) {
    unsigned int count1 = 1, count2 = 1, k = 0, i;
    if (a == 1 || a == 2)
        return a;
    while ((a & 1) == 0) {
        k++;
        a >>= 1;
    }
    if (a == 1)
        return k + 1;
    else
        count1 = k + 1;
    for (i = 0; i < N && prime[i]*prime[i] <= a; i++) {
        k = 0;
        while (a%prime[i] == 0) {
            k++;
            a /= prime[i];
        }
        count1 *= (k + 1);
    }
    if (a == 1)
        return count1;
    if (i < N)
        return count1 << 1;

    for (i = prime[N - 1] + 2; i*i <= a; i += 2) {
        k = 0;
        while (a%i == 0) {
            k++;
            a /= i;
        }
        count2 *= (k + 1);
    }
    if (a > 1)
        count2 <<= 1;
    return count1*count2;
}

template<typename T>
inline T getMax(const T &a, const T &b) { return a > b ? a : b; }
int binarySearch(const int arr[], const int l, const int r, const int &x) {
//    not_found_flag = false; //TODO: check this one
    if (r >= l) {
        int mid = l + (r - l)/2;
        the_last_mid = mid;
        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);

        return binarySearch(arr, mid + 1, r, x);
    }

    // We reach here when element is not
    // present in array
//    not_found_flag = true;
    return -1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int a = 0, b = 0, temp = 0, biggest = 0;
    cin >> a >> b;
    int potential_mid = binarySearch(numbers, 0, 66, b);

    //if everything is ok (b belongs to "top" numbers)
    if (potential_mid != -1) {
        cout << divisors_of_numbers[potential_mid];
    }
    //else check closest neighbors
    else {
        if (numbers[the_last_mid + 1] >= a && numbers[the_last_mid + 1] <= b) {
            cout << divisors_of_numbers[the_last_mid + 1];
        } else if (numbers[the_last_mid] >= a && numbers[the_last_mid] <= b) {
            cout << divisors_of_numbers[the_last_mid];
        } else if (numbers[the_last_mid - 1] >= a && numbers[the_last_mid - 1] <= b) {
            cout << divisors_of_numbers[the_last_mid - 1];
        }
            //or count for this range
        else {
            for (unsigned int i = a; i <= b; ++i) {
                temp = (int) Count(i);
                biggest = getMax(temp, biggest);
            }
            cout << biggest;
        }
    }
}