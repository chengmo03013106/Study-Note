#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
static void * spawn_thread_start( void * args) {
	int status;
	pid_t pid, retpid;
	while(1) {
		pid = fork();
		if ( pid == 0 ) {
			int count = 0;
			while( count ++ < 5) {
				printf("segmentd running ... %d seconds\n",count);
				sleep(1);
			}
			printf("segmentd bye %d seconds\n",getpid());
			return NULL;
			if( *(int*)args == 1) {
				printf("[%ld]%d running...\n",syscall(SYS_gettid),*(int*)args);
			}
			if( *(int*)args == 2) {
				printf("[%ld]%d running...\n",syscall(SYS_gettid),*(int*)args);
				while(1);
			}
		} else if ( pid < 0 ){
			perror("fork");
			return NULL;
		} else {
			printf("New process %d run.\n",pid);
			sleep(10);
		}
	}
	printf("spawn_thread_start: %d process eixt.\n",pid);
}


static void * wait_thread_start( void * args) {
	int status;	
	pid_t retpid;
	printf("wait_thread_start run\n");
	pid_t pid = fork();
	while(1) {
		if( pid == 0) {
			sleep(1);
			printf("undefined %d -- %d exit\n",getppid(),getpid());
			exit(EXIT_SUCCESS);
		} else if (pid < 0) {
			perror("fork()");
			return NULL;
		}
		printf("undefined %d run\n", pid);
		if( 0 > (retpid = wait(&status)) ) {
			printf("wait_thread_start:waitpid error %s\n", strerror(errno));
		} else if( retpid == pid ){
			printf("undefined process %d exit. Do check alive\n", retpid);
			pid = fork();
		} else {
			printf("segmentd process %d exit.\n", retpid);
		}
	}

	return NULL;
#if 0
		if( *(int*)args == 1) {
			printf("[%ld]%d running...\n",syscall(SYS_gettid),*(int*)args);
			while(1)
				sleep(60);
		}
		if( *(int*)args == 2) {
			printf("[%ld]%d running...\n",syscall(SYS_gettid),*(int*)args);
			while(1);
		}
#endif
	}

#define handle_error_en(en, msg) \
	do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
typedef void*(*MenuFun)(void*);

int main( int ac, char ** av) {
	int s, tnum, opt, num_threads;
 	pthread_t tid[2];
	int no[2]={1,2};
	void * res;
	int stack_size = 65536;
	pthread_attr_t attr;
	s = pthread_attr_init(&attr);
	if (s != 0)
		handle_error_en(s, "pthread_attr_init");

	if (stack_size > 0) {
		s = pthread_attr_setstacksize(&attr, stack_size);
		if (s != 0)
			handle_error_en(s, "pthread_attr_setstacksize");
	}
	//MenuFun funcs[] = {wait_thread_start, spawn_thread_start};
	MenuFun funcs[] = {spawn_thread_start, wait_thread_start};

	for ( int i = 0; i < 2; ++i) {
		s = pthread_create(&tid[i],&attr,funcs[i],&no[i]);
		sleep(1);
		if (s != 0)
			handle_error_en(s, "pthread_create");
	}

	for ( int i = 0; i < 2; ++i) {
		s = pthread_join(tid[i], &res);
		printf("Joined with thread %d;\n", i);
	}
	printf("[%ld] main running...\n",syscall(SYS_gettid));
	while(1);

	return 0;

}
