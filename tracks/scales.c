# include "scales.h"
#  define COLOR(r, g, b) {((double)(r) / (double)0xFF),	\
			  ((double)(g) / (double)0xFF),	\
			  ((double)(b) / (double)0xFF)}
# define IND_COLOR(c) (double)(c) / (double)0xFF

/* SSHWS (1-minute winds). Default option. */
struct colormapentry SSHWS_ENTRIES[8] = {
	{.name = "TD", .value = COLOR(0x5e, 0xba, 0xff), .wind = 0},
	{.name = "TS", .value = COLOR(0x00, 0xfa, 0xf4), .wind = 34},
	{.name = "C1", .value = COLOR(0xff, 0xff, 0xcc), .wind = 64},
	{.name = "C2", .value = COLOR(0xff, 0xe7, 0x75), .wind = 83},
	{.name = "C3", .value = COLOR(0xff, 0xc1, 0x40), .wind = 96},
	{.name = "C4", .value = COLOR(0xff, 0x8f, 0x20), .wind = 114},
	{.name = "C5", .value = COLOR(0xff, 0x60, 0x60), .wind = 136},
	{.name = "SENTINEL", .value = COLOR(0xff, 0xff, 0xff), .wind = 0x7fffffff}
};
struct colormap SSHWS_COLORMAP = {
	.numcolors = 7,
	.entries = SSHWS_ENTRIES,
	.disturbancecolor = COLOR(0x80, 0xcc, 0xff)
};

/* AUS scale (10-minute winds). */
struct colormapentry AUS_ENTRIES[7] = {
	{.name = "TL", .value = COLOR(0x53, 0xba, 0xff), .wind = 0},
	{.name = "C1", .value = COLOR(0x00, 0xfa, 0xf4), .wind = 34},
	{.name = "C2", .value = COLOR(0xcc, 0xff, 0xff), .wind = 48},
	{.name = "C3", .value = COLOR(0xff, 0xcc, 0xcc), .wind = 64},
	{.name = "C4", .value = COLOR(0xff, 0xc1, 0x40), .wind = 86},
	{.name = "C5", .value = COLOR(0xff, 0x60, 0x60), .wind = 107},
	{.name = "SENTINEL", .value = COLOR(0xff, 0xff, 0xff), .wind = 0x7fffffff}
};
struct colormap AUS_COLORMAP = {
	.numcolors = 6,
	.entries = AUS_ENTRIES,
	.disturbancecolor = COLOR(0x80, 0xcc, 0xff)
};

/* IMD scale (3-minute winds). */
struct colormapentry IMD_ENTRIES[8] = {
	{.name = "D", .value = COLOR(0x80, 0xcc, 0xff), .wind = 0},
	{.name = "DD", .value = COLOR(0x5e, 0xba, 0xff), .wind = 28},
	{.name = "CS", .value = COLOR(0x00, 0xfa, 0xf4), .wind = 34},
	{.name = "SCS", .value = COLOR(0xcc, 0xff, 0xff), .wind = 48}, 
	{.name = "VSCS", .value = COLOR(0xff, 0xcc, 0xcc), .wind = 65},
	{.name = "ESCS", .value = COLOR(0xff, 0xc1, 0x40), .wind = 90},
	{.name = "SUCS", .value = COLOR(0xff, 0x60, 0x60), .wind = 120},
	{.name = "SENTINEL", .value = COLOR(0xff, 0xff, 0xff), .wind = 0x7fffffff}
};
struct colormap IMD_COLORMAP = {
	.numcolors = 7,
	.entries = IMD_ENTRIES,
	.disturbancecolor = COLOR(0x80, 0xcc, 0xff) // disturbancecolor here must be understood as "well-marked low pressure area"; this is not a permanent color choice.
};

/* JMA scale (10-minute winds). */
struct colormapentry JMA_ENTRIES[5] = {
	{.name = "TD", .value = COLOR(0x5e, 0xba, 0xff), .wind = 0},
	{.name = "TS", .value = COLOR(0x00, 0xfa, 0xf4), .wind = 34},
	{.name = "STS", .value = COLOR(0xcc, 0xff, 0xff), .wind = 48}, 
	{.name = "TY", .value = COLOR(0xfd, 0xaf, 0x9a), .wind = 64},
	{.name = "SENTINEL", .value = COLOR(0xff, 0xff, 0xff), .wind = 0x7fffffff}	
};
struct colormap JMA_COLORMAP = {
	.numcolors = 4,
	.entries = JMA_ENTRIES,
	.disturbancecolor = COLOR(0x80, 0xcc, 0xff) // NOT USED in this basin.
};

/* MFR scale (10-minute winds). */
struct colormapentry MFR_ENTRIES[7] = {
	{.name = "TD", .value = COLOR(0x53, 0xba, 0xff), .wind = 0},
	{.name = "MTS", .value = COLOR(0x00, 0xfa, 0xf4), .wind = 34},
	{.name = "STS", .value = COLOR(0xcc, 0xff, 0xff), .wind = 48},
	{.name = "TC", .value = COLOR(0xff, 0xcc, 0xcc), .wind = 64},
	{.name = "ITC", .value = COLOR(0xff, 0xc1, 0x40), .wind = 86},
	{.name = "VITC", .value = COLOR(0xff, 0x60, 0x60), .wind = 116},
	{.name = "SENTINEL", .value = COLOR(0xff, 0xff, 0xff), .wind = 0x7fffffff}
};
struct colormap MFR_COLORMAP = {
	.numcolors = 6,
	.entries = MFR_ENTRIES,
	.disturbancecolor = COLOR(0x80, 0xcc, 0xff)
};