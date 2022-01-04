proc_t *p;
for (p = practive; p != NULL; p = p->p_next) {
	int pid = p->p_pidp->pid_id;
    int ppid = p->p_ppid;
}