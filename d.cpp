/* Осел и молодая чета огров едут в тридевятое царство. Хотя впереди еще половина пути, Осел уже 
изрядно всех достал поэтому Фиона предлагает ему игру: она загадывает Ослу слово, а тот пытается 
придумать из него другие слова. Фиона считает слово T неинтересным, если его можно составить из 
префиксов загаданного слова S. Шрек в бешенстве, что у Осла никак не получается придумать интересное 
Фионе слово и продолжить поездку в тишине и просит вас помочь своему другу.*/

#include<iostream>
#include<string>
#include<vector>

void PrefixFunc(std::string s, std::vector<int>& max_suffix_len) {
  size_t n = s.length();
  for (size_t i = 1; i < n; ++i) {
    int pos = max_suffix_len[i - 1];
    while (pos > 0 && s[i] != s[pos]) {
      pos = max_suffix_len[pos - 1];
    }
    if (s[i] == s[pos]) {
      ++pos;
    }
    max_suffix_len[i] = pos;
  }
}

bool Analyse(size_t start, std::vector<int>& max_suffix_len) {
    for(size_t i = start; i < max_suffix_len.size(); ++i) {
        if (max_suffix_len[i] == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    std::string s1;
    std::string s2;
    std::cin >> s1 >> s2;
    std::string s = s1 + '#' + s2;
    std::vector<int> max_suffix_len(s.length());
    PrefixFunc(s, max_suffix_len);
    if (Analyse(s1.size() + 1, max_suffix_len)) {
        std::cout << "No\n";
        std::vector<std::string> answer;
        int pos = static_cast<int>(s.size() - 1);
        while(pos > static_cast<int>(s1.size())) {
            int start = pos - max_suffix_len[pos] + 1;
            int end = pos;
            pos = start - 1;
            std::string curr_string;
            for(int i = start; i <= end; ++i) {
                curr_string += s[i];
            }
            answer.push_back(curr_string);
        }
        for(int i = static_cast<int>(answer.size() - 1); i >= 0; --i) {
            for(size_t j = 0; j < answer[i].size(); ++j) {
                std::cout << answer[i][j] ;
            }
            std::cout << " ";
        }
    }
    else {
        std::cout << "Yes\n";
    }
    return 0;
}