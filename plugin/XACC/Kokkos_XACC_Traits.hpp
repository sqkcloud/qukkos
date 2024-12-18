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

#ifndef KOKKOS_XACC_TRAITS_HPP
#define KOKKOS_XACC_TRAITS_HPP

#include <XACC.h>

namespace Kokkos::Experimental::Impl {

struct XACC_Traits {
#if defined(KOKKOS_IMPL_ARCH_NVIDIA_GPU)
  static constexpr acc_device_t dev_type     = acc_device_nvidia;
  static constexpr bool may_fallback_to_host = false;
#elif defined(KOKKOS_ARCH_AMD_GPU)
  static constexpr acc_device_t dev_type     = acc_device_radeon;
  static constexpr bool may_fallback_to_host = false;
#elif defined(KOKKOS_ENABLE_XACC_FORCE_HOST_AS_DEVICE)
  static constexpr acc_device_t dev_type     = acc_device_host;
  static constexpr bool may_fallback_to_host = true;
#else
  static constexpr acc_device_t dev_type     = acc_device_default;
  static constexpr bool may_fallback_to_host = true;
#endif
};

}  // namespace Kokkos::Experimental::Impl

#endif
