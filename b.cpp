/* Дана префикс-функция некоторой строки. Найти лексикографически 
минимальную строку, массив префикс-функции которой совпадет с данным. Алфавит для 
построения ответа: a-z.*/

#include <iostream>
#include <string>
#include <vector>

std::string MinStringWithPrefixFunc(const std::vector<int>& prefix_func) {
  std::string result = "a";
  for (size_t i = 1; i < prefix_func.size(); ++i) {
    if (prefix_func[i] != 0) {
      result += result[prefix_func[i] - 1];
    } else {
      std::vector<bool> used(26, false);
      int k = prefix_func[i - 1];
      while (k > 0) {
        used[result[k] - 'a'] = true;
        k = prefix_func[k - 1];
      }
      char c = 'b';
      while (used[c - 'a']) {
        ++c;
      }
      result += c;
    }
  }
  return result;
}

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<int> prefix_func(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> prefix_func[i];
  }
  if (n > 0) {
    std::string result = MinStringWithPrefixFunc(prefix_func);
    std::cout << result << std::endl;
  } else {
    std::cout << "" << std::endl;
  }

  return 0;
}
