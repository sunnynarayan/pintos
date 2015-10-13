#include <stdio.h>
#include <stdlib.h>
#include <random.h>
#include "../threads/thread.h"
#include "../threads/synch.h"
#define PRIORITY 13

struct semaphore* matches;
struct semaphore* tobbaco;
struct semaphore* paper;
struct semaphore* agent;

void agents();
void smoker1();// has matches
void smoker2();//has tobacco
void smoker3();//has paper
void test_lab5();

void agents(){
	while(1){
		sema_down(agent);
		int r = random_ulong()%3;
		if (r==0){
			//matches and tobacco produced
			sema_up(matches); sema_up(tobbaco);

		}else if(r==1){
			//paper and tobacco produced
			sema_up(paper); sema_up(tobbaco);
		}else if (r==2){
			//matches and paper produced
			sema_up(matches); sema_up(paper);
		}else{
			printf("%d is produced.\n", r);
		}
	}
}


void smoker1(){

	while(1){
		bool s1 = sema_try_down(matches); 
		bool s2 = sema_try_down(paper);
		if (s1 && s2)
		{
			printf("Smoker 1 is smoking \n");
			sema_up(agent);
		}
		else if (s1)
		{
			sema_up(matches);
		}
		else if (s2)
		{
			sema_up(paper);
		}
	}
}

void smoker2(){
	
	while(1){
		bool s1 = sema_try_down(tobbaco); 
		bool s2 = sema_try_down(matches);
		if (s1 && s2)
		{
			printf("Smoker 2 is smoking \n");
			sema_up(agent);
		}
		else if (s1)
		{
			sema_up(tobbaco);
		}
		else if (s2)
		{
			sema_up(matches);
		}
	}
}

void smoker3(){

	while(1){
		bool s1 = sema_try_down(tobbaco); 
		bool s2 = sema_try_down(paper);
		if(s1 && s2)
		{
			printf("Smoker 3 is smoking \n");
			sema_up(agent);
			
		}
		else if(s1)
		{
			sema_up(tobbaco);
		}
		else if(s2)
		{
			sema_up(paper);
		}
	}
}


void test_lab5(void){

	matches = (struct semaphore *)malloc(sizeof(struct semaphore));
	tobbaco = (struct semaphore *)malloc(sizeof(struct semaphore));
	paper = (struct semaphore *)malloc(sizeof(struct semaphore));
	
	agent = (struct semaphore *)malloc(sizeof(struct semaphore));

	sema_init(matches, 0);
	sema_init(tobbaco, 0);
	sema_init(paper, 0);
	sema_init(agent, 1);	
	thread_create("Agent",PRIORITY,&agents,"");

	thread_create("Man A",PRIORITY,&smoker1,"");
	thread_create("Man B",PRIORITY,&smoker2,"");
	thread_create("Man C",PRIORITY,&smoker3,"");
	
}