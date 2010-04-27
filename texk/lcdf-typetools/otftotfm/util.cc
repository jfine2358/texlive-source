/* util.{cc,hh} -- various bits
 *
 * Copyright (c) 2003-2010 Eddie Kohler
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version. This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif
#include "util.hh"
#include <lcdf/error.hh>
#include <lcdf/straccum.hh>
#include <lcdf/vector.hh>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#ifdef HAVE_FCNTL_H
# include <fcntl.h>
#endif
#if defined(_MSDOS) || defined(_WIN32)
# include <io.h>
#endif
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

String
read_file(String filename, ErrorHandler *errh, bool warning)
{
    FILE *f;
    if (!filename || filename == "-") {
	filename = "<stdin>";
	f = stdin;
#if defined(_MSDOS) || defined(_WIN32)
	// Set the file mode to binary
	_setmode(_fileno(f), _O_BINARY);
#endif
    } else if (!(f = fopen(filename.c_str(), "rb"))) {
	errh->xmessage((warning ? errh->e_warning : errh->e_error) + ErrorHandler::make_landmark_anno(filename), strerror(errno));
	return String();
    }

    StringAccum sa;
    while (!feof(f)) {
	if (char *x = sa.reserve(8192)) {
	    int amt = fread(x, 1, 8192, f);
	    sa.forward(amt);
	} else {
	    errh->xmessage((warning ? errh->e_warning : errh->e_error) + ErrorHandler::make_landmark_anno(filename), "Out of memory!");
	    break;
	}
    }
    if (f != stdin)
	fclose(f);
    return sa.take_string();
}

String
printable_filename(const String &s)
{
    if (!s || s == "-")
	return String::make_stable("<stdin>");
    else
	return s;
}

String
pathname_filename(const String &path)
{
    int slash = path.find_right('/');
    if (slash >= 0 && slash != path.length() - 1)
	return path.substring(slash + 1);
    else
	return path;
}

static String
simplify_filename(String x)
{
    while (x.substring(0, 2) == "./")
	x = x.substring(2);
    int pos;
    while ((pos = x.find_left("/./")) >= 0)
	x = x.substring(0, pos) + x.substring(pos + 2);
    return x;
}

bool
same_filename(const String &a, const String &b)
{
    return simplify_filename(a) == simplify_filename(b);
}

String
shell_quote(const String &str)
{
#if defined(_MSDOS) || defined(_WIN32)
    return str;			// XXX
#else
    if (!str)
	return String::make_stable("''");

    const char *begin = str.begin();
    const char *end = str.end();
    StringAccum sa;
    for (const char *s = begin; s < end; s++)
	if (isalnum((unsigned char) *s) || *s == '_' || *s == '-' || *s == '+' || *s == '/' || *s == ':' || *s == '.')
	    /* do nothing */;
	else {
	    sa.append(begin, s);
	    sa.append('\\');
	    begin = s;
	}

    if (!sa)
	return str;
    else {
	sa.append(begin, end);
	return sa.take_string();
    }
#endif
}

int
mysystem(const char *command, ErrorHandler *errh)
{
    if (no_create) {
	errh->message("would run %s", command);
	return 0;
    } else {
	if (verbose)
	    errh->message("running %s", command);
	return system(command);
    }
}

int
temporary_file(String &filename, ErrorHandler *errh)
{
    if (no_create)
	return 0;		// random number suffices

#ifdef HAVE_MKSTEMP
    const char *tmpdir = getenv("TMPDIR");
    if (tmpdir)
	filename = String(tmpdir) + "/otftotfm.XXXXXX";
    else {
# ifdef P_tmpdir
	filename = P_tmpdir "/otftotfm.XXXXXX";
# else
	filename = "/tmp/otftotfm.XXXXXX";
# endif
    }
    int fd = mkstemp(filename.mutable_c_str());
    if (fd < 0)
	errh->error("temporary file %<%s%>: %s", filename.c_str(), strerror(errno));
    return fd;
#else  // !HAVE_MKSTEMP
    for (int tries = 0; tries < 5; tries++) {
	if (!(filename = tmpnam(0)))
	    return errh->error("cannot create temporary file");
# ifdef O_EXCL
	int fd = ::open(filename.c_str(), O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0600);
# else
	int fd = ::open(filename.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0600);
# endif
	if (fd >= 0)
	    return fd;
    }
    return errh->error("temporary file %<%s%>: %s", filename.c_str(), strerror(errno));
#endif
}

bool
parse_unicode_number(const char* begin, const char* end, int require_prefix, uint32_t& result)
{
    bool allow_lower = (require_prefix == 1);
    if (require_prefix < 0)
	/* do not look for prefix */;
    else if (begin + 7 == end && begin[0] == 'u' && begin[1] == 'n' && begin[2] == 'i')
	begin += 3;
    else if (begin + 5 <= end && begin + 7 >= end && begin[0] == 'u')
	begin++;
    else if (begin + 3 <= end && begin + 8 >= end && begin[0] == 'U' && begin[1] == '+')
	begin += 2, allow_lower = true;
    else if (require_prefix > 1)
	/* some prefix was required */
	return false;

    uint32_t value;
    for (value = 0; begin < end; begin++)
	if (*begin >= '0' && *begin <= '9')
	    value = (value << 4) | (*begin - '0');
	else if (*begin >= 'A' && *begin <= 'F')
	    value = (value << 4) | (*begin - 'A' + 10);
	else if (allow_lower && *begin >= 'a' && *begin <= 'f')
	    value = (value << 4) | (*begin - 'a' + 10);
	else
	    return false;

    if (value <= 0xD7FF || (value >= 0xE000 && value <= 0x10FFFF)) {
	result = value;
	return true;
    } else
	return false;
}

#if 0
String
shell_command_output(String cmdline, const String &input, ErrorHandler *errh, bool strip_newlines)
{
    FILE *f = tmpfile();
    if (!f)
	errh->fatal("cannot create temporary file: %s", strerror(errno));
    ignore_result(fwrite(input.data(), 1, input.length(), f));
    fflush(f);
    rewind(f);

    String new_cmdline = cmdline + " 0<&" + String(fileno(f));
    FILE *p = popen(new_cmdline.c_str(), "r");
    if (!p)
	errh->fatal("%<%s%>: %s", cmdline.c_str(), strerror(errno));

    StringAccum sa;
    while (!feof(p) && !ferror(p) && sa.length() < 200000) {
	int x = fread(sa.reserve(2048), 1, 2048, p);
	if (x > 0)
	    sa.forward(x);
	else if (x < 0 && errno != EAGAIN)
	    errh->error("%<%s%>: %s", cmdline.c_str(), strerror(errno));
    }
    if (!feof(p) && !ferror(p))
	errh->warning("%<%s%> output too long, truncated", cmdline.c_str());

    fclose(f);
    pclose(p);
    while (strip_newlines && sa && (sa.back() == '\n' || sa.back() == '\r'))
	sa.pop_back();
    return sa.take_string();
}
#endif
