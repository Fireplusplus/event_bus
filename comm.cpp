#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/sysinfo.h>

#include "comm.h"

uint64_t cur_time()
{
	struct sysinfo info;
	if (sysinfo(&info) < 0) {
		return 0;
	}

	return info.uptime;
}

struct tm * get_local_time()
{
	time_t t;
	time(&t);

	struct tm *stm = localtime(&t);;
	return stm;
}

const char * ip2str(uint32_t ip, char *buf, uint32_t size)
{
	const char *str = inet_ntop(AF_INET, &ip, buf, size);
	return str ?: "";
}

uint32_t str2ip(const char *str)
{
	if (!str)
		return 0;

	uint32_t ip;
	if (inet_pton(AF_INET, str, &ip) < 0) {
		return 0;
	}
	
	return ip;
}

static uint32_t byte2bit(uint8_t byte)
{
	int cnt = 0;
	int n = 0x80;

	while (byte & n) {
		cnt++;
		n >>= 1;
	}

	return cnt;
}

uint32_t mask2bit(uint32_t mask)
{
	mask = ntohl(mask);

	if (mask >= 0xFFFFFF00) {
		return 24 + byte2bit(mask & 0xFF);
	} else if (mask >= 0xFFFF0000) {
		return 16 + byte2bit(mask >> 8 & 0xFF);
	} else if (mask >= 0xFF000000) {
		return 8 + byte2bit(mask >> 16 & 0xFF);
	} else {
		return byte2bit(mask >> 24 & 0xFF);
	}
}
