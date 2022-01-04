#include <unordered_map>
#include <cstdint>
#include <pthread.h>
#include <algorithm>

class CVset {
public:
    CVset(uint64_t n_conds, pthread_mutex_t *mutex);
    int lock();
    int unlock();
    int wait(short *cond_set);
    int signal(short cond_id);

private:
    uint64_t n_conds;
    pthread_mutex_t *mutex;
    std::unordered_map<uint64_t, pthread_cond_t*> cond_map;
};