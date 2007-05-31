/*-----------------------------------------------------------------------
 * File: CMDLINE.C
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#include <stdio.h>
#include <string.h>
#define NO_COMM
/* Disable Warnings due to non-ANSI content of windows.h */
/* Warning 4100 "unreferenced formal parameter", not flagged in gcc */
#pragma warning (disable:4201 4514 4214 4115 4100)
#include <windows.h>
#pragma warning (default:4201 4214 4115)


static char **l_argv = NULL;
static unsigned l_argc = 0;

#define MAX_OPTIONS 32

typedef struct _cmd_options {
	char option;
	char *parameter;
} COMMAND_OPTION, COMMAND_OPTION_PTR;

static COMMAND_OPTION options[MAX_OPTIONS];
unsigned optionCount = 0;

static CommandParseOptions() {
	unsigned index = 0;
	int option = -1;
	unsigned i;

	memset(options,0,sizeof(options));

	/* loop through the options and determine if each is an option or a parameter */
	for (i = 0; i < l_argc; i++) {
		if (l_argv[i][0] == '-') {
			/* Found an option string */
			for (index = 1; index < strlen(l_argv[i]); index++) {
				option++;
				options[option].option = l_argv[i][index];
			}
		} else {
			/* Found a parameter to the previous option */
			if ( option < 0 )
			{
				options[++option].parameter = l_argv[i];
			}
			else
			{
				options[option].parameter = l_argv[i];
			}
		}
	}
	if (options[option].option == 0 && options[option].parameter == NULL) {
		optionCount = option;
	} else {
		optionCount = option + 1;
	}

	return TRUE;
}

unsigned CommandInitParse(char **argv, unsigned argc) {
	l_argv = argv;
	l_argc = argc;

	return CommandParseOptions();
}

unsigned CommandGetOption(char option, char **parameter, unsigned *index) {
	unsigned i;

	for (i = *index; i < optionCount; i++) {
		if (options[i].option == option) {
			*parameter = options[i].parameter;
			*index = i;
			return TRUE;
		}
	}

	return FALSE;
}

unsigned CommandGetNextOption( char *option, char **parameter, unsigned index )
{
	if ( index >= optionCount )
	{
		return FALSE;
	}
	else
	{
		*option = options[index].option;
		*parameter = options[index].parameter;
		return TRUE;
	}
}