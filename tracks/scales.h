#ifndef __SCALE_H__
#define __SCALE_H__
#endif

#define SSHWS_CODE 0
#define AUS_CODE 1
#define IMD_CODE 2
#define JMA_CODE 3
#define MFR_CODE 4
struct colormapentry {
	double value[3];
	int wind;
	char* name;
};
struct colormap {
	int numcolors;
	struct colormapentry *entries;
};
struct colormap SSHWS_COLORMAP;