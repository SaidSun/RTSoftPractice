#ifndef __MYDRIVERIO_H__
#define __MYDRIVERIO_H__
#include <linux/ioctl.h>
#define MAJOR_NUM 509
#define GET_MAC _IOR(MAJOR_NUM, 1, int*)
#endif

