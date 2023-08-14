/* A work-in-progess MEGA65 (Commodore 65 clone origins) emulator
   Part of the Xemu project, please visit: https://github.com/lgblgblgb/xemu
   Copyright (C)2016-2023 LGB (Gábor Lénárt) <lgblgblgb@gmail.com>

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


#ifndef XEMU_MEGA65_HDOS_H_INCLUDED
#define XEMU_MEGA65_HDOS_H_INCLUDED

#ifndef XEMU_MEGA65_HDOS_H_ALLOWED
#error "You cannot include hdos.h!"
#endif

#define HDOSROOT_SUBDIR_NAME "hdos"

extern void hdos_init  ( const int do_virt, const char *virtroot );
extern void hdos_enter ( const Uint8 func_no );
extern void hdos_leave ( const Uint8 func_no );
extern void hdos_notify_system_start_begin ( void );
extern void hdos_notify_system_start_end   ( void );

#ifdef TRAP_XEMU
// though not so much HDOS specfific, it's still Xemu related (Xemu's own trap handler)
// so we put it into hdos.c ...
extern void trap_for_xemu ( const int func_no );
#endif

#endif
