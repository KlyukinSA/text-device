#ifndef MY_COMMAND_FUNS_H
#define MY_COMMAND_FUNS_H

long device_ioctl(
    struct file *file, /* ditto */
    unsigned int ioctl_num, /* number and param for ioctl */
    unsigned long ioctl_param);

ssize_t device_write(struct file *file,
    const char __user * buffer, size_t length, loff_t * offset);

ssize_t device_read(struct file *file, /* see include/linux/fs.h */
    char __user * buffer, /* buffer to be filled with data */
    size_t length, /* length of the buffer */
    loff_t * offset);

int handle_command(char* str);

#endif