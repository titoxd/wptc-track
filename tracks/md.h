#ifndef __MD_H__
#define __MD_H__

#include "track.h"

struct stormdata *read_stormdata_md(struct stormdata *storms,
				    struct storm_arg *args);

#endif
