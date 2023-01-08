#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/printk.h>

MODULE_LICENSE("GPL");

#define DEVICE_NAME "solution_node"
#define DEVICE_MAJOR 240

/*Interface functions*/
ssize_t read_interface (struct file *, char *, size_t, loff_t *);
ssize_t write_interface (struct file *, const char *, size_t, loff_t *);
int open_interface (struct inode *, struct file *);
int release_interface (struct inode *, struct file *);

/*Struct of pointers to interface functions*/
static struct file_operations fops = {
    .read = read_interface,
    .write = write_interface,
    .open = open_interface,
    .release = release_interface
};

/*Global variables*/
int a, b, sum;

static int __init init_solution(void)
{
    printk(KERN_INFO "Init file_interface_driver module.\n");
    return 0;
}

static void __exit cleanup_solution(void)
{
    printk(KERN_INFO "Cleanup file_interface_driver module.\n");
}

module_init (init_solution);
module_exit (cleanup_solution);