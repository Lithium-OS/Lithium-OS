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
/*MainDevloper: AlanCui*/
/*ISO C std Lib*/
#include "stdint.h"
uint32_t errno=999;
#ifndef _ERR_H
#define _ERR_H
    #define ERROR        0
    #define EPERM		 1
    #define ENOENT		 2
    #define ESRCH		 3
    #define EINTR		 4
    #define EIO		     5
    #define ENXIO		 6
    #define E2BIG		 7
    #define ENOEXEC		 8
    #define EBADF		 9
    #define ECHILD		10
    #define EAGAIN		11
    #define ENOMEM		12
    #define EACCES		13
    #define EFAULT		14
    #define ENOTBLK		15
    #define EBUSY		16
    #define EEXIST		17
    #define EXDEV		18
    #define ENODEV		19
    #define ENOTDIR		20
    #define EISDIR		21
    #define EINVAL		22
    #define ENFILE		23
    #define EMFILE		24
    #define ENOTTY		25
    #define ETXTBSY		26
    #define EFBIG		27
    #define ENOSPC		28
    #define ESPIPE		29
    #define EROFS		30
    #define EMLINK		31
    #define EPIPE		32
    #define EDOM		33
    #define ERANGE		34
    #define EDEADLK		35
    #define ENAMETOOLONG	36
    #define ENOLCK		37
    #define ENOSYS		38
    #define ENOTEMPTY	39
#endif