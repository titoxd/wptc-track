/*
 *  atcf.h
 *  wptc-track
 *
 *
 */

#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__

#include "track.h"

void make_storm_template(struct stormdata *storms,
                         struct storm_arg *args,
                         bool useoldcolorkey);

char* seasonname(struct storm_header header);

#endif
