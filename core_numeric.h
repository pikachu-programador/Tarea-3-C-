#ifndef UNTITLED3_CORE_NUMERIC_H
#define UNTITLED3_CORE_NUMERIC_H

#include <concepts>
#include <iterator>
#include <type_traits>

namespace core_numeric {

    // Concepts base
    template <typename C>
    concept Iterable = requires(C c) {
        std::begin(c);
        std::end(c);
    };

    template <typename T>
    concept Addable = requires(T a, T b) {
        { a + b } -> std::same_as<T>;
    };

    template <typename T>
    concept Divisible = requires(T a, std::size_t n) {
        { a / n } -> std::same_as<T>;
    };

    // Concepts propios
    template <typename T>
    concept Subtractable = requires(T a, T b) {
        { a - b } -> std::same_as<T>;
    };

    template <typename T>
    concept Multiplicable = requires(T a, T b) {
        { a * b } -> std::same_as<T>;
    };

    template <typename T>
    concept Comparable = requires(T a, T b) {
        { a > b } -> std::same_as<bool>;
    };

    // sum: suma todos los elementos
    template <Iterable C>
    requires Addable<typename C::value_type>
    auto sum(const C& container) {
        typename C::value_type result{};
        for (const auto& item : container) result = result + item;
        return result;
    }

    // mean: reutiliza sum
    template <Iterable C>
    requires Addable<typename C::value_type> && Divisible<typename C::value_type>
    auto mean(const C& container) {
        auto total = sum(container);
        std::size_t count = 0;
        for (auto it = std::begin(container); it != std::end(container); ++it) ++count;
        return total / count;
    }

    // variance: reutiliza mean
    template <Iterable C>
    requires Addable<typename C::value_type>
             && Divisible<typename C::value_type>
             && Subtractable<typename C::value_type>
             && Multiplicable<typename C::value_type>
    auto variance(const C& container) {
        auto m = mean(container);
        typename C::value_type acumulador{};
        std::size_t count = 0;
        for (const auto& val : container) {
            auto diff = val - m;
            acumulador = acumulador + (diff * diff);
            ++count;
        }
        return acumulador / count;
    }

    // max: mayor elemento
    template <Iterable C>
    requires Comparable<typename C::value_type>
    auto max(const C& container) {
        auto it = std::begin(container);
        auto end = std::end(container);
        auto result = *it;
        ++it;
        for (; it != end; ++it) if (*it > result) result = *it;
        return result;
    }

    // transform_reduce: aplica func y suma
    template <Iterable C, typename F>
    requires Addable<std::invoke_result_t<F, typename C::value_type>>
    auto transform_reduce(const C& container, F func) {
        using ResultType = std::invoke_result_t<F, typename C::value_type>;
        ResultType result{};
        for (const auto& item : container) result = result + func(item);
        return result;
    }

    // sum_variadic: fold expression con +
    template <typename... Ts>
    requires (Addable<Ts> && ...)
    auto sum_variadic(Ts... args) {
        using Common = std::common_type_t<Ts...>;
        return (static_cast<Common>(args) + ...);
    }

    // mean_variadic: reutiliza sum_variadic, if constexpr para int vs float
    template <typename... Ts>
    requires (Addable<Ts> && ...)
    auto mean_variadic(Ts... args) {
        using Common = std::common_type_t<Ts...>;
        auto total = sum_variadic(args...);
        constexpr std::size_t count = sizeof...(Ts);
        if constexpr (std::is_integral_v<Common>) {
            return static_cast<double>(total) / static_cast<double>(count);
        } else {
            static_assert(Divisible<Common>, "El tipo comun debe cumplir Divisible");
            return total / count;
        }
    }

    // variance_variadic: reutiliza mean_variadic
    template <typename... Ts>
    requires (Addable<Ts> && ...) && (Subtractable<Ts> && ...) && (Multiplicable<Ts> && ...)
    auto variance_variadic(Ts... args) {
        using Common = std::common_type_t<Ts...>;
        auto m = mean_variadic(args...);
        using MeanType = decltype(m);
        constexpr std::size_t count = sizeof...(Ts);

        auto squared_diff = [&m](auto val) {
            auto diff = static_cast<MeanType>(val) - m;
            return diff * diff;
        };
        auto acumulador = (squared_diff(args) + ...);

        if constexpr (std::is_integral_v<Common>) {
            return acumulador / static_cast<double>(count);
        } else {
            return acumulador / count;
        }
    }

    // max_variadic: fold expression con comparacion sucesiva
    template <typename T, typename... Ts>
    requires Comparable<T> && (Comparable<Ts> && ...)
    auto max_variadic(T first, Ts... rest) {
        using Common = std::common_type_t<T, Ts...>;
        Common result = static_cast<Common>(first);
        ((result = (static_cast<Common>(rest) > result ? static_cast<Common>(rest) : result)), ...);
        return result;
    }

}

#endif //UNTITLED3_CORE_NUMERIC_H
