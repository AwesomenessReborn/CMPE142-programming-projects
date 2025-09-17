// seconds_module.c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/jiffies.h> // Required for jiffies and HZ

#define PROC_NAME "seconds"
#define BUFFER_SIZE 128

static unsigned long start_jiffies;

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {
    int rv = 0;
    char buffer[BUFFER_SIZE];
    static int completed = 0;
    unsigned long elapsed_seconds;

    if (completed) {
        completed = 0;
        return 0;
    }

    completed = 1;

    elapsed_seconds = (jiffies - start_jiffies) / HZ;

    rv = sprintf(buffer, "Seconds elapsed: %lu\n", elapsed_seconds);

    if (copy_to_user(usr_buf, buffer, rv)) {
        rv = -EFAULT;
    }

    return rv;
}

static const struct proc_ops proc_ops = {
    .proc_read = proc_read,
};

int proc_init(void) {
    start_jiffies = jiffies;

    proc_create(PROC_NAME, 0666, NULL, &proc_ops);
    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
    return 0;
}

void proc_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Seconds Elapsed /proc Module");
MODULE_AUTHOR("SGG");
