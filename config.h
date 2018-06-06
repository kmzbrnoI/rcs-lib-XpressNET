#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <windows.h>

struct smod {
  int active;
  wchar_t name[64];
  wchar_t fw[64];      
};

struct scfg {
	wchar_t port_name[32];
	int port_baud;
  struct sxbus {
    int module_count;
    struct smod mod[128];
  } busi;
};
extern struct scfg *cfg;

/* load config data */
int cfg_load(void);

static int inihandler(void* user, const char* section, const char* name,
                   const char* value);

#endif /* __CONFIG_H__ */