#include <iostream>
#include <random>

using namespace std;

struct node
{
  int x, y;
  bool top = true;
  bool bottom = true;
  bool left = true;
  bool right = true;
  bool visited;
};

void grid_coords_setup(vector<vector<node>>& grid, int rows, int cols) {
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      grid[row][col].x = row;
      grid[row][col].y = cols;
    }
  }
}

vector<pair<int, int>> get_unvisited_neighbours(vector<vector<node>>& grid, int x, int y, int rows, int cols) {
  vector<pair<int, int>> neigbours;
  const int dx[] = {-1, 0, 1, 0};
  const int dy[] = {0, 1, 0, -1};
  
  for (int dir = 0; dir < 4; ++dir) {
    int nx = x + dx[dir];
    int ny = y + dy[dir];
  
    if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
      if (!grid[nx][ny].visited) {
        neigbours.push_back({nx, ny});
      }
    }
  }
  return neigbours;
}

void remove_walls(vector<vector<node>>& grid, int curr_x, int curr_y, int neighbour_x, int neighbour_y ) {
  if (curr_x == neighbour_x && curr_y < neighbour_y) {
    grid[curr_x][curr_y].top = false;
    grid[neighbour_x][neighbour_y].bottom = false;
  }

  if (curr_y == neighbour_y && curr_x < neighbour_x) {
    grid[curr_x][curr_y].right = false;
    grid[neighbour_x][neighbour_y].left = false;
  }

  if (curr_x == neighbour_x && curr_y > neighbour_y) {
    grid[curr_x][curr_y].bottom = false;
    grid[neighbour_x][neighbour_y].top = false;
  }

  if (curr_y == neighbour_y && curr_x > neighbour_x) {
    grid[curr_x][curr_y].left = false;
    grid[neighbour_x][neighbour_y].right = false;
  }
}

void dfs(vector<vector<node>>& grid, int curr_x, int curr_y,  int rows, int cols) {
  std::random_device rd;
  std::mt19937 gen(rd());
  grid[curr_x][curr_y].visited = true;
  
  while (true) {
    vector<pair<int, int>> neighbours = get_unvisited_neighbours(grid, curr_x, curr_y, rows, cols);
    if (neighbours.empty()) {
      break;
    }
    std::uniform_int_distribution<> dist(0, neighbours.size() - 1);
    auto [nx, ny] = neighbours[dist(gen)];

    remove_walls(grid, curr_x, curr_y, nx, ny);

    
    dfs(grid, nx, ny, rows, cols);
  }
}

void print_maze(vector<vector<node>>& grid, int rows, int cols) {
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      node curr_node = grid[row][col];
      if (curr_node.top == true) {
        cout << "+---";
      } else {
        cout << "+   ";
      }
    }
    cout << "+";
    cout << "\n";
    for (int col = 0; col < cols; ++col) {
      node curr_node = grid[row][col];
      if (curr_node.left == true) {
        cout << "|";
      } else {
        cout << " ";
      }
      cout << "   ";
    }
    cout << "|";
    cout << "\n";
  }
  for (int col = 0; col < cols; ++col) {
    node curr_node = grid[rows-1][col];
    if (curr_node.top == true) {
      cout << "+---";
    } else {
      cout << "+   ";
    }
  }
  cout << "+" << endl;
}

void runMazer(int rows, int cols) {
  vector<vector<node>> grid(rows, vector<node>(cols));
  grid_coords_setup(grid, rows, cols);
  dfs(grid, 0, 0, rows, cols);

  print_maze(grid, rows, cols);
}