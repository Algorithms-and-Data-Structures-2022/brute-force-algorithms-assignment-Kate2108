#include "assignment/subset_sum/backtracking.hpp"

#include <cassert>  // assert
#include <numeric>  // accumulate

#include "assignment/bits.hpp"  // set_bit, mask2indices

namespace assignment {

  std::vector<std::vector<int>> SubsetSumBacktracking::search(const std::vector<int>& set, int target_sum) const {
    assert(target_sum > 0 && set.size() <= 16);

    auto indices = std::vector<std::vector<int>>();

    // подсчитываем сумму всех элементов во множестве
    const int residual = std::accumulate(set.begin(), set.end(), 0);

    // вызов вспомогательной функции: обратите внимание на начальные значения индекса, маски и суммы
    search(set, -1, 0, 0, residual, target_sum, indices);

    return indices;
  }

  void SubsetSumBacktracking::search(const std::vector<int>& set, int index, int mask, int sum, int residual,
                                     int target_sum, std::vector<std::vector<int>>& indices) const {

    assert(index >= -1 && mask >= 0 && sum >= 0 && residual >= 0 && target_sum > 0);

    // Ограничение 0: вышли за пределы множества
    if (index == static_cast<int>(set.size())) {
      return;
    }

    // Ограничение 1: текущая сумма должна быть меньше целевой
    if (sum > target_sum /* ... */) {
      // если превысили целевую сумму, то сделать ее меньше уже не получится (все элементы множества положительные)
      return;
    }

    // Ограничение 2: "остаточная сумма" + "текущая сумма" должны быть больше или равны "целевой сумме"
    if (sum + residual < target_sum /* ... */) {
      // сумму невозможно будет набрать с оставшимися элементами множества
      return;
    }

    // если найдено подмножество с целевой суммой, то сохраняем в результат это подмножество
    if (sum == target_sum) {
      indices.push_back(mask2indices(set, mask));
      return;
      // ... сохранение в результат
      // ... нужно ли в этой ветке рекурсии рассматривать следующие элементы?
    }

    // рассматриваем следующий элемент
    index += 1;

    // обновляется несмотря на включение/исключение элемента => почему?
    residual -= set[index];

    // рекурсивный вызов со включением/исключением элемента с текущим индексом ...
    search(set, index, mask, sum, residual, target_sum, indices);
    search(set, index, set_bit(mask, index), sum + set[index], residual, target_sum, indices);
  }

}  // namespace assignment