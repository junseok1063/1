#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	struct passwd pwd;
	struct passwd *result;
	char   buf[1024];
	size_t bufsize;
	int    ret;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s username\n", argv[0]);
		return 1;
	}

	ret = getpwnam_r(argv[1], &pwd, buf, bufsize, &result);
	if (result == NULL) {
		if (ret == 0)
			printf("%s\n", buf);
		else {
			printf("getpwnam_r() error: %s\n", strerror(ret));
		}
		return 1;
	}

	printf("Name: %s; UID: %ld\n", pwd.pw_gecos, (long) pwd.pw_uid);

	return 0;
}