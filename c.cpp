/* Шрек и Кот в сапогах наконец-то нашли общий язык и теперь мучают Осла новыми каламбурами. 
Схема очень проста и именно поэтому просто невыносима - n слов склеиваются в одно, по следующему 
правилу: если два слова идут подряд, то удаляется самый длинный префикс второго слова, который 
совпадает с суффиксом первого слова. Например, слова "каламбур" и "буря" склеиваются в "каламбурю" 
(грозящую погрести под собой Осла). Каламбур склеивается слева направо (т.е. сначала склеиваются 
первые два слова, потом результат с третьим, и так далее).

Напишите программу, которая поможет культивировать это развлечение.*/

#include <iostream>
#include <vector>
#include <string>

int PrefixFunc(std::string s) {
  size_t n = s.length();
  std::vector<int> max_suffix_len(n, 0);
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
  return max_suffix_len[n - 1];
}

int main() {
    int n = 0;
    std::cin >> n;
    std::string main_string;
    std::cin >> main_string;

    std::string next_string;

    for(int i = 1; i < n; ++i) {
        std::cin >> next_string;
        std::string string_to_add;
        if (next_string.size() < main_string.size()) {
            string_to_add = main_string.substr(main_string.size() - next_string.size(), next_string.size());
        }
        else {
            string_to_add = main_string;
        }
        int symbols_to_add = PrefixFunc(next_string + '#' + string_to_add);
        main_string += next_string.substr(symbols_to_add, next_string.size());
    }
    std::cout << main_string << '\n';
    return 0;
}