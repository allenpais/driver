#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/gfp.h>


static struct kmem_cache *slub;

struct A {
	int a;
	int b;
};

struct A *st;

int slub_create_kmem(void)
{
	int ret = -1;
	slub = kmem_cache_create("slub-alloc", sizeof(struct A), 0, 0, NULL);
	if (slub != NULL) {
		printk("Successfully created kem for slub\n");
		ret = 0;
	}

	st = kmem_cache_alloc(slub, GFP_KERNEL);
	if (st != NULL) {
		printk("Allocation successful\n");
		ret = 0;
	}

	return ret;
}

static int __init slub_mod_init(void)
{
	int ret;
	printk("Slub lkm\n");
	ret = slub_create_kmem();
	return 0;
}

static void __exit slub_mod_exit(void)
{
	printk("Slub lkm exit\n");
	kmem_cache_free(slub, st);
	kmem_cache_destroy(slub);
}

module_init(slub_mod_init);
module_exit(slub_mod_exit);

MODULE_LICENSE("GPL");
