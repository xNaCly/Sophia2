#ifndef UTIL_H_
#define UTIL_H_

#define TODO()                                                                 \
  fprintf(stderr, "TODO: at %s:%d\n", __FILE_NAME__, __LINE__), exit(1)

void error(const char *txt);

#endif
