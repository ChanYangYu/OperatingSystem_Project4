#include <pthread.h>

typedef struct SSU_Sem {
	int count;
	pthread_mutex_t sem_lock;
	struct thread_info *head;
	struct thread_info *tail;
} SSU_Sem;

struct thread_info{
	pthread_t thread_id;
	struct thread_info *next;
	struct thread_info *prev;
};

void SSU_Sem_init(SSU_Sem *, int);
void SSU_Sem_up(SSU_Sem *);
void SSU_Sem_down(SSU_Sem *);
