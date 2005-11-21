#ifndef __HURDAT_H__
#define __HURDAT_H__

#include "track.h"

struct stormdata *read_stormdata_hurdat(struct stormdata *storms,
					struct storm_arg *args);

#endif
