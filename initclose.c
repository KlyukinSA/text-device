#include <linux/kernel.h> /* We're doing kernel work */
#include <linux/module.h> /* Specifically, a module */
#include <linux/fs.h>
#include <asm/uaccess.h> /* for get_user and put_user */
#include "ioctl.h"

#include "funs.h"
#include "defines.h"

char message[BUF_LEN];
int direction = 1;
char* left_pos;
char* right_pos;
int deleted = 0;

int Device_Open = 0;

/* open file */
static int device_open(struct inode *inode, struct file *file)
{
    // printk(KERN_INFO "device_open(%p)\n", file); //
    if (Device_Open)
    return -EBUSY;
    Device_Open++;
    
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

/* close file */
static int device_release(struct inode *inode, struct file *file)
{
    // printk(KERN_INFO "device_release(%p,%p)\n", inode, file); //
    Device_Open--;
    module_put(THIS_MODULE);
    return SUCCESS;
}

/* Module Declarations */
/*
 * This structure will hold the functions to be called
 * when a process does something to the device we
 * created. Since a pointer to this structure is kept in
 * the devices table, it can't be local to
 * init_module. NULL is for unimplemented functions.
 */

struct file_operations Fops = {
    .read = device_read,
    .write = device_write,
    .unlocked_ioctl = device_ioctl,
    .open = device_open,
    .release = device_release, /* a.k.a. close */
};
/*
 * Initialize the module - Register the character device
 */
int init_module()
{
    int ret_val;
    ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);
    if (ret_val < 0)
    {
        printk(KERN_ALERT "%s failed with %d\n",
        "Sorry, registering the character device ", ret_val);
        return ret_val;
    }
    printk(KERN_INFO "%s The major device number is %d.\n",
        "Registeration is a success", MAJOR_NUM);
    printk(KERN_INFO "If you want to talk to the device driver,\n");
    printk(KERN_INFO "you'll have to create a device file. \n");
    printk(KERN_INFO "We suggest you use:\n");
    printk(KERN_INFO "mknod %s c %d 0\n", DEVICE_FILE_NAME, MAJOR_NUM);
    printk(KERN_INFO "The device file name is important, because\n");
    printk(KERN_INFO "the ioctl program assumes that's the\n");
    printk(KERN_INFO "file you'll use.\n");

    //left_pos = message;
    //right_pos = left_pos;
    //direction = 1;

    return 0;
}
/*
 * Cleanup - unregister the appropriate file from /proc
 */
void cleanup_module()
{
    int ret = 0;
    unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
    if (ret < 0)
        printk(KERN_ALERT "Error: unregister_chrdev: %d\n", ret);
}
