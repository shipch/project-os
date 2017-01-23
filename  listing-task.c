#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Linux Kernel Module for Listing Tasks");
MODULE_AUTHOR("Chanakan Sukmetta");



int listing_task_init(void){

	struct task_struct *task;

	for_each_process(task){
		printk(KERN_INFO "pid: %d | state: %ld | pname: %s\n", task->pid, task->state, task->comm);
	}

	printk(KERN_INFO "Loading Module\n");
	return 0;
}

void listing_task_exit(void)
{
printk(KERN_INFO "Removing Module\n");
}

module_init(listing_task_init);
module_exit(listing_task_exit);

