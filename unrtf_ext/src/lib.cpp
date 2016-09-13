#include "defs.h"
#include "word.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "defs.h"
#include "error.h"
#include "word.h"
#include "convert.h"
#include "parse.h"
#include "hash.h"
#include "malloc.h"
#include "path.h"

#include "output.h"
#include "user.h"
#include "main.h"
#include "util.h"
#include "fontentry.h"

int nopict_mode = TRUE; /* TRUE => Do not write \pict's to files */
int dump_mode = FALSE;   /* TRUE => Output a dump of the RTF word tree */
int debug_mode = FALSE;  /* TRUE => Output debug comments within HTML */
int lineno;      /* Used for error reporting and final line count. */
int simple_mode = FALSE; /* TRUE => Output HTML without SPAN/DIV tags -- This would
                    probably be more useful if we could pull out <font> tags
                    as well. */
int inline_mode = TRUE; /* TRUE => Output HTML without HTML/BODY/HEAD -- This is
                    buggy. I've seen it output pages of </font> tags. */
/* marcossamaral - 0.19.9 */
int verbose_mode = FALSE;  /* TRUE => Output additional informations about unrtf */
int no_remap_mode = FALSE; /* don't remap codepoints */
int quiet = FALSE;       /* TRUE => don't output header comments */

FontEntry font_table[MAX_FONTS];
int total_fonts = 0;

OutputPersonality *op = NULL;

OutputPersonality *
get_config(char *name, OutputPersonality *op)
{
    char *configfile = 0;
    if (!path_checked && check_dirs() == 0)
    {
        fprintf(stderr, "No config directories. Searched: %s\n", search_path);
        exit(1);
    }
    configfile = search_in_path(name, "conf");
    if (configfile == NULL)
    {
        fprintf(stderr, "failed to find %s.conf in search path dirs\n", name);
        exit(1);
    }
    op = user_init(op, configfile);
    free(configfile);
    return op;
}


int unrtf(FILE * fp, bool nopict_mode_) {
    search_path = DEFAULT_UNRTF_SEARCH_PATH;
    if (op == NULL)
    {
        op = get_config(DEFAULT_OUTPUT, op);
    }

    nopict_mode = nopict_mode_;

    total_fonts = 0;
    Word * word = word_read(fp);
    word = optimize_word(word, 1);
    word_print(word);
    word_free(word);
    return 42;
}
