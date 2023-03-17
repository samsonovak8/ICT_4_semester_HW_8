/* "Приветствую вас, дети вселенной! Прошу в мой круг безмятежности!"

Неоплачиваемый труд подростков - освященная веками традиция магов. Пока Мерлин страдает из-за
нервного срыва, депрессии и вот этого вот всего, и окончательно перестает следить за тем,
что же он преподает ученикам, студенты Вустершира в погоне за высшим магическим образованием
вынуждены искать в древнем тексте T не только заданный паттерн P, но и все его циклические
сдвиги (волшебник олицетворяет собой древность и понемногу начинает путать порядок букв).
Помогите им найти количество вхождений (возможно пересекающихся) всех циклических сдвигов
паттерна в тексте.

Отметим, что если паттерн «abс», то его циклическими сдвигами называют следующие строки:
 «abс», «bca», «cab». */
 
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>

#define MOD 1000000007

struct Hash {

    explicit Hash(const std::string& s) : prefix_first_(s.size() + 1, 0), prefix_second_(s.size() + 1, 0){
        int n = static_cast<int>(s.size());

        power_1.clear();
        power_1.push_back(1);

        power_2.clear();
        power_2.push_back(1);

        for(int i = 0; i < n; ++i){
            power_1.push_back((power_1.back() * base_) % MOD);
            power_2.push_back(power_2.back() * base_);
        }

        for (int i = 0; i < n; ++i) { 
            prefix_first_[i + 1] = (prefix_first_[i] + s[i] * power_1[i]) % MOD;
            prefix_second_[i + 1] = (prefix_second_[i] + s[i] * power_2[i]);
        }
    }

    inline std::pair<int64_t, uint64_t> operator()(const int pos, const int len, const int max_pow = 0) const {
        int64_t hash1 = prefix_first_[pos + len] - prefix_first_[pos];
        uint64_t hash2 = prefix_second_[pos + len] - prefix_second_[pos];
        if(hash1 < 0) {
            hash1 += MOD;
        }
        if(max_pow != 0) {
            hash1 = (hash1 * power_1[max_pow - (pos + len - 1)]) % MOD;
            hash2 *= power_2[max_pow - (pos + len - 1)];
        }
        return std::make_pair(hash1, hash2);
    }

    int base_ = 257;
    static std::vector<int64_t> power_1;
    static std::vector<uint64_t> power_2;

    std::vector<int64_t> prefix_first_;
    std::vector<uint64_t> prefix_second_;

};

std::vector<int64_t> Hash::power_1;
std::vector<uint64_t> Hash::power_2;
std::vector<std::pair<int64_t, uint64_t> > hashes;

int main()
{
    std::string pattern;
    std::string text;

    std::cin >> pattern >> text;

    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pattern.size());
    pattern += pattern;

    int max_pow = std::max(static_cast<int>(text.size()), static_cast<int>(pattern.size()));

    Hash hash_text(text);
    Hash hash_pattern(pattern);

    for(int i = 0; i < m; ++i){
        hashes.push_back(hash_pattern(i, m, max_pow));
    }

    sort(hashes.begin(), hashes.end());

    int answer = 0;
    for(int i = 0; i <= n - m; ++i){
        if(binary_search(hashes.begin(), hashes.end(), hash_text(i, m, max_pow))){
            ++answer;
        }
    }

    std::cout << answer << '\n';
    
    return 0;
}
