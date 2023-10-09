/*
 *  atcf.h
 *  wptc-track
 *
 *
 */

#ifndef __HURDAT2_H__
#define __HURDAT2_H__

#include "track.h"

struct stormdata *read_stormdata_hurdat2(struct stormdata *storms,
									 struct storm_arg *args, bool skipasynoptic);

#endif
