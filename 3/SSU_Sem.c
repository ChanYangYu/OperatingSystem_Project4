#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include "SSU_Sem.h"

void signal_handler(int signo)
{
	if(signo == SIGUSR1)
		return;
	else{
		fprintf(stderr,"ERROR : wrong signal\n");
		exit(1);
	}
}

void SSU_Sem_init(SSU_Sem *s, int value) {
	s->count = value;
	pthread_mutex_init(&s->sem_lock, NULL);
	s->head = NULL;
	s->tail = NULL;
}

void SSU_Sem_down(SSU_Sem *s) {
	struct thread_info *new;

	pthread_mutex_lock(&s->sem_lock);
	s->count--;
	if(s->count < 0){
		new = (struct thread_info *)malloc(sizeof(struct thread_info));
		new->thread_id = pthread_self();
		//link initialize
		new->next = NULL;
		new->prev = NULL;

		//is_empty
		if(s->head == NULL && s->tail == NULL){
			s->head = new;
			s->tail = new;
		}
		else{
			//double link
			s->tail->next = new;
			new->prev = s->tail;
			s->tail = new;
		}
		pthread_mutex_unlock(&s->sem_lock);
		signal(SIGUSR1, signal_handler);
		//wait the signal
		pause();
	}
	else
		pthread_mutex_unlock(&s->sem_lock);
}

void SSU_Sem_up(SSU_Sem *s) {
	struct thread_info *cur;
	pthread_t tid;

	pthread_mutex_lock(&s->sem_lock);
	s->count++;

	//if wait thread exist
	if(s->head != NULL){
		tid = s->head->thread_id;
		//when there is only one thread
		if(s->head == s->tail){
			cur = s->head;
			s->head = NULL;
			s->tail = NULL;
			free(cur);
		}
		else{
			cur = s->head;
			s->head = s->head->next;
			//disconnect prev link
			s->head->prev = NULL;
			free(cur);
		}
		//send the signal 
		pthread_kill(tid, SIGUSR1);
		pthread_mutex_unlock(&s->sem_lock);
	}
	else
		pthread_mutex_unlock(&s->sem_lock);
}
