#if defined(__AVR__)

typedef signed char        int8_t;
typedef short              int16_t;
typedef long               int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned long      uint32_t;
typedef unsigned long long uint64_t;

#elif defined(__clang__)

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

#elif defined(__GNUC__) || defined(__GNUG__)

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

#elif defined(_MSC_VER)

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

#endif

template <class T, T Val>
struct integral_constant {
    static constexpr T value = Val;

    using value_type = T;
    using type = integral_constant;

    constexpr operator value_type() const noexcept {
        return value;
    }

    constexpr value_type operator()() const noexcept {
        return value;
    }
};

template <bool Val>
using bool_constant = integral_constant<bool, Val>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;


template<class T, class U>
struct is_same : false_type {};

template<class T>
struct is_same<T, T> : true_type {};

template< class T, class U >
inline constexpr bool is_same_v = is_same<T, U>::value;


template <typename T, typename U>
constexpr decltype(auto) plus(T t, U u)
{
    return t + u;
}

template <typename T, typename U>
constexpr decltype(auto) multiply(T t, U u)
{
    return t * u;
}

template <typename T, typename U>
constexpr decltype(auto) divide(T t, U u)
{
    return t / u;
}

#define WITH(X) WITH_PRIVATE_##X()

#define WITH_PRIVATE_DYNAMIC_ASSERTIONS() 0
#define WITH_PRIVATE_STATIC_ASSERTIONS() 1

#if WITH(STATIC_ASSERTIONS)
#define ASSERT static_assert
#else
#include <cassert>
#define ASSERT assert
#endif


constexpr void addition_unsigned()
{
    constexpr auto uint8_plus_uint8 = plus(uint8_t(256), uint8_t(256));
    ASSERT((is_same_v<decltype(uint8_plus_uint8), const int>));
    ASSERT(plus(uint8_t(1), uint8_t(2)) == 3);
    ASSERT(plus(uint8_t(1), uint8_t(256)) == 1); // NOT 257
    ASSERT(uint8_plus_uint8 == 0); // NOT 512

    constexpr auto uint8_plus_uint16 = plus(uint8_t(1), uint16_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(uint8_plus_uint16), const unsigned>));
#else
    ASSERT((is_same_v<decltype(uint8_plus_uint16), const int>));
#endif
    ASSERT(plus(uint8_t(1), uint16_t(65536)) == 1); // NOT 65537

    constexpr auto uint8_plus_uint32 = plus(uint8_t(1), uint32_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(uint8_plus_uint32), const unsigned long>));
#else
    ASSERT((is_same_v<decltype(uint8_plus_uint32), const unsigned int>));
#endif

    constexpr auto uint8_plus_uint64 = plus(uint8_t(1), uint64_t(2));
    ASSERT((is_same_v<decltype(uint8_plus_uint64), const unsigned long long>));

    constexpr auto uint16_plus_uint16 = plus(uint16_t(1), uint16_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(uint16_plus_uint16), const unsigned>));
#else
    ASSERT((is_same_v<decltype(uint16_plus_uint16), const int>));
#endif

    constexpr auto uint16_plus_uint32 = plus(uint16_t(1), uint32_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(uint16_plus_uint32), const unsigned long>));
#else
    ASSERT((is_same_v<decltype(uint16_plus_uint32), const unsigned>));
#endif

    constexpr auto uint16_plus_uint64 = plus(uint16_t(1), uint64_t(2));
    ASSERT((is_same_v<decltype(uint16_plus_uint64), const unsigned long long>));
    ASSERT(plus(uint16_t(65536), uint64_t(65536)) == 65536); // NOT 131072
    ASSERT(plus(uint64_t(65536), uint16_t(65536)) == 65536); // NOT 131072

    constexpr auto uint32_plus_uint64 = plus(uint32_t(1), uint64_t(2));
    ASSERT((is_same_v<decltype(uint32_plus_uint64), const unsigned long long>));

    constexpr auto uint64_plus_uint64 = plus(uint64_t(1), uint64_t(2));
    ASSERT((is_same_v<decltype(uint64_plus_uint64), const unsigned long long>));
}

constexpr void addition_signed()
{
    constexpr auto int8_plus_int8 = plus(int8_t(-128), int8_t(127));
    ASSERT((is_same_v<decltype(int8_plus_int8), const int>));
    ASSERT(int8_plus_int8 == -1);

    constexpr auto int8_plus_int16 = plus(int8_t(1), int16_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(int8_plus_int16), const int>));
