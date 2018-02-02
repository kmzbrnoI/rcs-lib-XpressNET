#ifndef SERIALPORT_H
#define SERIALPORT_H

// settings

// size of input and output buffer
#define SP_BUF_SIZE (1024)

// public
int sp_open(char* name, int baud);
void sp_close(void);
void sp_send(char *data, int len);


#endif