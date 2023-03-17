/* — Шрек, ты чего?

   — Не могу поверить, что я скоро стану отцом. Как это получилось?

Шрек и Фиона не могут неделями успокоить своих шебутных детей. Компьютерные игры еще не придумали, 
а бабушка с дедушкой вечно заняты, поэтому нашим героям приходится раздавать своих детей знакомым 
на выходные, чтобы хотя бы немного отдохнуть от суеты.

Больше всего маленькие огры любят проводить время с Волшебным Зеркалом. Зеркало примечательно тем,
 что люди, огры и другие обитатели 3-ки в нем не отражаются. Дети расставляют кубики в ряд и 
 ползают вдоль него, таким образом, что всегда видят перед собой 
N
N цветных кубиков, но не знают, какие из этих кубиков настоящие, а какие - всего лишь отражение
 в зеркале. Be patient - дети огров, выросшие на болоте, не самые сообразительные в мире дети. 
 Помогите им! Выясните, сколько кубиков может быть в комнате с Волшебным Зеркалом. Дети видят 
 отражение всех кубиков в зеркале и часть кубиков, которая находится перед ними. */
 
#include <algorithm>
#include <iostream>
#include <vector>

void ZFunctionModiFied(int n, std::vector<int>& cubes, std::vector<int>& z_function) {
  //int l = 0;
  int r = 0;
  for(int i = 0; i < n / 2 + 1; ++i) {
    if (i < r) {
      z_function[i] = std::min(r - i, z_function[r - i - 1]);
    }

    while(i + z_function[i] + 1 < n && i - z_function[i] >= 0 && cubes[i - z_function[i]] == cubes[i + z_function[i] + 1]) {
      ++z_function[i];
    }

    if (i + z_function[i] > r) {
      //l = i;
      r = i + z_function[i];
    }
  }
}

int main() {

  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<int> cubes(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> cubes[i];
  }

  std::vector<int> z_function(n, 0);
  ZFunctionModiFied(n, cubes, z_function);

  for (int i = 0; i < n; ++i) {
    if (z_function[n - i - 1] == n - i) {
      std::cout << i << " ";
    }
  }

  std::cout << n << '\n';

  return 0;
}