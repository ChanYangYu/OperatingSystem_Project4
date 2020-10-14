#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define UNUSED 0
#define READ 1
#define WRITE 2
struct rw_lock
{
	int mode;
	int reader_num;
	int wait_writer;
	pthread_mutex_t ref_mode;
};

void init_rwlock(struct rw_lock * rw);
void r_lock(struct rw_lock * rw);
void r_unlock(struct rw_lock * rw);
void w_lock(struct rw_lock * rw);
void w_unlock(struct rw_lock * rw);
long *max_element(long* start, long* end);
long *min_element(long* start, long* end);
