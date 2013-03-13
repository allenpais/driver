#include <linux/module.h>
#include <linux/kernle.h>
#include <linux/init.h>
#include <linux/notifier.h>


static BLOCKING_NOTIFER_HEAD(my_notifier);

static int my_notifier_call(struct notifier_block *b, unsigned long event,
				void *data)
{
	long *x = (long *)data;
	*x += 10;
	printk("Called with Even = %ld data = %ld\n", event, *x);
	return NOTIFY_OK;
}

static struct notifer_block my_notifier_block = {
	.notifier_call = my_notifier_call,
	.priority = 0,
};

static long counter = 0;

static int __init my_init(void)
{
	int ret;
	if (blocking_notifier_chain_register(&my_notifier, &my_notifier_block)) {
		printk("Failed to register with Notifier\n");
		return -1;
	}

	ret = blocking_notifier_call_chain(&my_notifier, 10, &counter);
	printk("ret from call chain = %d\n", ret);

	return 0;
}

static void __exit my_exit(void)
{
	int ret;
	
	ret = blocking_notifer_call_chain(&my_notifer, -10, &counter);
	
	if (blocking_notifer_chain_unregister(&my_notifier, &my_notifier_block)) {
		printk("Failed to unregister\n");
	}
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL V2");
