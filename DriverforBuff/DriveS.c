#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/wait.h>
#define maxMaga 50
MODULE_LICENSE("GPL");
static char msg[maxMaga];
static int count = 0;
static int Head = 0;
static int Tail = 0;
static char flag = 0;
static int Major;
static int Device_Open = 0;
static DECLARE_WAIT_QUEUE_HEAD(hd);
static DECLARE_WAIT_QUEUE_HEAD(wp);
struct module *owner;
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);

static struct file_operations fops = {
    .read = device_read,
    .open = device_open,
    .write = device_write,
    .release = device_release
};

static int device_open(struct inode *inode, struct file *file){
    static int counter = 0;
    try_module_get(THIS_MODULE);
    return 0;
};

static int device_release(struct inode *inode, struct file *file){
    Device_Open--;
    module_put(THIS_MODULE);
    return 0;
};

static ssize_t device_write(struct file *flip, const char *buffer1, size_t length1, loff_t * offset){
    int bytes_write = 0;
    int len1 = length1;
    while (len1){
        get_user(msg[Tail++], buffer1++);
        if (Tail > maxMaga-1){
            Tail = 0;
            count++;
        }
        len1--;
        bytes_write++;
        printk(KERN_INFO "%d", Tail);
    }
    flag = 1;
    wake_up_interruptible(&hd);
    wake_up_interruptible(&wp);
    printk(KERN_INFO "%d", flag);
    return bytes_write;
};

static ssize_t device_read(struct file *flip, char *buffer, size_t length, loff_t * offset){
    if (Tail == 0){
        wait_event_interruptible(hd, flag != 0);
    }
    printk(KERN_INFO "%d", flag);
    printk(KERN_INFO "Reading!");
    int bytes_read = 0;
    int len = length;
    wait_event_interruptible(wp, (Tail > Head) || (count > 0));
    while (len && ((Head != Tail) || count != 0)){
        put_user(msg[Head++], buffer++);
        len--;
        bytes_read++;
        printk(KERN_INFO "%d", Head);
        if (Head > maxMaga-1){
            Head = 0;
            count--;
        }
    }
    return bytes_read;
};


int init_module(void){
    Major = register_chrdev(0, "foo", &fops);
    if (Major < 0){
        printk(KERN_ALERT "Failed");
    }
    printk(KERN_INFO "mknod /dev/foo c %d 0", Major);
    return 0;
};

void cleanup_module(void){
    unregister_chrdev(Major, "foo");
    printk(KERN_ALERT "Cleanup_module OK");
}