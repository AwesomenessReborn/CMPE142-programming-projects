// simple.c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>     // Required for GOLDEN_RATIO_PRIME
#include <linux/gcd.h>      // Required for gcd()
#include <linux/jiffies.h>  // Required for jiffies and HZ

/* This function is called when the module is loaded. */
int simple_init(void)
{
    printk(KERN_INFO "Loading Kernel Module\n");

    // Project II, Step 1: Print GOLDEN_RATIO_PRIME
    // Note: Changed %lu to %llu to match the type and fix the compiler warning.
    printk(KERN_INFO "GOLDEN_RATIO_PRIME: %llu\n", GOLDEN_RATIO_PRIME);

    // Project II, Step 1 (jiffies/HZ part): Print jiffies and HZ
    printk(KERN_INFO "Initial jiffies: %lu\n", jiffies);
    printk(KERN_INFO "HZ value: %d\n", HZ);

    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
    unsigned long a = 3300;
    unsigned int b = 24;

    printk(KERN_INFO "Removing Kernel Module\n");

    // Project II, Step 2: Print gcd(3300, 24)
    printk(KERN_INFO "The GCD of %lu and %u is %lu\n", a, b, gcd(a, b));

    // Project II, Step 2 (jiffies/HZ part): Print jiffies
    printk(KERN_INFO "Final jiffies: %lu\n", jiffies);
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module with Project II Modifications");
MODULE_AUTHOR("SGG");