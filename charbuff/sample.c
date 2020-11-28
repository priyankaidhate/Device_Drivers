#include<linux/init.h>
#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/kernel.h>
#include<linux/circ_buf.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("DD");

# define SIZE 32
static dev_t devnum;
static struct cdev _cdev;
static struct circ_buf cbuf;

static int sample_open(struct inode *inodep,struct file *filep)
{
	printk("sample open function\n");
	return 0;
}
static int sample_release(struct inode *inodep,struct file *filep)
{
        printk("sample close function\n");
        return 0;
}  

static ssize_t sample_read(struct file *filep,char __user *ubuff,size_t cnt, loff_t *offset)
{
	int i;
	int ret;
	int mini;

	mini = min(cnt,(size_t)CIRC_CNT(cbuf.head,cbuf.tail,SIZE)) ;
	printk("size from userspace for read:%d\n",(int)cnt);
	for (i=0;i<mini ;i++)
	{
		ret = copy_to_user(ubuff+i,cbuf.buf+cbuf.tail,1);
	if(ret)
	{
		printk("error copying to user\n");
		return -EFAULT;
	}
	printk("copied %c to user \n",cbuf.buf[cbuf.tail]);
	cbuf.tail = (cbuf.tail+1)&(SIZE-1);
}
	return i;
}

static ssize_t sample_write(struct file *filep,const char __user *ubuff,size_t cnt,loff_t *offset)
{
	int ret,i;
	printk("size sent from userspace %d\n",(int)cnt);
	for(i=0;i<cnt;i++)
	{
		copy_from_user(cbuf.buf+cbuf.head,ubuff+i,1);
		if(ret)
		{
			printk("error copying\n");
			return -EFAULT;
		}
		printk("copied form user %c\t",cbuf.buf[cbuf.head]);
		cbuf.head - (cbuf.head +1) &(SIZE -1); 
	}
	return i;
}


struct file_operations fops={
	.open =sample_open,
	.release =sample_release,
	.read =sample_read,
	.write =sample_write,
};

static int sample_init(void)
{
	int ret;
	devnum= MKDEV(42,0);
	ret = register_chrdev_region(devnum,1,"sample_dev");

	if(ret)
	{
		printk("kernel did not grant us device number\n");
		return ret;
	}

	cdev_init(&_cdev,&fops);
	
	cbuf.buf = kmalloc(SIZE,GFP_KERNEL);
        if(!cbuf.buf){
	       printk("memory is not allocated\n");
	       unregister_chrdev_region(devnum,1);
	       return -1;
	}	       

	ret = cdev_add(&_cdev,devnum,1);
	if(ret)
	{
		printk("unable to add cdev to kernel\n");
		kfree(cbuf.buf);
		unregister_chrdev_region(devnum,1);
		return ret;
	}
	printk("Done init\n");
	return 0;
}

static void sample_exit(void)
{
	cdev_del(&_cdev);
	kfree(cbuf.buf);
	unregister_chrdev_region(devnum,1);
	printk("Goodbye\n");
}

module_init(sample_init);
module_exit(sample_exit);


