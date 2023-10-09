/*
 * jma.h
 * wptc-track
 */
#ifndef __JMA_H__
#define __JMA_H__

#include "track.h"

struct stormdata *read_stormdata_jma(struct stormdata *storms,
                                                                         struct storm_arg *args, bool skipasynoptic);

#endif
