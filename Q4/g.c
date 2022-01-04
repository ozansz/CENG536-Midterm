struct files_struct *files = current->files;

for (size_t index = 0; index < files->next_fd; index++) {
    struct file *fd = files->fd[index]; 

    if ((NULL == fd) || (fd->f_count == 0))
        continue;

    struct dentry *dentry = file_dentry(fd);
    dentry->d_inode->i_count--;
    dentry->d_count--;

    fd->f_inode->i_count--; 
    fd->f_count--;
}

if (files->fd != files->fd_array) {
    // Open file count was greater than NR_OPEN_DEFAULT
    // so the kernel had allocated another array

    kfree(files->fd);
    files->fd = files->fd_array;
}

for (size_t index = 0; index < NR_OPEN_DEFAULT; index++)
    files->fd = NULL;

files->next_fd = 0;
files->count = 0;