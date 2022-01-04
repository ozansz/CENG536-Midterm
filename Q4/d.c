void _ptree_child(proc_t *p) {
    if (NULL == p)
        return;

    _ptree_child(p->p_child);
    _ptree_child(p->p_sibling);

    do_something(p);
}

void ptree(proc_t *p) {
    if (NULL == p)
        return;

    _ptree_child(p->p_child);
}