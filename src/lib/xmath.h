// C Standard Library
// C++ Standard Library
// xmath.h [internal]

// float properties, little-endian
#ifndef __big_endian
#   define _F0 1
#   define _F1 0
#   define _D0 3
#   define _D1 2
#   define _D2 1
#   define _D3 0
#   define _L0 3
#   define _L1 2
#   define _L2 1
#   define _L3 0
#else
#   define _F0 0
#   define _F1 1
#   define _D0 0
#   define _D1 1
#   define _D2 2
#   define _D3 3
#   define _L0 0
#   define _L1 1
#   define _L2 2
#   define _L3 3
#endif

#define _DFRAC ((1 << _DOFF) - 1)
#define _DMASK (0x7fff & ~_DFRAC)
#define _DMAX ((1 << (15 - _DOFF)) - 1)
#define _DNAN (0x8000 | _DMAX << _DOFF | 1 << (_DOFF - 1))

// IEEE 754
#ifdef __cplusplus
#   define FHUGE_EXP static_cast<int>(_FMAX * 900l / 1000)
#   define HUGE_EXP static_cast<int>(_DMAX * 900l / 1000)
#   define LHUGE_EXP static_cast<int>(_LMAX * 900l / 1000)
#else
#   define FHUGE_EXP (int)(_FMAX * 900l / 1000)
#   define HUGE_EXP (int)(_DMAX * 900l / 1000)
#   define LHUGE_EXP (int)(_LMAX * 900l / 1000)
#endif

// store float to integer array
union __float_value {
    unsigned short sh[8];
    float val;
};

union __double_value {
    unsigned short sh[8];
    double val;
};

union __long_double_value {
    unsigned short sh[8];
    long double val;
};

// get sign
#ifdef __cplusplus
#   define FSIGN(x) (reinterpret_cast<__float_value*>(&(x))->sh[_F0] & 0x8000)
#   define DSIGN(x) (reinterpret_cast<__double_value*>(&(x))->sh[_D0] & 0x8000)
#   define LSIGN(x) (reinterpret_cast<__long_double_value*>(&(x))->sh[_L0] & 0x8000)
#else
#   define FSIGN(x) (__float_value*)(&(x))->sh[_F0] & 0x8000)
#   define DSIGN(x) (__double_value*)(&(x))->sh[_D0] & 0x8000)
#   define LSIGN(x) (__long_double_value*)(&(x))->sh[_L0] & 0x8000)
#endif

#define FINITE -1
#define INF 1
#define NAN 2

short __dtest(double *d);
