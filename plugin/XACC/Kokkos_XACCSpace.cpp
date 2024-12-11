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

#define KOKKOS_IMPL_PUBLIC_INCLUDE

#include <XACC/Kokkos_XACC.hpp>
#include <XACC/Kokkos_XACCSpace.hpp>
#include <XACC/Kokkos_XACC_DeepCopy.hpp>
#include <impl/Kokkos_Profiling_Interface.hpp>
#include <impl/Kokkos_Error.hpp>

#include <XACC.h>

void *Kokkos::Experimental::XACCSpace::allocate(
    const Kokkos::Experimental::XACC &exec_space,
    const size_t arg_alloc_size) const {
  return allocate(exec_space, "[unlabeled]", arg_alloc_size);
}

void *Kokkos::Experimental::XACCSpace::allocate(
    const size_t arg_alloc_size) const {
  return allocate("[unlabeled]", arg_alloc_size);
}

void *Kokkos::Experimental::XACCSpace::allocate(
    const Kokkos::Experimental::XACC &exec_space, const char *arg_label,
    const size_t arg_alloc_size, const size_t arg_logical_size) const {
  return impl_allocate(exec_space, arg_label, arg_alloc_size, arg_logical_size);
}

void *Kokkos::Experimental::XACCSpace::allocate(
    const char *arg_label, const size_t arg_alloc_size,
    const size_t arg_logical_size) const {
  return impl_allocate(arg_label, arg_alloc_size, arg_logical_size);
}

void *Kokkos::Experimental::XACCSpace::impl_allocate(
    const Kokkos::Experimental::XACC &exec_space, const char *arg_label,
    const size_t arg_alloc_size, const size_t arg_logical_size,
    const Kokkos::Tools::SpaceHandle arg_handle) const {
  (void)exec_space;
  return impl_allocate(arg_label, arg_alloc_size, arg_logical_size, arg_handle);
}

void *Kokkos::Experimental::XACCSpace::impl_allocate(
    const char *arg_label, const size_t arg_alloc_size,
    const size_t arg_logical_size,
    const Kokkos::Tools::SpaceHandle arg_handle) const {
  static_assert(sizeof(void *) == sizeof(uintptr_t),
                "Error sizeof(void*) != sizeof(uintptr_t)");

  void *ptr = nullptr;

  ptr = acc_malloc(arg_alloc_size);

  if (!ptr) {
    Kokkos::Impl::throw_bad_alloc(name(), arg_alloc_size, arg_label);
  }

  if (Kokkos::Profiling::profileLibraryLoaded()) {
    const size_t reported_size =
        (arg_logical_size > 0) ? arg_logical_size : arg_alloc_size;
    Kokkos::Profiling::allocateData(arg_handle, arg_label, ptr, reported_size);
  }

  return ptr;
}

void Kokkos::Experimental::XACCSpace::deallocate(
    void *const arg_alloc_ptr, const size_t arg_alloc_size) const {
  deallocate("[unlabeled]", arg_alloc_ptr, arg_alloc_size);
}

void Kokkos::Experimental::XACCSpace::deallocate(
    const char *arg_label, void *const arg_alloc_ptr,
    const size_t arg_alloc_size, const size_t arg_logical_size) const {
  impl_deallocate(arg_label, arg_alloc_ptr, arg_alloc_size, arg_logical_size);
}

void Kokkos::Experimental::XACCSpace::impl_deallocate(
    const char *arg_label, void *const arg_alloc_ptr,
    const size_t arg_alloc_size, const size_t arg_logical_size,
    const Kokkos::Tools::SpaceHandle arg_handle) const {
  if (Kokkos::Profiling::profileLibraryLoaded()) {
    const size_t reported_size =
        (arg_logical_size > 0) ? arg_logical_size : arg_alloc_size;
    Kokkos::Profiling::deallocateData(arg_handle, arg_label, arg_alloc_ptr,
                                      reported_size);
  }

  if (arg_alloc_ptr) {
    acc_free(arg_alloc_ptr);
  }
}
