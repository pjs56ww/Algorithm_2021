#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = -1;

    sort(dist.begin(), dist.end());

    for (int i = 0; i < weak.size(); i++) {
        int tmp = weak[0] + n;
        for (int j = 1; j < weak.size(); j++) {
            weak[j - 1] = weak[j];
        }
        weak[weak.size() - 1] = tmp;

        do {
            int i = 0;
            int j = 0;

            for (j = 0; j < dist.size(); j++) {
                int f = weak[i] + dist[j];
                while (f >= weak[i]) {
                    i++;
                    if (i == weak.size()) {
                        break;
                    }
                }
                if (i == weak.size()) {
                    break;
                }
            }
            if (i == weak.size()) {
                if (answer == -1 || j + 1 < answer) {
                    answer = j + 1;
                }
            }
        } while (next_permutation(dist.begin(), dist.end()));
    }
    return answer;
}

int main() {
    vector <int> weak = { 1, 5, 6, 10 };
    vector <int> dist = { 1, 2, 3, 4 };
    cout << solution(12, weak, dist) << endl;

    return 0;
}