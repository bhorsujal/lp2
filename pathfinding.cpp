#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int x, y;
    int g, h;

    Node(int _x, int _y, int _g, int _h)
    {
        x = _x;
        y = _y;
        g = _g;
        h = _h;
    }

    int f() const
    {
        return g + h;
    }
    bool operator>(const Node &other) const
    {
        return f() > other.f();
    }
};
int Heuristic(int sx, int sy, int gx, int gy)
{
    return abs(sx - gx) + abs(sy - gy);
}

bool isValid(int x, int y, vector<vector<int>> &grid)
{
    return (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] == 0);
}

void ConstructPath(map<string, string> &cameFrom, int sx, int sy, int gx, int gy)
{
    string current = to_string(gx) + "," + to_string(gy);
    vector<pair<int, int>> path;

    while (cameFrom.find(current) != cameFrom.end())
    {
        int comma = current.find(',');
        int x = stoi(current.substr(0, comma));
        int y = stoi(current.substr(comma + 1));
        path.push_back({x, y});
        current = cameFrom[current];
    }
    path.push_back({sx, sy});
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (auto [x, y] : path)
        cout << "(" << x << "," << y << ") ";
    cout << endl;
}

void astarSearch(int sx, int sy, int gx, int gy, vector<vector<int>> grid)
{
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    map<string, string> cameFrom;
    map<string, int> gScore;

    vector<int> dx = {-1, 1, 0, 1};
    vector<int> dy = {0, 0, -1, 1};

    openSet.emplace(sx, sy, 0, Heuristic(sx, sy, gx, gy));

    while (!openSet.empty())
    {
        Node current = openSet.top();
        openSet.pop();

        if (visited[current.x][current.y])
            continue;
        visited[current.x][current.y] = true;

        if (current.x == gx && current.y == gy)
        {
            cout << "Path Found" << endl;
            ConstructPath(cameFrom, sx, sy, gx, gy);
            return;
        }

        for (int d = 0; d < 4; d++)
        {
            int nx = current.x + dx[d];
            int ny = current.y + dy[d];

            if (isValid(nx, ny, grid) && !visited[nx][ny])
            {
                int newG = current.g + 1;
                string from = to_string(current.x) + "," + to_string(current.y);
                string to = to_string(nx) + "," + to_string(ny);

                if (!gScore.count(to) || newG < gScore[to])
                {
                    gScore[to] = newG;
                    cameFrom[to] = from;
                    int newH = Heuristic(nx, ny, gx, gy);
                    openSet.emplace(nx, ny, newG, newH);
                }
            }
        }
    }
    cout << "Path no6 found" << endl;
}

int main()
{
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}};

    int sx = 0;
    int sy = 0;
    int gx = 4;
    int gy = 4;

    astarSearch(sx, sy, gx, gy, grid);

    return 0;
}
