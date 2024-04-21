#include <linux/kernel.h> /* We're doing kernel work */
#include <linux/module.h> /* Specifically, a module */
#include <linux/fs.h>
#include "ioctl.h"

#include "defines.h"
#include "funs.h"
#include "vars.h"

/*
 * This function is called whenever a process tries to do an ioctl on our
 * device file. We get two extra parameters (additional to the inode and file
 * structures, which all device functions get): the number of the ioctl called
 * and the parameter given to the ioctl function.
 *
 * If the ioctl is write or read/write (meaning output is returned to the
 * calling process), the ioctl call returns the output of this function.
 *
 */
long device_ioctl(
    struct file *file, /* ditto */
    unsigned int ioctl_num, /* number and param for ioctl */
    unsigned long ioctl_param)
{

    int i;
    char *temp;
    char ch;
    switch (ioctl_num)
    {
        case IOCTL_SET_MSG:
            temp = (char *)ioctl_param;
            get_user(ch, temp);
            for (i = 0; ch && i < BUF_LEN; i++, temp++)
                get_user(ch, temp);
            device_write(file, (char *)ioctl_param, i, 0);
            break;
        case IOCTL_DELETE_MSG:
            deleted = 1;
        break;
    }
    return SUCCESS;
}