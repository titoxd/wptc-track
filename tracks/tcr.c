#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "tcr.h"
#include "track.h"

static char *stripspace(char *str)
{
  while (isspace(str[0])) {
    str++;
  }
  while (isspace(str[strlen(str) - 1])) {
    str[strlen(str) - 1] = '\0';
  }
  return str;
}

struct stormdata *read_stormdata_tcr(struct stormdata *storms,
				     struct storm_arg *args)
{
  FILE *file;
  char *line, buf[10240];
  struct storm storm;
  char *targets[] = {"Date/Time", "Latitude", "Longitude", "Pressure",
		     "Wind Speed", "Stage"};
  const int num_targets = sizeof(targets) / sizeof(targets[0]);
  int targets_found = 0;
  float val;
  int type = TROPICAL;

  file = fopen(args->input, "r");

  if (!file) {
    fprintf(stderr, "Couldn't open file '%s': %s\n",
	    args->input, strerror(errno));
    exit(-1);
  }

  init_storm(&storm);

  while ((line = fgets(buf, sizeof(buf), file))) {
    struct pos pos;

    line = stripspace(line);

    if (targets_found < num_targets) {
      if (strcmp(line, targets[targets_found]) == 0) {
	targets_found++;
      }
      continue;
    }

    /* Line 1: time */

    if (!strchr(line, '/')) {
      printf("No / in '%s', breaking.\n", line);
      break;
    }

    /* Line 2: latitude */
    line = fgets(buf, sizeof(buf), file);
    sscanf(line, "%f", &val);
    pos.lat = val;

    /* Line 3: longitude */
    line = fgets(buf, sizeof(buf), file);
    sscanf(line, "%f", &val);
    pos.lon = val;

    /* Line 4: pressure */
    line = fgets(buf, sizeof(buf), file);
    pos.pres = atoi(line);

    /* Line 5: wind */
    line = fgets(buf, sizeof(buf), file);
    pos.wind = atoi(line);
    if (pos.wind == 0) {
      break;
    }

    /* Line 6: comment */
    line = fgets(buf, sizeof(buf), file);
    line = stripspace(line);
    if (strcasecmp(line, "hurricane") == 0
	|| strcasecmp(line, "tropical storm") == 0
	|| strcasecmp(line, "tropical depression") == 0) {
      type = TROPICAL;
    } else if (strcasecmp(line, "extratropical") == 0) {
      type = EXTRATROPICAL;
    } else if (strcasecmp(line, "low") == 0
	       || strcasecmp(line, "remnant low") == 0
	       || strcasecmp(line, "tropical wave") == 0) {
      type = LOW;
    } else if ((strcasecmp(line, "subtropical depression") == 0) 
               || strcasecmp(line, "subtropical storm") == 0) {
      type = SUBTROPICAL;
    } else if (strcmp(line, "\"") == 0
	       || strcmp(line, "\223") == 0) {
      /*nothing */
    } else {
      printf("Unrecognized comment '%s'.\n", line);
      exit(1);
    }
    pos.type = type;
    save_pos(args, storms, &storm, &pos);
  }
  fclose(file);

  save_storm(args, storms, &storm);

#if 0
  printf("Longitude: %d, %d\n", minlon, maxlon);
  printf("Latitude: %d, %d\n", minlat, maxlat);

  printf("%d %d %d %d\n", t, s, e, l);
#endif

  return storms;
}
