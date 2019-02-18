class Solution {
public:
   
    using value = unordered_map<string, double>;
    
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        vector<double> res;
        for(int i = 0; i < equations.size(); ++i) {
            const auto & up = equations[i].first;
            const auto & down = equations[i].second;
            const auto & val = values[i];
            if(!is_in(down)) g[down] = value{};
            if(!is_in(up)) g[up] = value{};
            g[down][up] = 1.0 / val;
            g[up][down] = val;
        }
        //print_graph();
        for(const auto& q : queries) {
            if (!is_in(q.first) || !is_in(q.second)) {
                res.push_back(-1.0);
                continue;
            }
            auto t = bfs(q.first, q.second);
            if (t.first) {
                res.push_back(t.second);
            } else {
                res.push_back(-1.0);
            }
        }
        return res;
    }
    
    pair<bool, double> dfs(const string& src, const string& dst) {
        unordered_set<string> has_visited;
        return dfs_helper(src, dst, has_visited, 1.0);
    }
    
    pair<bool, double> bfs(string src, string dst) {
        unordered_set<string> has_visited;
        return bfs_helper(src, dst, has_visited);
    }
    
    pair<bool, double> bfs_helper(const string& src,const string& dst, unordered_set<string>& visited) {
       queue<pair<string, double>> q;
       q.push(make_pair(src, 1.0));
       visited.insert(src);
       while(!q.empty()) {
           const auto& node = q.front();
           q.pop();
           if (node.first == dst) {
               return make_pair(true, node.second);
           }
           
           for(const auto& n : g[node.first]) {
               if (visited.count(n.first) == 0) {
                   visited.insert(n.first);
                   q.push(make_pair(n.first, node.second*n.second));
               }
           }
       }
       return make_pair(false, -1.0);
    }
    
    pair<bool, double> dfs_helper(const string& cur, const string& dst, unordered_set<string>& has_visited, double res) {
        //cout << cur << ":" << dst << endl;
        if(cur == dst) {
            return make_pair(true, res);
        }
        has_visited.insert(cur);
        for(const auto& e : g[cur]) {
            if (has_visited.count(e.first) == 0) {
                auto r = dfs_helper(e.first, dst, has_visited, res * e.second);
                if (r.first) return r;
            }
        }
       return make_pair(false, res);
    }
    
   bool is_in(string s) {
        return g.count(s) != 0;
    }
     
   void print_graph() {
        for(const auto& pair : g) {
            cout << pair.first << ": ";
            for (const auto& v : pair.second) {
                cout << "(" << v.first << ",";
                cout << v.second << ")";
            }
            cout << endl;
        }
    }
    
    unordered_map<string, value> g;
};