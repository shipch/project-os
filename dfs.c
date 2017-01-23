#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

//create

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Iterating over Tasks with a Depth-First Tree");
MODULE_AUTHOR("Chanakan Sukmetta");


void dfs_list(struct task_struct *task){

	struct task_struct *another_task;
	struct list_head *list;

	list_for_each(list, &init_task->children){
		another_task = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO "pid: %d | state: %ld | pname: %s\n", another_task->pid, another_task->state, another_task->comm);
		dfs_list(another_task);
	}

}

int dfs_init(void){

	printk(KERN_INFO "Loading Module\n");
	dfs_list(&init_task);
	return 0;
}

void dfs_exit(void)
{
printk(KERN_INFO "Removing Module\n");
}

module_init(dfs_init);
module_exit(dfs_exit);

