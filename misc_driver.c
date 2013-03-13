#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>

#define MYDEV_NAME	"misc_device"

static char *disk;
static size_t disk_size = (16 * PAGE_SIZE);

static const struct file_operations misc_drv_fops = {
	.owner = THIS_MODULE,
};

static struct miscdevice my_misc_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = MYDEV_NAME,
	.fops  = &misc_drv_fops,
};

static int __init my_init(void)
{
	disk = kmalloc(disk_size, GFP_KERNEL);
	if (misc_register(&my_misc_device)) {
		printk("Could not register misc device \n"
				"%d\n", my_misc_device.minor);
		return -EBUSY;
	}
	return 0;
}

static void __exit my_exit(void)
{
	misc_deregister(&my_misc_device);
	kfree(disk);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL V2");
