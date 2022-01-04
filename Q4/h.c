uf_info_t *fip = P_FINFO(p);

for (int fd = 0; fd < fip->fi_nfiles; fd++) {
    uf_entry_t *ufp = fip->f_list[fd];
    file_t *fp = ufp->uf_file;

    if (NULL == fp)
        continue;

    fp->f_vnode->v_op->vop_close(fp->f_vnode, fp->f_flag, fp->f_count, fp->f_offset, fp->f_cred, NULL);

    if (fp->f_vnode->v_count == 1)
        fp->f_vnode->v_op->vop_inactive(fp->f_vnode, fp->f_cred, NULL);

    ufp->uf_file = NULL;
    ufp->uf_flag = 0;
    fp->f_count--;
}

fip->fi_nfiles = 0;