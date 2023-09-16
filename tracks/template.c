/*
*  template.c
*  wptc-track
*
* Automatically fills out upload templates for {{WPTC track map}}
* 
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stddef.h>

#include "template.h"
#include "track.h"
#include "scales.h"

void make_storm_template(const struct stormdata *storms,
                         const struct storm_arg *args,
			 const bool useoldcolorkey,
                         const int scalecode)
{
	char* stormname;
	char* season;
    struct storm storm;
    struct pos pos;
    int i;

    /* To make the template sensible, only print things when we have exactly one storm; */
    if (storms->nstorms != 1) {
        return;
    }

    /* Copy the storm structure locally */
    storm = *storms->storms;


    /* Convert storm name to proper capitalization */
    stormname = strdup(storm.header.name);
    if (!stormname) {
        perror("Malloc failed");
        return;
    }
    stormname[0] = toupper(stormname[0]);
    i=1;
    while (stormname[i])
    {
        stormname[i] = tolower(stormname[i]);
        i++;
    }

    /* Figure out what we call this season */
    season = seasonname(storm.header);

    /* Print out the information header */
    if (storm.npos > 0) {
        pos = storm.pos[storm.npos-1];
        printf("{{WPTC track map\n");
        printf(" | author = {{subst:REVISIONUSER}}\n");

        if (strcasecmp(storm.header.stormclass, "TD") == 0) {
            printf(" | name = %s %s\n", "Tropical Depression", stormname);
            printf(" | article = %s %s (%d)\n", "Tropical Depression", stormname, storm.header.year);
        } else if (strcasecmp(storm.header.stormclass, "TS") == 0) {
            printf(" | name = %s %s\n", "Tropical Storm", stormname);
            printf(" | article = %s %s (%d)\n", "Tropical Storm", stormname, storm.header.year);
        } else if (strcasecmp(storm.header.stormclass, "TY") == 0) {
            printf(" | name = %s %s\n", "Typhoon", stormname);
            printf(" | article = %s %s (%d)\n", "Typhoon", stormname, storm.header.year);
        } else if (strcasecmp(storm.header.stormclass, "ST") == 0) {
            printf(" | name = %s %s\n", "Super Typhoon", stormname);
            printf(" | article = %s %s (%d)\n", "Super Typhoon", stormname, storm.header.year);
        } else if (strcasecmp(storm.header.stormclass, "TC") == 0) {
            printf(" | name = %s %s\n", "Tropical Cyclone", stormname);
            printf(" | article = %s %s (%d)\n", "Tropical Cyclone", stormname, storm.header.year);
        } else if (strcasecmp(storm.header.stormclass, "HU") == 0) {
            printf(" | name = %s %s\n", "Hurricane", stormname);
            printf(" | article = %s %s (%d)\n", "Hurricane", stormname, storm.header.year);
        } else if (strcasecmp(storm.header.stormclass, "SD") == 0) {
            printf(" | name = %s %s\n", "Subtropical Depression", stormname);
            printf(" | article = %s %s (%d)\n", "Subtropical Depression", stormname, storm.header.year);
        } else if (strcasecmp(storm.header.stormclass, "SS") == 0) {
            printf(" | name = %s %s\n", "Subtropical Storm", stormname);
            printf(" | article = %s %s (%d)\n", "Subtropical Storm", stormname, storm.header.year);
        } else {
            printf(" | name = %s %s\n", "Cyclone\n", stormname);
            printf(" | article = %s %s (%d)\n", "Cyclone", stormname, storm.header.year);
        }
        printf(" | season = %s\n", season);
        printf(" | start = %4.4d-%2.2d-%2.2d\n", storm.header.year, storm.header.month, storm.header.day);
        printf(" | end = %4.4d-%2.2d-%2.2d\n", pos.year, pos.month, pos.day);
        printf(" | othersource={{{fill me}}}\n");
        printf(" | catname={{{fill me}}}\n");
        printf(" | code={{{fill me}}}\n");
	if (!useoldcolorkey) {
		printf(" | colors=new\n");
	}
	if (scalecode == JMA_CODE) { // Replace with a switch statement as template support for other scales is added.
		printf(" | scale=JMA\n");
	}
        printf("}}\n");

        printf("Edit summary: Refreshing information for %s as of %4.4d-%2.2d-%2.2d, %2.2d00 UTC\n",
               stormname, pos.year, pos.month, pos.day, pos.hour);

    } else {
        fprintf(stderr, "Parsing error in file '%s': No data points found\n", args->input);
    }

    free(season);
    free(stormname);
}


char* seasonname(struct storm_header header) {
    char season[100];
    char *res;
    
    if (strcasecmp(header.basin, "AL") == 0) {
        snprintf(season, 100, "%4.4d %s", header.year, "Atlantic hurricane season");
    } else if (strcasecmp(header.basin, "EP") == 0) {
        snprintf(season, 100, "%4.4d %s", header.year, "Pacific hurricane season");
    } else if (strcasecmp(header.basin, "WP") == 0) {
        snprintf(season, 100, "%4.4d %s", header.year, "Pacific typhoon season");
    } else if (strcasecmp(header.basin, "SL") == 0) {
        snprintf(season, 100, "%s", "List of South Atlantic tropical cyclones");
    } else {
        snprintf(season, 100, "%s", "{{{fill me}}}");
    }

    res = strdup(season);
    return res;
}
