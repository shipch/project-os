#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Data Structure");
MODULE_AUTHOR("Chanakan Sukmetta");


static LIST_HEAD(birthday_list);

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

int birthday_init(void)
{
	struct birthday *person;
	int i=0;
	while (i<5){
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		person->day = 2+i+1;
		person->month = 8;
		person->year = 1995;
		INIT_LIST_HEAD(&person->list);
		list_add_tail(&person->list, &birthday_list);
		i++;
	}

	printk(KERN_INFO "Loading Module\n");
	printk(KERN_INFO "This list be constructed\n");
	
	list_for_each_entry(person, &birthday_list, list) {
		printk(KERN_INFO "Day: %d Month: %d Year: %d\n", person->day, person->month, person->year);
	}

	return 0;
}	

void birthday_exit(void)
{
	struct birthday *person, *next;
	list_for_each_entry_safe(person, next, &birthday_list, list) {
		list_del(&person->list);
		kfree(person);
	}

	printk(KERN_INFO "Removing Module\n");
}

module_init(birthday_init);
module_exit(birthday_exit);