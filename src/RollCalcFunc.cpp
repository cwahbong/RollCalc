#include "RollCalcFunc.h"

namespace roll_calc {

namespace {

template <typename First, typename Second>
void
MapAdd(std::map<First, Second> & m, const std::pair<First, Second> & p)
{
  if (m.find(p.first) == m.end()) {
    m.insert(p);
  }
  else {
    m[p.first] += p.second;
  }
}

std::map<int, double>
DistributionAddDie(const std::map<int, double> & distribution, int sides)
{
  std::map<int, double> result;
  for (const auto & pair: distribution) {
    for (int num = 1; num <= sides; ++num) {
      MapAdd(result, std::make_pair(pair.first + num, pair.second / sides));
    }
  }
  return result;
}

std::map<int, double>
DistributionAddDice(const std::map<int, double> & distribution, int sides, size_t count)
{
  std::map<int, double> result = distribution;
  while (count--) {
    result = DistributionAddDie(result, sides);
  }
  return result;
}

} // namepsace

std::map<int, double>
Distribution(size_t d4, size_t d6, size_t d8, size_t d10, size_t d12)
{
  std::map<int, double> result = {{0, 1.0}};
  result = DistributionAddDice(result, 4, d4);
  result = DistributionAddDice(result, 6, d6);
  result = DistributionAddDice(result, 8, d8);
  result = DistributionAddDice(result, 10, d10);
  result = DistributionAddDice(result, 12, d12);
  return result;
}

} // namespace roll_calc
