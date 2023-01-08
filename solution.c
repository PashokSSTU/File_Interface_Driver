#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/printk.h>

MODULE_LICENSE("GPL");

#define DEVICE_NAME     "solution_node"
#define DEVICE_MAJOR    510
#define FIRST_MINOR     0
#define MAX_MINORS      1

/*Interface functions prototypes*/
static ssize_t read_interface (struct file *, char *, size_t, loff_t *);
static ssize_t write_interface (struct file *, const char *, size_t, loff_t *);
static int open_interface (struct inode *, struct file *);
static int release_interface (struct inode *, struct file *);

/*Global variables*/
int a, b, sum;
char a_buffer[10], b_buffer[10];

struct my_device_data 
{
    struct cdev cdev;
};

static struct my_device_data devs[MAX_MINORS];

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = read_interface,
    .write = write_interface,
    .open = open_interface,
    .release = release_interface
};

static int minor_count = 1;

static int __init init_solution(void)
{
    printk(KERN_INFO "Initialization of chrdev module started.\n");
    int err = register_chrdev_region(MKDEV(DEVICE_MAJOR, FIRST_MINOR), minor_count, DEVICE_NAME);
    if(err != 0)
    {
        printk(KERN_ALERT "Error of chrdev registration!\n");
        return err;
    }
    printk(KERN_INFO "Initialization of chrdev module ended.\n");

    int i;
    for(i = 0; i < MAX_MINORS; i++)
    {
        cdev_init(&devs[i].cdev, &fops);
        cdev_add(&devs[i].cdev, MKDEV(DEVICE_MAJOR, i), 1);
    }

    return 0;
}

static void __exit cleanup_solution(void)
{
    int i;
    for(i = 0; i < MAX_MINORS; i++)
    {
        cdev_del(&devs[i].cdev);
    }

    unregister_chrdev_region(MKDEV(DEVICE_MAJOR, 0), minor_count);
    printk(KERN_INFO "Cleanup chrdev module.\n");
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