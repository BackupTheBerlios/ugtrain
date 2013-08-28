/* memattach_w.c:    functions to attach/read/write victim proc. memory
 * This file is for Windows only.
 *
 * Copyright (c) 2013, by:      Sebastian Riemer
 *    All rights reserved.      Ernst-Reinke-Str. 23
 *                              10369 Berlin, Germany
 *                             <sebastian.riemer@gmx.de>
 *
 * powered by the Open Game Cheating Association
 *
 * This file may be used subject to the terms and conditions of the
 * GNU General Public License Version 2, or any later version
 * at your option, as published by the Free Software Foundation.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#if defined(__WINNT__) || defined (__WIN32__)

#include "memattach.h"


i32 memattach_test (pid_t pid)
{
	return -1;
}

i32 memattach (pid_t pid)
{
	return -1;
}

i32 memdetach (pid_t pid)
{
	return -1;
}

i32 memread (pid_t pid, void *addr, void *buf, long buf_len)
{
	return -1;
}

i32 memwrite (pid_t pid, void *addr, void *buf, long buf_len)
{
	return -1;
}

#endif