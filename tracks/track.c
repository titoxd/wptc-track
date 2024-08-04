/* By Jason Dorje Short <jdorje@users.sf.net>.
 *
 * Distributed under the GPL.  See http://gnu.org/.
 *
 * Compile as
 *   gcc -g -Wall -Werror scales.c template.c tab.c track.c tcr.c atcf.c hurdat2.c hurdat.c md.c `pkg-config --cflags --libs cairo` -o track
 */

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <cairo.h>

#include "hurdat.h"
#include "hurdat2.h"
#include "atcf.h"
#include "jma.h"
#include "md.h"
#include "scales.h"
#include "tab.h"
#include "tcr.h"
#include "template.h"
#include "track.h"

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

#  define COLOR(r, g, b) {((double)(r) / (double)0xFF),	\
			  ((double)(g) / (double)0xFF),	\
			  ((double)(b) / (double)0xFF)}
# define IND_COLOR(c) (double)(c) / (double)0xFF
#define NUMCOLORS 7

#define NO_ARG -200

static void help(void)
{
  printf("Usage: track [--year] [--name] [--res]\n");
  printf("Create hurricane track maps\n\n");

  printf("Options:\n");
  printf("  --year			Select tropical cyclones from a specific year\n");
  printf("  --name 			Select tropical cyclones  with a specific name\n");
  printf("  --input 			Use a text file to create tracking map\n");
  printf("  --id				Storm ID number in its year\n");
  printf("  --format			Set format for input files (hurdat,tcr,atcf,md,tab,jma)\n");
  printf("  --negx   			Set to non-zero value for longitude west of the prime meridian\n");
  printf("  --negy   			Set to non-zero value for latitude south of the equator\n");
  printf("  --wind			Look for storms with at least this wind.\n");
  printf("  --next			Add on another storm\n");
  printf("  --res 			Set the horizontal resolution of output image\n");
  printf("  --bg Set 			map to use for background\n");
  printf("  --output 			Set the output file; is ignored when inferoutputlocation≠0\n");
  printf("  --template 			Set to non-zero to pre-fill {{WPTC track map}} (default: on)\n");
  printf("  --alpha  			Set transparency for storm tracks\n");
  printf("  --extra  			Do not cut off the extratropical portion of the tracks when extra≠0\n");
  printf("  --dots   			Set size of dots, in degrees\n");
  printf("  --lines  			Set size of lines, in degrees\n");
  printf("  --scale  			Set the TC classification scale to use for this map (default: SSHWS). Valid values are SSHWS, AUS, IMD, JMA, or MFR. The input file's winds are assumed to be over the correct averaging interval (e.g. 3-minute sustained winds for the IMD scale). If specified, this argument MUST be given before any color arguments.\n");
  printf("  --<category>color		Set the color of this category (default: classic SSHWS color), for example --c5color 000000. Must be a hexadecimal color code with or without the 0x prefix. Multiple arguments of this type may be specified. As valid category names depend on the scale used, these arguments MUST be specified after --scale if that is specified.\n");
  printf("More than one storm can be included on the map with the \n"
	 "use of the --next field.  The year, name, input, id, and\n"
	 "format fields apply to a storm.  Each time --next is given\n"
	 "in the argument list this halts the current storm spec and\n"
	 "instead adds another storm to the list.\n");
  printf("  --useoldcolorkey		Use the legacy color key when useoldcolorkey≠0\n");
  printf("  --skipasynoptic             Set to 0 to not have the maker skip asynoptic points, i.e. those whose hours are not a multiple of 6 hours (0z, 6z, 12z, 18z).");
  printf("  --inferoutputlocation       Automatically infer the file name when inferoutputlocation≠0. For individual storms, <storm name, or designation if no storm name found in file> <year> path.png, or when multiple storms are present, <year> <season type name, such as Atlantic hurricane season> summary.png, where the season type is inferred from the basin of the first storm given.\n");
}

__attribute__((nonnull)) static void init_storm_arg(struct storm_arg *stormp) 
{

  stormp->year = 0;
  stormp->id = 0;
  stormp->name = NULL;
  stormp->wind = 0;
  stormp->extra = false;  /* Hmm, what should be default? */
  stormp->format = 0;
  stormp->input = "../data/natlantic.txt\0";
  stormp->negx = true; /* longitude given in negatives */
  stormp->negy = false;
  stormp->wind_format = MPH;
}

