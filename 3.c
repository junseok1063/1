#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

int main()
{
    char *user_name;
    struct passwd *user_pw;

    user_name =getlogin();
    user_pw = getpwnam( user_name);

    printf("user name : %s\n", user_pw->pw_name);
    printf("user id : %d\n", user_pw->pw_uid);
    
}