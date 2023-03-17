/* Комитет По Исследованию Бинарных Вирусов обнаружил, что некоторые последовательности единиц и 
нулей являются кодами вирусов. Комитет изолировал набор кодов вирусов. Последовательность из единиц 
и нулей называется безопасной, если никакой ее сегмент (т.е. последовательность из соседних элементов)
не является кодом вируса. Сейчас цель комитета состоит в том, чтобы установить, существует ли 
бесконечная безопасная последовательность из единиц и нулей.*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>

struct BorNode {
    bool is_leaf = false;
    int parent = -1;
    int parent_char;
    int link = -1;
    int suffix_link = -1;
    std::map<int, int> next;
    std::map<int, int> go;
};

struct Bor {

    Bor() { graph_.resize(1); }

    void AddVirus(std::vector<int> virus) {
        int v = 0;
        for(int bit : virus) {
            if (graph_[v].next.count(bit) == 0) {
                graph_[v].next[bit] = static_cast<int>(graph_.size());

                BorNode n;
                n.parent = v;
                n.parent_char = bit;
                graph_.push_back(std::move(n));

                v = static_cast<int>(graph_.size()) - 1;
            }
            else {
                v =  graph_[v].next[bit];
            }
        }
        graph_[v].is_leaf = true;
    }

    int Go(int v, int parent_char) {
        if (graph_[v].go.count(parent_char) == 0) {
            if(graph_[v].next.count(parent_char) != 0) {
                graph_[v].go[parent_char] = graph_[v].next[parent_char];
            }
            else {
                if (v == 0) {
                    graph_[v].go[parent_char] = 0;
                }
                else {
                    graph_[v].go[parent_char] = Go(GetSuffixLink(v), parent_char);
                }
            }
        }
        return graph_[v].go[parent_char];
    }

    int GetSuffixLink(int v) {
        if (graph_[v].suffix_link == -1) {
            if (v == 0 || graph_[v].parent == 0) {
                graph_[v].suffix_link = 0;
            }
            else {
                graph_[v].suffix_link = Go(GetSuffixLink(graph_[v].parent), graph_[v].parent_char);
            }
        } 
        return graph_[v].suffix_link;
    }

    void Count() {
        for(int i = 0; i < static_cast<int>(graph_.size()); ++i) {
            GetSuffixLink(i);
            Go(i, 0);
            Go(i, 1);
        }   
    }

    int GetLink(int v) {
        if (graph_[v].link == -1) {
            auto step = GetSuffixLink(v);
            while(step != 0 && !graph_[step].is_leaf) {
                step = GetSuffixLink(step);
            }
            graph_[v].link = step;
        }
        return graph_[v].link;
    }

    bool Dfs(int v) {
        if (used_[v] == 1) {
            return true;
        }
        if (used_[v] == 2  || graph_[v].is_leaf || GetLink(v) != 0) {
            return false;
        }

        used_[v] = 1;
        bool result = Dfs(Go(v, 0)) || Dfs(Go(v, 1));
        used_[v] = 2;
        return result;
    }


    std::string FindCycle() {
        used_.resize(graph_.size(), 0);
        std::string answer;
        if (Dfs(0)) {
            answer = "TAK\n";
        }
        else {
            answer = "NIE\n";
        }
        return answer;
    }

    std::vector<BorNode> graph_;
    std::vector<int> used_;

};


int main() {
    Bor bor;

    int n = 0;
    std::cin >> n;
    std::string s;
    for(int i = 0; i < n; ++i) {
        std::cin >> s;
        int len = static_cast<int>(s.size());
        std::vector<int> virus;
        for(int j = 0; j < len; ++j) {
            virus.push_back(s[j] - '0');
        }
        bor.AddVirus(virus);
    }
    bor.Count();
    std::cout << bor.FindCycle();
    return 0;
}