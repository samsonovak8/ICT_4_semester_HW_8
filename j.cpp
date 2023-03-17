/* — Бесподобно. Что это за блюдо?

   — Это блюдо подают собакам на завтрак, Ваше Величество

Но кто обратит на это внимание на балу, если дать каждому блюду звучное название? 
Звучным названием считается строка, одинаково читающаяся, как слева направо, так и справа налево.

Дан набор из N строк. Найдите среди них такие пары, которые при конкатенации дают палиндром. 
Более формально, найдите все пары (i, j) такие, что i ≠ j и строка s_i + s_j является палиндромом.

Выведите все упорядоченные пары индексов (нумерация с единицы).*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

void CalculatePalindromePairs(int n, std::vector<std::string> &wordlist, std::vector<std::pair<int, int>> &answer)
{
    std::unordered_map<std::string, int> hmap_reverse;

    for (int i = 0; i < n; ++i)
    {
        std::string reverse_word = std::string(wordlist[i].rbegin(), wordlist[i].rend());
        hmap_reverse[reverse_word] = i;
    }

    for (int i = 0; i < n; ++i)
    {
        std::string word = wordlist[i];
        int len = static_cast<int>(word.size());
        for (int j = 0; j < len; ++j)
        {
            std::string left = word.substr(0, j + 1);
            std::string right = word.substr(j + 1);
            if (!left.empty() && left == std::string(left.rbegin(), left.rend()) && hmap_reverse.count(right) && hmap_reverse[right] != i)
            {
                answer.emplace_back(hmap_reverse[right], i);
            }
            if (right == std::string(right.rbegin(), right.rend()) && hmap_reverse.count(left) && hmap_reverse[left] != i)
            {
                answer.emplace_back(i, hmap_reverse[left]);
            }
        }
    }
}

int main()
{
    int n = 0;
    std::cin >> n;
    std::vector<std::string> words(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> words[i];
    }
    std::vector<std::pair<int, int>> answer;
    CalculatePalindromePairs(n, words, answer);
    std::cout << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); ++i)
    {
        std::cout << answer[i].first + 1 << " " << answer[i].second + 1 << '\n';
    }
    return 0;
}