/* By Jason Dorje Short <jdorje@users.sf.net>.
 *
 * Distributed under the GPL.  See http://gnu.org/.
 *
 * Compile as
 *   gcc -g -Wall -Werror `pkg-config --cflags --libs cairo` track.c hurdat.c md.c -o track
 */

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <cairo/cairo.h>

#include "hurdat.h"
#include "md.h"
#include "track.h"

#define MAX_STORMS 3

#define storms_iterate(storms, storm)					\
  {									\
    int _storm_index;							\
    for (_storm_index = 0; _storm_index < MAX_STORMS; _storm_index++) {	\
      struct storm *storm = storms[storm];				\
      if (storm) {
#define storms_iterate_end			\
      }						\
    }						\
  }						\

struct args {
  struct storm_arg storm[MAX_STORMS];
  int resolution;
  int xmin, xmax, ymin, ymax;
  double mindim;
  int fmt;
  double dots, lines;
  double alpha;
  const char *bg;
  const char *output;
};

#define NO_ARG -200

static struct args read_args(int argc, char **argv)
{
  int i = 1;
  struct args args = {
    .resolution = 1024,
    .xmin = NO_ARG,
    .xmax = NO_ARG,
    .ymin = NO_ARG,
    .ymax = NO_ARG,
    .mindim = NO_ARG,
    .dots = 0.3,
    .lines = 0.075,
    .alpha = 1.0,
    .bg = "bg.png",
    .output = "output.png",

    .storm[0] = {
      .year = 0,
      .id = 0,
      .name = NULL,
      .wind = 0,
      .extra = false, /* Hmm, what should be default? */

      .format = 0,
      .input = "natlantic.txt",
      .negx = true, /* longitude given in negatives */
      .negy = false
    },
    .storm[1] = {
      .year = 0,
      .id = 0,
      .name = NULL,
      .wind = 0,
      .extra = true, /* Hmm, what should be default? */

      .format = 0,
      .input = NULL,
      .negx = true, /* longitude given in negatives */
      .negy = false
     },
    .storm[2] = {
      .year = 0,
      .id = 0,
      .name = NULL,
      .wind = 0,
      .extra = true, /* Hmm, what should be default? */

      .format = 0,
      .input = NULL,
      .negx = true, /* longitude given in negatives */
      .negy = false
    }
  };

