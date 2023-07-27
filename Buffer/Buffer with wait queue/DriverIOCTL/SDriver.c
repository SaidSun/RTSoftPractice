#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/wait.h>
#include "MyDR/mydriverio.h"
MODULE_LICENSE("GPL");
static int count = 0;
struct module *owner;
static int Major;
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static long device_ioctl(struct file *, unsigned int, unsigned long);
static int tms = 100;
struct task_struct *ts;

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .unlocked_ioctl = device_ioctl 
};

int f_thread(void* data){
    while(1){
        count++;
        printk(KERN_INFO "%d", count);
        msleep(tms);
        if (kthread_should_stop()){
            break;
        }
    }
    return 0;
}
int init_module(void){
    ts = kthread_run(f_thread, NULL, "foo kthr");
    Major = register_chrdev(0, "foo", &fops);
    if (Major < 0){
        printk(KERN_ALERT "Failed");
    }
    printk(KERN_INFO "mknod /dev/foo c %d 0", Major);
    printk(KERN_INFO "Thread start///");
    return 0;
};



static int device_open(struct inode *inode, struct file *file){
    static int counter = 0;
    try_module_get(THIS_MODULE);
    return 0;
};




static int device_release(struct inode *inode, struct file *file){
    module_put(THIS_MODULE);
    return 0;
};

static long device_ioctl(struct file * flip, unsigned int cmd, unsigned long arg){
    switch (cmd){
        case MYDRIVER_NULL:
            count = 0;
            printk(KERN_INFO "NULL");
            break;
        case MYDRIVER_GET:
            printk(KERN_INFO "GET");
            copy_to_user(arg, &count, sizeof(int));
            break;
        case MYDRIVER_SET:
            copy_from_user(&tms, arg, sizeof(int));
            printk(KERN_INFO "%lu", tms);
            break;
    }
    return count;
};
void cleanup_module(void){
    kthread_stop(ts);
    unregister_chrdev(Major, "foo");
    printk(KERN_ALERT "Cleanup_module OK, Thread is stopped/");
}