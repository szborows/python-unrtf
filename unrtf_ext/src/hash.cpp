/*=============================================================================
   GNU UnRTF, a command-line program to convert RTF documents to other formats.
   Copyright (C) 2000,2001,2004 by Zachary Smith

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

   The maintainer is reachable by electronic mail at daved@physiol.usyd.edu.au
=============================================================================*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "error.h"
#include "main.h"
#include "malloc.h"


typedef struct _hi
{
	struct _hi *next;
	char str[1];
} HashItem;


/* Index by first char of string not \ */
static HashItem *hash[256];

/*========================================================================
 * Name:	hash_stats
 * Purpose:	Return the number of words stored. This is all words,
 * 			including commands to RTF, NOT the number of printed words in
 * 			a given document.
 * Args:	None.
 * Returns:	Number of words stored.
 *=======================================================================*/

unsigned long
hash_stats()
{
	int i;
	unsigned long total = 0;
	HashItem *hi;
	for (i = 0; i < 256; i++)
	{
		hi = hash[i];
		while (hi)
		{
			total++;
			hi = hi->next;
		}
	}
	return total;
}



/*========================================================================
 * Name:	hashitem_new
 * Purpose:	Creates a new linked list item for the hash table.
 * Args:	String.
 * Returns:	HashItem.
 *=======================================================================*/

static HashItem *
hashitem_new(char *str)
{
	HashItem *hi;

	/* We already have a char[1], so allocating strlen() does
	   yield space for the ending 0 */
	unsigned int l = sizeof(HashItem) + strlen(str);
	hi = (HashItem *) my_malloc(l);
	if (!hi)
	{
		error_handler("Out of memory");
	}
	strcpy(hi->str, str);
	hi->next = NULL;

	return hi;
}


/*========================================================================
 * Name:	hash_store
 * Purpose:	Given a string, find or store it and return the address of
 *              the copy.
 * Args:	String.
 * Returns:	Address of readonly clone.
 *=======================================================================*/

const char *
hash_store(char *str)
{
	unsigned char ch = (unsigned char) * str;
	HashItem *hi;

	if (ch == '\\' && *(str + 1))
	{
		ch = *(str + 1);
	}
	hi = hash[ch];
	while (hi)
	{
		if (!strcmp(hi->str, str))
		{
			return hi->str;
		}
		hi = hi->next;
	}
	/* not in hash */
	hi = hashitem_new(str);
	hi->next = hash[ch];
	hash[ch] = hi;
	return hi->str;
}

