#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stddef.h>

#include "jma.h"
#include "track.h"

static char* get_max_classification(int wind) {
	if (wind >= 64) {
		return "TY";
	} else if (wind >=34) {
		return "TS";
	} else {
		return "TD";
	}
}

static int get_full_year(int two_digit_date)
{
        /* The files only have the last two digits; they will have y2k problem in 2051,
           because their database begins in 1951. */
	if (two_digit_date > 50) {
		return 1900 + two_digit_date;
	} else {
		return 2000 + two_digit_date;
	}
}

static struct storm_header read_header(char** token)
{
	struct storm_header header;
	memset(header.name, 0, STORM_NAME_LENGTH);
	int identifier = atoi(token[1]);
	header.id = identifier % 100;
	header.year = get_full_year(identifier/100);
	strncpy(header.name, token[7], strlen(token[7]));
	strncpy(header.basin, "WP", 3);
	return header;
}
struct stormdata *read_stormdata_jma(struct stormdata *storms, struct storm_arg* args, bool skipasynoptic)
{
	FILE* file;
	int i;
	char *line, *linecopy, buf[10240];
	struct storm storm;
	char *token[9]; // JMA BT files have only nine tokens max per line.
	int dateset = 0;
	int points = 0;
	struct pos pos;
	int count = 0;
	file = fopen(args->input, "r");
	if (!file) {
		fprintf(stderr, "Couldn't open file '%s': %s\n",
		args->input, strerror(errno));
	}
        while ((line = fgets(buf, sizeof(buf), file))) {
		if (strlen(line) <= 2) { // Ignore blank lines
			continue;
		}
		linecopy = strdup(line);
		/* Line parsing. JMA uses spaces as delineators and extra spaces are ignored by strtok(), so no need to strip. */
		token[0] = strtok(linecopy, " ");
		i = 1;
		while ((token[i-1] != NULL) && (i < 9)) {
			token[i] = strtok(NULL, " ");
			i++;
		}
		if (i < 6) {
			fprintf(stderr, "Parsing error in file '%s': Not enough data fields to parse data point properly\n", args->input);
			exit(-1);
		}
		// Header line always prefixed with 66666 as first token
		if (strcmp(token[0],"66666") == 0) {
			if (i < 8) {
				fprintf(stderr, "Parsing error in file '%s': Not enough data fields to parse header line properly.\n", args->input);
				exit(-1);
			}
			if (count > 0) {
				if (points > 0) {
					save_storm(args, storms, &storm);
				} else {
					fprintf(stderr, "Parsing error in file %s for storm %s: No data points found\n", args->input, storm.header.name);
					exit(-1);
				}
			}
			count++;
			init_storm(&storm);
			storm.header = read_header(token);
			points = 0;
			dateset = 0;
		} else if (strcmp(token[1], "002") == 0) { // Data lines always have 002 as second token
			int date = atoi(token[0]);
			pos.year = get_full_year(date/1000000);
			pos.month = (date % 1000000)/10000;
			pos.day = (date % 10000)/100;
			pos.hour = (date % 100);
			if (skipasynoptic && (pos.hour % 6 != 0)) {
				continue;
			}
			if (!dateset) {
				storm.header.year = pos.year;
				storm.header.month = pos.month;
				storm.header.day = pos.day;
				dateset = 1;
			}
			int stormtype = atoi(token[2]);
			if (stormtype == 6) {
				pos.type = EXTRATROPICAL;
			} else {
				pos.type = TROPICAL;  // JMA doesn't do ST
			}
			pos.lat = atoi(token[3])/10.0;
			pos.lon = -atoi(token[4])/10.0;
			pos.wind = atoi(token[6]);
			if (pos.wind > storm.maxwind) {
				storm.maxwind = pos.wind;
				if (pos.type != EXTRATROPICAL) {
					strncpy(storm.header.stormclass, get_max_classification(pos.wind), 3);
				}
			}
			pos.pres = atoi(token[5]);
			points++;
			save_pos(args, storms, &storm, &pos);
		}
		free(linecopy);
	}
	if (count > 0) {
		save_storm(args, storms, &storm);
	}
	fclose(file);
	return storms;
}

