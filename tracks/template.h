/*
 *  template.h
 *  wptc-track
 *
 *
 */

#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__

#include "track.h"

void make_storm_template(const struct stormdata *storms,
                         const struct storm_arg *args,
                         const bool useoldcolorkey,
                         const int scalecode);

char* seasonname(struct storm_header header);

#endif
