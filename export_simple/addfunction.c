#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>


MODULE_LICENSE("GPL");

int Helloworld_type=1;

static int Helloworld_add(int a,int b);

static int hello_init(void)

{
	printk(KERN_ALERT"\n init module .....the module parameter is %d\n ",Helloworld_type);
        printk(KERN_ALERT"\n hello ,world");
	return 0;
}
int Helloworld_add(int a ,int b)
{
	printk(KERN_ALERT"\n in function Helloworld_add of module .....add\n");
	return(a+b);
}

EXPORT_SYMBOL_GPL(Helloworld_add);

static void hello_exit(void)
{
	printk(KERN_ALERT"\n in clean module ......the module parameter is %d\n",Helloworld_type);
	printk(	KERN_ALERT"\n goodbye\n");
}
module_init(hello_init);
module_exit(hello_exit);