static int get_scale_code(const char* scalename) {
	if (strcasecmp("AUS", scalename) == 0) {
		return AUS_CODE;
	} else if (strcasecmp("IMD", scalename) == 0) {
		return IMD_CODE;
	} else if (strcasecmp("JMA", scalename) == 0) {
		return JMA_CODE;
	} else if (strcasecmp("MFR", scalename) == 0) {
		return MFR_CODE;
	} else if (strcasecmp("JMADOM", scalename) == 0) {
		return JMADOM_CODE;
	}
	else {
		return SSHWS_CODE;
	}
}
__attribute__((nonnull)) static void init_color_arg(struct colormap *colorp, const int scale) {
	struct colormap colors;
   switch (scale) {
		case AUS_CODE:
			colors = AUS_COLORMAP;
		break;
		case IMD_CODE:
			colors = IMD_COLORMAP;
		break;
		case JMA_CODE:
			colors = JMA_COLORMAP;
		break;
		case MFR_CODE:
			colors = MFR_COLORMAP;
		break;
		case JMADOM_CODE:
			colors = JMADOM_COLORMAP;
		break;
		default:
			colors = SSHWS_COLORMAP;
   }
   *colorp = colors;
}

__attribute__((nonnull))  static bool is_valid_color_input(const char *argv_piece, struct colormap* colors, int *colorindex) {
	for (int i = 0; i < colors->numcolors; i++) {
                int colorname_size = 2 + strlen(colors->entries[i].name) + 5 + 1; //2 for --, strlen() doesn't count null terminator, 5 for "color", 1 for null terminator
                char* colorarg = (char*) calloc(colorname_size, sizeof(char)); // use calloc() here to guarantee string is null-terminated
                if (!colorarg) {
                        perror("Calloc failed");
                        return false;
                }
		sprintf(colorarg, "%s%s%s", "--", colors->entries[i].name, "color");
		if (strcasecmp(argv_piece, colorarg) == 0) {
			*colorindex = i;
			free(colorarg);
			return true;
		}
		free(colorarg);
	}
	return false;
}
static void parse_color(const char* color_code, int *r, int *g, int *b) {
	int i = 0;
	if (color_code[1] == 'x') {
		i = 2; // Skip possible "0x" prefix
	}
	char r_string[3];
	char g_string[3];
	char b_string[3];
	r_string[0] = color_code[i];
	r_string[1] = color_code[i + 1];
	g_string[0] = color_code[i + 2];
	g_string[1] = color_code[i + 3];
	b_string[0] = color_code[i + 4];
	b_string[1] = color_code[i + 5];
	r_string[2] = '\0'; // Guard against buffer overflow
	g_string[2] = '\0';
	b_string[2] = '\0';
	sscanf(r_string, "%x", r);
	sscanf(g_string, "%x", g);
	sscanf(b_string, "%x", b);
}

static struct args read_args(const int argc, char **argv)
{
  int i = 1;
  int colorindex = 0;
  bool colorspecified = false; // To implement restriction against specifying color before scale.
  struct args args = {
    /* Set Default Options */
    .nstorms = 1,
    .resolution = 1024,
    .xmin = NO_ARG,
    .xmax = NO_ARG,
    .ymin = NO_ARG,
    .ymax = NO_ARG,
    .mindim = NO_ARG,
    .dots = 0.3,
    .lines = 0.075,
    .alpha = 1.0,
    .template = true,
    .bg = "../data/bg8192.png",
    .output = "../png/output.png",
    .scale = SSHWS_CODE,
    .useoldcolorkey = 0,
    .skipasynoptic = 1,
    .inferoutputlocation = 0
  };

