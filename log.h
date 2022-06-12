#ifndef __LOG_20201219__
#define __LOG_20201219__

#include <string>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#include "comm.h"

#define MIN(a, b)	((a) < (b) ? (a) : (b))
#define MAX(a, b)	((a) < (b) ? (b) : (a))	

#define __LOG(level, fmt, args...)		do {	\
			struct tm *stm = get_local_time();	\
			std::string __file(__FILE__);		\
			printf("%d-%d-%d %d:%d:%d|" level "|%s:%d|%s|" fmt "\n", \
			stm->tm_year + 1900, stm->tm_mon + 1, stm->tm_mday, \
				stm->tm_hour, stm->tm_min, stm->tm_sec, \
			__file.substr(__file.find_last_of("/")).c_str() + 1, \
			__LINE__, __FUNCTION__, ## args);	\
		} while (0)

#define DEBUG(fmt, args...)		\
		__LOG("[debug]", fmt, ## args)
#define INFO(fmt, args...)		\
		__LOG("[info]", fmt, ## args)
#define WARN(fmt, args...)		\
		__LOG("[warn]", fmt, ## args)
#define ERROR(fmt, args...)		\
		__LOG("[error]", fmt, ## args)

#define DUMP_HEX(str, data, len)	do {					\
		char tmp[2048], *p = tmp;							\
		uint32_t __len = MIN((uint32_t)sizeof(tmp), (uint32_t)len);		\
		for (uint32_t i = 0; i < __len; i++) {				\
			if (i && i % 8 == 0) 							\
				p += snprintf(p, sizeof(tmp) - (p - tmp) - 1, "\n");						\
			p += snprintf(p, sizeof(tmp) - (p - tmp) - 1, "%02x ", ((uint8_t*)data)[i]);	\
		}	\
		DEBUG("%s ==> len:%d:\n%s", (const char*)str, __len, tmp);	\
	} while (0)


#endif