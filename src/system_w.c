/* system_w.c:    provide OS specific helpers (e.g. run cmds)
 *
 * Copyright (c) 2013, by:      Sebastian Riemer
 *    All rights reserved.     <sebastian.riemer@gmx.de>
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

#include "common.h"
#include "system.h"


inline void wait_proc (pid_t pid)
{
}

inline void kill_proc (pid_t pid)
{
}

/*
 * Run a task in background.
 *
 * Parameters: task function pointer,
 *             void *argument for the task
 * Returns: pid for success, -1 for failure
 *
 * Please note: The task has to cast the argument pointer to its
 *              correct type again. If more arguments are required,
 *              please use a structure.
 */
pid_t fork_proc (void (*task) (void *), void *argp)
{
	return -1;
}

bool pid_is_running (pid_t pid, char *proc_name, bool use_wait)
{
	return true;
}

pid_t run_pgrp_bg (const char *pcmd, char *const pcmdv[],
		   const char *ccmd, char *const ccmdv[],
		   char *const pid_str, char *proc_name,
		   u32 delay, bool do_wait, bool use_shell)
{
	return -1;
}

/*
 * Run a command in background.
 *
 * Parameters: execvp params, wait for the process 0/1
 * Returns: pid for success, -1 for failure
 */
pid_t run_cmd_bg (const char *cmd, char *const cmdv[], bool do_wait,
		  bool use_shell)
{
	return -1;
}

/*
 * Run a command in the background, wait for it
 * and get its result string from a pipe.
 *
 * Parameters: execvp params, pipe buffer, its size,
 *             run the command in a shell 0/1
 * Returns: what read() returns or -1
 *
 * Please note: If the shell is used, then execlp is
 *              used with cmd and cmdv[] is ignored.
 */
ssize_t run_cmd_pipe (const char *cmd, char *const cmdv[], char *pbuf,
		      size_t pbuf_size, bool use_shell)
{
	return -1;
}

/*
 * Get the pid of a process name.
 *
 * We always get the first pid we find in case
 * of multiple instances.
 *
 * Parameters: the process name
 * Returns: the pid or -1
 */
pid_t proc_to_pid (char *proc_name)
{
	return -1;
}

char *get_abs_app_path (char *app_name)
{
	return NULL;
}

#endif
