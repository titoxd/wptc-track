#ifndef __SCALE_H__
#define __SCALE_H__
#endif

#define SSHWS_CODE 0
#define AUS_CODE 1
#define IMD_CODE 2
#define JMA_CODE 3
#define MFR_CODE 4
#define JMADOM_CODE 5
struct colormapentry {
	double value[3];
	int wind;
	char* name;
};
struct colormap {
	int numcolors;
	struct colormapentry *entries;
	double disturbancecolor[3]; // For PTC/DI/TDI. Can be overridden using the distcolor argument.
	// The disturbance color is considered separately from the other entries since unlike the others, it is not uniquely determined by storm intensity, overlapping with depressions.
};
struct colormapentry SSHWS_ENTRIES[8];
struct colormap SSHWS_COLORMAP;
struct colormapentry AUS_ENTRIES[7];
struct colormap AUS_COLORMAP;
struct colormapentry IMD_ENTRIES[8];
struct colormap IMD_COLORMAP;
struct colormapentry JMA_ENTRIES[5];
struct colormap JMA_COLORMAP;
struct colormapentry MFR_ENTRIES[8];
struct colormap MFR_COLORMAP;
struct colormapentry JMADOM_ENTRIES[7];
struct colormap JMADOM_COLORMAP;
