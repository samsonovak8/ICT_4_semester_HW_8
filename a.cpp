/* "Шрек, помнишь, как ты говорил, что великаны многослойные? Должен тебе признаться в том,
что ослы устроены проще. Наши страхи написаны у нас на лбу."

Шрек так запутался в слоях, что стал бояться своих чувств. Неизвестно, как в Средневековье, 
но в современном мире все подобные ситуации решаются просто --- походом к психотерапевту. 
Тот попросил Шрека выписать все слова, что приходят на ум и теперь анализирует чувства великана, 
смотря как часто в тексте появляются слова-триггеры. Работа муторная, кропотливая, а потому 
стоит того, чтобы переложить её на кого-то другого. Теперь доктор просит вас помочь найти все 
вхождения строки 
P в строку S.*/

#include <iostream>
#include <string>
#include <vector>

void PrefixFunc(std::string s, std::vector<size_t>& max_suffix_len) {
  size_t n = s.length();
  for (size_t i = 1; i < n; ++i) {
    size_t pos = max_suffix_len[i - 1];
    while (pos > 0 && s[i] != s[pos]) {
      pos = max_suffix_len[pos - 1];
    }
    if (s[i] == s[pos]) {
      ++pos;
    }
    max_suffix_len[i] = pos;
  }
}

int main() {
  std::string s;
  std::string p;
  std::cin >> s >> p;

  std::string result = p + "#" + s;
  std::vector<size_t> max_suffix_len(result.size(), 0);
  PrefixFunc(result, max_suffix_len);

  size_t len = result.length();
  for (size_t i = 0; i < len; ++i) {
    if (max_suffix_len[i] == p.length()) {
      std::cout << (i - 2 * p.size()) << '\n';
    }
  }
  return 0;
}