#include "rw_lock.h"

void init_rwlock(struct rw_lock * rw)
{
	rw->mode = UNUSED;
	rw->reader_num = 0;
	rw->wait_writer = 0;
	pthread_mutex_init(&rw->ref_mode, NULL);
}

void r_lock(struct rw_lock * rw)
{
	while(1){
		pthread_mutex_lock(&rw->ref_mode);
		if(rw->mode != WRITE){
			if(rw->wait_writer == 0){
				rw->mode = READ;
				rw->reader_num++;
				pthread_mutex_unlock(&rw->ref_mode);
				return;
			}
		}
		pthread_mutex_unlock(&rw->ref_mode);
	}
}

void r_unlock(struct rw_lock * rw)
{
	rw->reader_num--;
	if(rw->reader_num == 0)
		rw->mode = UNUSED;
}

void w_lock(struct rw_lock * rw)
{
	int check = 0;
	while(1)
	{
		pthread_mutex_lock(&rw->ref_mode);
		//wait_writer count ++ at first time
		if(check == 0){
			rw->wait_writer++;
			check = 1;
		}
		if(rw->mode == UNUSED){
			rw->mode = WRITE;
			pthread_mutex_unlock(&rw->ref_mode);
			return;
		}
		pthread_mutex_unlock(&rw->ref_mode);
	}
}

void w_unlock(struct rw_lock * rw)
{
	rw->mode = UNUSED;
	rw->wait_writer--;
}
