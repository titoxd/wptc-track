/*
 *  atcf.c
 *  wptc-track
 *
 * WPTC-TRACKS reader for ATCF best-track files
 * File format documented at http://www.nrlmry.navy.mil/atcf_web/docs/database/new/abrdeck.html
 */

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stddef.h>

#include "atcf.h"
#include "track.h"

static char *stripspace(char *str)
{
	while (isspace(str[0])) {
		str++;
	}
	while (isspace(str[strlen(str) - 1])) {
		str[strlen(str) - 1] = '\0';
	}
	return str;
}

struct stormdata *read_stormdata_atcf(struct stormdata *storms,
									  struct storm_arg *args)
{
	FILE *file;
	int i;
	char *line, *linecopy, buf[10240];
	struct storm storm;
	char *token[35], *datestamp;
	char ds[5];
	char stormclass[3];
	int dateset = 0;
    int points = 0;
	int lasttype;
	int year; 
	struct pos pos;
	file = fopen(args->input, "r");
	
	if (!file) {
		fprintf(stderr, "Couldn't open file '%s': %s\n",
				args->input, strerror(errno));
		exit(-1);
	}
	
	init_storm(&storm);
	
	while ((line = fgets(buf, sizeof(buf), file))) {
		/* Clean up the line */
		line = stripspace(line);
		linecopy = strdup(line);
		
		/* Begin parsing the line */
		token[0] = strtok(linecopy, ",");
		i = 1;	
		while ((token[i-1] != NULL) && (i<35)) {
			token[i-1] = stripspace(token[i-1]);
			token[i] = strtok(NULL, ",");
			i++;
		}
        
        if (i < 12) {
            fprintf(stderr, "Parsing error in file '%s': Not enough data fields to parse data point properly\n",
                    args->input);
            exit(-1);
        }

		/* Begin storing data */
		/* Check the storm's characteristics for this time point */
		if ((strcasecmp(token[10], "TD") == 0) || (strcasecmp(token[10], "TS") == 0) || (strcasecmp(token[10], "TY") == 0) || 
			(strcasecmp(token[10], "ST") == 0) || (strcasecmp(token[10], "TC") == 0) || (strcasecmp(token[10], "HU") == 0)) {
			pos.type = TROPICAL;
			lasttype = TROPICAL;
		} else if ((strcasecmp(token[10], "SD") == 0) || (strcasecmp(token[10], "SS") == 0)) {
			pos.type = SUBTROPICAL;
			lasttype = SUBTROPICAL;
		} else if ((strcasecmp(token[10], "EX") == 0)) {
			pos.type = EXTRATROPICAL;
			lasttype = EXTRATROPICAL;
		} else if ((strcasecmp(token[10], "LO") == 0) || (strcasecmp(token[10], "WV") == 0) || (strcasecmp(token[10], "DB") == 0)) {
			pos.type = LOW;
			lasttype = LOW;
		} else {
			/* If we have a different condition (e.g. inland, dissipating), 
			 * assume that the last valid condition is still true */
			pos.type = lasttype;
		}
		
		/* Set the storm name and ID */
		if ((strcasecmp(token[10], "TS") == 0) || (strcasecmp(token[10], "TY") == 0) || (strcasecmp(token[10], "ST") == 0) || 
			(strcasecmp(token[10], "TC") == 0) || (strcasecmp(token[10], "HU") == 0) || (strcasecmp(token[10], "SS") == 0)) {
			if (strcasecmp(token[27], storm.header.name) != 0) {
				strncpy(storm.header.name, token[27], strlen(token[27]));
				storm.header.id = atoi(token[1]);
			}
		}
		
		if (!dateset) {
			datestamp = strdup(token[2]);
			strncpy(ds, datestamp+0,4); 
			ds[4] = '\0';
			storm.header.year = atoi(ds);
			
			datestamp = strdup(token[2]);
			strncpy(ds, datestamp+4,2);  
			ds[2] = '\0';
			storm.header.month = atoi(ds);
			
			datestamp = strdup(token[2]);
			strncpy(ds, datestamp+6,2);
			ds[2] = '\0';
			storm.header.day = atoi(ds);
			dateset = 1;
		}
		
		/* month, day, hour */
		datestamp = strdup(token[2]);
		strncpy(ds, datestamp+0,4);
		ds[4] = '\0';
		year = atoi(ds);
		
		datestamp = strdup(token[2]);
		strncpy(ds, datestamp+4,2);
		ds[2] = '\0';
		pos.month = atoi(ds);
		
		datestamp = strdup(token[2]);
		strncpy(ds, datestamp+6,2);
		ds[2] = '\0';
		pos.day = atoi(ds);
		
		datestamp = strdup(token[2]);
		strncpy(ds, datestamp+8,2);
		ds[2] = '\0';
		pos.hour = atoi(ds);
		
		/* latitude */
		if (token[6][strlen(token[6])-1] == 'N') {
			pos.lat = (double)atoi(token[6]) / 10.0;
		} else {
			/* TODO: check this actually works */
			pos.lat = -(double)atoi(token[6]) / 10.0;
		}
		
		if (token[7][strlen(token[7])-1] == 'W') {
			pos.lon = (double)atoi(token[7]) / 10.0;
		} else {
			/* TODO: check this actually works */
			pos.lon = -(double)atoi(token[7]) / 10.0;
		}
		
		/* wind */
		pos.wind = atoi(token[8]);
		/* if peak wind: store the current classification */
		if (pos.wind > storm.maxwind) {
			strncpy(stormclass, token[10],2);
			stormclass[2] = '\0';
		}
		
		/* pressure */ 
		pos.pres = atoi(token[9]);
		
		if (pos.wind == 0) {
			break;
		}
		
        points++;
        
		save_pos(args, storms, &storm, &pos);
		
	}
	fclose(file);
	
