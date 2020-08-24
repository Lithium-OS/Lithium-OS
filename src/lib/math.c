 /* Copyright (C) 2020 LithiumOS-Team

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "./math.h"
#include "./xmath.h"

static const double tau = 6.28318530717958647693;

double fabs(double x) {
    switch (__dtest(&x)) {
    case NAN:
        errno = EDOM;
        return x;
    case INF:
        errno = ERANGE;
        return __inf._D;
    case 0:
        return 0.0;
    default:
        return x < 0.0 ? -x : x;
    }
}

double __sin(double x, double y, int iy) {
    static const double
        HA =  5.00000000000000000000e-01, /* 0x3FE00000, 0x00000000 */
        S1 = -1.66666666666666324348e-01, /* 0xBFC55555, 0x55555549 */
        S2 =  8.33333333332248946124e-03, /* 0x3F811111, 0x1110F8A6 */
        S3 = -1.98412698298579493134e-04, /* 0xBF2A01A0, 0x19C161D5 */
        S4 =  2.75573137070700676789e-06, /* 0x3EC71DE3, 0x57B1FE7D */
        S5 = -2.50507602534068634195e-08, /* 0xBE5AE5E6, 0x8A2B9CEB */
        S6 =  1.58969099521155010221e-10; /* 0x3DE5D93A, 0x5ACFD57C */
    double z = x * x, w = z * z;
    double r = S2 + z * (S3 + z * S4) + z * w + (S5 + z * S6);
    double v = z * x;
    if (iy == 0) {
        return x + v * (S1 + z * r);
    }
    else {
        return x - ((z * (HA * y - v * r) - y) - v * S1);
    }

}

double __sin(double x, unsigned int off) {
    switch(__dtest(&x)) {
    case NAN:
        errno = EDOM;
        return x;
    case 0:
        return qoff ? 1.0 : 0.0;
    case INF:
        errno = EDOM;
        return __nan.D;
    default: {
        double g;
        long quad;
        if (x < -HUGE_RAD || HUGE_RAD < x) {
            g = x / tau;

        }
    }
    }
}
