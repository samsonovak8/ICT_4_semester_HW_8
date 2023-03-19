/* Дана строка длины N и отсортированный массив суффиксов этой строки (т.е. суффиксный массив), 
вам нужно вычислить LCP. При сортировке строка a считается меньше строки aa. 
LCP — наибольший общий префикс двух последовательных суффиксов в суффиксном массиве.*/

#include<iostream>
#include<vector>
#include<string>

std::vector<int> KasaiAlgorithm(std::string str, std::vector<int> suffix_array) {
   int n = static_cast<int>(suffix_array.size());

   std::vector<int> longest_common_prefix(n, 0);  
   std::vector<int> suffix_inverse(n, 0);

   for (int i=0; i < n; ++i) {
        suffix_inverse[suffix_array[i]] = i;
   }

   int k = 0;
   for (int i = 0; i < n; ++i) { 

      if (suffix_inverse[i] == n - 1) { 
         k = 0;
         continue;
      }

      int j = suffix_array[suffix_inverse[i] + 1];   

      while (j + k < n && i + k < n && str[j + k] == str[i + k]) {
        ++k;
      }

      longest_common_prefix[suffix_inverse[i]] = k;

      if (k > 0) {
        --k;    
      }
   }
   return longest_common_prefix;
}

void ShowArray(std::vector<int>& vec, size_t n) {
    for(size_t i = 0; i < n - 1; ++i) {
        printf("%d ", vec[i]);
    } 
}

int main() {
    int n = 0;
    std::string str;
    std::cin >> n >> str;

    std::vector<int> suffix_array(n);
    for(int i = 0; i < n; ++i) {
        std::cin >> suffix_array[i];
        --suffix_array[i];
    }

    std::vector<int> longest_common_prefix = KasaiAlgorithm(str, suffix_array);
    ShowArray(longest_common_prefix, str.size());

    return 0;
}