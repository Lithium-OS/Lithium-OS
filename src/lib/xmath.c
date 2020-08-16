#include "./xmath.h"
#include "./stdint.h"
#include "./stdlib.h"

short __dtest(double *d) {
    __double_value *v = (__double_value)x;
    int16_t xc = (v->sh[_D0] & _DMASK) >> _DOFF;

    if (xc == _DMAX) {
        return v->sh[_D0] & _DFRAC || v->sh[_D1]
            || v->sh[_D2] || v->sh[_D3] ? NAN : INF;
    }
    else if (0 < xc || v->sh[_D0] & _DFRAC
        || v->sh[_D1] || v->sh[_D2] || v->sh[_D3]
    ) {
        return FINITE
    }
    else {
        return 0;
    }
}

short __dint(double *x, short xe) {
    __double_value *v = (__double_value)x;
    uint16_t frac = v->sh[_D0] & _DFRAC || v->sh[_D1]
        || v->sh[_D2] || v->sh[_D3];
    int16_t xc = (v->sh[_D0] & _DMASK) >> _DOFF;

    if (xc == 0 && !frac) {
        return 0;
    }
    else if (xc != _DMAX) {
        xc = (_DBIAS + 48 + _DOFF + 1) - xc - xe;
        if (xc <= 0) {
            return 0;
        }
        else if ((48 + _DOFF) < xc) {
            v->sh[_D0] = v->sh[_D1] = 0;
            v->sh[_D2] = v->sh[_D3] = 0;
            return FINITE;
        }
        else {
            static const uint16_t mask[] = {
                0x0000, 0x0001, 0x0003, 0x0007,
                0x000f, 0x001f, 0x003f, 0x007f,
                0x00ff, 0x01ff, 0x03ff, 0x07ff,
                0x0fff, 0x1fff, 0x3fff, 0x7fff
            }
            static const size_t sub[] = {
                _D3, _D2, _D1, _D0
            };

            frac = mask[xc & 0xf];
            xc >>= 4;
            frac &= v->sh[sub[xc]];
            v->sh[sub[xc]] ^= frac;
            switch (xc) {
            case 3:
                frac |= v->sh[_D1], v->sh[_D1] = 0;
            case 2:
                frac |= v->sh[_D2], v->sh[_D2] = 0;
            case 1:
                frac |= v->sh[_D3], v->sh[_D3] = 0;
            }
            return frac ? FINITE : 0;
        }
    }
    else if (!frac) {
        return INF;
    }
    else {
        errno = EDOM;
        return NAN;
    }
}

