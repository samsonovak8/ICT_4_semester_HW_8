/* Дана строка, требуется построить суффиксный массив для этой строки. 
Суффиксный массив —– лексикографически отсортированный массив всех суффиксов строки. 
Каждый суффикс задается целым числом — позицией начала. Строка s лексикографически меньше строки t,
если есть такое i, что si < ti и sj = tj для всех j < i, или если такого i не существует 
и строка s короче строки t. Здесь si — код i-го символа строки s. Формат входных данных 
Файл состоит из единственной строки. Эта строка — английский литературный текст.
Длина текста не превосходит 105 . Коды всех символов в тексте от 32 до 127. 
Формат выходных данных Выведите чисел — суффиксный массив данной строки.*/

#include<iostream>
#include<vector>
#include<algorithm>

struct Suffix { 
   int index_;
   std::pair<int, int> class_;
};

bool CmpFunc(Suffix a, Suffix b) {
    return a.class_ < b.class_;
}

std::vector<Suffix> ZeroIteration(std::string& str) {
   int n = static_cast<int>(str.size());
   std::vector<Suffix> suffix_array(n);

   for (int i = 0; i < n; ++i) {
      suffix_array[i].index_ = i;
      suffix_array[i].class_.first = str[i] - ' ';     
      suffix_array[i].class_.second = ((i + 1) < n) ? (str[i + 1] - ' ') : -1; 
   }
   sort(suffix_array.begin(), suffix_array.end(), CmpFunc); 
   return suffix_array;
}

std::vector<int> BuildSuffixArray(std::string& str, std::vector<Suffix>& suffix_array) { 
   int n = static_cast<int> (str.size()); 
   std::vector<int> index(n); 

   for (int step = 4; step < (n << 1); step <<= 1) {   

      int curr_class = 0;
      int prev_class = suffix_array[0].class_.first;

      suffix_array[0].class_.first = curr_class;
      index[suffix_array[0].index_] = 0;

      for (int i = 1; i < n; ++i) { 

         if (suffix_array[i].class_.first != prev_class || suffix_array[i].class_.second != suffix_array[i - 1].class_.second) {
            prev_class = suffix_array[i].class_.first;
            suffix_array[i].class_.first = ++curr_class;
         }
         else { 
            prev_class = suffix_array[i].class_.first;
            suffix_array[i].class_.first = curr_class;
         }

         index[suffix_array[i].index_] = i;
      }

      for (int i = 0; i < n; ++i) {   
         int next_index = suffix_array[i].index_ + (step >> 1);
         if (next_index < n) {
            suffix_array[i].class_.second = suffix_array[index[next_index]].class_.first;
         }
         else {
            suffix_array[i].class_.second = -1;
         }
      }
      sort(suffix_array.begin(), suffix_array.end(), CmpFunc); 
   }

   std::vector<int> suffix_vector;
   for (int i = 0; i < n; ++i) {
        suffix_vector.push_back(suffix_array[i].index_); 
    }
      
    return suffix_vector;
}

void ShowArray(std::vector<int>& vec, size_t n) {
    for(size_t i = 0; i < n; ++i) {
        printf("%d ", vec[i] + 1);
    } 
}


int main() {
    
    std::string str;

    getline(std::cin, str);

    std::vector<Suffix> suffix_array = ZeroIteration(str);
    std::vector<int>suffix_indices = BuildSuffixArray(str, suffix_array);

    ShowArray(suffix_indices, str.size());
    return 0;
}