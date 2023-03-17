/* Дана Z-функция некоторой строки. Найти лексикографически минимальную строку, 
массив Z-функции которой совпадет с данным. Алфавит для построения ответа: a-z.*/

#include<iostream>
#include<string>
#include<vector>

void ZFunctionToPrefixFunction(int n, std::vector<int>& z_function, std::vector<int>& prefix_function) {
    for(int i = 1; i < n; ++i) {
        if (z_function[i]) {
            for(int j = z_function[i] - 1; j >= 0 && !prefix_function[i + j]; --j) {
                prefix_function[i + j] = j + 1;
            }
        } 
    }
}

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
    int n = 0;
    std::cin >> n;
    std::vector<int> z_function(n);
    std::vector<int> prefix_function(n, 0);
    for(int i = 0; i < n; ++i) {
        std::cin >> z_function[i];
    }
    ZFunctionToPrefixFunction(n, z_function, prefix_function);
    std::cout << MinStringWithPrefixFunc(prefix_function) << '\n';
    return 0;
}