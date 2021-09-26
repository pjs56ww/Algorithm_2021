#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

struct Robot {
    int time;
    int x;
    int y;
    int isLying;
};

int dx[] = { -1, 0, 0, 1 };
int dy[] = { 0, -1, 1, 0 };
int visited[101][101][2];
vector <vector<int>> _map;

bool inMap(int x, int y, int isL) {
    int N = _map.size();
    if (isL == 0) {
        if (x < 0 || y < 0 || x >= N || y + 1 >= N) return false;
        if (_map[x][y] || _map[x][y + 1]) return false;
    }
    else {
        if (x < 0 || y < 0 || x + 1 >= N || y >= N) return false;
        if (_map[x][y] || _map[x + 1][y]) return false;
    }
    return true;
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    int N = board.size();
    _map = board;
    memset(visited, 0, sizeof(visited));

    queue<Robot> q;
    q.push({ 0, 0, 0, 0 });
    while (!q.empty()) {
        Robot cur = q.front(); q.pop();
        if ((cur.isLying == 0 && cur.x == N - 1 && cur.y == N - 2) || (cur.isLying == 1 && cur.x == N - 2 && cur.y == N - 1)) {
            return cur.time;
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (!inMap(nx, ny, cur.isLying) || visited[nx][ny][cur.isLying]) continue;
            visited[nx][ny][cur.isLying] = 1;
            q.push({ cur.time + 1, nx, ny, cur.isLying });
        }
        if (cur.isLying == 0) { 
            if (cur.x + 1 <= N - 1 && !_map[cur.x + 1][cur.y] && !_map[cur.x + 1][cur.y + 1] && !visited[cur.x][cur.y + 1][1]) {
                q.push({ cur.time + 1, cur.x, cur.y + 1, 1 });
            }
            if (cur.x - 1 >= 0 && !_map[cur.x - 1][cur.y] && !_map[cur.x - 1][cur.y + 1] && !visited[cur.x - 1][cur.y + 1][1]) {
                q.push({ cur.time + 1, cur.x - 1, cur.y + 1, 1 });
            }
            if (cur.x + 1 <= N - 1 && !_map[cur.x + 1][cur.y + 1] && !_map[cur.x + 1][cur.y] && !visited[cur.x][cur.y][1]) {
                q.push({ cur.time + 1, cur.x, cur.y, 1 });
            }
            if (cur.x - 1 >= 0 && !_map[cur.x - 1][cur.y + 1] && !_map[cur.x - 1][cur.y] && !visited[cur.x - 1][cur.y][1]) {
                q.push({ cur.time + 1, cur.x - 1, cur.y, 1 });
            }
        }
        else {
            if (cur.y - 1 >= 0 && !_map[cur.x][cur.y - 1] && !_map[cur.x + 1][cur.y - 1] && !visited[cur.x + 1][cur.y - 1][0]) {
                q.push({ cur.time + 1, cur.x + 1, cur.y - 1, 0 });
            }
            if (cur.y + 1 <= N - 1 && !_map[cur.x][cur.y + 1] && !_map[cur.x + 1][cur.y + 1] && !visited[cur.x + 1][cur.y][0]) {
                q.push({ cur.time + 1, cur.x + 1, cur.y, 0 });
            }
            if (cur.y - 1 >= 0 && !_map[cur.x + 1][cur.y - 1] && !_map[cur.x][cur.y - 1] && !visited[cur.x][cur.y - 1][0]) {
                q.push({ cur.time + 1, cur.x, cur.y - 1, 0 });
            }
            if (cur.y + 1 <= N - 1 && !_map[cur.x + 1][cur.y + 1] && !_map[cur.x][cur.y + 1] && !visited[cur.x][cur.y][0]) {
                q.push({ cur.time + 1, cur.x, cur.y, 0 });
            }
        }
    }
    return answer;
}
int main() {
    vector<vector <int>> board = { {0, 0, 0, 1, 1}, {0, 0, 0, 1, 0}, {0, 1, 0, 1, 1}, {1, 1, 0, 0, 1}, {0, 0, 0, 0, 0} };
    cout << solution(board) << endl;
    return 0;
}