  args.storm = malloc(sizeof(*args.storm));
  if (!args.storm) {
        perror("Error when allocating memory for storm");
        return args;
  }
  args.colors = malloc(sizeof(*args.colors));
  if (!args.colors) {
        perror("Error when allocating memory for colormap");
        free(args.storm);
        args.storm = NULL;
        return args;
  }
  init_storm_arg(args.storm);
  init_color_arg(args.colors, SSHWS_CODE);
  while (i < argc) {
    float val;
    int colorval_r;
    int colorval_g;
    int colorval_b;
    const int s = args.nstorms - 1;

    if (strcasecmp(argv[i], "--help") == 0) {
      help();
      exit(0);
    } else if (i < argc - 1) {
      if (strcasecmp(argv[i], "--input") == 0) {
	i++;
	args.storm[s].input = argv[i];
	  } else if (strcasecmp(argv[i], "--scale") == 0) {
	i++;
		  if (colorspecified) {
			  	fprintf(stderr, "You appear to have tried to specify --scale with value '%s' after one or more color arguments were already specified. --scale MUST be specified before any color arguments.\n", argv[i]);
				exit(-1);
		  }
	int scale_code = get_scale_code(argv[i]);
	args.scale = scale_code;
	init_color_arg(args.colors, scale_code);
      } else if (strcasecmp(argv[i], "--format") == 0) {
	i++;
	args.storm[s].format = argv[i];
      } else if (strcasecmp(argv[i], "--negy") == 0) {
	i++;
	args.storm[s].negy = (atoi(argv[i]) != 0);
      } else if (strcasecmp(argv[i], "--negx") == 0) {
	i++;
	args.storm[s].negx = (atoi(argv[i]) != 0);
      } else if (strcasecmp(argv[i], "--year") == 0) {
	i++;
	args.storm[s].year = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--id") == 0) {
	i++;
	args.storm[s].id = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--name") == 0) {
	i++;
	args.storm[s].name = argv[i];
      } else if (strcasecmp(argv[i], "--wind") == 0) {
	i++;
	args.storm[s].wind = atoi(argv[i]);

      } else if (strcasecmp(argv[i], "--next") == 0) {
	args.nstorms++;
	args.storm = realloc(args.storm,
			     args.nstorms * sizeof(*args.storm));
	args.storm[s + 1] = args.storm[s];
      } else if (strcasecmp(argv[i], "--res") == 0) {
	i++;
	args.resolution = atoi(argv[i]);
      } else if (strcasecmp(argv[i], "--template") == 0) {
    i++;
    args.template = atoi(argv[i]);
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
      } else if ( is_valid_color_input(argv[i], args.colors, &colorindex) ) {
	i++;
	parse_color(argv[i], &colorval_r, &colorval_g, &colorval_b);
	args.colors->entries[colorindex].value[0] = IND_COLOR(colorval_r);
	args.colors->entries[colorindex].value[1] = IND_COLOR(colorval_g);
	args.colors->entries[colorindex].value[2] = IND_COLOR(colorval_b);
	colorspecified = true;
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
      } else if (strcasecmp(argv[i], "--useoldcolorkey") == 0) {
	i++;
	args.useoldcolorkey = (atoi(argv[i]) != 0);
      } else if (strcasecmp(argv[i], "--skipasynoptic") == 0) {
	i++;
	args.skipasynoptic = (atoi(argv[i]) != 0);
      } else if (strcasecmp(argv[i], "--inferoutputlocation") == 0) {
	i++;
	args.inferoutputlocation = (atoi(argv[i]) != 0);
      } else if (strcasecmp(argv[i], "--bg") == 0) {
	i++;
	args.bg = argv[i];
      } else if (strcasecmp(argv[i], "--output") == 0) {
	i++;
	args.output = argv[i];
	  } else if ( strcasecmp(argv[i], "--windformat") == 0) {
			i++;
			if ( strcasecmp(argv[i],"kt") == 0 || strcasecmp(argv[i],"knots") == 0) {
				args.storm[0].wind_format = KT;
			}
	  } else if ( strcasecmp(argv[i], "--windformat1") == 0) {
			i++;
			if ( strcasecmp(argv[i],"kt") == 0 || strcasecmp(argv[i],"knots") == 0) {
				args.storm[1].wind_format = KT;
			}
      }	else if ( strcasecmp(argv[i], "--windformat2") == 0) {
			i++;
			if ( strcasecmp(argv[i],"kt") == 0 || strcasecmp(argv[i],"knots") == 0) {
				args.storm[2].wind_format = KT;
			}
	  }
	  else {
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
static bool storm_matches(const struct storm *storm, const struct storm_arg *args)
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

static bool pos_matches(const struct pos *pos, const struct storm_arg *args)
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
  storm->minpres = 9999; /* mbar */
  storm->maxtype = 0;
  storm->ace = 0;

  storm->maxlon = -180;
  storm->minlon = 180;
  storm->maxlat = -90;
  storm->minlat = 90;
  storm->formlon = 0;
  storm->formlat = 0;
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
    for (int i = 1; storm->header.name[i]; i++) {
        storm->header.name[i] = tolower(storm->header.name[i]);
    }
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
  if (pos->wind > 0 || ABS(pos->lon) > 0.0001 || ABS(pos->lat) > 0.0001) {
    double oldlon = 0;

    if (args->negy) {
      pos->lat *= -1.0;
    }
    if (args->negx) {
      pos->lon *= -1.0;
    }

    if (pos->month < 1 || pos->month > 12) {
      fprintf(stderr, "Bad month %d.\n", pos->month);
    }
    if (pos->day < 1 || pos->day > 31) {
      fprintf(stderr, "Bad day %d.\n", pos->day);
    }
    if (pos->hour < 0 || pos->hour >= 24) {
      fprintf(stderr, "Bad hour %d.\n", pos->hour);
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
    if (pos->pres > 0) {
      storm->minpres = MIN(storm->minpres, pos->pres);
    }

    if (pos->wind >= 35) {
      int type = pos->type;        // cast from an anonymous enum to suppress a warning in GCC when passing it to the MAX() macro
      storm->maxtype = MAX(storm->maxtype, type);

      if (type == TROPICAL) {
	if (ABS(storm->formlon) < 0.0001 && ABS(storm->formlat) < 0.0001) {
	  storm->formlon = pos->lon;
	  storm->formlat = pos->lat;
	}
	/* ACE is the accumulation of the squares of the wind speed, in knots,
	 * of a tropical system with at least 35-knot winds. */
	storm->ace += pos->wind * pos->wind;
      }
    }

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

__attribute__ ((malloc)) static struct stormdata *new_stormdata(void)
{
  struct stormdata *storms = malloc(sizeof(*storms));
  if (!storms) {
        return NULL;
  }
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
  storms = NULL;
  return;
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

static void get_color(double *r, double *g, double *b, struct pos *pos, struct colormap *colors)
{
   int i;
   double unknown[3] = COLOR(0xc0, 0xc0,0xc0);

  if (pos->wind == 0) {
    *r = unknown[0];
    *g = unknown[1];
    *b = unknown[2];
    return;
  }

  for (i = 0; i < 6 && colors->entries[i + 1].wind < pos->wind; i++) {
    /* Skip down until we get to the right category. */
  }
  if (i >= 7) {
	  printf("Attempting to access illegal color\n");
   }
  *r = colors->entries[i].value[0];
  *g = colors->entries[i].value[1];
  *b = colors->entries[i].value[2];
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
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
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

  if ((int)args->mindim == NO_ARG) {
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

#ifdef ACE
static int ace_compare(const void *a, const void *b)
{
  const struct storm *storma = a, *stormb = b;

  return stormb->ace - storma->ace;
}
#endif

#ifdef NAMING
static const char *get_storm_description(struct storm *storm)
{
  /* Atlantic only (for now) */
  if (storm->maxtype == SUBTROPICAL) {
    return "subtropical storm";
  } else if (storm->maxtype == TROPICAL && storm->maxwind >= 65) {
    return "hurricane";
  } else if (storm->maxtype == TROPICAL && storm->maxwind >= 35) {
    return "tropical storm";
  } else {
    return "storm";
  }
}
#endif

#define WIKI
/*#define EXTREMES */

#ifdef EXTREMES
static int long_fact, lat_fact;

static int extremes_compare(const void *a, const void *b)
{
  const struct storm *storma = a, *stormb = b;
  double diff = ((long_fact * stormb->formlon + lat_fact * stormb->formlat)
		 - (long_fact * storma->formlon + lat_fact * storma->formlat));

  /* Exclude storms that never achieved "formation" */
  if (stormb->formlon == 0.0 && stormb->formlat == 0.0) {
    return -1;
  } else if (storma->formlon == 0.0 && storma->formlat == 0.0) {
    return 1;
  }

  if (diff > 0) {
    return 1;
  } else if (diff < 0) {
    return -1;
  } else {
    return 0;
  }
}
#endif

static void print_extreme_locations(struct stormdata *storms)
{
#ifdef EXTREMES
  struct {
    int long_fact, lat_fact;
    char *desc;
  } factors[] = {
    {1, 0, "east"},
    {0, 1, "north"},
    {-1, 0, "west"},
    {0, -1, "south"},

    {1, 1, "northeast"},
    {-1, 1, "northwest"},
    {1, -1, "southeast"},
    {-1, -1, "southwest"},
  };
  int i, j;

  for (i = 0; i < ARRAY_SIZE(factors); i++) {
    long_fact = factors[i].long_fact;
    lat_fact = factors[i].lat_fact;
    qsort(storms->storms, storms->nstorms, sizeof(*storms->storms),
	  extremes_compare);

#ifdef WIKI
    printf("{| class=wikitable\n");
    printf("|+Most %s formations of Atlantic storms\n", factors[i].desc);
    printf("|-\n");
    printf("! Name !! Year !! ID !! Location\n");
#else
    printf("%s\n", factors[i].desc);
#endif
    for (j = 0; j < MIN(10, storms->nstorms); j++ ) {
      struct storm *storm = storms->storms + j;

#ifdef WIKI
      printf("|-\n");
      printf("| %12s || %4d || %2d || %4.1f&deg;E, %2.1f&deg;N\n",
	     storm->header.name, storm->header.year, storm->header.id,
	     storm->formlon, storm->formlat);
#else
      printf("%12s | %d | %2d | %4.1f,%2.1f\n",
	     storm->header.name, storm->header.year, storm->header.id,
	     storm->formlon, storm->formlat);
#endif
    }
#ifdef WIKI
    printf("|}\n\n");
#endif
  }
#endif
}

/*#define STRONGEST */

#ifdef STRONGEST
static int strongest_compare(const void *a, const void *b)
{
  const struct storm *storma = a, *stormb = b;

  if (storma->minpres == stormb->minpres) {
    return stormb->maxwind - storma->maxwind;
  }
  return storma->minpres - stormb->minpres;
}
#endif

static void print_strongest_storms(struct stormdata *storms)
{
#ifdef STRONGEST
  int s;

  qsort(storms->storms, storms->nstorms, sizeof(*storms->storms),
	strongest_compare);

#ifdef WIKI
  printf("{|class=\"wikitable\"\n");
  printf("|+Tropical cyclones by minimum pressure\n");
  printf("|-\n");
  printf("!Year || ID || Name || Min. Pressure || Max. Winds (kt)\n");
#endif
  for (s = 0; s < storms->nstorms; s++) {
    struct storm *storm = storms->storms + s;
#ifdef WIKI
    printf("|-\n");
    printf("| %d || %d || %s || %d || %d\n",
	   storm->header.year, storm->header.id, storm->header.name,
	   storm->minpres, storm->maxwind);
#else
    printf("%4d %2d %10s %4d (%3d)\n",
	   storm->header.year, storm->header.id, storm->header.name,
	   storm->minpres, storm->maxwind);
#endif
  }
#ifdef WIKI
  printf("|}\n");
#endif
#endif
}

static void print_extra_data(struct stormdata *storms)
{
#if 0 /* Earliest storm in each season */
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

#ifdef NAMING
  /* List of storms */
  int year = -1, s, linelen = 0;

  for (s = 0; s < storms->nstorms; s++) {
    struct storm *storm = storms->storms + s;
    int i;
    char text[128];
    char *lead = "       ";

    for (i = 1; i < strlen(storm->header.name); i++) {
      storm->header.name[i] = tolower(storm->header.name[i]);
    }

    if (strcasecmp(storm->header.name, "not named") == 0
	|| strncasecmp(storm->header.name, "subtrop", strlen("subtrop")) == 0) {
      continue;
    }

    if (storm->header.year != year) {
      if (year != -1) {
	printf("\n      )],\n");
      }
      printf("     \"%d\" =>\n     [(\n%s", storm->header.year, lead);
      year = storm->header.year;
      linelen = strlen(lead);
    }
    sprintf(text, "'%s', ", storm->header.name);
    printf("%s", text);
    linelen += strlen(text);
    if (linelen > 65) {
      printf("\n%s", lead);
      linelen = strlen(lead);
    }
  }
  if (year != -1) {
    printf("\n      )],\n");
  }

  for (s = 0; s < storms->nstorms; s++) {
    struct storm *storm = storms->storms + s;
    int number = storm->header.id;

    if (strcasecmp(storm->header.name, "not named") == 0
	|| strncasecmp(storm->header.name, "subtrop", strlen("subtrop")) == 0) {
      if (strncasecmp(storm->header.name, "subtrop", strlen("subtrop")) == 0) {
	char *name = storm->header.name + strlen("subtrop");

	if (atoi(name) != 0) {
	  number = atoi(name);
	}
      }

      printf("      [ (\"--year %d --id %d --name \\\"%s\\\"\", "
	     "\"%d Atlantic %s %d\") ],\n",
	     storm->header.year, storm->header.id,
	     storm->header.name,
	     storm->header.year,
	     get_storm_description(storm),
	     number);
    }
  }
#endif

#ifdef ACE /* ACE data */
  int s;

  qsort(storms->storms, storms->nstorms, sizeof(*storms->storms), ace_compare);
  for (s = 0; s < storms->nstorms; s++) {
#if 0
    /* Text format */
    printf("%4d %2d %10s %f\n",
	   storms->storms[s].header.year,
	   storms->storms[s].header.id,
	   storms->storms[s].header.name,
	   (double)storms->storms[s].ace / 10000.0);
#else
    /* Wiki format */
    printf("|-\n|%4d || %2d || %10s || %2.5f\n",
	   storms->storms[s].header.year,
	   storms->storms[s].header.id,
	   storms->storms[s].header.name,
	   (double)storms->storms[s].ace / 10000.0);
#endif
  }
#endif

#ifdef ACTIVITY
  int max = 0;
  int s;

  for (s = 0; s < storms->nstorms; s++) {
    struct storm *storm = storms->storms + s;

    if (storm->header.id < 50) {
      /* Numbers above 50 are seemingly used for crossover storms that
       * aren't part of the basin. */
      max = MAX(storm->header.id, max);
    }
  }

  for (s = 0; s < storms->nstorms; s++) {
    struct storm *storm = storms->storms + s;

    if (storm->header.id == max) {
      printf("%d : %d\n", max, storm->header.year);
    }
  }
#endif

#ifdef BYMONTH
  int pressure[12], wind[12];
  int i, s, p;

  for (i = 0; i < 12; i++) {
    pressure[i] = 9999;
    wind[i] = 0;
  }
  for (s = 0; s < storms->nstorms; s++) {
    struct storm *storm = storms->storms + s;

    for (p = 0; p < storm->npos; p++) {
      struct pos *pos = storm->pos + p;

      assert(pos->month >= 1 && pos->month <= 12);
      if (pos->pres != 0) {
	pressure[pos->month - 1] = MIN(pos->pres, pressure[pos->month - 1]);
      }
      if (pos->wind != 0) {
	wind[pos->month - 1] = MAX(pos->wind, wind[pos->month - 1]);
      }
    }
  }
  for (i = 0; i < 12; i++) {
    for (s = 0; s < storms->nstorms; s++) {
      struct storm *storm = storms->storms + s;
      bool is_pressure = false, is_wind = false;

      for (p = 0; p < storm->npos; p++) {
	struct pos *pos = storm->pos + p;

	if (pos->month - 1 == i) {
	  if (!is_pressure && pos->pres == pressure[i]) {
	    printf("%2d : %d/%2d '%s' : %d mbar\n",
		   i + 1, storm->header.year, storm->header.id,
		   storm->header.name,
		   pos->pres);
	    is_pressure = true;
	  }
	  if (!is_wind && pos->wind == wind[i]) {
	    printf("%2d : %d/%2d '%s' : %d knots\n",
		   i + 1, storm->header.year, storm->header.id,
		   storm->header.name,
		   pos->wind);
	    is_wind = true;
	  }
	}
      }
    }
  }
#endif

  print_extreme_locations(storms);
  print_strongest_storms(storms);
}

static void infer_output_location(char* output_location, struct stormdata *storms) {
        int storm_year = storms->storms[0].header.year;
	if (storms->nstorms == 1) { // Single storm track
                if (strlen(storms->storms[0].header.name) > 0 && strcmp(storms->storms[0].header.name, "Unnamed") != 0) {
			char* storm_name = storms->storms[0].header.name;
			snprintf(output_location, strlen(storm_name) + 16, "%s %d path.png", storm_name, storm_year);
                } else {
                        if (strlen(storms->storms[0].header.basin) == 0) {
				fprintf(stderr, "--inferoutputlocation was enabled but no name was found for this storm, and the basin also cannot be inferred.\n");
				exit(-1);
			}
			char storm_name[4];
			if (strcmp(storms->storms[0].header.basin, "SH") == 0) {
				if (storms->storms[0].npos == 0) {
					fprintf(stderr, "--inferoutputlocation was enabled but no name was found for this storm, and because it has no positions and is in the southern hempisphere, it is not possible to infer its basin letter.\n");
					exit(-1);
				}
				if (storms->storms[0].pos[0].lon >= 160.0) {
					snprintf(storm_name, 3, "%d%c", storms->storms[0].header.id, 'P');
                                } else {
					snprintf(storm_name, 3, "%d%c", storms->storms[0].header.id, 'S');
				}
			} else if (strcmp(storms->storms[0].header.basin, "AL") == 0) {
				snprintf(storm_name, 4, "%d%c", storms->storms[0].header.id, 'L');
			} else if (strcmp(storms->storms[0].header.basin, "EP") == 0) {
				snprintf(storm_name, 4, "%d%c", storms->storms[0].header.id, 'E');
			} else if (strcmp(storms->storms[0].header.basin, "CP") == 0) {
				snprintf(storm_name, 4, "%d%c", storms->storms[0].header.id, 'C');
			} else if (strcmp(storms->storms[0].header.basin, "IO") == 0) {
				if (storms->storms[0].npos == 0) {
					fprintf(stderr, "--inferoutputlocation was enabled but no name was found for this storm, and because there were no positions and the basin is the North Indian Ocean, it cannot be inferred whether A or B should be the basin letter.\n");
					exit(-1);
				}
				if (storms->storms[0].pos[0].lon >= 77.55) {
					snprintf(storm_name, 4, "%d%c", storms->storms[0].header.id, 'B');
				} else {
					snprintf(storm_name, 4, "%d%c", storms->storms[0].header.id, 'A');
				}
			} else if (strcmp(storms->storms[0].header.basin, "WP") == 0) {
				snprintf(storm_name, 4, "%d%c", storms->storms[0].header.id, 'W');
			} else {
				fprintf(stderr, "Basin %s is not recognized.\n", storms->storms[0].header.basin);
				exit(-1);
			}
                        snprintf(output_location, strlen(storm_name) + 16, "%s %d path.png", storm_name, storm_year);
		}
	} else if (storms->nstorms > 1) { //Avoid == 0
		char season_name[40];
		memset(season_name, 0, 40);
		int basin_name_length = 0;
		bool is_shem = 0;
		struct storm storm = storms->storms[0];
		if (strlen(storm.header.basin) == 0) {
			fprintf(stderr, "--inferoutputlocation was enabled and there are multiple storms, but the basin cannot be inferred. Please instead pass the output location manually.\n");
			exit(-1);
		}
		if (strcmp(storm.header.basin, "WP") == 0) {
			strncpy(season_name, "Pacific typhoon season", 23);
		} else if (strcmp(storm.header.basin, "EP") == 0 || strcmp(storm.header.name, "CP") == 0) {
			strncpy(season_name, "Pacific hurricane season", 25);
		} else if (strcmp(storm.header.basin, "AL") == 0) {
			strncpy(season_name, "Atlantic hurricane season", 26);
		} else if (strcmp(storm.header.basin, "IO") == 0) {
			strncpy(season_name, "North Indian Ocean cyclone season", 34);
		} else if (strcmp(storm.header.basin, "SH") == 0) {
			if (storm.npos == 0) {
				fprintf(stderr, "--inferoutputlocation was enabled and there are multiple storms, but the basin is a southern hemisphere one and the first storm has no positions to infer which southern hemisphere basin.\n");
				exit(-1);
			}
			double startinglon = storm.pos[0].lon;
			is_shem = 1;
			if (startinglon <= -70.0) {
				strncpy(season_name, "South-East Pacific cyclone season", 34);
			} else if (startinglon <= 25.0) {
			        strncpy(season_name, "South Atlantic hurricane season", 31);
			} else if (startinglon <= 90.0) {
				strncpy(season_name, "South-West Indian Ocean cyclone season", 39);
			} else if (startinglon <= 160.0) {
				strncpy(season_name, "Australian region cyclone season", 33);
			} else {
				strncpy(season_name, "South Pacific cyclone season", 29);
			}
		} else {
			fprintf(stderr, "--inferoutputlocation was enabled and there are multiple storms, but the basin designation %s cannot be recognized.\n", storm.header.basin);
		}
		if (is_shem) {
			int previous_year = storm.header.year - 1;
			snprintf(output_location, 24 + strlen(season_name), "%d-%d %s summary.png", storm.header.year, previous_year, season_name);
		} else {
			snprintf(output_location, 19 + strlen(season_name), "%d %s summary.png", storm.header.year, season_name);		}
	}
}

static void write_stormdata(struct stormdata *storms, struct args *args)
{
  cairo_surface_t *surface;
  cairo_t *cr;
  int s, p;
  FILE *file;

#if 0
  return;
#endif

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
    cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, args->alpha);
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
      get_color(&r, &g, &b, pos, args->colors);

      cairo_save(cr);
      cairo_set_source_rgba(cr, r, g, b, args->alpha);
      cairo_new_path(cr);
      switch (pos->type) {

      case TROPICAL:
	cairo_arc(cr, x, y, sz, 0.0, 2.0 * M_PI);
	break;

      case SUBTROPICAL:
	/* 
	 * Draws an inscribed square of the same size as the circle from above.
	 */
	sz /= sqrt(2.0);
	cairo_rectangle(cr, x - sz, y - sz, sz * 2.0, sz * 2.0);
	break;

      case EXTRATROPICAL:
      case LOW:
	/*
	 * We want the inscribed triangle of the circle this time. This
	 * has side sqrt(3) and bisector 3/2.
	 */
	side = sz * sqrt(3.0);
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

  file = fopen(args->output, "wb+");
  cairo_surface_write_to_png_stream(surface, write_callback, file);

  cairo_destroy(cr);
  cairo_surface_destroy(surface);
}

int substr_to_int(char *token, int start, int len) {
    int res = 0;
    char substr[100] = "\0";
    strncpy(substr, token+start,len);
    substr[len] = '\0';
    res = atoi(substr);
    return res;
}

double substr_to_double(char *token, int start, int len) {
    double res = 0.0;
    char substr[100] = "\0";
    strncpy(substr, token+start,len);
    substr[len] = '\0';
    res = atof(substr);
    return res;
}

int main(int argc, char **argv)
{
  struct args args = read_args(argc, argv);
  struct stormdata *storms = new_stormdata();
  if (!storms) {
        perror("Error while allocating storage for storm data");
        return -1;
  }
  int i;
  int count = 0;

  for (i = 0; i < args.nstorms; i++) {
    const char *format = args.storm[i].format;

    if (!args.storm[i].input) {
      continue;
    }
    if (!format || strcasecmp(format, "hurdat") == 0) {
      storms = read_stormdata_hurdat(storms, &args.storm[i]);
    } else if (strcasecmp(format, "atcf") == 0) {
		storms = read_stormdata_atcf(storms, &args.storm[i], args.skipasynoptic);
    } else if (strcasecmp(format, "jma") == 0) {
		storms = read_stormdata_jma(storms, &args.storm[i], args.skipasynoptic);
    } else if (strcasecmp(format, "hurdat2") == 0) {
		storms = read_stormdata_hurdat2(storms, &args.storm[i], args.skipasynoptic);
    } else if (strcasecmp(format, "md") == 0) {
      storms = read_stormdata_md(storms, &args.storm[i]);
    } else if (strcasecmp(format, "tcr") == 0) {
      storms = read_stormdata_tcr(storms, &args.storm[i]);
    } else if (strcasecmp(format, "tab") == 0) {
      storms = read_stormdata_tab(storms, &args.storm[i]);
    } else {
      fprintf(stderr, "Invalid format.\n");
      free_stormdata(storms);
      return -1;
    }

    if (args.template && storms) {
      make_storm_template(storms, &args.storm[i], args.useoldcolorkey, args.scale);
    }

    if (!storms) {
      fprintf(stderr, "Storm reader returned an error.\n");
      return -1;
    }
    if (storms->nstorms == count) {
      fprintf(stderr, "No storms found.\n");
      return -1;
    }
    count = storms->nstorms;
  }
  if (args.inferoutputlocation) {
	args.output = malloc(128);
	infer_output_location(args.output, storms);
  }
  write_stormdata(storms, &args);
  print_extra_data(storms);
  if (args.inferoutputlocation) {
	free(args.output);
  }
  free_stormdata(storms);

  return 0;
}
