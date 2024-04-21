#ifndef MY_COMMAND_IOCTL_H
#define MY_COMMAND_IOCTL_H
#include <linux/ioctl.h>

#define MAJOR_NUM 100
#define DEVICE_FILE_NAME "my_char_dev"

/*
 * Set the message of the device driver 
 */
#define IOCTL_SET_MSG _IOR(MAJOR_NUM, 0, char *)
/*
 * _IOR means that we're creating an ioctl command
 * number for passing information from a user process
 * to the kernel module.
 *
 * The first arguments, MAJOR_NUM, is the major device
 * number we're using.
 *
 * The second argument is the number of the command
 * (there could be several with different meanings).
 *
 * The third argument is the type we want to get from
 * the process to the kernel.
 */

/* delete the message of the device driver */
#define IOCTL_DELETE_MSG _IO(MAJOR_NUM, 1)

#endif