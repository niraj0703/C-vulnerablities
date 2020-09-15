/* platform: ubuntu on x86_64 
   compiler: gcc
   command to reproduce:
    username admin
    cutomerChat BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
    reset
    login
*/
struct currentUser {
    char username[0x100];
    char password[4];
} ;
char *customerChat;
struct currentUser * user;

int main(int argc, char *argv[]){
    printf("Use after free challenge. Try to log in without entering the password. Available commands are:\na) username XYZ\nb) login\nc) customerChat XYZ.\n");
    char line[0x400];
    while(1) {
        printf("{user = %p, customerChat = %p }\n", user, customerChat);
        
        if(fgets(line, sizeof(line), stdin) == NULL) break;
        
        if(strncmp(line, "username ", 9) == 0) {
            user = malloc(sizeof(struct currentUser));
            memset(user, 0, sizeof(struct currentUser));
            if(strlen(line + 5) < 0x100) {
                printf("Setting username\n");
                strcpy(user->username, line + 9);
            }
        }
        if(strncmp(line, "reset", 5) == 0) {
            printf("Freeing user object\n");
            free(user);
        }
        if(strncmp(line, "customerChat ", 13) == 0) {
            customerChat = strdup(line + 12);
        }
        if(strncmp(line, "currentUser", 11) == 0) {
            printf("Current user is %s", user->username);
        }
        if(strncmp(line, "login", 5) == 0) {
            if(strncmp(user->password, "BBB", 3) == 0) {
                printf("You have successfully logged in with password %s!\n", user->password);
            } else {
                printf("Please enter your password\n");
                printf("current password is %s\n", user->password);
            }
        }
    }
    return 0;
}
