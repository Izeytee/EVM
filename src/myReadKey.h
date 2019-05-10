#ifndef _MY_READ_KEY_H
#define _MY_READ_KEY_H

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int siging);
int rk_mytermsave();
int rk_mytermrestore();
int rk_readkey(enum keys*);

#endif
