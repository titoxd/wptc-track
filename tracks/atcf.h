/*
 *  atcf.h
 *  wptc-track
 *
 *
 */

#ifndef __ATCF_H__
#define __ATCF_H__

#include "track.h"

struct stormdata *read_stormdata_atcf(struct stormdata *storms,
									 struct storm_arg *args, bool skipasynoptic);

#endif
