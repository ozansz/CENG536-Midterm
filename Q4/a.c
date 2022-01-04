struct task_struct *task;
for (task = &init_task ; (task = next_task(task)) != &init_task ; ) {
    int pid = task->pid;
    int ppid = task->real_parent->pid;
}