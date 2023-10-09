#ifndef __TRACK_H__
#define __TRACK_H__

#include <stdbool.h>

/* Static storage limits */
#define STORM_NAME_LENGTH 36
#define MAX_POS 1024

/* Convenience macros */
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define ABS(x) ((x) >= 0 ? (x) : -(x))

enum wind_format {
	MPH, KPH, KT
};

struct args {
  struct storm_arg *storm;
  int nstorms;
  int resolution;
  int xmin, xmax, ymin, ymax;
  double mindim;
  int fmt;
  int template;
  double dots, lines;
  double alpha;
  const char *bg;
  char *output;
  int scale;
  struct colormap *colors;
  bool useoldcolorkey;
  bool skipasynoptic;
  bool inferoutputlocation;
};

struct storm_arg {
  int year;
  int id;
  char *name;
  int wind;

  bool extra;

  char *format;
  const char *input;
  bool negx, negy;
  enum wind_format wind_format;
};

struct storm_header {
  char name[STORM_NAME_LENGTH];
  int id;
  int year, month, day; /* # of days since start of year */
  char basin[3];
  char stormclass[3];
};

struct pos {
  /* Ignores time. */
  enum { /* Increasing order. */
    LOW,
    EXTRATROPICAL,
    SUBTROPICAL,
    TROPICAL
  } type;
  int year, month, day, hour;
  double lat, lon;
  int pres;
  int wind;
};

struct storm {
  struct storm_header header;

  int maxwind;
  int minpres;
  int maxtype;
  int ace;

  double minlon, maxlon;
  double minlat, maxlat;
  double formlon, formlat;

  int npos;
  struct pos pos[MAX_POS];
};

struct stormdata {
  int nstorms;
  struct storm *storms;

  double minlon, maxlon;
  double minlat, maxlat;
};

int substr_to_int(char *token, int start, int len);
double substr_to_double(char *token, int start, int len);

/* Storm helper functions (move to storm.h) */
void init_storm(struct storm *storm);
void save_storm(struct storm_arg *args, struct stormdata *storms, struct storm *storm);
void save_pos(struct storm_arg *args, struct stormdata *storms,
	      struct storm *storm, struct pos *pos);
double wraplon(double lon);

#endif
