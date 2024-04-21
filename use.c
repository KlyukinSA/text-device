/*
 * use.c - the process to use ioctl's to control the kernel module
 *
 * Until now we could have used cat for input and output. But now
 * we need to do ioctl's, which require writing our own process.
 */
/*
 * device specifics, such as ioctl numbers and the
 * major device file.
 */
#include "ioctl.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> /* open */
#include <unistd.h> /* exit */
#include <sys/ioctl.h> /* ioctl */
/* set devise messege */
void ioctl_set_msg(int fd, char *message)
{
    int ret_val;
    ret_val = ioctl(fd, IOCTL_SET_MSG, message);
    if (ret_val < 0)
    {
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
}
/* delete devise messege */
void ioctl_msg_delete(int fd)
{
    int ret_val = ioctl(fd, IOCTL_DELETE_MSG);
    if (ret_val < 0)
    {
        printf("ioctl_msg_delete failed:%d\n", ret_val);
        exit(-1);
    }
    printf("message deleted\n");
}
/* call ioctl funcs */
int main()
{
    int fd, ret_val;
    char *msg = "Message passed by ioctl\n";
    fd = open(DEVICE_FILE_NAME, 0);
    if (fd < 0)
    {
        printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
        exit(-1);
    }
    ioctl_msg_delete(fd);
    //ioctl_set_msg(fd, msg);
    close(fd);
}
