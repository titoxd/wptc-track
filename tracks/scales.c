# include "scales.h"
#  define COLOR(r, g, b) {((double)(r) / (double)0xFF),	\
			  ((double)(g) / (double)0xFF),	\
			  ((double)(b) / (double)0xFF)}
# define IND_COLOR(c) (double)(c) / (double)0xFF

/* SSHWS (1-minute winds). Default option. */
struct colormapentry SSHWS_ENTRIES[8] = {
	{.name = "TD", .value = COLOR(0x6e, 0xc1, 0xea), .wind = 0},
	{.name = "TS", .value = COLOR(0x4d, 0xff, 0xff), .wind = 34},
	{.name = "C1", .value = COLOR(0xff, 0xff, 0xd9), .wind = 64},
	{.name = "C2", .value = COLOR(0xff, 0xd9, 0x8c), .wind = 83},
	{.name = "C3", .value = COLOR(0xff, 0x9e, 0x59), .wind = 96},
	{.name = "C4", .value = COLOR(0xff, 0x73, 0x8a), .wind = 114},
	{.name = "C5", .value = COLOR(0xa1, 0x88, 0xfc), .wind = 136},
	{.name = "SENTINEL", .value = COLOR(0xff, 0xff, 0xff), .wind = 0x7fffffff}
};
struct colormap SSHWS_COLORMAP = {
	.numcolors = 7,
	.entries = SSHWS_ENTRIES,
	.disturbancecolor = COLOR(0x15, 0x91, 0xde)
};

/* AUS scale (10-minute winds). */
struct colormapentry AUS_ENTRIES[7] = {
	{.name = "TL", .value = COLOR(0x61, 0xc1, 0xea), .wind = 0},
	{.name = "C1", .value = COLOR(0x4d, 0xff, 0xff), .wind = 34},
	{.name = "C2", .value = COLOR(0xc0, 0xff, 0xc0), .wind = 48},
	{.name = "C3", .value = COLOR(0xff, 0xd9, 0x8c), .wind = 64},
	{.name = "C4", .value = COLOR(0xff, 0x73, 0x8a), .wind = 86},
	{.name = "C5", .value = COLOR(0xa1, 0x88, 0xfc), .wind = 107},
	{.name = "SENTINEL", .value = COLOR(0xff, 0xff, 0xff), .wind = 0x7fffffff}
};
struct colormap AUS_COLORMAP = {
	.numcolors = 6,
	.entries = AUS_ENTRIES,
	.disturbancecolor = COLOR(0x15, 0x91, 0xde)
};

/* IMD scale (3-minute winds). */
struct colormapentry IMD_ENTRIES[8] = {
	{.name = "D", .value = COLOR(0x15, 0x91, 0xde), .wind = 0},
	{.name = "DD", .value = COLOR(0x6e, 0xc1, 0xea), .wind = 28},
	{.name = "CS", .value = COLOR(0x4d, 0xff, 0xff), .wind = 34},
	{.name = "SCS", .value = COLOR(0xc0, 0xff, 0xc0), .wind = 48},
	{.name = "VSCS", .value = COLOR(0xff, 0xd9, 0x8c), .wind = 65},
	{.name = "ESCS", .value = COLOR(0xff, 0x73, 0x8a), .wind = 90},
	{.name = "SUCS", .value = COLOR(0xa1, 0x88, 0xfc), .wind = 120},
	{.name = "SENTINEL", .value = COLOR(0xff, 0xff, 0xff), .wind = 0x7fffffff}
};
struct colormap IMD_COLORMAP = {
	.numcolors = 7,
	.entries = IMD_ENTRIES,
	.disturbancecolor = COLOR(0x15, 0x91, 0xde) // disturbancecolor here must be understood as "well-marked low pressure area"; this is not a permanent color choice.
};

/* JMA scale (10-minute winds). */
struct colormapentry JMA_ENTRIES[7] = {
	{.name = "TD", .value = COLOR(0x6e, 0xc1, 0xea), .wind = 0},
	{.name = "TS", .value = COLOR(0x4d, 0xff, 0xff), .wind = 34},
	{.name = "STS", .value = COLOR(0xc0, 0xff, 0xc0), .wind = 48},
	{.name = "TY", .value = COLOR(0xff, 0xd9, 0x8c), .wind = 64},
	{.name = "VSTY", .value = COLOR(0xff, 0x73, 0x8a), .wind = 84},
        {.name = "VITY", .value = COLOR(0xa1, 0x88, 0xfc), .wind = 104},
	{.name = "SENTINEL", .value = COLOR(0xff, 0xff, 0xff), .wind = 0x7fffffff}
};
struct colormap JMA_COLORMAP = {
	.numcolors = 6,
	.entries = JMA_ENTRIES,
	.disturbancecolor = COLOR(0x15, 0x91, 0xde) // NOT USED in this basin.
};

/* MFR scale (10-minute winds). */
struct colormapentry MFR_ENTRIES[8] = {
	{.name = "TDi", .value = COLOR(0x15, 0x91, 0xde), .wind = 0},
	{.name = "TD", .value = COLOR(0x6e, 0xc1, 0xea), .wind = 28},
	{.name = "MTS", .value = COLOR(0x4d, 0xff, 0xff), .wind = 34},
	{.name = "STS", .value = COLOR(0xc0, 0xff, 0xc0), .wind = 48},
	{.name = "TC", .value = COLOR(0xff, 0xd9, 0x8c), .wind = 64},
	{.name = "ITC", .value = COLOR(0xff, 0x73, 0x8a), .wind = 86},
	{.name = "VITC", .value = COLOR(0xa1, 0x88, 0xfc), .wind = 116},
	{.name = "SENTINEL", .value = COLOR(0xff, 0xff, 0xff), .wind = 0x7fffffff}
};
struct colormap MFR_COLORMAP = {
	.numcolors = 7,
	.entries = MFR_ENTRIES,
	.disturbancecolor = COLOR(0x15, 0x91, 0xde) // Must be understood to mean ZODW not TDi
};

/* JMA domestic scale (10-minute winds). */
struct colormapentry JMADOM_ENTRIES[7] = {
        {.name = "TD", .value = COLOR(0x6e, 0xc1, 0xea), .wind = 0},
        {.name = "TS", .value = COLOR(0x4d, 0xff, 0xff), .wind = 34},
        {.name = "STS", .value = COLOR(0xc0, 0xff, 0xc0), .wind = 48},
        {.name = "TY", .value = COLOR(0xff, 0xd9, 0x8c), .wind = 64},
        {.name = "VSTY", .value = COLOR(0xff, 0x73, 0x8a), .wind = 84},
        {.name = "VITY", .value = COLOR(0xa1, 0x88, 0xfc), .wind = 104},
        {.name = "SENTINEL", .value = COLOR(0xff, 0xff, 0xff), .wind = 0x7fffffff}
};
struct colormap JMADOM_COLORMAP = {
	.numcolors = 6,
	.entries = JMADOM_ENTRIES,
	.disturbancecolor = COLOR(0x15, 0x91, 0xde) // NOT USED in this basin
};
