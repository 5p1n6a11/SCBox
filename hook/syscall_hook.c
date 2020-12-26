#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <linux/utsname.h>
#include <asm/pgtable.h>
#include <linux/kallsyms.h>

MODULE_DESCRIPTION("system call replace test module");
MODULE_AUTHOR("u2i");
MODULE_LICENSE("GPL");

static void **sys_call_table;

asmlinkage long (*orig_sys_uname)(struct old_utsname __user *buf);

asmlinkage long syscall_replace_sys_uname(struct old_utsname __user *buf)
{
    printk(KERN_INFO "[u2i] : uname system call hooked!\n");
    return orig_sys_uname(buf);
}

static void save_original_syscall_address(void)
{
    orig_sys_uname = sys_call_table[__NR_uname];
}

static void change_page_attr_to_rw(pte_t *pte)
{
    set_pte_atomic(pte, pte_mkwrite(*pte));
}

static void change_page_attr_to_ro(pte_t *pte)
{
    set_pte_atomic(pte, pte_clear_flags(*pte, _PAGE_RW));
}

static void replace_system_call(void *new)
{
    unsigned int level = 0;
    pte_t *pte;

    pte = lookup_address((unsigned long) sys_call_table, &level);
    /* Need to set r/w to a page which sys_call_table is in. */
    change_page_attr_to_rw(pte);

    sys_call_table[__NR_uname] = new;
    /* set back to read only */
    change_page_attr_to_ro(pte);
}

static int syscall_replace_init(void)
{
    sys_call_table = (void *) kallsyms_lookup_name("sys_call_table");
    pr_info("sys_call_table address is 0x%p\n", sys_call_table);

    save_original_syscall_address();
    pr_info("original sys_uname's address is 0x%p\n", orig_sys_uname);

    replace_system_call(syscall_replace_sys_uname);

    pr_info("system call replaced\n");
    return 0;
}

static void syscall_replace_cleanup(void)
{
    pr_info("cleanup");
    if (orig_sys_uname)
        replace_system_call(orig_sys_uname);
}

module_init(syscall_replace_init);
module_exit(syscall_replace_cleanup);
