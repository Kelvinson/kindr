/*
 * Copyright (c) 2013, Christian Gehring, Hannes Sommer, Paul Furgale, Remo Diethelm
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Autonomous Systems Lab, ETH Zurich nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Christian Gehring, Hannes Sommer, Paul Furgale,
 * Remo Diethelm BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef KINDER_POSITIONS_POSITIONBASE_HPP_
#define KINDER_POSITIONS_POSITIONBASE_HPP_


#include "kinder/common/common.hpp"

namespace kinder {
//! Generic position interface
/*! \ingroup positions
 */
namespace positions {
//! Internal stuff (only for developers)
namespace internal {

/*! \brief Addition traits for positions
 *  \class AdditionTraits
 *  (only for advanced users)
 */
template<typename LEFT_AND_RIGHT>
class AdditionTraits {
 public:
//  inline static LEFT add(const LEFT & l, const RIGHT & r);
//  inline static LEFT subtract(const LEFT & l, const RIGHT & r);
};

template<typename POSITION>
class get_scalar {
 public:
//  typedef PrimType Scalar;
};

} // namespace internal


template<typename DERIVED>
class PositionBase {
 public:
  /*! \brief Standard constructor.
    *  Creates an empty generic position object
    */
  PositionBase() = default;

  /*! \brief Constructor from derived position.
   *  This constructor has been deleted because the abstract class does not contain any data.
   */
  PositionBase(const DERIVED &) = delete; // on purpose!!

  /*! \brief Gets the derived position.
   *  (only for advanced users)
   *  \returns the derived position
   */
  operator DERIVED & () {
    return static_cast<DERIVED &>(*this);
  }

  /*! \brief Gets the derived position.
   *  (only for advanced users)
   *  \returns the derived position
   */
  operator const DERIVED & () const {
    return static_cast<const DERIVED &>(*this);
  }

  /*! \brief Gets the derived position.
   *  (only for advanced users)
   *  \returns the derived position
   */
  const DERIVED & derived() const {
    return static_cast<const DERIVED &>(*this);
  }


  /*! \brief Sets the position to zero.
   *  \returns reference
   */
  DERIVED & setZero();

  /*! \brief Addition.
   *  \returns
   */
  template<typename OTHER_DERIVED>
  DERIVED operator +(const PositionBase<OTHER_DERIVED> & other) const {
    return internal::AdditionTraits<PositionBase<DERIVED>>::add(this->derived(), other.derived()); // todo: 1. ok? 2. may be optimized
  }

  template<typename OTHER_DERIVED>
  DERIVED operator -(const PositionBase<OTHER_DERIVED> & other) const {
    return internal::AdditionTraits<PositionBase<DERIVED>>::subtract(this->derived(), other.derived()); // todo: 1. ok? 2. may be optimized
  }


  /*! \brief Addition and assignment.
   *  \returns  sum of the two positions
   */
  template<typename OTHER_DERIVED>
  DERIVED & operator +=(const PositionBase<OTHER_DERIVED> & other);

  /*! \brief Subtraction and assignment.
   *  \returns
   */
  template<typename OTHER_DERIVED>
  DERIVED & operator -=(const PositionBase<OTHER_DERIVED> & other);

};


template<typename DERIVED>
class Position3Base : public PositionBase<DERIVED> {
 public:
  typedef typename internal::get_scalar<DERIVED>::Scalar Scalar;
//  Position3Base() = default;
//  Position3Base(const Base& other);

//  Position3Base(const typename internal::get_scalar<DERIVED>::Scalar & x, const typename internal::get_scalar<DERIVED>::Scalar & y, const typename internal::get_scalar<DERIVED>::Scalar & z);

  inline const Scalar & x() const;
  inline Scalar& x();

  inline const Scalar& y() const;
  inline Scalar& y();

  inline Scalar& z() const;
  inline Scalar& z();

};


namespace internal {

template<typename LEFT_AND_RIGHT>
class AdditionTraits<PositionBase<LEFT_AND_RIGHT>> {
 public:
  inline static LEFT_AND_RIGHT add(const PositionBase<LEFT_AND_RIGHT> & l, const PositionBase<LEFT_AND_RIGHT> & r) {
    return LEFT_AND_RIGHT(typename LEFT_AND_RIGHT::Implementation(l.derived().toImplementation() + r.derived().toImplementation()));
  }

  inline static LEFT_AND_RIGHT subtract(const PositionBase<LEFT_AND_RIGHT> & l, const PositionBase<LEFT_AND_RIGHT> & r) {
    return LEFT_AND_RIGHT(typename LEFT_AND_RIGHT::Implementation(l.derived().toImplementation() - r.derived().toImplementation()));
  }
};

} // namespace internal

} // namespace positions
} // namespace kinder


#endif /* KINDER_POSITIONS_POSITIONBASE_HPP_ */