	/* Convert storm name to proper capitalization */
	storm.header.name[0] = toupper(storm.header.name[0]);
	i=1;
	while (storm.header.name[i])
	{
		storm.header.name[i] = tolower(storm.header.name[i]);
		i++;
	}
	
	/* Print out the information header */
    if (points > 0) {
        printf("{{WPTC track map\n");
        printf(" | author = {{subst:REVISIONUSER}}\n");
        
        if (strcasecmp(stormclass, "TD") == 0) {
            printf(" | name = %s %s\n", "Tropical Depression", storm.header.name);
            printf(" | article = %s %s (%d)\n", "Tropical Depression", storm.header.name, storm.header.year);
        } else if (strcasecmp(stormclass, "TS") == 0) {
            printf(" | name = %s %s\n", "Tropical Storm", storm.header.name);
            printf(" | article = %s %s (%d)\n", "Tropical Storm", storm.header.name, storm.header.year);
        } else if (strcasecmp(stormclass, "TY") == 0) {
            printf(" | name = %s %s\n", "Typhoon", storm.header.name);
            printf(" | article = %s %s (%d)\n", "Typhoon", storm.header.name, storm.header.year);
        } else if (strcasecmp(stormclass, "ST") == 0) {
            printf(" | name = %s %s\n", "Super Typhoon", storm.header.name);
            printf(" | article = %s %s (%d)\n", "Super Typhoon", storm.header.name, storm.header.year);
        } else if (strcasecmp(stormclass, "TC") == 0) {
            printf(" | name = %s %s\n", "Tropical Cyclone", storm.header.name);
            printf(" | article = %s %s (%d)\n", "Tropical Cyclone", storm.header.name, storm.header.year);
        } else if (strcasecmp(stormclass, "HU") == 0) {
            printf(" | name = %s %s\n", "Hurricane", storm.header.name);
            printf(" | article = %s %s (%d)\n", "Hurricane", storm.header.name, storm.header.year);
        } else if (strcasecmp(stormclass, "SD") == 0) {
            printf(" | name = %s %s\n", "Subtropical Depression", storm.header.name);
            printf(" | article = %s %s (%d)\n", "Subtropical Depression", storm.header.name, storm.header.year);
        } else if (strcasecmp(stormclass, "SS") == 0) {
            printf(" | name = %s %s\n", "Subtropical Storm", storm.header.name);
            printf(" | article = %s %s (%d)\n", "Subtropical Storm", storm.header.name, storm.header.year);
        } else {
            printf(" | name = %s %s\n", "Cyclone\n", storm.header.name);
            printf(" | article = %s %s (%d)\n", "Cyclone", storm.header.name, storm.header.year);
        }
        printf(" | season = %4.4d {{{season name}}}\n", storm.header.year);
        printf(" | start = %4.4d-%2.2d-%2.2d\n", storm.header.year, storm.header.month, storm.header.day);
        printf(" | end = %4.4d-%2.2d-%2.2d\n", year, pos.month, pos.day);
        printf(" | othersource={{{fill me}}}\n");
        printf(" | catname={{{fill me}}}\n");
        printf(" | code={{{fill me}}}\n");
        printf("}}\n");
        
        printf("Edit summary: Refreshing information for %s as of %4.4d-%2.2d-%2.2d, %2.2d00 UTC\n", 
               storm.header.name, year, pos.month, pos.day, pos.hour);
        
        
        save_storm(args, storms, &storm);
        
    } else {
        fprintf(stderr, "Parsing error in file '%s': No data points found\n", args->input);
    }
    
#if 0
	printf("Longitude: %d, %d\n", minlon, maxlon);
	printf("Latitude: %d, %d\n", minlat, maxlat);
	
	printf("%d %d %d %d\n", t, s, e, l);
#endif
	
	return storms;
}

