//@HEADER
// ************************************************************************
//
//                        Kokkos v. 4.0
//       Copyright (2022) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Part of Kokkos, under the Apache License v2.0 with LLVM Exceptions.
// See https://kokkos.org/LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//@HEADER

#ifndef KOKKOS_XACC_MDRANGE_POLICY_HPP_
#define KOKKOS_XACC_MDRANGE_POLICY_HPP_

#include <KokkosExp_MDRangePolicy.hpp>

template <>
struct Kokkos::default_outer_direction<Kokkos::Experimental::XACC> {
  using type                     = Iterate;
  static constexpr Iterate value = Iterate::Left;
};

template <>
struct Kokkos::default_inner_direction<Kokkos::Experimental::XACC> {
  using type                     = Iterate;
  static constexpr Iterate value = Iterate::Left;
};

namespace Kokkos {
namespace Impl {

template <typename Rank, TeamMDRangeThreadAndVector ThreadAndVector>
struct ThreadAndVectorNestLevel<Rank, Kokkos::Experimental::XACC,
                                ThreadAndVector>
    : AcceleratorBasedNestLevel<Rank, ThreadAndVector> {};

}  // namespace Impl
}  // namespace Kokkos

namespace Kokkos::Experimental::Impl {

struct XACCCollapse {};
struct XACCTile {};
using XACCIterateLeft  = std::integral_constant<Iterate, Iterate::Left>;
using XACCIterateRight = std::integral_constant<Iterate, Iterate::Right>;
template <int N>
using XACCMDRangeBegin = decltype(MDRangePolicy<XACC, Rank<N>>::m_lower);
template <int N>
using XACCMDRangeEnd = decltype(MDRangePolicy<XACC, Rank<N>>::m_upper);
template <int N>
using XACCMDRangeTile = decltype(MDRangePolicy<XACC, Rank<N>>::m_tile);

}  // namespace Kokkos::Experimental::Impl

#endif
