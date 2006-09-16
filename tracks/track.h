#ifndef __TRACK_H__
#define __TRACK_H__

#include <stdbool.h>
enum wind_format {
	MPH, KPH, KT
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
  char name[36];
  int id;
  int year, month, day; /* # of days since start of year */
};

struct pos {
  /* Ignores time. */
  enum { /* Increasing order. */
    LOW,
    EXTRATROPICAL,
    SUBTROPICAL,
    TROPICAL,
  } type;
  int month, day, hour;
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
#define MAX_POS 1024
  struct pos pos[MAX_POS];
};

struct stormdata {
  int nstorms;
  struct storm *storms;

  double minlon, maxlon;
  double minlat, maxlat;
};

/* Storm helper functions (move to storm.h) */
void init_storm(struct storm *storm);
void save_storm(struct storm_arg *args, struct stormdata *storms, struct storm *storm);
void save_pos(struct storm_arg *args, struct stormdata *storms,
	      struct storm *storm, struct pos *pos);
double wraplon(double lon);

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#endif
