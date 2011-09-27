#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

#include <linux/interrupt.h>

#define MY_IRQ	7


static irqreturn_t my_thfn(int irq)
{
	return IRQ_HANDLED;
}


int __init my_init(void)
{
	int ret;
	ret = request_threaded_irq(MY_IRQ, NULL, my_thfn,
			IRQF_TRIGGER_NONE, "my_dev", 0);

	if (!ret) 
		printk("request_threaded_irq failed\n");

}	

void __exit my_exit(void)
{
	free_irq(MY_IRQ, NULL);
}

module_init(my_init);
module_exit(my_exit);	
