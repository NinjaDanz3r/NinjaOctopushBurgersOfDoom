#ifndef __GLERROR_H__
#define __GLERROR_H__

void _check_gl_error(const char *file, int line);

#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

#endif