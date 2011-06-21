#include <linux/init.h>
#include <linux/kernel.h>

int __init my_init(void)
{
	printk("Hello github\n");
	return 0;
}

void __exit my_exit(void)
{
	printk("Good Bye github\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Allen Pais");
