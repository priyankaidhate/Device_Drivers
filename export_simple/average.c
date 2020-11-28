
#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");

static int Helloworld_add(int a,int b);

int a_test=10 ,b_test=20;

static int hello_init(void)
{
	int average;
	printk(KERN_ALERT"In init module .....the module parameter is %d\n",a_test);
	printk(KERN_ALERT"hello,world\n");
	average=Helloworld_add(a_test,b_test)/2;
	printk(KERN_ALERT"\nthe average is %d\n",average);
	return 0;
}
static void hello_exit(void)
{
	printk(KERN_ALERT"\nin cleaning module ..... the module parameter is %d\n",a_test);
	printk(KERN_ALERT"goodbye\n");
}

module_init(hello_init);
module_exit(hello_exit);

module_param(a_test,int,S_IRUGO);
module_param(b_test,int,S_IRUGO);
