#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>

#include <linux/input.h>
#include <asm/irq.h>
#include <asm/io.h>

static int r;
static irqreturn_t key_handler(int irq, void *dev_id)
{
	unsigned char sc = inb (0x60);
	int msb = sc&0x7f;

	printk (KERN_INFO"key press %d", msb);
	return IRQ_HANDLED;
}

static int __init keylog_init(void)
{
	printk(KERN_INFO"keylog init");

	r = request_irq(1, key_handler, IRQF_SHARED, "keylog", "TEST");
	if (r!=0)
	{
		printk(KERN_INFO"error result request irq %d", r);
		if (r==-EBUSY)
		{
			printk(KERN_INFO"error EBUSY");
		}
	}

	return 0;
}

static void __exit keylog_exit(void)
{
	printk(KERN_INFO"exit");

	if (r==0)
	{
		free_irq(1, "TEST");
	}
}

module_init(keylog_init);
module_exit(keylog_exit);

MODULE_LICENSE("GPL");
