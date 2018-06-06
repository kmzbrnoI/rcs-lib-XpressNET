/* ========================================================================== */
/*                                                                            */
/*   XpressNET.c                                                              */
/*   (c) 2017 Michal Petrilak                                                 */
/*                                                                            */
/*   XpressNET 2. layer driver                                                */
/*      provides only accessory messages                                      */
/*                                                                            */
/* ========================================================================== */

#include "config.h"
#include "Serialport.h"
#include "XpressNET.h"

void xpn_init()
{
  /* */
  int i;
  for(i=0; i<1024; i++) {
    xpn_inputs[i] = 0;
    xpn_outputs[i] = 0;
  }
  sp_open(cfg->port_name, cfg->port_baud);
}

void xpn_destroy()
{
  sp_close();
}

void xpn_send(char *data, int len)
{
  unsigned char xor;
  int i;
  
  /* calculate frame xor */
  xor = 0x00;
  for(i=0; i<len; i++) {
    xor ^= data[i];
  }
  data[len] = xor;
  len++;
  
  /* send frame */
  sp_send(data,len);
}

void xpn_set_output(int addr, int out)
{
  unsigned char data[32];
  
  // check values
  if (addr < 0) return;
  if (addr > 1023) return;
  out = (out) ? 1 : 0;
  
  // send frame
  data[0] = 0x52;
  data[1] = (addr >> 2);
  data[2] = 0x80 | ((addr & 0x03) << 1) | (out);
  xpn_send(data, 3);
  
  // save state
  xpn_outputs[addr] = out;
}



/*g_ConfigThread = CreateThread(NULL, 0, ConfigThreadFunc, NULL, 0, NULL);*/
