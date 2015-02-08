#ifndef ROLL_CALC__FUNC_H
#define ROLL_CALC__FUNC_H

#include <numeric>
#include <map>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace roll_calc {

template <class Point, class ProbWeight>
using Die = std::map<Point, ProbWeight>;

template <class Point, class ProbWeight>
Die<Point, ProbWeight>
regular_die(Point p)
{
  Die<Point, ProbWeight> die;
  for (Point i = 1; i <= p; ++i) {
    die[i] = 1.0;
  }
  return die;
}

template <class Point, class Count, class ProbWeight>
using Dice = std::map<Die<Point, ProbWeight>, Count>;

template <class Count, class ProbWeight>
using Dist = std::map<Count, ProbWeight>;

template <class Point, class Count, class ProbWeight>
Dist<Count, ProbWeight>
distribution_add_die(const Dist<Count, ProbWeight> & dist, const Die<Point, ProbWeight> & die)
{
  static_assert(std::is_integral<Point>::value,       "Side should be integral.");
  static_assert(std::is_unsigned<Count>::value,       "Count should be unsigned.");
  static_assert(std::is_floating_point<ProbWeight>::value, "Prob should be floating point.");

  const auto acc_die_pair = [](ProbWeight prob, std::pair<Point, ProbWeight> die_pair) {
    return prob + die_pair.second;
  };
  const ProbWeight prob_sum = std::accumulate(die.begin(), die.end(), 0.0, acc_die_pair);

  Dist<Count, ProbWeight> result;
  for (const auto & dist_pair: dist) {
    const auto & origin_point = dist_pair.first;
    const auto & origin_prob = dist_pair.second;
    for (const auto & die_pair: die) {
      const auto & point = die_pair.first;
      const auto & prob = die_pair.second / prob_sum * origin_prob;
      result[origin_point + point] += prob;
    }
  }
  return result;
}

template <class Point, class Count, class ProbWeight>
Dist<Count, ProbWeight>
distribution(const Dice<Point, Count, ProbWeight> & dice)
{
  static_assert(std::is_integral<Point>::value,       "Side should be integral.");
  static_assert(std::is_unsigned<Count>::value,       "Count should be unsigned.");
  static_assert(std::is_floating_point<ProbWeight>::value, "Prob should be floating point.");

  Dist<Count, ProbWeight> result = {{0, 1.0}};
  for (const auto & dice_pair: dice) {
    const auto & die = dice_pair.first;
    auto count = dice_pair.second;
    while (count--) {
      result = distribution_add_die(result, die);
    }
  }
  return result;
}

template <class Point, class Count, class ProbWeight, class Predicate>
ProbWeight
probability(const Dice<Point, Count, ProbWeight> & dice, Predicate pred)
{
  static_assert(std::is_integral<Point>::value,       "Side should be integral.");
  static_assert(std::is_unsigned<Count>::value,       "Count should be unsigned.");
  static_assert(std::is_floating_point<ProbWeight>::value, "Prob should be floating point.");

  ProbWeight result = 0.0;
  for (const auto & pair: distribution(dice)) {
    const auto & point = pair.first;
    const auto & prob = pair.second;
    if (pred(point)) {
      result += prob;
    }
  }
  return result;
}

} // namespace roll_calc

#endif // ROLL_CALC__FUNC_H
