#ifndef __MYDRIVERIO_H__
#define __MYDRIVERIO_H__
#include <linux/ioctl.h>
#define MAJOR_NUM 509
#define MYDRIVER_NULL _IO(MAJOR_NUM, 0)
#define MYDRIVER_GET _IOR(MAJOR_NUM, 1, int*)
#define MYDRIVER_SET _IOW(MAJOR_NUM, 2, int*)
#endif

