#include "user.c"

struct User;

struct User save(struct User record);

unsigned long hash(unsigned char *str);

struct User login(char *username, unsigned long password);

unsigned long GetPassword();

struct User ShowLogin();