  while (i < argc) {
    float val;

    if (i < argc - 1) {
      if (strcasecmp(argv[i], "--input") == 0) {
	i++;
	args.storm[0].input = argv[i];
      } else if (strcasecmp(argv[i], "--input1") == 0) {
	i++;
	args.storm[1].input = argv[i];
      } else if (strcasecmp(argv[i], "--input2") == 0) {
	i++;
	args.storm[2].input = argv[i];

      } else if (strcasecmp(argv[i], "--format") == 0) {
	i++;
	args.storm[0].format = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--format1") == 0) {
	i++;
	args.storm[1].format = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--format2") == 0) {
	i++;
	args.storm[2].format = atoi(argv[i]);

      } else if (strcasecmp(argv[i], "--negy") == 0) {
	i++;
	args.storm[0].negy = (atoi(argv[i]) != 0);
      } else if (strcasecmp(argv[i], "--negy1") == 0) {
	i++;
	args.storm[1].negy = (atoi(argv[i]) != 0);
      } else if (strcasecmp(argv[i], "--negy2") == 0) {
	i++;
	args.storm[2].negy = (atoi(argv[i]) != 0);

      } else if (strcasecmp(argv[i], "--negx") == 0) {
	i++;
	args.storm[0].negx = (atoi(argv[i]) != 0);
      } else if (strcasecmp(argv[i], "--negx1") == 0) {
	i++;
	args.storm[1].negx = (atoi(argv[i]) != 0);
      } else if (strcasecmp(argv[i], "--negx2") == 0) {
	i++;
	args.storm[2].negx = (atoi(argv[i]) != 0);

      } else if (strcasecmp(argv[i], "--year") == 0) {
	i++;
	args.storm[0].year = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--year1") == 0) {
	i++;
	args.storm[1].year = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--year2") == 0) {
	i++;
	args.storm[2].year = atoi(argv[i]);

      } else if (strcasecmp(argv[i], "--id") == 0) {
	i++;
	args.storm[0].id = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--id1") == 0) {
	i++;
	args.storm[1].id = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--id2") == 0) {
	i++;
	args.storm[2].id = atoi(argv[i]);

      } else if (strcasecmp(argv[i], "--name") == 0) {
	i++;
	args.storm[0].name = argv[i];
      } else if (strcasecmp(argv[i], "--name1") == 0) {
	i++;
	args.storm[1].name = argv[i];
      } else if (strcasecmp(argv[i], "--name2") == 0) {
	i++;
	args.storm[2].name = argv[i];

      } else if (strcasecmp(argv[i], "--wind") == 0) {
	i++;
	args.storm[0].wind = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--wind1") == 0) {
	i++;
	args.storm[1].wind = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--wind2") == 0) {
	i++;
	args.storm[2].wind = atoi(argv[i]);

      } else if (strcasecmp(argv[i], "--res") == 0) {
	i++;
	args.resolution = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--xmin") == 0) {
	i++;
	args.xmin = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--xmax") == 0) {
	i++;
	args.xmax = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--ymin") == 0) {
	i++;
	args.ymin = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--ymax") == 0) {
	i++;
	args.ymax = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--mindim") == 0) {
	i++;
	sscanf(argv[i], "%f", &val);
	args.mindim = val;
      } else if (strcasecmp(argv[i], "--dots") == 0) {
	i++;
	sscanf(argv[i], "%f", &val);
	args.dots = val;
      } else if (strcasecmp(argv[i], "--lines") == 0) {
	i++;
	sscanf(argv[i], "%f", &val);
	args.lines = val;
      } else if (strcasecmp(argv[i], "--alpha") == 0) {
	i++;
	sscanf(argv[i], "%f", &val);
	args.alpha = val;
      } else if (strcasecmp(argv[i], "--extra") == 0) {
	i++;

	args.storm[0].extra
	  = args.storm[1].extra
	  = args.storm[2].extra
	  = (atoi(argv[i]) != 0);
      } else if (strcasecmp(argv[i], "--bg") == 0) {
	i++;
	args.bg = argv[i];
      } else if (strcasecmp(argv[i], "--output") == 0) {
	i++;
	args.output = argv[i];
      } else {
	fprintf(stderr, "Unknown argument '%s'.\n", argv[i]);
	exit(-1);
      }
    } else {
      fprintf(stderr, "Unmatched argument '%s'.\n", argv[i]);
      exit(-1);
    }
    i++;
  }

  return args;
}

static bool storm_matches(struct storm *storm, struct storm_arg *args)
{
  if (args->year != 0 && args->year != storm->header.year) {
    return false;
  }
  if (args->id != 0 && args->id != storm->header.id) {
    return false;
  }
  if (args->name && strcasecmp(args->name, storm->header.name) != 0) {
    return false;
  }
  if (args->wind > storm->maxwind) {
    return false;
  }
  return true;
}

static bool pos_matches(struct pos *pos, struct storm_arg *args)
{
  if (pos->type == EXTRATROPICAL || pos->type == LOW) {
    if (pos->wind < 65 && !args->extra) {
      return false;
    }
  }
  return true;
}

double wraplon(double lon)
{
  while (lon > 180.0) lon -= 360.0;
  while (lon < -180.0) lon += 360.0;

  return lon;
}

void init_storm(struct storm *storm)
{
  memset(storm, 0, sizeof(*storm));

  storm->npos = 0;
  storm->maxwind = 0;
  storm->maxlon = -180;
  storm->minlon = 180;
  storm->maxlat = -90;
  storm->minlat = 90;
}

