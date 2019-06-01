/*
 * @lc app=leetcode id=642 lang=cpp
 *
 * [642] Design Search Autocomplete System
 *
 * algorithms
 * Hard (35.86%)
 * Total Accepted:    22.5K
 * '["AutocompleteSystem","input","input","input","input"]\n[[["i love
 * you","island","iroman","i love leetcode"],[5,3,2,2]],["i"],["
 * "],["a"],["#"]]'
 *
 * Design a search autocomplete system for a search engine. Users may input a
 * sentence (at least one word and end with a special character '#'). For each
 * character they type except '#', you need to return the top 3 historical hot
 * sentences that have prefix the same as the part of sentence already typed.
 * Here are the specific rules:
 *
 *
 * The hot degree for a sentence is defined as the number of times a user typed
 * the exactly same sentence before.
 * The returned top 3 hot sentences should be sorted by hot degree (The first
 * is the hottest one). If several sentences have the same degree of hot, you
 * need to use ASCII-code order (smaller one appears first).
 * If less than 3 hot sentences exist, then just return as many as you can.
 * When the input is a special character, it means the sentence ends, and in
 * this case, you need to return an empty list.
 *
 *
 * Your job is to implement the following functions:
 *
 * The constructor function:
 *
 * AutocompleteSystem(String[] sentences, int[] times): This is the
 * constructor. The input is historical data. Sentences is a string array
 * consists of previously typed sentences. Times is the corresponding times a
 * sentence has been typed. Your system should record these historical data.
 *
 * Now, the user wants to input a new sentence. The following function will
 * provide the next character the user types:
 *
 * List<String> input(char c): The input c is the next character typed by the
 * user. The character will only be lower-case letters ('a' to 'z'), blank
 * space (' ') or a special character ('#'). Also, the previously typed
 * sentence should be recorded in your system. The output will be the top 3
 * historical hot sentences that have prefix the same as the part of sentence
 * already typed.
 *
 *
 * Example:
 * Operation: AutocompleteSystem(["i love you", "island","ironman", "i love
 * leetcode"], [5,3,2,2])
 * The system have already tracked down the following sentences and their
 * corresponding times:
 * "i love you" : 5 times
 * "island" : 3 times
 * "ironman" : 2 times
 * "i love leetcode" : 2 times
 * Now, the user begins another search:
 *
 * Operation: input('i')
 * Output: ["i love you", "island","i love leetcode"]
 * Explanation:
 * There are four sentences that have prefix "i". Among them, "ironman" and "i
 * love leetcode" have same hot degree. Since ' ' has ASCII code 32 and 'r' has
 * ASCII code 114, "i love leetcode" should be in front of "ironman". Also we
 * only need to output top 3 hot sentences, so "ironman" will be ignored.
 *
 * Operation: input(' ')
 * Output: ["i love you","i love leetcode"]
 * Explanation:
 * There are only two sentences that have prefix "i ".
 *
 * Operation: input('a')
 * Output: []
 * Explanation:
 * There are no sentences that have prefix "i a".
 *
 * Operation: input('#')
 * Output: []
 * Explanation:
 * The user finished the input, the sentence "i a" should be saved as a
 * historical sentence in system. And the following input will be counted as a
 * new search.
 *
 *
 * Note:
 *
 *
 * The input sentence will always start with a letter and end with '#', and
 * only one blank space will exist between two words.
 * The number of complete sentences that to be searched won't exceed 100. The
 * length of each sentence including those in the historical data won't exceed
 * 100.
 * Please use double-quote instead of single-quote when you write test cases
 * even for a character input.
 * Please remember to RESET your class variables declared in class
 * AutocompleteSystem, as static/class variables are persisted across multiple
 * test cases. Please see here for more details.
 *
 *
 *
 *
 */
struct Node {
  unordered_map<char, unique_ptr<Node>> map;
  std::string word;
  int times = 0;
};

struct s_pair {
  s_pair(int times_, int len_, const char *s_)
      : times(times_), len(len_), s(s_) {}
  int times;
  size_t len;
  const char *s;
};

class TrieTree {
public:
  TrieTree() : root_(make_unique<Node>()), cur_(root_.get()), cur_word_("") {}

  void add(const std::string &word, int times = 1) {
    Node *cur = root_.get();
    for (const auto &c : word) {
      if (!cur->map.count(c)) {
        cur->map[c] = make_unique<Node>();
      }
      cur = cur->map[c].get();
    }
    cur->times += times;
    cur->word = word;
  }

  int is_in(const std::string &word) {
    Node *cur = root_.get();
    for (const auto &c : word) {
      if (!cur->map.count(c)) {
        return 0;
      }
      cur = cur->map[c].get();
    }
    return cur->times;
  }

  vector<string> on_type(const char c) {
    vector<string> res;
    if (c == '#' && cur_) {
      cur_->times++;
      cur_->word = std::move(cur_word_);
      cur_ = root_.get();
    } else {
      cur_word_.push_back(c);
      if (cur_->map.count(c)) {
        vector<s_pair> suffix;
        find_suffix(cur_->map[c].get(), &suffix);
        sort_result(&suffix, &res);
      } else {
        cur_->map[c] = make_unique<Node>();
      }
      cur_ = cur_->map[c].get();
    }
    return res;
  }

  void find_suffix(const Node *node, vector<s_pair> *suffix) {
    if (!node || !suffix) {
      return;
    }
    if (node->times > 0) {
      suffix->emplace_back(node->times, node->word.size(), node->word.c_str());
    }
    for (const auto &n : node->map) {
      find_suffix(n.second.get(), suffix);
    }
  }

  void sort_result(vector<s_pair> *suffix, vector<string> *res) {
    if (!suffix || !res || suffix->empty()) {
      return;
    }
    std::sort(suffix->begin(), suffix->end(),
              [](const s_pair &p1, const s_pair &p2) -> bool {
                if (p1.times == p2.times) {
                  for (int i = 0; i < min(p1.len, p2.len); ++i) {
                    if (p1.s[i] == p2.s[i]) {
                      continue;
                    }
                    return p1.s[i] < p2.s[i];
                  }
                  return p1.len < p2.len;
                }
                return p1.times > p2.times;
              });

    for (int i = 0; i < std::min(static_cast<int>(suffix->size()), 3); ++i) {
      res->emplace_back((*suffix)[i].s, (*suffix)[i].len);
    }
  }

private:
  const unique_ptr<Node> root_;
  Node *cur_;
  string cur_word_;
};

class AutocompleteSystem {
public:
  AutocompleteSystem(const vector<string> &sentences,
                     const vector<int> &times) {
    for (int i = 0; i < sentences.size(); ++i) {
      trie.add(sentences[i], times[i]);
    }
  }

  vector<string> input(char c) { return trie.on_type(c); }

private:
  TrieTree trie;
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */
