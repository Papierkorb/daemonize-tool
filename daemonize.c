/* Korbs Daemonize Tool. This file is licensed under the BSD 3-clause license.
   See README.md for the complete license text.
   
   Compile: $ gcc -o d daemonize.c
*/

#define _GNU_SOURCE
#include <linux/limits.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

enum Mode {
	/* Close stdout/err and stdin. */
	SilentMode = 0,
	
	/* Don't close stdout/err, but stdin. */
	VerboseMode = 1
};

static enum Mode chooseMode(int filedes) {
	struct stat s;
	if (fstat (filedes, &s) != 0)
		return SilentMode;
	return S_ISCHR(s.st_mode) ? SilentMode : VerboseMode;
}

static int isExecutable (const char *file) {
	struct stat s;
	if (stat (file, &s) == 0)
		return (!S_ISDIR(s.st_mode) && (s.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) != 0);
	return 0;
}

int main (int argc, char **argv) {
	
	if (argc < 2) {
		printf ("Usage: %s <Command ...>\n", argv[0]);
		return 1;
	}
	
	// 
	int offset = 1;
	int executable = (argc > 2);
	if (!executable) {
		char *path = strdup (secure_getenv ("PATH"));
		char *cur = strtok (path, ":");
		char p[PATH_MAX];
		
		while ((cur = strtok (NULL, ":")) != NULL && !executable) {
			snprintf (p, PATH_MAX, "%s/%s", cur, argv[1]);
			executable = isExecutable (p);
		}
		
		free (path);
	}
	
	//
	if (!executable) {
		argv[0] = "xdg-open";
		offset = 0;
	}
	
	// 
	if (fork () == 0) {
		int null = open ("/dev/null", O_WRONLY | O_NONBLOCK);
		if (chooseMode (fileno(stdout)) == SilentMode) {
			dup2 (null, fileno(stdout));
			dup2 (null, fileno(stderr));
		}
		
		if (chooseMode (fileno(stdin)) == SilentMode) {
			dup2 (null, fileno(stdin));
		}
		
		close (null);
		
		// Start process
		execvp (argv[offset], argv + offset);
		
		perror ("Failed to execute");
		return errno;
		
	}
	
	// 
	return 0;
	
}
