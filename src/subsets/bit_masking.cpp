#include "assignment/subsets/bit_masking.hpp"

#include <cassert>  // assert

#include "assignment/bits.hpp"  // is_bit_set

namespace assignment {

  std::vector<std::vector<int>> SubsetsBitMasking::generate(const std::vector<int>& set) const {
    assert(set.size() <= 16);

    const auto num_elems = static_cast<int>(set.size());  // N
    const int num_subsets = 1 << num_elems;               // 2^N

    // выделяем память
    std::vector<std::vector<int>> subsets;

    // 1. Внешний цикл: пробегаемся по всем битовым маскам от 0..00 до 1..11
    for (int m = 0; m < num_subsets; m++) {
      std::vector<int> subset;
      for (int p = 0; p < num_elems; p++) {
        // 2. Внутренний цикл: проверка разрядов битовой маски и генерация подмножества, ассоциирующегося с этой маской
        // Tips: для проверки разряда бита на 1 (единицу) используйте функцию is_bit_set
        if (is_bit_set(m, p)) {
          subset.push_back(p);
        }
      }
      subsets.push_back(subset);
    }

    return subsets;
  }

}  // namespace assignment