/* ========================================================================== */
/*                                                                            */
/*   Serialport.c                                                             */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */

#include "rs232.h"
#include "serialport.h"

unsigned char *sp_buf_out = NULL;
int sp_buf_out_b = 0;
int sp_buf_out_e = 0;
unsigned char *sp_buf_in = NULL;
int sp_buf_in_b = 0;
int sp_buf_in_e = 0;

#define BUF_OUT_FREE ((sp_buf_out_b - sp_buf_out_e) & SP_BUF_SIZE)

int sp_open(char* name, int baud)
{
	// open com 0, baud=1M, 8data, no parity, 1 stopbit
	RS232_OpenComport(name, baud, "8n1");
 
  // create memory buffers
  HANDLE hheap = NULL;  /* process heap handle */
  hheap = GetProcessHeap();
  if (hheap == NULL) return -2;
  sp_buf_out = HeapAlloc(hheap, HEAP_ZERO_MEMORY, SP_BUF_SIZE);
  sp_buf_in = HeapAlloc(hheap, HEAP_ZERO_MEMORY, SP_BUF_SIZE);
}

void sp_close(void)
{
  HANDLE hheap = NULL;  /* process heap handle */
  hheap = GetProcessHeap();
	//
	RS232_CloseComport(0);
  HeapFree(hheap, 0, (LPVOID) sp_buf_out);
  HeapFree(hheap, 0, (LPVOID) sp_buf_in);
}

void sp_send(char *data, int len)
{
  int i;
  
  if (!BUF_OUT_FREE) return; // no space in buffer - drop request
  
  // add data to output buffer
  for(i=0; i<len; i++) {
    sp_buf_out[sp_buf_out_e] = data[i];
    sp_buf_out_e = (sp_buf_out_e+1) & SP_BUF_SIZE;
  }
}