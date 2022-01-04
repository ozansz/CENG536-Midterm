void ptree(struct task_struct *p) {
    struct task_struct *c;
    list_for_each_entry(c, &p->children, sibling) {
        ptree(c);
        do_something(c);
    }
}