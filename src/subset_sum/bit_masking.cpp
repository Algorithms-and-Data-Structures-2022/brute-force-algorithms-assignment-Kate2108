#include "assignment/subset_sum/bit_masking.hpp"

#include <cassert>  // assert

#include "assignment/bits.hpp"  // is_bit_set, mask2indices

namespace assignment {

  std::vector<std::vector<int>> SubsetSumBitMasking::search(const std::vector<int>& set, int target_sum) const {
    assert(target_sum > 0 && set.size() <= 16);

    std::vector<std::vector<int>> indices;

    const auto num_elems = static_cast<int>(set.size());  // N
    const int num_subsets = 1 << num_elems;               // 2^N

    // выделяем память
    std::vector<std::vector<int>> subsets;

    // 1. Внешний цикл: пробегаемся по всем битовым маскам от 0..00 до 1..11
    for (int m = 0; m < num_subsets; m++) {
      std::vector<int> subtest;
      for (int p = 0; p < num_elems; p++) {
        // 2. Внутренний цикл: проверка разрядов битовой маски и генерация подмножества, ассоциирующегося с этой маской
        if (is_bit_set(m, p)) {
          subtest.push_back(p);
        }
      }
      // 3. Подсчет суммы текущего подмножества, сохранение индексов подмножества с целевой суммой в результат
      // Tips: можно пропустить итерацию, если сумма текущего подмножества стала больше целевой суммы
      int current_sum = 0;
      for (int i = 0; i < subtest.size(); i++) {
        current_sum += set[subtest[i]];
        if (current_sum > target_sum) {
          break;
        }
      }
      if (current_sum == target_sum) {
        indices.push_back(subtest);
      }
    }
    return indices;
  }

}  // namespace assignment