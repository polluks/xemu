/* Part of the Xemu project, please visit: https://github.com/lgblgblgb/xemu
   Copyright (C)2016-2022 LGB (Gábor Lénárt) <lgblgblgb@gmail.com>

   The goal of emutools.c is to provide a relative simple solution
   for relative simple emulators using SDL2.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include "xemu/emutools_basicdefs.h"

const char XEMU_BUILDINFO_CC[]  = CC_TYPE " " __VERSION__ " " ARCH_BITS_AS_TEXT ENDIAN_NAME;

const char emulators_disclaimer[] =
	"LICENSE: Copyright (C)" COPYRIGHT_YEARS " Gábor Lénárt (aka LGB) lgb@lgb.hu http://lgb.hu/" NL
	"LICENSE: This software is a GNU/GPL version 2 (or later) software." NL
	"LICENSE: <http://gnu.org/licenses/gpl.html>" NL
	"LICENSE: This is free software; you are free to change and redistribute it." NL
	"LICENSE: There is NO WARRANTY, to the extent permitted by law." NL
;

int xemu_is_official_build ( void )
{
#ifdef XEMU_OFFICIAL_BUILD
	return 1;
#else
	static int is_official = -1;
	if (is_official < 0)
		is_official = !!getenv("XEMU_OFFICIAL_BUILD");
	return is_official;
#endif
}

void xemu_dump_version ( FILE *fp, const char *slogan )
{
	if (!fp)
		return;
	if (slogan)
		fprintf(fp, "**** %s ****" NL, slogan);
	fprintf(fp, "This software is part of the Xemu project: https://github.com/lgblgblgb/xemu" NL);
	fprintf(fp, "CREATED: %s at %s" NL "CREATED: %s for %s" NL, XEMU_BUILDINFO_ON, XEMU_BUILDINFO_AT, XEMU_BUILDINFO_CC, XEMU_ARCH_NAME);
	fprintf(fp, "VERSION: %s %s %s" NL, XEMU_BUILDINFO_GIT, XEMU_BUILDINFO_CDATE, xemu_is_official_build() ? "official-build" : "custom-build");
	fprintf(fp, "EMULATE: %s (%s): %s" NL, TARGET_DESC, TARGET_NAME, XEMU_BUILDINFO_TARGET);
	fprintf(fp, "%s" NL, emulators_disclaimer);
}
