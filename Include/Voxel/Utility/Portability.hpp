//==--- Utility/Utility/Portability.hpp ------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Utility 
//
//                        Copyright (c) 2017 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  Portability.hpp
/// \brief This file defines macros to allow correct compilation for host and
///        device code.
//
//==-----------------------------------------------------------------------==//

#ifndef VOXEL_UTILITY_UTILITY_PORTABILITY_HPP
#define VOXEL_UTILITY_UTILTIY_PORTABILITY_HPP

#if defined(__CUDA_ARCH__)

// Cuda device code compilation:
#define CUDA_DEVICE_COMPILE

#if defined(__clang__) && !defined(__CUDA__)

/// Definition for when clang is compiling CUDA code in host mode.
# define CLANG_CUDA_HOST_COMPILE

#elif defined(__clang__) && defined(__CUDA__)

/// Definition for when clang is compiling CUDA code in device mode.
# define CLANG_CUDA_DEVICE_COMPILE

#endif // clang and cuda
#endif // cuda_arch

#include <cuda.h>
#include <cuda_runtime.h>

/// Definition for host, device, and host device functions.
#if defined(__CUDACC__) || defined(__clang__)  // GPU Environment, or clang:
# define VoxxHost       __host__
# define VoxxDevice     __device__
# define VoxxDeviceHost __device__ __host__
#else                                          // Non-GPU Environment:
# define VoxxHost
# define VoxxDevice
# define VoxxDeviceHost
#endif 

#endif // VOXEL_UTILITY_UTILITY_PORTABILITY_HPP