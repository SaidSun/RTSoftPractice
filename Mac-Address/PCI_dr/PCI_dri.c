#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include "MyPCIDR/mypcidriverio.h"
MODULE_LICENSE("GPL");
u8 __iomem *hwmem = NULL;
static int c = 0;
static int major;
int pci_init_one(struct pci_dev *, const struct pci_device_id *);
void pci_remove_one(struct pci_dev *);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static long device_ioctl(struct file *, unsigned int, unsigned long);

static struct pci_device_id pci_tbl[] = {
    {PCI_DEVICE(0x10ec, 0xc821)},
    {0,}
};

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .unlocked_ioctl = device_ioctl 
};

MODULE_DEVICE_TABLE(pci, pci_tbl);

static struct pci_driver pci_device_driver = {
    .name = "NC",
    .id_table = pci_tbl,
    .probe = pci_init_one,
    .remove = pci_remove_one
};

int init_module(void){
    printk(KERN_INFO "I am ready!\n");
    return pci_register_driver(&pci_device_driver);
}

void cleanup_module(void){
    printk(KERN_INFO "I am sleep///\n");
    pci_unregister_driver(&pci_device_driver);
}

int pci_init_one(struct pci_dev *dev, const struct pci_device_id *id){
    printk(KERN_INFO "Started///\n");
    unsigned long mmio_start, mmio_len;

    mmio_start = pci_resource_start(dev, 2);
    mmio_len = pci_resource_len(dev, 2);

    if ((mmio_start == 0)||(mmio_len == 0)){
        printk(KERN_INFO "Failed///\n");
        return -1;
    }
    else{
        printk(KERN_INFO "OK\n");
    }

    hwmem = ioremap(mmio_start, mmio_len);
    major = register_chrdev(0, "MyPCI", &fops);

    if (hwmem == 0){
        return -EIO;
    };
    uint8_t data;
    unsigned long t = 0;
    while (t < mmio_len){
        data = ioread8(&hwmem[t]);
        if (data == 0x24){
            pr_info(KERN_INFO "MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", (unsigned int)data, (unsigned int)ioread8(&hwmem[t+1]), (unsigned int)ioread8(&hwmem[t+2]), (unsigned int)ioread8(&hwmem[t+3]),
            (unsigned int)ioread8(&hwmem[t+4]), (unsigned int)ioread8(&hwmem[t+5]));
            pr_info("t = %d", t);
        };
        t++;
    };

    return 0;
};

void pci_remove_one(struct pci_dev *dev){
    unregister_chrdev(major, "MyPCI");
};

static int device_open(struct inode *inode, struct file *file){
    try_module_get(THIS_MODULE);
    return 0;
};

static int device_release(struct inode *inode, struct file *file){
    module_put(THIS_MODULE);
    return 0;
};


static long device_ioctl(struct file * flip, unsigned int cmd, unsigned long arg){
    switch(cmd){
        case(GET_MAC):
            break;
    }
    return c;
};