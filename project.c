#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<semaphore.h>

int c=0,a1=0,a2=0,a3=0;
sem_t x;
struct sharedtable
{
int pen;

int paper;

int qp;

};

void *S1(void *p)
{
sem_wait(&x);
struct sharedtable *s = (struct sharedtable*)p;
s->pen+=1;
if(s->pen==0||s->paper==0||s->qp==0)
{
	s->pen-=1;
 sem_post(&x);

wait();
}
else

{
printf("1st student completed the task\n");
a1=1;
c++;
s->pen=0;
s->qp=0;
s->paper=0;

}

sem_post(&x);
}

void *S2(void *p)
{ 
sem_wait(&x);

struct sharedtable *s = (struct sharedtable*)p;
s->paper+=1;
if(s->pen==0||s->paper==0||s->qp==0) 
{	s->paper-=1;
	sem_post(&x);
	
	wait();
}
else
{
printf("2nd student completed the task\n");
a2=1;
c++;
s->qp=0;
s->paper=0;
s->pen=0;

}

sem_post(&x);
}

void *S3(void *p)
{
sem_wait(&x);

struct sharedtable *s = (struct sharedtable*)p;
s->qp+=1;
if(s->pen==0||s->paper==0||s->qp==0)
{	s->qp-=1;
	sem_post(&x);
	wait();
}
else
{
printf("3rd student completed the task\n");
a3=1;
c++;
s->qp=0;
s->pen=0;
s->paper=0;
}

sem_post(&x);

}

void main()

{

sem_init(&x,0,2);
int a;

pthread_t t1,t2,t3;

struct sharedtable s;

s.pen=0;

s.paper=0;

s.qp=0;

//pthread_create(&t1,NULL,S1,&s);

//pthread_create(&t2,NULL,S2,&s);

//pthread_create(&t3,NULL,S3,&s);

while(c!=3)

{

printf("Enter the things you want to place in the shared table\n")
;
printf("Enter 1 for Pen and paper\n");

printf("Enter 2 for pen and qustion paper\n");

printf("Enter 3 for paper and question paper\n");

scanf("%d",&a);

switch(a)

{

case 1:

{

s.pen=1;
s.paper=1;
break;

}

case 2:

{

s.pen=1;
s.qp=1;
break;

}


case 3:

{

s.paper=1;
s.qp=1;
break;

}
default:
exit(0);

}
if(a1 != 1)
pthread_create(&t1,NULL,S1,&s);
if(a2 != 1)
pthread_create(&t2,NULL,S2,&s);
if(a3 != 1)
pthread_create(&t3,NULL,S3,&s);

if(a1 != 1)
pthread_join(t1,NULL);

if(a2 != 1)
pthread_join(t2,NULL);

if(a3 != 1)
pthread_join(t3,NULL);


}

printf("All students completed the task!!!");

}
