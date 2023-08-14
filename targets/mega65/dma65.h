/* F018 DMA core emulation for MEGA65
   Part of the Xemu project.  https://github.com/lgblgblgb/xemu
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

#ifndef XEMU_MEGA65_DMA_H_INCLUDED
#define XEMU_MEGA65_DMA_H_INCLUDED

extern int   in_dma;

extern void  dma_write_reg                ( int addr, Uint8 data );
extern Uint8 dma_read_reg                 ( int reg );
extern void  dma_init                     ( void );
extern void  dma_init_set_rev             ( const Uint8 *rom );
extern void  dma_reset                    ( void );
extern int   dma_update                   ( void );
extern int   dma_update_multi_steps       ( const int do_for_cycles );
extern int   dma_get_revision             ( void );
extern void  dma_get_list_addr_as_bytes   ( Uint8 *p );
extern void  dma_set_list_addr_from_bytes ( const Uint8 *p );

#ifdef XEMU_SNAPSHOT_SUPPORT
#include "xemu/emutools_snapshot.h"
extern int dma_snapshot_load_state ( const struct xemu_snapshot_definition_st *def, struct xemu_snapshot_block_st *block );
extern int dma_snapshot_save_state ( const struct xemu_snapshot_definition_st *def );
#endif

#endif
