#include <linux/kernel.h> /* We're doing kernel work */
#include <linux/module.h> /* Specifically, a module */
#include <linux/fs.h>
#include <asm/uaccess.h> /* for get_user and put_user */
#include "ioctl.h"

#include "vars.h"

/* read from device */
ssize_t device_read(struct file *file, /* see include/linux/fs.h */
    char __user * buffer, /* buffer to be filled with data */
    size_t length, /* length of the buffer */
    loff_t * offset)
{
    int read = 0;
    printk("device_read(%ld,%ld,%ld,%d)\n", length, left_pos - message, right_pos - message, direction); //
    if(deleted)
        return 0;
    if(direction)
    {
        while (length > 0 && left_pos <= right_pos + 1)
        {
            put_user(*left_pos, buffer);
            printk("put %d to buffer\n", *buffer); //
            buffer++;
            left_pos++;
            length--;
            read++;
        }
    }
    else
    {
        if(right_pos >= left_pos)
        {
            while (length > 1 && right_pos >= left_pos)
            {
                put_user(*right_pos, buffer);
                printk("put %d to buffer\n", *buffer); //
                buffer++;
                right_pos--;
                length--;
                read++;
            } 
            put_user('\n', buffer);
            printk("put %d to buffer\n", *buffer); //
            length--;
            read++;
        }
    }
    printk("Read %d bytes, %d left\n", read, (int)length); //
    return read;
}