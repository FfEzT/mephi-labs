#pragma once

#ifndef _lib_try_catch
#define _lib_try_catch

#include <setjmp.h>

enum error_status_code {
    EOF_io,
    null_ptr,
    open_file
};

extern jmp_buf _buf;
extern int _exception;

#define try if ( (_exception = setjmp(_buf)) == 0 )
#define catch(err) else if (_exception == err)
#define catch_all else
#define throw(err) longjmp(_buf, err)

#endif