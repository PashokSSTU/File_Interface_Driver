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

/*Interface functions prototypes*/
static ssize_t read_interface (struct file *, char *, size_t, loff_t *);
static ssize_t write_interface (struct file *, const char *, size_t, loff_t *);
static int open_interface (struct inode *, struct file *);
static int release_interface (struct inode *, struct file *);

/*Struct of pointers to interface functions*/
static struct file_operations fops = {
    .read = read_interface,
    .write = write_interface,
    .open = open_interface,
    .release = release_interface
};

/*Global variables*/
int a, b, sum;
char a_buffer[10], b_buffer[10];

static int __init init_solution(void)
{
    int result = register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &fops);
    if(result < 0)
    {
        printk(KERN_ALERT "Init file_interface_driver module.\n");
        return result;
    }
    
    return 0;
}

static void __exit cleanup_solution(void)
{
    unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
    printk(KERN_INFO "Cleanup file_interface_driver module.\n");
}

module_init (init_solution);
module_exit (cleanup_solution);

/*Interface functions prototypes*/
static int open_interface (struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "Opening device: %s.\n", DEVICE_NAME);
    return 0;
}

static int release_interface (struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "Closing device: %s.\n", DEVICE_NAME);
    return 0;
}

static ssize_t read_interface (struct file *filp, char *buf, size_t size, loff_t *off)
{
    printk(KERN_INFO "Read device: %s.\n", DEVICE_NAME);
    int error_count = 0;
    
    return error_count;
}

static ssize_t write_interface (struct file *filp, const char *buf, size_t size, loff_t *off)
{
    printk(KERN_INFO "Write device: %s.\n", DEVICE_NAME);
    int error_counter = 0;
    
    return error_counter;
}