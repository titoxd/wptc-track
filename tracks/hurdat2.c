/*
 *  hurdat2.c
 *  wptc-track
 *
 * WPTC-TRACKS reader for HURDAT2 best-track files
 * File format documented at http://www.aoml.noaa.gov/hrd/hurdat/newhurdat-format.pdf
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

struct stormdata *read_stormdata_hurdat2(struct stormdata *storms,
                                         struct storm_arg *args,
				         bool skipasynoptic)
{
	FILE *file;
	int i;
	char *line, *linecopy, buf[10240];
	struct storm storm;
	char *token[35];
	char recID[4];
    int points = 0;
    int minute = 0;
	int lasttype;
	bool dateset = false;
    bool syn_time = false;
	struct pos pos;
	file = fopen(args->input, "r");
	
	if (!file) {
		fprintf(stderr, "Couldn't open file '%s': %s\n",
				args->input, strerror(errno));
		exit(-1);
	}
	
	while ((line = fgets(buf, sizeof(buf), file))) {
		/* Clean up the line */
		line = stripspace(line);
		linecopy = strdup(line);      // Need to make a copy here, as strtok() is a destructive operation
		
		/* Begin parsing the line */
		token[0] = strtok(linecopy, ",");
		i = 1;
		while ((token[i-1] != NULL) && (i<35)) {
			token[i-1] = stripspace(token[i-1]);
			token[i] = strtok(NULL, ",");
			i++;
		}
        
        /* Preventing horrible explosions in case we can't read anything */
        if (i == 1) {
            fprintf(stderr, "Parsing error in file '%s': Could not parse the following input line:\n%s\n",
                    args->input, line);
            exit(-1);
        }
        
        /* Check if this is a header line; if it is, the first character of the line should be non-numeric */
        if (isalpha(token[0][0]) && i==4) {
            /***** Parse the header row *****/
            
            
            /* Before we do anything, check whether we had already processed points
             * for a storm; if we have, we should probably try to save it before we
             * start processing the new storm
             */
            if (points > 0) {
                save_storm(args, storms, &storm);
            }
            init_storm(&storm);
            
            /* Copy the cyclone identifier */
            /* Split it into multiple parts */
            strncpy(storm.header.basin, token[0], 2);
            storm.header.basin[2] = '\0';
            storm.header.id = substr_to_int(token[0], 2, 2);
            storm.header.year = substr_to_int(token[0], 4, 4);
            
            /* Figure out the name */
            strncpy(storm.header.name, token[1], strlen(token[1]));
            
            /* Mark that the initial date for the storm has not been set */
            dateset = false;
            
            /* Reset row counter */
            points = 0;
            
        } else if (isdigit(token[0][0]) && i>8) {
            /***** Parse the data row *****/

            /* For the first time stamp: Set initial map date
             * NOTE: THIS IS NOT NECESSARILY THE DATE OF CYCLOGENESIS
             */
            if (!dateset) {
                storm.header.year = substr_to_int(token[0], 0, 4);
                storm.header.month = substr_to_int(token[0], 4, 2);
                storm.header.day = substr_to_int(token[0], 6, 2);
                dateset = true;
            }
            
            /* Parse this date for our position point data */
            /* year, month, day */
            pos.year = substr_to_int(token[0], 0, 4);
            pos.month = substr_to_int(token[0], 4, 2);
            pos.day = substr_to_int(token[0], 6, 2);
            
            /* hour */
            pos.hour = substr_to_int(token[1], 0, 2);
            minute = substr_to_int(token[1], 2, 2);
            /* Check whether this is a synoptic time */
            if ((pos.hour % 6 == 0) && minute == 0) {
                /* This is a synoptic time */
                syn_time = true;
            } else {
                /* This is not a synoptic time */
                syn_time = false;
            }
            
            /* Copy the record ID to DS (and figure out what to do with it later 
             * Possible values:
             *   L = landfall;
             *   W = peak wind;
             *   P = min pressure;
             *   I = peak wind/pressure;
             *   C = closest approach;
             *   S = change in status;
             *   G = genesis; 
             *   T = extra detail
             */
            strncpy(recID, token[2], strlen(token[3]));
            
            /* Check the storm's status for this time point */
            if ((strcasecmp(token[3], "TD") == 0) || (strcasecmp(token[3], "TS") == 0) || (strcasecmp(token[3], "TY") == 0) ||
                (strcasecmp(token[3], "ST") == 0) || (strcasecmp(token[3], "TC") == 0) || (strcasecmp(token[3], "HU") == 0)) {
                pos.type = TROPICAL;
                lasttype = TROPICAL;
            } else if ((strcasecmp(token[3], "SD") == 0) || (strcasecmp(token[3], "SS") == 0)) {
                pos.type = SUBTROPICAL;
                lasttype = SUBTROPICAL;
            } else if ((strcasecmp(token[3], "EX") == 0)) {
                pos.type = EXTRATROPICAL;
                lasttype = EXTRATROPICAL;
            } else if ((strcasecmp(token[3], "LO") == 0) || (strcasecmp(token[3], "WV") == 0) || (strcasecmp(token[3], "DB") == 0)) {
                pos.type = LOW;
                lasttype = LOW;
            } else {
                /* If we have a different condition (e.g. inland, dissipating),
                 * assume that the last valid condition is still true */
                pos.type = lasttype;
            }

            /* latitude */
            if (token[4][strlen(token[4])-1] == 'N') {
                pos.lat = substr_to_double(token[4], 0, (int)strlen(token[4])-1);
            } else {
                pos.lat = - substr_to_double(token[4], 0, (int)strlen(token[4])-1);
            }
            
            if (token[5][strlen(token[5])-1] == 'W') {
                pos.lon = substr_to_double(token[5], 0, (int)strlen(token[5])-1);
            } else {
                pos.lon = - substr_to_double(token[5], 0, (int)strlen(token[5])-1);
            }

            /* wind */
            pos.wind = atoi(token[6]);
            /* if peak wind: store the current classification */
            if (pos.wind > storm.maxwind) {
                strncpy(storm.header.stormclass, token[3],2);
                storm.header.stormclass[2] = '\0';
            }

            /* pressure */
            pos.pres = atoi(token[7]);
            
            /* Check if no wind and jump out for whatever reason */
            if (pos.wind == 0) {
                break;
            }
            
            /* Update the number of rows processed */
            points++;
            
            /* Save the parsed position point */
            /* NOTE: We are skipping non-synoptic times right now, 
             * until we figure out what to do with them! 
             */
            if (syn_time || !skipasynoptic)
                save_pos(args, storms, &storm, &pos);

            

            /* The following fields are not parsed yet:
             * token[ 8]: TS radii NE
             * token[ 9]: TS radii SE
             * token[10]: TS radii SW
             * token[11]: TS radii NW
             * token[12]: gale radii NE
             * token[13]: gale radii SE
             * token[14]: gale radii SW
             * token[15]: gale radii NW
             * token[16]: HU radii NE
             * token[17]: HU radii SE
             * token[18]: HU radii SW
             * token[19]: HU radii NW
             */
            
            
        } else {
            /* Something is off */
            fprintf(stderr, "Parsing error in file '%s': Could not parse the following input line:\n%s\n",
                    args->input, line);
            exit(-1);

        }

        free(linecopy);
    }
    fclose(file);
    
#if 0
    printf("Longitude: %d, %d\n", minlon, maxlon);
    printf("Latitude: %d, %d\n", minlat, maxlat);
    
    printf("%d %d %d %d\n", t, s, e, l);
#endif
    
    return storms;
}

