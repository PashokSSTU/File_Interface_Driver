#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>

MODULE_LICENSE("GPL");

int init_module(void)
{
    printk(KERN_INFO "Init file_interface_driver module.\n");
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Cleanup file_interface_driver module.\n");
}