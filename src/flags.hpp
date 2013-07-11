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

namespace Flags {
  /// Operations are additive. So sentence like
  /// object.set(a | a | !a | !a | a);
  /// makes sense and in turn is equal to
  /// object.set(a);
  enum Operation {
    Remove = -1,
    Ignore =  0,
    Set    =  1,
  };

  template<size_t len>
  struct Field;



  template<size_t pos, size_t len>
  struct Bit {
    Operation op;
    
    template<template<size_t,size_t> Tb, size_t Tp, size_t Tl>
      Field<len> operator | (const Tb<Tp,Tl> & bit);

    template<template<size_t,size_t> Tb, size_t Tp>
      Field<len> operator | (const Tb<Tp,len> & bit);

    template<template<size_t> Tf, size_t Tl>
      Field<len> operator | (const Tf<Tl> & field);

    template<template<size_t> Tf>
      Field<len> operator | (const Tf<len> & field);

    Bit operator | (const Bit & bit) {
      return {this.op + bit.op};
    }
  };

  template<size_t length>
  struct Field {
    const Bit[length];
  };
  

} 
