#ifndef _lib_try_catch
#define _lib_try_catch

#include <setjmp.h>

enum error_status_code {
    EOF_io,
    null_ptr,
    open_file
};

extern int _exception;

#define try(arg) if ( (_exception = setjmp(*arg)) == 0 )
#define catch(err) else if (_exception == (err) )
#define catch_all else
#define throw(arg, err) longjmp(*arg, (err) )

#endif
