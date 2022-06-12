#ifndef __COMM_20210217__
#define __COMM_20210217__

#include <time.h>
#include <stdint.h>

uint64_t cur_time();
struct tm * get_local_time();

const char * ip2str(uint32_t ip, char *buf, uint32_t size);
uint32_t str2ip(const char *str);
uint32_t mask2bit(uint32_t mask);

#endif