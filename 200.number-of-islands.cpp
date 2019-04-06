struct node {
  int rank = 0;
  int parent = -1;
};

class UnionFind {
public:
  UnionFind(size_t num) : num_(num) {
    list_.resize(num_);
  }
  
  int find(int index) {
    auto& n = list_[index];
    if(n.parent == -1) {
      return index;
    }
    n.parent = find(n.parent);
    return n.parent;
  }
  
  void union_node(int index1, int index2) {
   //cout << "union" << index1 <<"," << index2 << endl;
 
    auto& n1 = list_[index1];
    auto& n2 = list_[index2];
    if (n1.rank < n2.rank) {
      n1.parent = index2;
    } else if (n1.rank > n2.rank) {
      n2.parent = index1;
    } else {
      n1.parent = index2;
      n2.rank++;
    }
  }
  

  void print_list() {
      for(const auto& item : list_) {
          cout << item.parent << ", " << item.rank << endl;
      }
  }
private:
  vector<node> list_;
  size_t num_;
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.size() == 0 || grid[0].size() == 0) return 0;
        m = grid.size();
        n = grid[0].size();
        auto uf = UnionFind(m * n);
        for(int i = 0; i < m; ++i) {
          for(int j = 0; j < n; ++j) {
            if(grid[i][j] == '1') {
              island_num++;
              union_island(grid, uf, i, j);
            }
          }
        }
      //uf.print_list();
      return island_num;
    }
    
    void union_island(const vector<vector<char>>& grid, UnionFind& uf, int i, int j) {
      for(const auto& d : dirs) {
        auto i_ = i + d[0];
        auto j_ = j + d[1];
        if (in_range(i_, j_) && grid[i_][j_] == '1') {
          //cout << i << ":" << j << endl;
          auto index1 = i*n + j;
          auto index2 = i_*n + j_;
          auto root1 = uf.find(index1);
          auto root2 = uf.find(index2);
          if (root1 != root2) {
            //cout << i << ", " << j << endl;
            uf.union_node(root1, root2);
            island_num--;
          }
        }
      }
    }
    
    bool in_range(int i, int j) {
      return (i >= 0 && i < m && j >= 0 && j < n);
    }
    
private:
  int island_num = 0;
  int m = 0;
  int n = 0;
  vector<vector<int>> dirs {{-1,0}, {0,-1}, {1, 0}, {0,1}};
  vector<bool> visited;
};
