/** @file volatile_op.hpp.h
*   @brief Created on 2021-03-24 by Ben
*/
#pragma once

/**********************************************************************
* Includes
**********************************************************************/
#include <type_traits>

/**********************************************************************
* Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Typedefs
**********************************************************************/

/*https://embeddedartistry.com/blog/2019/03/11/improve-volatile-usage-with-volatile_load-and-volatile_store/*/

/** Read from a volatile variable
 *
 * @tparam TType the type of the variable. This will be deduced by the compiler.
 * @note TType shall satisfy the requirements of TrivallyCopyable.
 * @param target The pointer to the volatile variable to read from.
 * @returns the value of the volatile variable.
 */
template<typename TType>
constexpr inline TType volatile_load(const TType* target)
{
  static_assert(std::is_trivially_copyable<TType>::value,
                "Volatile load can only be used with trivially copiable types");
  return *static_cast<const volatile TType*>(target);
}

template<typename TType>
constexpr inline TType volatile_load(volatile const TType* target)
{
  static_assert(std::is_trivially_copyable<TType>::value,
                "Volatile load can only be used with trivially copiable types");
  return *static_cast<const volatile TType*>(target);
}

/** Write to a volatile variable
 *
 * Causes the value of `*target` to be overwritten with `value`.
 *
 * @tparam TType the type of the variable. This will be deduced by the compiler.
 * @note TType shall satisfy the requirements of TrivallyCopyable.
 * @param target The pointer to the volatile variable to update.
 * @param value The new value for the volatile variable.
 */
template<typename TType>
inline void volatile_store(TType* target, TType value)
{
  static_assert(std::is_trivially_copyable<TType>::value,
                "Volatile store can only be used with trivially copiable types");
  *static_cast<volatile TType*>(target) = value;
}

template<typename TType>
inline void volatile_store(volatile TType* target, TType value)
{
  static_assert(std::is_trivially_copyable<TType>::value,
                "Volatile store can only be used with trivially copiable types");
  *static_cast<volatile TType*>(target) = value;
}