void save_storm(struct storm_arg *args, struct stormdata *storms, struct storm *storm)
{
  if (storm_matches(storm, args)) {
#if 0
	printf("%d.%02d: '%s'\n", storm.header.year, storm.header.id,
	       storm.header.name);
#endif
    /* Save last storm. */
    storms->nstorms++;
    storms->storms = realloc(storms->storms,
			     storms->nstorms * sizeof(*storms->storms));
    storms->storms[storms->nstorms - 1] = *storm;

    storms->maxlon = MAX(storm->maxlon, storms->maxlon);
    storms->minlon = MIN(storm->minlon, storms->minlon);
    storms->maxlat = MAX(storm->maxlat, storms->maxlat);
    storms->minlat = MIN(storm->minlat, storms->minlat);
  }
}

void save_pos(struct storm_arg *args, struct stormdata *storms,
	      struct storm *storm, struct pos *pos)
{
  if (pos->wind > 0 || pos->lon != 0.0 || pos->lat != 0.0) {
    double oldlon = 0;

    if (args->negy) {
      pos->lat *= -1.0;
    }
    if (args->negx) {
      pos->lon *= -1.0;
    }

    /* Since the file doesn't use negatives, wrap-around is needed
     * (e.g., 350 instead of -10). */
    if (storm->npos > 0) {
      oldlon = storm->pos[storm->npos - 1].lon;
    } else {
      oldlon = (storms->minlon + storms->maxlon) / 2.0;
    }
    pos->lon = wraplon(pos->lon - oldlon) + oldlon;

    if (storm->npos >= MAX_POS) {
      fprintf(stderr, "Not enough positions.\n");
      exit(1);
    }

    storm->pos[storm->npos] = *pos;
    storm->npos++;

    storm->maxwind = MAX(storm->maxwind, pos->wind);

    if (pos_matches(pos, args)) {
      storm->maxlon = MAX(pos->lon, storm->maxlon);
      storm->minlon = MIN(pos->lon, storm->minlon);
      storm->maxlat = MAX(pos->lat, storm->maxlat);
      storm->minlat = MIN(pos->lat, storm->minlat);
    }

#if 0
    if (pos->lon < -300) {
      printf("%s %d %d\n", storm->header.name,
	     storm->header.year, storm->header.id);
    }
#endif
#if 0
    printf("  %02.1f,%02.1f %03d %04d\n",
	   pos->lat, pos->lon, pos->wind, pos->pres);
#endif
  }
}

static struct stormdata *new_stormdata(void)
{
  struct stormdata *storms = malloc(sizeof(*storms));

  storms->nstorms = 0;
  storms->storms = NULL;
  storms->maxlon = -180;
  storms->minlon = 180;
  storms->maxlat = -90;
  storms->minlat = 90;

  return storms;
}

static void free_stormdata(struct stormdata *storms)
{
  if (storms->storms) free(storms->storms);
  free(storms);
}

static cairo_status_t write_callback (void *closure, const unsigned char *data,
				      unsigned int length)
{
    size_t written;
    FILE *file = closure;

    written = fwrite (data, 1, length, file);

    if (written == length)
	return CAIRO_STATUS_SUCCESS;
    else
	return CAIRO_STATUS_WRITE_ERROR;
}

static double xmin = -180, xmax = 180, ymin = -90, ymax = 90;
static int xres, yres;

static void get_pos(double *x, double *y, struct pos *pos)
{
  /* We do this by hand because someday it may use a non-linear projection. */

  *x = (pos->lon - xmin) / (xmax - xmin) * xres;
  *y = (ymax - pos->lat) / (ymax - ymin) * yres;
}

static double get_dot_size(struct args *args)
{
  return args->dots / (xmax - xmin) * xres;
}

static double get_line_size(struct args *args)
{
  return args->lines / (xmax - xmin) * xres;
}

