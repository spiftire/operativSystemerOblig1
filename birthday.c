#include <linux/list.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/slab.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

LIST_HEAD(birthday_list);

struct birthday *set_person_birthday(int day, int month, int year)
{
	struct birthday *person_birthday;

	person_birthday = kmalloc(sizeof(*person_birthday), GFP_KERNEL);
	person_birthday->day = day;
	person_birthday->month = month;
	person_birthday->year = year;

	return person_birthday;
}

/* Entry point */

int linkedList_init(void) 
{

	printk(KERN_INFO "Creating list\n");

	struct birthday *person;
	
	person = set_person_birthday(30, 7, 1987);
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);
	person = set_person_birthday(18, 9, 1977);
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);
	person = set_person_birthday(22, 1, 2020);
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);
	person = set_person_birthday(15, 3, 1990);
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);
	person = set_person_birthday(12, 3, 1939);
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list, &birthday_list);

/* Traversing the list */

	printk(KERN_INFO "Traversing the birtday list\n");

	struct birthday *ptr;

	list_for_each_entry(ptr, &birthday_list, list) 
	{
		printk(KERN_INFO "BIRTHDAY: Day: %d Month: %d Year: %d\n",
			ptr->day,
			ptr->month,
			ptr->year);
	}
	return 0;
}

void linkedList_exit(void) 
{
	printk(KERN_INFO "Removing module\n");

	struct birthday *ptr, *next;

	list_for_each_entry_safe(ptr, next, &birthday_list, list) {
		printk(KERN_INFO "REMOVING BIRTHDAY: Day: %d Month: %d Year: %d\n",
			ptr->day,
			ptr->month,
			ptr->year);

		list_del(&ptr->list);
		kfree(ptr);
	}
}

module_init(linkedList_init);
module_exit(linkedList_exit);

MODULE_LICENSE("GROUP 9");
MODULE_DESCRIPTION("A list of birthdays");
MODULE_AUTHOR("Steffen Holanger");
