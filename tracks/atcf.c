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
									  struct storm_arg *args, bool skipasynoptic)
{
	FILE *file;
	int i;
	char *line, *linecopy, buf[10240];
	struct storm storm;
	char *token[35];
	int dateset = 0;
    int points = 0;
	int lasttype = 0;
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
        
        if (i < 9) {
            fprintf(stderr, "Parsing error in file '%s': Not enough data fields to parse data point properly\n",
                    args->input);
            exit(-1);
        }
		if (i >= 11) {
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
			} else if ((strcasecmp(token[10], "LO") == 0) || (strcasecmp(token[10], "WV") == 0) || (strcasecmp(token[10], "MD") == 0) || (strcasecmp(token[10], "DB") == 0)) {
				pos.type = LOW;
				lasttype = LOW;
			} else {
				/* If we have a different condition (e.g. inland, dissipating), 
			 	* assume that the last valid condition is still true */
				pos.type = lasttype;
			}
		} else {
			fprintf(stdout, "Not enough fields to infer storm type; falling back to tropical.\n");
			pos.type = TROPICAL; //Fallback in case of shortened ATCF
		}
		/* Set the storm name and ID */
		if (i >= 11) {
			if ((strcasecmp(token[10], "TS") == 0) || (strcasecmp(token[10], "TY") == 0) || (strcasecmp(token[10], "ST") == 0) || 
				(strcasecmp(token[10], "TC") == 0) || (strcasecmp(token[10], "HU") == 0) || (strcasecmp(token[10], "SS") == 0)) {
				if (strcasecmp(token[27], storm.header.name) != 0) {
					strncpy(storm.header.name, token[27], strlen(token[27]));
					if (strlen(token[27]) < STORM_NAME_LENGTH) {
						storm.header.name[strlen(token[27])] = '\0';
					}
				}
			}
			storm.header.id = atoi(token[1]);
		} else {
			strncpy(storm.header.name, "UNNAMED", 8);
			storm.header.id = atoi(token[1]);
		}
		if (!dateset) {
            strncpy(storm.header.basin, token[0], 2);
            storm.header.basin[2] = '\0';

            storm.header.year = substr_to_int(token[2], 0, 4);
            storm.header.month = substr_to_int(token[2], 4, 2);
            storm.header.day = substr_to_int(token[2], 6, 2);
			dateset = 1;
		}
		
		/* month, day, hour */
        pos.year = substr_to_int(token[2], 0, 4);
        pos.month = substr_to_int(token[2], 4, 2);
        pos.day = substr_to_int(token[2], 6, 2);
        pos.hour = substr_to_int(token[2], 8, 2);
	if (skipasynoptic && (pos.hour % 6 != 0)) {
		continue;
	}
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
		if (i >= 11) { // Can only do for full ATCF, not abbreviated.
			if (pos.wind > storm.maxwind) {
				strncpy(storm.header.stormclass, token[10],2);
				storm.header.stormclass[2] = '\0';
				storm.maxwind = pos.wind;
			}
		} else if (pos.wind > storm.maxwind) { // Fall back to inferring directly from winds
			storm.maxwind = pos.wind;
			if (strcmp(storm.header.basin, "WP") == 0) {
				if (storm.maxwind >= 64) {
					strncpy(storm.header.stormclass, "TY", 3);
				} else if (storm.maxwind >= 34) {
					strncpy(storm.header.stormclass, "TS", 3);
                                } else {
					strncpy(storm.header.stormclass, "TD", 3);
				}
			} else if (strcmp(storm.header.basin, "EP") == 0 || strcmp(storm.header.basin, "AL") == 0 || strcmp(storm.header.basin, "CP") == 0) {
				if (storm.maxwind >= 64) {
                                        strncpy(storm.header.stormclass, "HU", 3);
                                } else if (storm.maxwind >= 34) {
                                        strncpy(storm.header.stormclass, "TS", 3);
                                } else {
                                        strncpy(storm.header.stormclass, "TD", 3);
                                }
			}
		}
		/* pressure */
		if (i >= 11) { // Full ATCF only
			pos.pres = atoi(token[9]);
		}
		if (pos.wind == 0) {
			break;
		}
		
        points++;        
		save_pos(args, storms, &storm, &pos);

        /* Preventing memory leaks */
        free(linecopy);

	}
	fclose(file);
	
    /* Save the parsed result */
    if (points > 0) {
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