static void get_color(double *r, double *g, double *b, struct pos *pos)
{
  /* Purely by windspeed.  Note that the HURDAT data is not entirely
   * official. */
  int winds[] = {
    0,
    34,
    64,
    83,
    96,
    114,
    136
  };
#undef UNISYS_COLORS
#ifdef UNISYS_COLORS
  double colors[7][3] = {
    {0, 0.7, 0}, /* DEP */
    {1, 1, 0.3}, /* TS */
    {0.7, 0, 0}, /* 1 */
    {1, 0.3, 0.3}, /* 2 */
    {0.7, 0, 0.7}, /* 3 */
    {1, 0.3, 1}, /* 4 */
    {1, 1, 1} /* 5 */
  };
#else
#  define COLOR(r, g, b) {((double)(r) / (double)0xFF),	\
			  ((double)(g) / (double)0xFF),	\
			  ((double)(b) / (double)0xFF)}
    /* Wikipedia colors */
#if 1
  /* Old colors. */
  double colors[7][3] = {
    COLOR(0x00, 0xFF, 0xFF), /* DEP */
    COLOR(0x90, 0xEE, 0x90), /* TS */
    COLOR(0xFF, 0xFF, 0xFF), /* cat1 */
    COLOR(0xFF, 0xFF, 0xB0), /* cat2 */
    COLOR(0xFF, 0xFF, 0x00), /* cat3 */
    COLOR(0xFF, 0xA5, 0x00), /* cat4 */
    COLOR(0xFF, 0x20, 0x20) /* cat5 */
  };
#else
  /* New colors. */
  double colors[7][3] = {
    COLOR(0x5e, 0xba, 0xff), /* DEP */
    COLOR(0x00, 0xfa, 0xf4), /* TS */
    COLOR(0xff, 0xff, 0xcc), /* cat1 */
    COLOR(0xff, 0xe7, 0x75), /* cat2 */
    COLOR(0xff, 0xc1, 0x40), /* cat3 */
    COLOR(0xff, 0x8f, 0x20), /* cat4 */
    COLOR(0xff, 0x60, 0x60) /* cat5 */
  };
#endif
#endif
  int i;

#if 0 /* Extratropical/low is now handled by shape not color. */
  double extratropical[3] = COLOR(0xc0, 0xc0,0xc0);

  if (pos->type == EXTRATROPICAL || pos->type == LOW) {
    *r = extratropical[0];
    *g = extratropical[1];
    *b = extratropical[2];
    return;
  }
#endif

  for (i = 0; winds[i + 1] < pos->wind && i < 6; i++) {
    /* Skip down until we get to the right category. */
  }
  *r = colors[i][0];
  *g = colors[i][1];
  *b = colors[i][2];
}

static void write_background(cairo_t *cr, struct args *args)
{
  cairo_surface_t *bg;
  double w, h;
  double xscale, yscale;

  bg = cairo_image_surface_create_from_png(args->bg);
  if (cairo_surface_status(bg) != CAIRO_STATUS_SUCCESS) {
    printf("Couldn't load bg %d: %s\n",
	   cairo_surface_status(bg),
	   cairo_status_to_string(cairo_surface_status(bg)));
    cairo_surface_destroy(bg);
    cairo_save(cr);
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);
    cairo_restore(cr);
    return;
  }
  w = cairo_image_surface_get_width(bg);
  h = cairo_image_surface_get_height(bg);

  xscale = w / xres * (xmax - xmin) / 360.0;
  yscale = h / yres * (ymax - ymin) / 180.0;

#if 0
  printf("%2.2i,%2.2i %2.2f,%2.2f %2.2f,%2.2f %2.2f,%2.2f\n",
	 xres, yres, w, h,
	 xscale, yscale, xmin, ymax);
#endif

  cairo_save(cr);
  cairo_scale(cr, 1.0 / xscale, 1.0 / yscale);
  cairo_set_source_surface(cr, bg,
			   -(xmin + 180) / (xmax - xmin) * xres * xscale,
			   (ymax - 90) / (ymax - ymin) * yres * yscale);
  cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
  cairo_paint(cr);
  cairo_restore(cr);

  cairo_surface_destroy(bg);
}

