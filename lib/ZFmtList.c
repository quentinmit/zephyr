/* This file is part of the Project Athena Zephyr Notification System.
 * It contains source for the ZFormatNoticeList function.
 *
 *	Created by:	Robert French
 *
 *	$Source$
 *	$Author$
 *
 *	Copyright (c) 1987,1991 by the Massachusetts Institute of Technology.
 *	For copying and distribution information, see the file
 *	"mit-copyright.h". 
 */
/* $Header$ */

#ifndef lint
static char rcsid_ZFormatNoticeList_c[] =
    "$Id$";
#endif

#include <zephyr/zephyr_internal.h>

Code_t ZFormatNoticeList(notice, list, nitems, buffer, ret_len, 
			 cert_routine)
    ZNotice_t *notice;
    register char **list;
    int nitems;
    char **buffer;
    int *ret_len;
    Z_AuthProc cert_routine;
{
    char header[Z_MAXHEADERLEN];
    register int i;
    int hdrlen, size;
    char *ptr;
    Code_t retval;

    if ((retval = Z_FormatHeader(notice, header, sizeof(header), &hdrlen,
				 cert_routine)) != ZERR_NONE)
	return (retval);

    size = 0;
    for (i=0;i<nitems;i++)
	size += strlen(list[i])+1;

    *ret_len = hdrlen+size;

    /* *ret_len can never be zero here, no need to worry about malloc(0). */
    if (!(*buffer = malloc((unsigned)*ret_len)))
	return (ENOMEM);

    bcopy(header, *buffer, hdrlen);

    ptr = *buffer+hdrlen;

    for (;nitems;nitems--, list++) {
	i = strlen(*list)+1;
	bcopy(*list, ptr, i);
	ptr += i;
    }

    return (ZERR_NONE);
}
