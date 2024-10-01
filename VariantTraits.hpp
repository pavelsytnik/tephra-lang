#ifndef TEPHRA_VARIANT_TRAITS_HPP
#define TEPHRA_VARIANT_TRAITS_HPP

#include <type_traits>
#include <variant>

namespace tephra
{
template <typename, typename>
struct IsVariantAlternative :
    std::false_type
{};

template <typename T, typename... Ts>
struct IsVariantAlternative<T, std::variant<Ts...>> :
    std::disjunction<std::is_same<T, Ts>...>
{};

template <typename T, typename Variant>
constexpr bool isVariantAlternative =
    IsVariantAlternative<T, Variant>::value;

template <typename T, typename Variant>
concept VariantAlternative = requires {
    isVariantAlternative<T, Variant>;
};
}

#endif // !defined(TEPHRA_VARIANT_TRAITS_HPP)
