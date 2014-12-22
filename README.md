PAL: The Parallel Architectures Library
========================================

The Parallel Architectures Library (PAL) is a free and open-source C-libary written for tiny programmable CPUs that can be found in embedded applications and massively parallel processor architectures. PAL contains the following set of components:

* HAL: Minimalist hardware abstraction layer
* IPC: Set of basic synchronization primitives
* MATH: Vectorized math library
* DSP: Vectorized DSP library
* FFT: Optimized FFT library

Before starting the PAL project, we reviewed an long list of existing libraries/APIs and found the following issues:

* IPC code targeted mostly targeted for "big iron" processors and is not suitable for tiny processors
* Free and open source scalar APIs (like math.h) does not leverage vector/SIMD architectures
* Hardware vendor provided math and DSP libraries come with proprietary license restrictions

We are not trying to duplicated work here and have tried to cut down the API to the minimal possible.

A complete list of PAL functions can be found at the end of this file.

PAL Design Goals:

* Fast (assumes program and data resides in local cache/scratchpad)
* Open (permissive open source license)
* Small (because every bit counts for embedded processors)
* Scalable (should lend itself to vector and task parallelism)
* Portable (should be useful for different ISAs, with and without vector extensions, 32/64 bit)


##Licensing
PAL is licensed under the Apache License, Version 2.0. See LICENSE for full license text.

##Contributing
PAL is an ambitious project and neeeds all the help it can get. If you have anything to contribute, please do!! Instructions for get started can be found [HERE](CONTRIBUTING.md). 

##Coding style 
* C99
* "K&R coding style, 4 spaces for tabs"

##API Style Example
``` c
/*Function: Vector addition
            y[n-1:0]=a[n-1:0]+b[n-1:0]

  Arguments: 
  
  n is the number of elements in the vector
  a is a pointer to an intput array of floats
  b is a pointer to an input array of floats
  y is a pointer to an output array of floats
 */
 
void p_add_32f( int n, float* a, float* b, float* y );

```

PAL Library Functions
========================================
## HAL

**Memory Management (shared memory):**
* p_read()
* p_write()
* p_memcpy()
* p_memcpy_scatter()
* p_memcpy_gather()
* p_memcpy_bcast()
* p_memalloc()
* p_memfree()
* p_memptr()


**Program Execution (shared memory):**
* p_init()
* p_open()
* p_close()
* p_finalize()
* p_load()
* p_exec()


## IPC

**Mutex:**
* p_mutex_attr_init()
* p_mutex_atr_destroy()
* p_mutex_attr_setdevice()
* p_mutex_init()
* p_mutex_destroy()
* p_mutex_lock()
* p_mutex_unlock()
* p_mutex_trylock()

**Atomics:**
* p_atomic_init()
* p_atomic_exchange()
* p_atomic_compare_exchange()
* p_atomic_fetch_add()
* p_atomic_fetch_sub()
* p_atomic_fetch_or()
* p_atomic_fetch_xor()
* p_atomic_fetch_and()

**Memory ordering:**
* p_mem_flush()

**Barrier:**
* p_barrier_init()
* p_barrier_wait()

## MATH

**Conversion:**
* p_itof()
* p_ftoi()
* p_itod()
* p_dtoi()

**Trancendental:**
* p_acos_32f()
* p_acosh_32f()
* p_asin_32f()
* p_atan_32f()
* p_atan2_32f()
* p_cbrt_32f()
* p_cos_32f()
* p_cosh_32f()
* p_exp_32f()
* p_icbrt_32f()
* p_ln_32f()
* p_log10_32f()
* p_pow_32f()
* p_sin_32f()
* p_sincos_32f()
* p_sin_32f()
* p_tan_32f()
* p_tanh_32f()
 
**Reduction Operations**
* p_sum_32f()
* p_ave_32f()
* p_mean_32f()
* p_maxval_32f()
* p_minval_32f()
* p_sop_32f()

**Matrix Operations**
* p_matmul_32f()
* p_matadd_32f()
* p_matacc_32f()
* p_mataccw_32f()
* p_matand_32f()
* p_matxor_32f()
* p_mator_32f()
* p_matmac_32f()
* p_mattran_32f()
* p_matdiv_32f()
* p_matsqrt_32f()
* p_matisqrt_32f()
* p_matinv_32f()
* p_matabsdiff_32f()
* p_matsqadd_32f()


## DSP

**1D**
* p_acorr_32f()
* p_conf_32f()
* p_corr_32f()
* p_fir_32f()
* p_firdec_32f()
* p_firint_32f()
* p_firlat_32f()
* P_iir_32f()
* p_hist_32f()

**2D**
* p_conv2D_32f()
* p_acorr2D_32f()
* p_ave2D_32f()
* p_median2D_32f()
* p_sobel2D_32f()
* p_box2D_32f()
* p_canny2D_32f()
* p_harris2D_32f()
* p_gauss2D_32f()
* p_sad2D_32f()
* p_mad2D_32f()
* p_hist2D_32f()
* p_mag2D_32f()
* p_histeq2D_32f()
* p_minmax2D_32f()
* p_thresh2D_32f()
* p_scale2D_32f()
* p_lut2D_32f()
* p_memcpy2D_32f()

## FFT
* p_fftplan_32f()
* p_fftexec_32f()
* p_fftdestroy()


