#include <stdlib.h>

#include "tab.h"
#include "track.h"

struct stormdata *read_stormdata_tab(struct stormdata *storms,
				     struct storm_arg *args)
{
#if 0
  FILE *file = fopen(args->input, "r");
  char *line, buf[10240];
  struct storm storm;

  if (!hurdat) {
    fprintf(stderr, "Couldn't open file '%s': %s\n",
	    args->input, strerror(errno));
    return NULL;
  }

  while ((line = fgets(buf, sizeof(buf), hurdat))) {
    char *name;

    sscanf(buf, "%s\t");
  }
#endif

  return NULL;
}
