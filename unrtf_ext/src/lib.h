#pragma once
#include <stdio.h>

#include "output.h"

extern int lineno;
extern int debug_mode;
extern int simple_mode;
extern int inline_mode;
extern int no_remap_mode;
#define CONFIG_DIR PKGDATADIR
#define DEFAULT_OUTPUT "html"

extern OutputPersonality *op;

OutputPersonality * get_config(char *name, OutputPersonality *op);
int unrtf(FILE * fp, bool no_pict_mode_);
