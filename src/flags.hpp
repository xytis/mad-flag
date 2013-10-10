// =====================================================================================
// 
//       Filename:  flags.hpp
// 
//    Description:  Reinvention of simple bit flags.
// 
//        Version:  1.0
//        Created:  07/11/2013 10:28:49 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Vytis Valentinavičius (VV), vytis@nolife4life.org
//        Company:  N4L
// 
// =====================================================================================

#include <iostream>
#include <bitset>


namespace Flags {
  template<typename T, size_t pos, bool state>
  struct flag;
  
  template<typename T, typename lhs_t, typename rhs_t>
  struct flag_group;
  
  template<typename T, size_t length>
  struct field {
    constexpr field() : data() {};
    std::bitset<length> data;
    
    void print() {
      std::cout << "Flag state: ";
      for (int i = 0; i < length; ++i) {
        std::cout << data[i];
      }
      std::cout << std::endl;
    }
    
    
    template<size_t pos>
    inline bool is(const flag<T, pos, true> & flag) const {
      return data.test(pos);
    }
    
    template<size_t pos>
    inline bool is(const flag<T, pos, false> & flag) const {
      return !data.test(pos);
    }
    
    template<typename U, size_t pos>
    inline field & operator |= (const flag<U, pos, true> & flag) {
      static_assert(std::is_same<T,U>::value, "Flag type missmatch!");
      static_assert(pos < length, "Can not apply flag. Index out of bounds.");
      data.set(pos);
      return *this;
    }
    
    template<typename U, size_t pos>
    inline field & operator |= (const flag<U, pos, false> & flag) {
      static_assert(std::is_same<T,U>::value, "Flag type missmatch!");
      static_assert(pos < length, "Can not apply flag. Index out of bounds.");
      data.reset(pos);
      return *this;
    }
    
    template<typename U, typename lhs_t, typename rhs_t>
    inline field & operator |= (const flag_group<U, lhs_t, rhs_t> & group) {
      static_assert(std::is_same<T,U>::value, "Flag type missmatch!");
      (*this) |= group.lhs;
      (*this) |= group.rhs;
      return *this;
    }
  };
  
  template<typename T, size_t pos, bool state = true>
  struct flag {
    constexpr flag() {}
  };
  
  template<typename T, size_t pos, bool state>
  flag<T, pos, !state> operator ! (flag<T, pos, state> in) { return flag<T, pos, !state>(); }
  
  template<typename T, typename lhs_t, typename rhs_t>
  struct flag_group {
    lhs_t & lhs;
    rhs_t & rhs;
  };
  
  template<
  typename T,     size_t l_index, bool l_state,
  typename U,     size_t r_index, bool r_state,
  template<typename, size_t, bool> class lhs_t,
  template<typename, size_t, bool> class rhs_t
  >
  constexpr auto operator | (lhs_t<T, l_index, l_state> lhs, rhs_t<U, r_index, r_state> rhs) -> flag_group<T, decltype(lhs), decltype(rhs)> {
    static_assert(std::is_same<T,U>::value, "Flag type missmatch!");
    return {lhs, rhs};
  }
  
  template<
  typename T, typename l_lhs_t, typename l_rhs_t,
  typename U,     size_t r_index, bool r_state,
  template<typename, typename, typename> class lhs_t,
  template<typename, size_t, bool> class rhs_t
  >
  constexpr auto operator | (lhs_t<T, l_lhs_t, l_rhs_t> lhs, rhs_t<U, r_index, r_state> rhs) -> flag_group<T, decltype(lhs), decltype(rhs)> {
    static_assert(std::is_same<T,U>::value, "Flag type missmatch!");
    return {lhs, rhs};
  }
  
  template<
  typename T, typename l_lhs_t, typename l_rhs_t,
  typename U,     typename r_lhs_t, typename r_rhs_t,
  template<typename, typename, typename> class lhs_t,
  template<typename, typename, typename> class rhs_t>
  constexpr auto operator | (lhs_t<T, l_lhs_t, l_rhs_t> lhs, rhs_t<U, r_lhs_t, r_rhs_t> rhs) -> flag_group<T, decltype(lhs), decltype(rhs)> {
    static_assert(std::is_same<T,U>::value, "Flag type missmatch!");
    return {lhs, rhs};
  }
  
}

#if _MSC_VER >= 1400

#       define LEFT_PARENTHESIS         (
#       define RIGHT_PARENTHESIS                )
#       define PASS_VA(...)                     LEFT_PARENTHESIS __VA_ARGS__ RIGHT_PARENTHESIS

