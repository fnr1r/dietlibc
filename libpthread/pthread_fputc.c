#include <dietstdio.h>
#ifndef WANT_BUFFERED_STDIO
#include <unistd.h>
#endif

int fputc(int c, FILE *stream) {
  int tmp;
  pthread_mutex_lock(&stream->m);
  tmp=fputc_unlocked(c,stream);
  pthread_mutex_unlock(&stream->m);
  return tmp;
}
