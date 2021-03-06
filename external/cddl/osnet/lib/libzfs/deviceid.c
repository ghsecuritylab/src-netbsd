/*	$NetBSD: deviceid.c,v 1.3 2017/01/10 19:20:35 christos Exp $	*/

/*-
 * Copyright (c) 2009 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Andrew Doran.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*-
 * Copyright (c) 2007 Pawel Jakub Dawidek <pjd@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
/* __FBSDID("$FreeBSD: src/compat/opensolaris/misc/deviceid.c,v 1.1 2007/05/06 01:39:38 pjd Exp $"); */
__RCSID("$NetBSD: deviceid.c,v 1.3 2017/01/10 19:20:35 christos Exp $");

#include <sys/param.h>
#include <sys/ioctl.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <devid.h>
#include <err.h>

int
devid_str_decode(char *devidstr, ddi_devid_t *retdevid, char **retminor_name)
{

	if (strlcpy(retdevid->devid, devidstr, sizeof(retdevid->devid)) >=
	    sizeof(retdevid->devid)) {
		return (EINVAL);
	}
	*retminor_name = strdup("");
	if (*retminor_name == NULL)
		return (ENOMEM);
	return (0);
}

int
devid_deviceid_to_nmlist(const char *search_path, ddi_devid_t devid,
    const char *minor_name, devid_nmlist_t **retlist)
{

	errx(1, "XXXNETBSD devid_deviceid_to_nmlist");
}

void
devid_str_free(char *str)
{

	free(str);
}

void
devid_free(ddi_devid_t devid)
{
	/* Do nothing. */
}

void
devid_free_nmlist(devid_nmlist_t *list)
{

	free(list);
}

int
devid_get(int fd, ddi_devid_t *retdevid)
{
#ifdef XXXNETBSD
	errx(1, "XXXNETBSD devid_get");

	if (ioctl(fd, DIOCGIDENT, retdevid->devid) == -1)
		return (errno);
	if (retdevid->devid[0] == '\0')
		return (ENOENT);
#else
	memset(retdevid->devid, 0, sizeof(retdevid->devid));
	strlcpy(retdevid->devid, "device", sizeof(retdevid->devid));
#endif
	return (0);
}

int
devid_get_minor_name(int fd, char **retminor_name)
{

	*retminor_name = strdup("");
	if (*retminor_name == NULL)
		return (ENOMEM);
	return (0);
}

char *
devid_str_encode(ddi_devid_t devid, char *minor_name)
{

	return (strdup(devid.devid));
}
