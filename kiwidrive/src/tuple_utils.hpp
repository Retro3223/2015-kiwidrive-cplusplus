#ifndef SRC_TUPLE_UTILS_HPP_
#define SRC_TUPLE_UTILS_HPP_

#include <tuple>
#include <utility>
#include <type_traits>

// for_each

template<std::size_t I = 0, typename FuncT, typename ... Tp>
typename std::enable_if<I == sizeof...(Tp), void>::type
for_each(std::tuple<Tp...> &, FuncT)  // Unused arguments are given no names.
{}

template<std::size_t I = 0, typename FuncT, typename... Tp>
typename std::enable_if<I < sizeof...(Tp), void>::type
for_each(std::tuple<Tp...>& t, FuncT f)
{
  f(std::get<I>(t));
  for_each<I + 1, FuncT, Tp...>(t, f);
}

// tuple_zip

template<std::size_t ...S>
struct seq {
};

template<std::size_t N, std::size_t ...S>
struct gens : gens<N - 1, N - 1, S...> {
};

template<std::size_t ...S>
struct gens<0, S...> {
  typedef seq<S...> type;
};

template<template<typename ...> class Tup1,
template <typename ...> class Tup2,
typename ...A, typename ...B,
std::size_t ...S>
auto tuple_zip_helper(Tup1<A...> t1, Tup2<B...> t2, seq<S...> s) ->
decltype(std::make_tuple(std::make_pair(std::get<S>(t1),std::get<S>(t2))...)) {
  return std::make_tuple(std::make_pair(std::get<S>(t1), std::get<S>(t2))...);
}

template<template<typename ...> class Tup1,
template <typename ...> class Tup2,
typename ...A, typename ...B>
auto tuple_zip(Tup1<A...> t1, Tup2<B...> t2) ->
decltype(tuple_zip_helper(t1, t2, typename gens<sizeof...(A)>::type())) {
  static_assert(sizeof...(A) == sizeof...(B), "The tuple sizes must be the same");
  return tuple_zip_helper(t1, t2, typename gens<sizeof...(A)>::type());
}

#endif /* SRC_TUPLE_UTILS_HPP_ */
