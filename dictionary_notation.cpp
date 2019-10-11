#include <iostream>
#include <map>

using namespace std;

const int diffs[7] = {0, 1, 26, 1976, 98176, 3987776, 143150176};

int fact(const int &upper, const int &number) {
    int answer = 1;
    if (number > 0)
        for (int i = upper - number + 1; i <= upper; ++i) {
            answer *= i;
        }
    return answer;
}

void update_map(map<char, int> &_map, const char &starting_letter) {
    _map.find(starting_letter)->second = 0;
    for (auto x = _map.find(starting_letter); x != _map.end(); ++x) {
        --x->second;
    }
}
void restore_map(map<char, int> &_map) {
    int a = 1;
    for (auto &x : _map) {
        x.second = a++;
    }
}
int analyze(const int array[], const int &length) {
    int total_difference = 0;
    if (length > 1)
        for (int i = 0; i < length - 1; ++i)
            if (array[i] > 1)
                total_difference += diffs[length - i - 1]*(array[i] - 1);

    return total_difference;
}

int main() {
    map<char, int> alphabet;
    for (int j = 0; j < 26; ++j)
        alphabet.insert(pair<char, int>('a' + j, j + 1));

    int total_num;
    cin >> total_num;

    for (int x = 1; x <= total_num; ++x) {
        string temp_string;
        cin >> temp_string;

        int decr = 0;
        int converted_number[temp_string.length()];

        for (int i = 0; i < (int) temp_string.length(); ++i) {
            decr += alphabet[temp_string[i]]*fact(26 - i, (int) temp_string.length() - i - 1);
            converted_number[i] = alphabet[temp_string[i]];
            update_map(alphabet, temp_string[i]);
        }

        cout << decr - analyze(converted_number, temp_string.length()) << '\n';
        restore_map(alphabet);
    }
}