#else
    ASSERT((is_same_v<decltype(int8_plus_int16), const int>));
#endif
    ASSERT(plus(int16_t(-32768), int8_t(127)) == -32641);
    ASSERT(plus(int8_t(-128), int16_t(255)) == 127);

    constexpr auto int8_plus_int32 = plus(int8_t(1), int32_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(int8_plus_int32), const long>));
#else
    ASSERT((is_same_v<decltype(int8_plus_int32), const int>));
#endif

    constexpr auto int8_plus_int64 = plus(int8_t(1), int64_t(2));
    ASSERT((is_same_v<decltype(int8_plus_int64), const long long>));

    constexpr auto int16_plus_int16 = plus(int16_t(1), int16_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(int16_plus_int16), const int>));
#else
    ASSERT((is_same_v<decltype(int16_plus_int16), const int>));
#endif

    constexpr auto int16_plus_int32 = plus(int16_t(1), int32_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(int16_plus_int32), const long>));
#else
    ASSERT((is_same_v<decltype(int16_plus_int32), const int>));
#endif

    constexpr auto int16_plus_int64 = plus(int16_t(1), int64_t(2));
    ASSERT((is_same_v<decltype(int16_plus_int64), const long long>));
    ASSERT(plus(int16_t(32767), int64_t(65536)) == 98303);
    ASSERT(plus(int64_t(65536), int16_t(32767)) == 98303);

    constexpr auto int32_plus_int64 = plus(int32_t(1), int64_t(2));
    ASSERT((is_same_v<decltype(int32_plus_int64), const long long>));

    constexpr auto int64_plus_int64 = plus(int64_t(1), int64_t(2));
    ASSERT((is_same_v<decltype(int64_plus_int64), const long long>));
}


constexpr void addition_mixed()
{
    constexpr auto unit8_plus_int8 = plus(uint8_t(0), int8_t(127));
    ASSERT((is_same_v<decltype(unit8_plus_int8), const int>));
    ASSERT(unit8_plus_int8 == 127);
    ASSERT(plus(int8_t(-128), uint8_t(256)) == -128); // NOT 128
    ASSERT(plus(uint8_t(256), int8_t(-128)) == -128); // NOT 128


    constexpr auto uint8_plus_int16 = plus(uint8_t(1), int16_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(uint8_plus_int16), const int>));
#else
    ASSERT((is_same_v<decltype(uint8_plus_int16), const int>));
#endif
    ASSERT(plus(uint8_t(256), int16_t(1)) == 1); // NOT 0 or 257 !!!
    ASSERT(plus(int16_t(1), uint8_t(256)) == 1); // NOT 0 or 257 !!!
    ASSERT(plus(uint8_t(1), int16_t(256)) == 257);
    ASSERT(plus(int16_t(256), uint8_t(1)) == 257);
    ASSERT(plus(int16_t(256), uint8_t(256)) == 256); // NOT 512 !!!


    constexpr auto uint8_plus_int32 = plus(uint8_t(1), int32_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(uint8_plus_int32), const long>));
#else
    ASSERT((is_same_v<decltype(uint8_plus_int32), const int>));
#endif
    ASSERT(plus(uint8_t(256), int32_t(1)) == 1); // NOT 0 or 257 !!!
    ASSERT(plus(int32_t(1), uint8_t(256)) == 1); // NOT 0 or 257 !!!
    ASSERT(plus(uint8_t(1), int32_t(256)) == 257);
    ASSERT(plus(int32_t(256), uint8_t(1)) == 257);
    ASSERT(plus(int32_t(256), uint8_t(256)) == 256); // NOT 512 !!!


    constexpr auto uint8_plus_int64 = plus(uint8_t(1), int64_t(2));
    ASSERT((is_same_v<decltype(uint8_plus_int64), const long long>));
    ASSERT(plus(uint8_t(256), int64_t(1)) == 1); // NOT 0 or 257 !!!
    ASSERT(plus(int64_t(1), uint8_t(256)) == 1); // NOT 0 or 257 !!!
    ASSERT(plus(uint8_t(1), int64_t(256)) == 257);
    ASSERT(plus(int64_t(256), uint8_t(1)) == 257);
    ASSERT(plus(int64_t(256), uint8_t(256)) == 256); // NOT 512 !!!


    constexpr auto uint16_plus_int16 = plus(uint16_t(1), int16_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(uint16_plus_int16), const unsigned>)); // !!!
    ASSERT(plus(uint16_t(65536), int16_t(-32768)) == 32768);
    ASSERT(plus(int16_t(-32768), uint16_t(65536)) == 32768);
