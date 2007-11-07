#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "md.h"
#include "track.h"

static bool is_header1_line(char *line)
{
  return isalpha(line[0]);
}

static bool is_header2_line(char *line)
{
  return isalpha(line[4]);
}

static struct storm_header read_header(char *line)
{
  struct storm_header header;
  char *sub;

  strncpy(header.name, line, sizeof(header.name));
  if ((sub = strstr(header.name, "  "))) {
    *sub = '\0';
  }

  header.id = 1;
  header.year = 0;

  return header;
}

struct stormdata *read_stormdata_md(struct stormdata *storms,
				    struct storm_arg *args)
{
  FILE *file;
  char *line, buf[10240];
  int lineno = 0;
  struct storm storm;
  int count = 0;

  file = fopen(args->input, "r");

  if (!file) {
    fprintf(stderr, "Couldn't open file '%s': %s\n",
	    args->input, strerror(errno));
    exit(-1);
  }

  while ((line = fgets(buf, sizeof(buf), file))) {
    lineno++;
    if (is_header1_line(line)) {
      if (count > 0) {
	save_storm(args, storms, &storm);
      }
      init_storm(&storm);
      storm.header = read_header(line);
#if 0
      printf("Beginning %s.\n", storm.header.name);
#endif
      count++;
    } else if (is_header2_line(line)) {
      /* Nothing */
    } else {
      int i;

      for (i = 0; i < 4; i++) {
	struct pos pos;
	float val;

#if 0
	printf("%s", line);
#endif

	pos.type = TROPICAL;

	line[28] = 0;
	sscanf(line + 22, "%f", &val);
	pos.lon = val;

	line[36] = 0;
	sscanf(line + 31, "%f", &val);
	pos.lat = val;

	line[41] = 0;

	pos.wind = atoi(line + 37);
	switch (args->wind_format) {
	case MPH:
		pos.wind = (double)pos.wind / 1.15 + 0.5;
		break;
	case KT:
		/* nothing */
		break;
	case KPH:
		pos.wind = (double)pos.wind / 1.852 + 0.5;
		break;
	}

	pos.pres = atoi(line + 45);

	save_pos(args, storms, &storm, &pos);
      }
    }
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
