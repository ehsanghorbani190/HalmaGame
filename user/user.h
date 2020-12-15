#include "user.c"

struct User;

void save(struct User record);

unsigned long hash(unsigned char *str);

int login(char *username, unsigned long password);

unsigned long GetPassword();

void ShowLogin();