#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define N 41 // Tamanho do labirinto


struct Point {
    int x, y;
};


int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};


int maze[N][N] = { /* Insira a matriz aqui */ };


bool isValid(int x, int y, vector<vector<bool>>& visited) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1 && !visited[x][y]);
}


Point findEntry() {
    for (int j = 0; j < N; j++) {
        if (maze[0][j] == 1) return {0, j};
    }
    return {-1, -1}; 
}

Point findExit() {
    for (int j = 0; j < N; j++) {
        if (maze[N-1][j] == 1) return {N-1, j};
    }
    return {-1, -1}; 
}


int solveMaze() {
    Point start = findEntry();
    Point end = findExit();
    
    if (start.x == -1 || end.x == -1) {
        cout << "Sem entrada ou saída válida!" << endl;
        return -1;
    }
    
    queue<pair<Point, int>> q;
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    
    q.push({start, 0});
    visited[start.x][start.y] = true;
    
    while (!q.empty()) {
        Point current = q.front().first;
        int steps = q.front().second;
        q.pop();
        
        if (current.x == end.x && current.y == end.y) {
            return steps; // Caminho encontrado
        }
        
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            
            if (isValid(nx, ny, visited)) {
                visited[nx][ny] = true;
                q.push({{nx, ny}, steps + 1});
            }
        }
    }
    
    return -1; // Caminho não encontrado
}

int main() {
    int result = solveMaze();
    if (result != -1)
        cout << "Menor caminho encontrado com " << result << " passos." << endl;
    else
        cout << "Não há caminho possível." << endl;
    return 0;
}
