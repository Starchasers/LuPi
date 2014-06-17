//this file is mostly stolen, but who cares...
#include <_ansi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <errno.h>
#include <reent.h>
#include "driver/uart/uart.h"
#include "lib/debug/dmesg.h"
#undef errno

int errno;

unsigned int heap_end=0x0080000;
unsigned int prev_heap_end;

int
_read (int file,
       char * ptr,
       int len)
{
  kprint("W] call read\n");
  return len;
}


int
_lseek (int file,
    int ptr,
    int dir)
{
	kprint("W] call lseek\n");
    return 0;
}


int
_write (int file,
    char * ptr,
    int len)
{
	kprint("W] call write\n");
    int r;
    for(r=0;r<len;r++) uart_putc(ptr[r]);
    return len;
}

int
_open (const char * path,
       int flags,
       ...)
{
	kprint("W] call open\n");
    return 0;
}


int
_close (int file)
{
	kprint("W] call close\n");
    return 0;
}

void
_exit (int n)
{
	kprint("W] call exit\n");
    while(1);
}

int
_kill (int n, int m)
{
	kprint("W] call kill\n");
    return(0);
}

int
_getpid (int n)
{
  kprint("W] call getpid\n");
  return 1;
  n = n;
}


caddr_t
_sbrk (int incr)
{
	kprint("W] call sbrk\n");
    prev_heap_end = heap_end;
    heap_end += incr;
    return (caddr_t) prev_heap_end;
}

/*
caddr_t sbrk(int incr){
      extern char end;		// Defined by the linker 
      static char *heap_end;
      char *prev_heap_end;
     
      if (heap_end == 0) {
        heap_end = &end;
      }
      prev_heap_end = heap_end;
      if (heap_end + incr > stack_ptr)
        {
          _write (1, "Heap and stack collision\n", 25);
          abort ();
        }

      heap_end += incr;
      return (caddr_t) prev_heap_end;
    }
*/

int _fstat(int file, struct stat *st) {
  kprint("W] call fstat\n");
  st->st_mode = S_IFCHR;
  return 0;
}
    
int _stat (const char *fname, struct stat *st)
{
  kprint("W] call stat\n");
  return 0;
}

int
_link (void)
{
  kprint("W] call link\n");
  return -1;
}

int
_unlink (void)
{
  kprint("W] call unlink\n");
  return -1;
}

void
_raise (void)
{
  kprint("W] call raise\n");
  return;
}

int
_gettimeofday (struct timeval * tp, struct timezone * tzp)
{
	kprint("W] call gettimeofday\n");
    if(tp)
    {
        tp->tv_sec = 10;
        tp->tv_usec = 0;
    }
    if (tzp)
    {
        tzp->tz_minuteswest = 0;
        tzp->tz_dsttime = 0;
    }
    return 0;
}

clock_t
_times (struct tms * tp)
{
	kprint("W] call times\n");
    clock_t timeval;

    timeval = 10;
    if (tp)
    {
        tp->tms_utime = timeval; /* user time */
        tp->tms_stime = 0; /* system time */
        tp->tms_cutime = 0; /* user time, children */
        tp->tms_cstime = 0; /* system time, children */
    }
    return timeval;
};


int
_isatty (int fd)
{
  return 1;
  fd = fd;
}

int
_system (const char *s)
{
  kprint("W] call system\n");
  if (s == NULL)
    return 0;
  errno = ENOSYS;
  return -1;
}

int
_rename (const char * oldpath, const char * newpath)
{
  kprint("W] call rename\n");
  errno = ENOSYS;
  return -1;
}
