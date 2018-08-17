#include <linux/init.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/utsname.h>

// Custom functions.
void uptime(void);
void getSystemInfo(void);

// This function is called when the module is loaded.
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
       uptime();
       getSystemInfo();
       return 0;
}

// This function is called when the module is removed.
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}


// This functions gets the uptime
void uptime() {
  printk("Uptime: %i\n", jiffies_to_msecs(get_jiffies_64())/1000);
}


// This function gets the general system information
void getSystemInfo(){  
  struct new_utsname *buf;
  buf = utsname();

  printk("Nodename: %s\n",buf->nodename);
  printk("Machine: %s\n",buf->machine);
  printk("Sysname: %s\n",buf->sysname);
  printk("Release: %s\n",buf->release);
  printk("Version: %s\n",buf->version);
#ifdef __linux__
  printk("Domain Name: %s\n", buf->domainname); // GNU extension
#endif
}


/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

