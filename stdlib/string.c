/*
    This file is part of the Lithium Kernel.

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
/*Copyright (C) 2020-2021 AlanCui*/
#include <bits/btypes.h>
#include <console/video.h>
size_t strlen(const char *s)
{
    for (size_t i = 0; i < SIZE_T_MAX; i++)
        if (s[i] == 0)
            return i;
    return 0;
}
size_t strnlen(const char *s, size_t maxlen)
{
    for (size_t i = 0; i < maxlen; i++)
        if (s[i] == '/0')
            return i;
    return 0;
}
void *memchr(const void *s, int c, size_t n)
{
    for (size_t i = 0; i < n; i++)
        if(*((char *)s+i)==c)
            return (void *)((char *)s+i);
}
void *memset(void *s, int c, size_t n)
{
    for (size_t i = 0; i < n; i++)
        *(((char *)s)+i ) = c;
}
static void *memrchr(const void *s, int c, size_t n)
{
    for (size_t i = n; i > 0; i--)
        if(*((char *)s+i)==c)
            return (void *)((char *)s+i);
}
void *memcpy(void *restrict s1, const void *restrict s2, size_t n)
{
    for (size_t i = 0; i < n; i++)
        ((char *)s1)[i] = ((char *)s2)[i];
    return s1;
}
char *strcpy(char *restrict s1, const char *restrict s2)
{
    return (char *)memcpy((void *)s1, (void *)s2, strlen(s2));
}
char *strncpy(char *restrict s1, const char *restrict s2, size_t n)
{
    return (char *)memcpy((void *)s1, (void *)s2, n);
}
char *strcat(char *restrict s1, const char *restrict s2)
{
    memcpy((void *)(s1 + strlen(s1)), s2, strlen(s2));
    return s1;
}
char *strncat(char *restrict s1, const char *restrict s2, size_t n)
{
    memcpy((void *)(s1 + strlen(s1)), s2, n);
    return s1;
}
int strcmp(const char *s1, const char *s2)
{
    for (size_t i = 0; i < (strlen(s1) < strlen(s2) ? strlen(s1) : strlen(s2)) + 1; i++)
        if (s1[i] < s2[i])
            return -1;
        else if (s1[i] > s2[i])
            return 1;
    return 0;
}
int strncmp(const char *s1, const char *s2, size_t n)
{
    for (size_t i = 0; i < n; i++)
        if (s1[i] < s2[i])
            return -1;
        else if (s1[i] > s2[i])
            return 1;
    return 0;
}
char *strchr(const char *s, int c){
    return (char *)memchr(s,c,strlen(s));
}
char *strrchr(const char *s, int c){
    return (char *)memrchr(s,c,strlen(s));
}

char *strins(char *restrict s1, const char *restrict s2,size_t n)
{
    strncpy(s1+n+strlen(s2),s1+n,strlen(s2));
    strcpy(s1+n,s2);
  //  strdel(s1,n+strlen(s2),1);
    return s1;
}

char *strdel(char *restrict s, int p, size_t n)
{
    size_t v1 = strlen(s) - n;
    strcpy(s+p,s+p+n);
    memset(s+v1,0,n);
    return s;
}
char *num2str32(char* tmp,uint32_t num)
{
    for (size_t i = 2; i < 10; i++)
    {
        switch (((num >> ((9 - i)) * 4)) & 0xfUL)
        {
        case 0:
            tmp[i] = '0';
            break;
        case 1:
            tmp[i] = '1';
            break;
        case 2:
            tmp[i] = '2';
            break;
        case 3:
            tmp[i] = '3';
            break;
        case 4:
            tmp[i] = '4';
            break;
        case 5:
            tmp[i] = '5';
            break;
        case 6:
            tmp[i] = '6';
            break;
        case 7:
            tmp[i] = '7';
            break;
        case 8:
            tmp[i] = '8';
            break;
        case 9:
            tmp[i] = '9';
            break;
        case 10:
            tmp[i] = 'A';
            break;
        case 11:
            tmp[i] = 'B';
            break;
        case 12:
            tmp[i] = 'C';
            break;
        case 13:
            tmp[i] = 'D';
            break;
        case 14:
            tmp[i] = 'E';
            break;
        case 15:
            tmp[i] = 'F';
            break;
        default:
            tmp[i] = '*';
            break;
        }
    }
    kputstr(0,2,tmp,YELLOW,BLACK);
    return tmp;
}
/*char* num2dec32(char* tmp,uint32_t num)
{
    
}*/