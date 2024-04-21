#include <linux/kernel.h> /* We're doing kernel work */
#include <linux/module.h> /* Specifically, a module */
#include <linux/fs.h>
#include <asm/uaccess.h> /* for get_user and put_user */
#include "ioctl.h"

#include "vars.h"
#include "defines.h"
#include "funs.h"

/* write to device */
ssize_t device_write(struct file *file,
    const char __user * buffer, size_t length, loff_t * offset)
{
    int i, j;
    char tmp[BUF_LEN];
    for(i = 0; i < length && i < BUF_LEN; i++)
        get_user(tmp[i], buffer + i);

    j = handle_command(tmp);
    
    if(!j) // (if no command)
    {
        for(i = 0; i < length; i++)
            message[i] = tmp[i];
        left_pos = message;
        right_pos = message + length - 2;
        deleted = 0;
    }
    printk("device_write(%s,%d,%d)", buffer, i, j); //
    return i;
}