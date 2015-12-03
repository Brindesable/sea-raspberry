#include "syscall.h"
#include "util.h"
#include "sched.h"

struct pcb_s pcb1, pcb2, pcb_kmain_process;
struct pcb_s *p1, *p2, *kmain_process, *current_process;

void sched_init()
{
	current_process = &pcb_kmain_process;
}

void kmain(void)
{
	/*sched_init();
	p1 = &pcb1;
	p2 = &pcb2;
	kmain_process = &pcb_kmain_process;

	p1->lr_svc = (uint32_t*) &user_process_1;
	p1->lr_user = (uint32_t*) &user_process_1;	
	p2->lr_svc = (uint32_t*) &user_process_2;	
	p2->lr_user = (uint32_t*) &user_process_2;

	__asm("mov r1,%0" : : "r"(p1): "r0");

	__asm("cps 0x10");
	sys_yieldto(p1);*/
}

//__asm("mov r0,%0" : : "r"(X));
//__asm("mov %0,r0" : "=r"(X));
//__asm("mov %0,r0":"=r"(var0): :"r0", "r1");
