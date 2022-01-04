#include "cvset.h"

CVset::CVset(uint64_t n_conds, pthread_mutex_t *mutex) {
    this->n_conds = n_conds;
    this->mutex = mutex;
}

int CVset::wait(short *cond_set) {
    uint64_t cond_set_mask = 0;

    for (uint64_t i = 0; i < this->n_conds; i++)
        cond_set_mask = cond_set_mask << 1 + (cond_set[i] ? 1 : 0);

    pthread_cond_t *cv = new pthread_cond_t;
    
    // Assume that the proper error checks have beed done here.
    pthread_cond_init(cv, NULL);

    this->cond_map[cond_set_mask] = cv;

    return pthread_cond_wait(cv, this->mutex);
}

int CVset::signal(short cond_id) {
    for (std::unordered_map<uint64_t, pthread_cond_t*>::iterator it = this->cond_map.begin(); it != this->cond_map.end(); it++)
        if (it->first && (cond_id ? 1 : 0))
            return pthread_cond_signal(it->second);

    return EINVAL;
}

int CVset::lock() {
    return pthread_mutex_lock(this->mutex);
}

int CVset::unlock() {
    return pthread_mutex_unlock(this->mutex);
}
