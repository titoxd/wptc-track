#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "hurdat.h"
#include "track.h"

static bool is_header_line(char *line)
{
  return line[11] == '/';
}

static struct storm_header read_header(char *line)
{
  struct storm_header header;
  char *sub;

  strncpy(header.name, line + 35, sizeof(header.name));
  if ((sub = strstr(header.name, "  "))) {
    *sub = '\0';
  }

  line[24] = 0;
  header.id = atoi(line + 22);

  line[16] = 0;
  header.year = atoi(line + 12);

  return header;
}

struct stormdata *read_stormdata_hurdat(struct stormdata *storms,
					struct storm_arg *args)
{
  FILE *hurdat;
  char *line, buf[10240];
  int t = 0, s = 0, e = 0, l = 0;
  int lineno = 0;
  struct storm storm;
  int count = 0;

  hurdat = fopen(args->input, "r");

  if (!hurdat) {
    fprintf(stderr, "Couldn't open file '%s': %s\n",
	    args->input, strerror(errno));
    return NULL;
  }

  while ((line = fgets(buf, sizeof(buf), hurdat))) {
    lineno++;
    if (is_header_line(line)) {
      init_storm(&storm);
      storm.header = read_header(line);
#if 0
      printf("Beginning %s.\n", storm.header.name);
#endif

      line[11] = 0;
      line[8] = 0;
      storm.header.month = atoi(line + 6);
      storm.header.day = atoi(line + 9); /* estimate */

      count++;
    } else if (!isdigit(line[7])) {
      /* Some storms (like Andrew/1992) have an extra line at the
       * end.  I don't know what it does.  This skips it. */
      if (count > 0) {
	save_storm(args, storms, &storm);
      }
    } else {
      int i;

      for (i = 0; i < 4; i++) {
	struct pos pos;
	char subline[18];

#if 0
	printf("%s", line);
#endif

	pos.month = 10 * (line[6] - '0') + (line[7] - '0');
	pos.day = 10 * (line[9] - '0') + (line[10] - '0');
	pos.hour = i * 6;

	strncpy(subline, line + 11 + i * 17, 17);
	subline[17] = 0;

	switch (subline[0]) {
	case '*':
	case 'D': /* depression? */
	case 'd':
	  pos.type = TROPICAL;
	  t++;
	  break;
	case 'E':
	case 'e':
	case 'X':
	case 'x':
	  pos.type = EXTRATROPICAL;
	  e++;
	  break;
	case 'S':
	case 's':
	  pos.type = SUBTROPICAL;
	  s++;
	  break;
	case 'L': /* low */
	case 'l':
	case 'W': /* "wave" */
	case 'w':
	  pos.type = LOW;
	  l++;
	  break;
	case ' ':
	  continue;
	default:
	  fprintf(stderr, "Unknown line : %d : '%s'\n", lineno, subline);
	  break;
	}

	subline[12] = 0;
	subline[8] = 0;
	pos.lon = atoi(subline + 4) / 10.0;
	subline[4] = 0;
	pos.lat = atoi(subline + 1) / 10.0;
	pos.wind = atoi(subline + 9);
	pos.pres = atoi(subline + 13);

	save_pos(args, storms, &storm, &pos);
      }
    }
  }
  fclose(hurdat);

#if 0
  printf("Longitude: %d, %d\n", minlon, maxlon);
  printf("Latitude: %d, %d\n", minlat, maxlat);

  printf("%d %d %d %d\n", t, s, e, l);
#endif

  return storms;
}
