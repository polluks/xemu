/* Part of the Xemu project, please visit: https://github.com/lgblgblgb/xemu
   Copyright (C)2016-2022 LGB (Gábor Lénárt) <lgblgblgb@gmail.com>

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

#ifdef	XEMU_COMMON_ARCH_SYS_H_INCLUDED
#	error "xemu/arch-sys.h cannot be included multiple times (and it's included by C compiler command line)."
#endif
#define	XEMU_COMMON_ARCH_SYS_H_INCLUDED

#undef	_ISOC11_SOURCE
#define	_ISOC11_SOURCE 1

// We need this otherwise stupid things happen like M_E is not defined by math.h, grrr.
#ifndef _DEFAULT_SOURCE
#	define	_DEFAULT_SOURCE
#endif
//#ifdef __STRICT_ANSI__
//#	undef __STRICT_ANSI__
//#endif

// Generic stuff to signal we're inside XEMU build
// Useful for multi-purpose sources, can be also compiled out-of-source-tree, and stuff like that ...
#define	XEMU_BUILD

#if	defined(__arm64__) || defined(__arm64) || defined(__aarch64__) || defined(__aarch64) || defined(__arm64e__) || defined(__arm64e) || defined(__aarch64e__) || defined(__aarch64e)
#	define	XEMU_CPU_ARM
#	define	XEMU_CPU_ARM64
#	if defined(__arm64e__) || defined(__arm64e)
		// thus should be refined later, how Apple M1 is called himself, in terms of __arm* and similar macros to check for it, TODO
#		define XEMU_CPU_ARM_APPLE
#	endif
#elif	defined(__arm__) || defined(__arm32__) || defined(__arm) || defined(__arm32) || defined(__aarch__) || defined(__aarch) || defined(__aarch32__) || defined(__aarch32)
#	define	XEMU_CPU_ARM
#	define	XEMU_CPU_ARM32
#endif

#ifdef	__EMSCRIPTEN__
#	define	XEMU_ARCH_HTML
#	define	XEMU_ARCH_NAME	"html"
#	ifndef	DISABLE_DEBUG
#		define	DISABLE_DEBUG
#	endif
//#	define	XEMU_OLD_TIMING
#elif	defined(__ANDROID__)
#	define	XEMU_ARCH_ANDROID
#	define	XEMU_ARCH_NAME	"android"
#	ifndef	DISABLE_DEBUG
#		define	DISABLE_DEBUG
#	endif
#	define	XEMU_SLEEP_IS_SDL_DELAY
#elif	defined(_WIN64)
#	define	XEMU_ARCH_WIN64
#	define	XEMU_ARCH_WIN
#	define	XEMU_ARCH_NAME	"win64"
#	define	XEMU_SLEEP_IS_USLEEP
#elif	defined(_WIN32)
#	define	XEMU_ARCH_WIN32
#	define	XEMU_ARCH_WIN
#	define	XEMU_ARCH_NAME	"win32"
#	define	XEMU_SLEEP_IS_USLEEP
#elif	defined(__APPLE__)
	// Actually, MacOS / OSX is kinda UNIX, but for some minor reasons we handle it differently here
#	include	<TargetConditionals.h>
#	ifndef	TARGET_OS_MAC
#		error	"Unknown Apple platform (TARGET_OS_MAC is not defined by TargetConditionals.h)"
#	endif
#	define	XEMU_ARCH_OSX
#	define	XEMU_ARCH_MAC
#	define	XEMU_ARCH_UNIX
#	define	XEMU_ARCH_NAME	"osx"
#	define	XEMU_SLEEP_IS_NANOSLEEP
#	ifdef	XEMU_CPU_ARM
#		define	XEMU_ARCH_MAC_ARM
#	endif
#elif	defined(__unix__) || defined(__unix) || defined(__linux__) || defined(__linux)
#	define	XEMU_ARCH_UNIX
#	if	defined(__linux__) || defined(__linux)
#		define	XEMU_ARCH_LINUX
#		define	XEMU_ARCH_NAME	"linux"
#	else
#		define	XEMU_ARCH_NAME	"unix"
		// It seems at least on FreeBSD there is some problem hiding definitions by the FreeBSD system headers
		// when using some other macros like _C11_SOURCE by default. Thus we define this as well, to avoid
		// the problem. Thanks to @Scott on MEGA65/Xemu Discord for the the hint.
#		define	__BSD_VISIBLE	1
#	endif
#	define	XEMU_SLEEP_IS_NANOSLEEP
#elif defined(__HAIKU__)
		// Haiku is not really a UNIX, but for starting point let's define
		// it that way, since Xemu relies at many places that everything
		// which is not Windows is UNIX (including Linux and MacOS)
#		define	XEMU_ARCH_UNIX
#		define	XEMU_ARCH_HAIKU
#		define	XEMU_ARCH_NAME	"haiku"
#		define	XEMU_SLEEP_IS_NANOSLEEP
		// Haiku is not so much a multi-user system, thus we want
		// to do this:
#		define	XEMU_DO_NOT_DISALLOW_ROOT
		// Also in general:
#		define	XEMU_ARCH_SINGLEUSER
#else
#	error	"Unknown target OS architecture."
#endif

#if defined(XEMU_ARCH_UNIX) && !defined(_XOPEN_SOURCE)
#	define	_XOPEN_SOURCE	700
#endif

#if defined(XEMU_ARCH_WIN) && !defined(_USE_MATH_DEFINES)
	// It seems, some (?) versions of Windows requires _USE_MATH_DEFINES to be defined to define some math constants by math.h
#	define	_USE_MATH_DEFINES
#endif

// It seems Mingw on windows defaults to 32 bit off_t which causes problems, even on win64
// In theory this _FILE_OFFSET_BITS should work for UNIX as well (though maybe that's default there since ages?)
// Mingw "should" support this since 2011 or so ... Thus in nutshell: use this trick to enable large file support
// in general, regardless of the OS, UNIX-like or Windows. Hopefully it will work.
#ifdef	_FILE_OFFSET_BITS
#	undef	_FILE_OFFSET_BITS
#endif
#define	_FILE_OFFSET_BITS	64

#ifdef XEMU_ARCH_OSX
	// MacOS and/or SDL bug: even if this prototype is in string.h system header in MacOS,
	// somehow it does not work even if string.h _IS_ included. So I have to create my
	// own prototype for this function here :-O For the prototype, we also need the stddef.h
	// though, for the "size_t".
#	include <stddef.h>
	void memset_pattern4(void *__b, const void *__pattern4, size_t __len);
#endif