#else
    ASSERT((is_same_v<decltype(uint16_plus_int16), const int>));
    ASSERT(plus(uint16_t(65536), int16_t(-32768)) == -32768);
    ASSERT(plus(int16_t(-32768), uint16_t(65536)) == -32768); // NOT 32768
#endif
    ASSERT(plus(int16_t(1), uint16_t(65536)) == 1); // NOT 0 or 65537 !!!
    ASSERT(plus(uint16_t(1), int16_t(256)) == 257);
    ASSERT(plus(int16_t(256), uint16_t(1)) == 257);
    ASSERT(plus(int16_t(32767), uint16_t(32767)) == 65534);


    constexpr auto uint16_plus_int32 = plus(uint16_t(1), int32_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(uint16_plus_int32), const long>));
#else
    ASSERT((is_same_v<decltype(uint16_plus_int32), const int>));
#endif
    ASSERT(plus(uint16_t(65536), int32_t(1)) == 1); // NOT 65537
    ASSERT(plus(int32_t(1), uint16_t(65536)) == 1); // NOT 65537


    constexpr auto uint16_plus_int64 = plus(uint16_t(1), int64_t(2));
    ASSERT((is_same_v<decltype(uint16_plus_int64), const long long>));
    ASSERT(plus(int16_t(65536), int64_t(65536)) == 65536); // NOT 131072
    ASSERT(plus(int64_t(65536), int16_t(65536)) == 65536); // NOT 131072

    constexpr auto int32_plus_int64 = plus(int32_t(1), int64_t(2));
    ASSERT((is_same_v<decltype(int32_plus_int64), const long long>));

    constexpr auto int64_plus_int64 = plus(int64_t(1), int64_t(2));
    ASSERT((is_same_v<decltype(int64_plus_int64), const long long>));
}

constexpr void multiplication()
{
    constexpr auto uint8_mult_uint8 = multiply(uint8_t(256), uint8_t(256));
    ASSERT((is_same_v<decltype(uint8_mult_uint8), const int>));
    ASSERT(multiply(uint8_t(1), uint8_t(2)) == 2);
    ASSERT(multiply(uint8_t(1), uint8_t(256)) == 0); // NOT 256
    ASSERT(uint8_mult_uint8 == 0); // NOT 65536

    constexpr auto uint8_mult_uint16 = multiply(uint8_t(1), uint16_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(uint8_mult_uint16), const unsigned>));
#else
    ASSERT((is_same_v<decltype(uint8_mult_uint16), const int>));
#endif
    ASSERT(multiply(uint8_t(1), uint16_t(65536)) == 0); // NOT 65536

    constexpr auto uint8_mult_uint32 = multiply(uint8_t(1), uint32_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(uint8_mult_uint32), const unsigned long>));
#else
    ASSERT((is_same_v<decltype(uint8_mult_uint32), const unsigned int>));
#endif

    constexpr auto uint8_mult_uint64 = multiply(uint8_t(1), uint64_t(2));
    ASSERT((is_same_v<decltype(uint8_mult_uint64), const unsigned long long>));

    constexpr auto uint16_mult_uint16 = multiply(uint16_t(1), uint16_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(uint16_mult_uint16), const unsigned>));
#else
    ASSERT((is_same_v<decltype(uint16_mult_uint16), const int>));
#endif

    constexpr auto uint16_mult_uint32 = multiply(uint16_t(1), uint32_t(2));
#if defined(__AVR__)
    ASSERT((is_same_v<decltype(uint16_mult_uint32), const unsigned long>));
#else
    ASSERT((is_same_v<decltype(uint16_mult_uint32), const unsigned>));
#endif

    constexpr auto uint16_mult_uint64 = multiply(uint16_t(1), uint64_t(2));
    ASSERT((is_same_v<decltype(uint16_mult_uint64), const unsigned long long>));
    ASSERT(multiply(uint16_t(65536), uint64_t(65536)) == 0); // NOT 2^32
    ASSERT(multiply(uint64_t(65536), uint16_t(65536)) == 0); // NOT 2^32

    constexpr auto uint32_mult_uint64 = multiply(uint32_t(1), uint64_t(2));
    ASSERT((is_same_v<decltype(uint32_mult_uint64), const unsigned long long>));
    ASSERT(multiply(uint64_t(65536), uint64_t(65536)) == 4294967296);
}


int main()
{
    addition_unsigned();

    addition_signed();

    addition_mixed();

    multiplication();

    return 0;
}