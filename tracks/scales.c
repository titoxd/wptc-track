# include "scales.h"
#  define COLOR(r, g, b) {((double)(r) / (double)0xFF),	\
			  ((double)(g) / (double)0xFF),	\
			  ((double)(b) / (double)0xFF)}
# define IND_COLOR(c) (double)(c) / (double)0xFF
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
	.entries = SSHWS_ENTRIES
};
