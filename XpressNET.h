#ifndef XPRESSNET_H
#define XPRESSNET_H

byte xpn_inputs[1024];
byte xpn_outputs[1024];

void xpn_send(char *data, int len);
void xpn_set_output(int addr, int out);       // create outgoing message
void xpn_set_speed(int addr, int speed);      // create outgoing message

void xpn_input_data(char *data, int len);     // insert incoming data here

void xpn_parse_data(void);                        // find frame in input buffer, call parse_message
int  xpn_parse_message(char *data, int len);  // parse one message, return how many bytes can be deleted from buffer

#endif