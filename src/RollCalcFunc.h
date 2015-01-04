#ifndef ROLL_CALC__ROLL_CALC_FUNC_H
#define ROLL_CALC__ROLL_CALC_FUNC_H

#include <map>
#include <cstddef>

#include <wx/msgout.h>

namespace roll_calc {

std::map<int, double>
Distribution(size_t d4, size_t d6, size_t d8, size_t d10, size_t d12);

template <typename Predicate>
double Prob(size_t d4, size_t d6, size_t d8, size_t d10, size_t d12, Predicate pred)
{
  double result = 0.0;
  for (const auto & pair: Distribution(d4, d6, d8, d10, d12)) {
    if (pred(pair.first)) {
      result += pair.second;
    }
  }
  return result;
}

}

#endif // ROLL_CALC__ROLL_CALC_FUNC_H
