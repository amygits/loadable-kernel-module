/** 
* Purpose: An LMK that displays details of the processes 
* (with parent and child) executing in the kernel
*
* Completion time: 8 hours
* 
* @author Amy Ma
* @version 09/06/2021
*
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/list.h>

static int userInput = 1500;
module_param(userInput, int, 0660);
/* This function is called when the module is loaded. */
int simple_init(void)
{
	
       struct list_head *p;
       struct task_struct entryList;
       printk(KERN_INFO "\n-----------Loading Module-----------\n");
       printk(KERN_WARNING "PID's greater than: %d", userInput);
       
      struct task_struct *task;
    	for_each_process(task)
    	{	
    		// if the task instance's PIDD is greater than the user's input (int)
    		if (task->pid > userInput) {
    			// task details
    			printk("\nPROCESS\tPID\tSTATE\tPRIO\tST_PRIO\tNORM_PRIO\n");
    			printk("%.7s\t%d\t%li\t%d\t%d\t%d\n",
	    			task->comm, 
	    			task->pid, 
	    			task->state, 
	    			task->prio, 
	    			task->static_prio, 
	    			task->normal_prio);
	    		// Parent details
    			printk("PARENT:\n");
    			printk("%.7s\t%d\t%li\t%d\t%d\t%d\n",
	    			task->parent->comm, 
	    			task->parent->pid, 
	    			task->parent->state, 
	    			task->parent->prio, 
	    			task->parent->static_prio, 
	    			task->parent->normal_prio);
    			/* for each child in list_head of task struct instance */
    			list_for_each(p, &(task->children)){
    				entryList = *list_entry(p, struct task_struct, sibling);
    				printk("CHILD:\n");
    				printk("%.7s\t%d\t%li\t%d\t%d\t%d\n",
	    			entryList.comm, 
	    			entryList.pid, 
	    			entryList.state, 
	    			entryList.prio, 
	    			entryList.static_prio, 
	    			entryList.normal_prio);
    			}
    		}
    	}
       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {

	printk(KERN_INFO "-----------Removing Module-----------\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LMK");
MODULE_AUTHOR("Amy Ma (amyma1@asu.edu)");

