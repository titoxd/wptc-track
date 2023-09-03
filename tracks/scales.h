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
extern struct colormapentry SSHWS_ENTRIES[8];
extern struct colormap SSHWS_COLORMAP;
extern struct colormapentry AUS_ENTRIES[7];
extern struct colormap AUS_COLORMAP;
extern struct colormapentry IMD_ENTRIES[8];
extern struct colormap IMD_COLORMAP;
extern struct colormapentry JMA_ENTRIES[7];
extern struct colormap JMA_COLORMAP;
extern struct colormapentry MFR_ENTRIES[8];
extern struct colormap MFR_COLORMAP;
extern struct colormapentry JMADOM_ENTRIES[7];
extern struct colormap JMADOM_COLORMAP;
