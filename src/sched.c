#include "sched.h"
#include "syscall.h"

struct pcb_s *current_process;
extern struct pcb_s *p1, *p2, *kmain_process, *current_process;

void user_process_1()
{
	int v1 = 5;
	while(1)
	{
		v1++;
		sys_yieldto(p2);
	}
}

void user_process_2()
{
	int v1 = -12;
	while(1)
	{
		v1 -= 2;
		sys_yieldto(p1);
	}
}