static void calc_dimensions(struct stormdata *storms, struct args *args)
{
  const double extra_space = 5; /* 5 degrees extra on each side */
  const double xratio = 1.618033988749894; /* the golden ratio ;-) */
  const double yratio = 1.0;

  xmin = args->xmin;
  if (args->xmin == NO_ARG) {
    xmin = storms->minlon - extra_space;
  }

  xmax = args->xmax;
  if (args->xmax == NO_ARG) {
    xmax = storms->maxlon + extra_space;
  }

  ymin = args->ymin;
  if (args->ymin == NO_ARG) {
    ymin = storms->minlat - extra_space;
  }

  ymax = args->ymax;
  if (args->ymax == NO_ARG) {
    ymax = storms->maxlat + extra_space;
  }

  if (args->mindim == NO_ARG) {
    args->mindim = 45.0; /* 45 degree minimum coverage. */
  }
  if (xmax - xmin < args->mindim) {
    double diff = args->mindim - (xmax - xmin);

    xmax += diff / 2.0;
    xmin -= diff / 2.0;
  }

  /* Keep the dimensions within certain ratios. */
  if (xmax - xmin < (ymax - ymin) / yratio) {
    double diff = (ymax - ymin) / yratio - (xmax - xmin);

    xmax += diff / 2.0;
    xmin -= diff / 2.0;
  }
  if (ymax - ymin < (xmax - xmin) / xratio) {
    double diff = (xmax - xmin) / xratio - (ymax - ymin);

    ymax += diff / 2.0;
    ymin -= diff / 2.0;
  }

  if (ymax - ymin > xmax - xmin) {
    yres = args->resolution;
    xres = yres * (xmax - xmin) / (ymax - ymin) + 0.5;
  } else {
    xres = args->resolution;
    yres = xres * (ymax - ymin) / (xmax - xmin) + 0.5;
  }
}

static void write_stormdata(struct stormdata *storms, struct args *args)
{
  cairo_surface_t *surface;
  cairo_t *cr;
  int s, p;
  FILE *file;

  calc_dimensions(storms, args);

  surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, xres, yres);
  cr = cairo_create(surface);

  write_background(cr, args);

  cairo_set_operator(cr, CAIRO_OPERATOR_OVER);

  for (s = 0; s < storms->nstorms; s++) {
    struct storm *storm = storms->storms + s;
    double x, y;

    cairo_save(cr);
    if (storm->npos == 0) {
      continue;
    }
    get_pos(&x, &y, storm->pos);
    cairo_move_to(cr, x, y);
    cairo_set_source_rgba(cr, 1, 1, 1, args->alpha);
    cairo_set_line_width(cr, get_line_size(args));
    for (p = 1; p < storm->npos; p++) {
      struct pos *pos = storm->pos + p;

      get_pos(&x, &y, pos);

      cairo_line_to(cr, x, y);
    }
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
    cairo_stroke(cr);
    cairo_restore(cr);
  }

  for (s = 0; s < storms->nstorms; s++) {
    struct storm *storm = storms->storms + s;

    for (p = 0; p < storm->npos; p++) {
      struct pos *pos = storm->pos + p;
      double x, y, r, g, b;
      double sz = get_dot_size(args), side, bis;

      get_pos(&x, &y, pos);
      get_color(&r, &g, &b, pos);

      cairo_save(cr);
      cairo_set_source_rgba(cr, r, g, b, args->alpha);
      cairo_new_path(cr);
      switch (pos->type) {

      case TROPICAL:
	cairo_arc(cr, x, y, sz, 0, 2.0 * M_PI);
	break;

      case EXTRATROPICAL:
	/* We want a square with the same area as the circle.
	 *
	 *   circleArea = pi * rc ^ 2
	 *   squareArea = 4 * rs ^ 2
	 *
	 * Where rc is the circle radius and rs is the square radius (half
	 * the side). If they have the same area:
	 *
	 *   pi * rc ^ 2 = 4 * rs ^ 2
	 *   sqrt(pi) * rc = 2 * rs
	 *   rs = sqrt(pi) * rc / 2
	 */
	sz *= sqrt(M_PI) / 2.0; /* A square with same area as the circle. */
	cairo_rectangle(cr, x - sz, y - sz, sz * 2.0, sz * 2.0);
	break;

      case SUBTROPICAL:
      case LOW:
	/* We want an equilateral triangle with the same area as the circle.
	 *
	 * The triangle has side s and bisector k.  Now
	 *
	 *   (s / 2) ^ 2 + k ^ 2 = s ^ 2
	 *   (3/4) s^2 = k^2
	 *   k = sqrt(3)/2 * s
	 *
	 * The area of the triangle is
	 *
	 *   triangleArea = (s/2) * k
	 *                = (s/2) * sqrt(3)/2 * s
	 *                = s^2 * sqrt(3)/4
	 *
	 * If triangle and circle have equal areas then
	 *
	 *   s^2 * sqrt(3)/4 = pi * rs ^ 2
	 *   s = r * sqrt(pi * 4 / sqrt(3))
	 *
	 * where rs is the circle's radius.  The center of the triangle is
	 * at the intersection of the bisectors, which is 2/3 of the way down
	 * the bisector or k/3 of the distance from the base.
	 */
	side = sz * sqrt(M_PI * 4.0 / sqrt(3.0));
	bis = side * sqrt(3.0) / 2.0;
	cairo_move_to(cr, x, y - bis * 2.0 / 3.0);
	cairo_line_to(cr, x - side / 2.0, y + bis / 3.0);
	cairo_line_to(cr, x + side / 2.0, y + bis / 3.0);
	cairo_close_path(cr);
	break;
      }

      cairo_fill(cr);
      cairo_restore(cr);
    }
  }

  file = fopen(args->output, "w+");
  cairo_surface_write_to_png_stream(surface, write_callback, file);

  cairo_destroy(cr);
  cairo_surface_destroy(surface);  
}

