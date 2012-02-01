/*
 * blah blah copyright goes here
 *
 * Shamelessly ripped from:
 *  The Linux Kernel Module Programming Guide
 *  4.1. Character Device Drivers
 *  http://tldp.org/LDP/lkmpg/2.6/html/lkmpg.html#AEN569
 *
 */

#include "four.h"

MODULE_LICENSE("GPL");

/*
 * might move this stuff to a .h later
 */

#define SUCCESS     0
#define DEVICE_NAME "four"
#define FOUR        4

static int Major;
static int Device_Open;

const struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static struct class *four_class;

int init_module(void)
{
	struct device *err_dev;
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if (Major < SUCCESS) {
		printk(KERN_ALERT "Failed to register dev %s with %d\n",
					DEVICE_NAME, Major);
		return Major;
	} else {
		four_class = class_create(THIS_MODULE, DEVICE_NAME);
		err_dev = device_create(four_class, NULL, MKDEV(Major, 0),
					 NULL, DEVICE_NAME);
		printk(KERN_INFO "Registered dev %s with %d\n",
					DEVICE_NAME, Major);
	}
	return SUCCESS;
}

void cleanup_module(void)
{
	device_destroy(four_class, MKDEV(Major, 0));
	class_unregister(four_class);
	class_destroy(four_class);
	unregister_chrdev(Major, DEVICE_NAME);
}

static int device_open(struct inode *inode, struct file *file)
{
	if (Device_Open)
		return -EBUSY;

	Device_Open++;
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{
	Device_Open--;

	module_put(THIS_MODULE);

	return SUCCESS;
}

static ssize_t device_read(struct file *filp,
			char *buffer,
			size_t length,
			loff_t *offset)
{
	int t_len = length;
	while (length) {
		put_user(FOUR, buffer++);
		length--;
	}
	return t_len;
}

static ssize_t device_write(struct file *filp,
			const char *buff,
			size_t len,
			loff_t *off)
{
	return len;
}
