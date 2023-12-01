#ifndef util_h_
#define util_h_

#define TODO()                                                                 \
  fprintf(stderr, "TODO: at %s:%d\n", __FILE_NAME__, __LINE__), exit(1)

void error(const char *txt);

#endif