static void print_earliest(struct stormdata *storms)
{
#if 0
#define MAX_STORMS 25
  int i, s;
  struct storm **early[MAX_STORMS];
  int nearly[MAX_STORMS];

  for (i = 0; i < MAX_STORMS; i++) {
    early[i] = NULL;
    nearly[i] = 0;
  }
  for (s = 0; s < storms->nstorms; s++) {
    struct storm *storm = storms->storms + s;
#define DATE(storm) (storm->header.month * 31 + storm->header.day)

    i = storm->header.id;
    if (i >= MAX_STORMS || i < 0) {
      printf("Error: storm %d found.\n", i);
    }
    if (nearly[i] == 0 || DATE(early[i][0]) > DATE(storm)) {
      nearly[i] = 1;
      early[i] = realloc(early[i], nearly[i] * sizeof(*early[i]));
      early[i][0] = storm;
    } else if (nearly[i] > 0 && DATE(early[i][0]) == DATE(storm)) {
      nearly[i]++;
      early[i] = realloc(early[i], nearly[i] * sizeof(*early[i]));
      early[i][nearly[i] - 1] = storm;
    }
  }

  for (i = 0; i < MAX_STORMS; i++) {
    int j;

    for (j = 0; j < nearly[i]; j++) {
      printf(" %02d: %02d/%02d/%4d %s\n", i,
	     early[i][j]->header.month,
	     early[i][j]->header.day,
	     early[i][j]->header.year,
	     early[i][j]->header.name);
    }
  }
#endif
}

int main(int argc, char **argv)
{
  struct args args = read_args(argc, argv);
  struct stormdata *storms = new_stormdata();
  int i;
  int count = 0;

  for (i = 0; i < MAX_STORMS; i++) {
    if (!args.storm[i].input) {
      continue;
    }
    switch (args.storm[i].format) {
    case 0:
      storms = read_stormdata_hurdat(storms, &args.storm[i]);
      break;
    default:
      storms = read_stormdata_md(storms, &args.storm[i]);
      break;
    }

    if (storms->nstorms == count) {
      fprintf(stderr, "No storms found.\n");
      return -1;
    }
    count = storms->nstorms;
  }

  print_earliest(storms);
  write_stormdata(storms, &args);

  free_stormdata(storms);

  return 0;
}