#       define VA_NUM_ARGS(...)                 VA_NUM_ARGS_HELPER PASS_VA(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#       define EXPAND_0(macro, ...)
#       define EXPAND_1(macro, index, arg, ...) macro(index, arg)
#       define EXPAND_2(macro, index, arg, ...) macro(index, arg) EXPAND_1 PASS_VA(macro, index + 1, __VA_ARGS__)
#       define EXPAND_3(macro, index, arg, ...) macro(index, arg) EXPAND_2 PASS_VA(macro, index + 1, __VA_ARGS__)
#       define EXPAND_4(macro, index, arg, ...) macro(index, arg) EXPAND_3 PASS_VA(macro, index + 1, __VA_ARGS__)
#       define EXPAND_5(macro, index, arg, ...) macro(index, arg) EXPAND_4 PASS_VA(macro, index + 1, __VA_ARGS__)
#       define EXPAND_6(macro, index, arg, ...) macro(index, arg) EXPAND_5 PASS_VA(macro, index + 1, __VA_ARGS__)
#       define EXPAND_7(macro, index, arg, ...) macro(index, arg) EXPAND_6 PASS_VA(macro, index + 1, __VA_ARGS__)
#       define EXPAND_8(macro, index, arg, ...) macro(index, arg) EXPAND_7 PASS_VA(macro, index + 1, __VA_ARGS__)
#       define EXPAND_9(macro, index, arg, ...) macro(index, arg) EXPAND_8 PASS_VA(macro, index + 1, __VA_ARGS__)
#       define EXPAND_10(macro, index, arg, ...) macro(index, arg) EXPAND_9 PASS_VA(macro, index + 1, __VA_ARGS__)

#       define EXPAND(macro, ...) JOIN(EXPAND_, VA_NUM_ARGS(__VA_ARGS__)) PASS_VA(macro, 0, __VA_ARGS__)

#else

#       define VA_NUM_ARGS(...)                 VA_NUM_ARGS_HELPER(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#       define EXPAND_0(macro, ...)
#       define EXPAND_1(macro, index, arg, ...) macro(index, arg)
#       define EXPAND_2(macro, index, arg, ...) macro(index, arg) EXPAND_1(macro, index + 1, __VA_ARGS__)
#       define EXPAND_3(macro, index, arg, ...) macro(index, arg) EXPAND_2(macro, index + 1, __VA_ARGS__)
#       define EXPAND_4(macro, index, arg, ...) macro(index, arg) EXPAND_3(macro, index + 1, __VA_ARGS__)
#       define EXPAND_5(macro, index, arg, ...) macro(index, arg) EXPAND_4(macro, index + 1, __VA_ARGS__)
#       define EXPAND_6(macro, index, arg, ...) macro(index, arg) EXPAND_5(macro, index + 1, __VA_ARGS__)
#       define EXPAND_7(macro, index, arg, ...) macro(index, arg) EXPAND_6(macro, index + 1, __VA_ARGS__)
#       define EXPAND_8(macro, index, arg, ...) macro(index, arg) EXPAND_7(macro, index + 1, __VA_ARGS__)
#       define EXPAND_9(macro, index, arg, ...) macro(index, arg) EXPAND_8(macro, index + 1, __VA_ARGS__)
#       define EXPAND_10(macro, index, arg, ...) macro(index, arg) EXPAND_9(macro, index + 1, __VA_ARGS__)

#       define EXPAND(macro, ...) JOIN(EXPAND_, VA_NUM_ARGS(__VA_ARGS__))(macro, 0, __VA_ARGS__)

#endif

#define VA_NUM_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...)    N
#define JOIN(x, y)                                      JOIN_HELPER(x, y)
#define JOIN_HELPER(x, y)                       JOIN_HELPER_HELPER(x, y)
#define JOIN_HELPER_HELPER(x, y)        x##y

#define FLAG(index, name) constexpr Flags::flag<_guard, index> name;
#define PRINT_FLAG(index, name) if (flags.is(name)) {\
result.append(" "#name);\
}

#define FLAGS(name, ...)\
namespace name\
{\
  typedef struct{} _guard; \
  typedef Flags::field<_guard, VA_NUM_ARGS(__VA_ARGS__)> State;\
  EXPAND(FLAG, __VA_ARGS__)\
  \
  static std::string ToString( const State & flags ) {\
    std::string result;\
    result.append(#name" are:");\
    EXPAND(PRINT_FLAG, __VA_ARGS__)\
    return result;\
  };\
}

