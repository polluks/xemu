/* Part of the Xemu project, please visit: https://github.com/lgblgblgb/xemu
   Copyright (C)2016,2019 LGB (Gábor Lénárt) <lgblgblgb@gmail.com>

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

#ifndef __EMUTOOLS_NATIVEGUI_H_INCLUDED
#define __EMUTOOLS_NATIVEGUI_H_INCLUDED

#define XEMUNATIVEGUI_FSEL_DIRECTORY		0
#define XEMUNATIVEGUI_FSEL_OPEN			1
#define XEMUNATIVEGUI_FSEL_SAVE			2
#define XEMUNATIVEGUI_FSEL_FLAG_STORE_DIR	0x100


#if defined(_WIN32) || defined(HAVE_GTK3)
#	define XEMU_NATIVEGUI
#endif

extern int is_xemunativegui_ok;

extern int xemunativegui_init          ( void );
extern int xemunativegui_iteration     ( void );
extern int xemunativegui_file_selector ( int dialog_mode, const char *dialog_title, char *default_dir, char *selected, int path_max_size );

#endif