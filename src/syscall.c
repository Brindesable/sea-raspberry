#include "hw.h"
#include "sched.h"
#include "syscall.h"
#include "util.h"

extern struct pcb_s *p1, *p2, *kmain_process, *current_process;

void swi_handler()
{
	__asm("stmfd sp!, {r0-r12, lr}");
	uint32_t * sp = 0;	
	__asm("mov %0, sp":"=r"(sp));		
	
	int sys_call = 0;
	__asm("mov %0, r0":"=r"(sys_call) : : "sp");

	//sp -= 4;
	
	switch(sys_call)
	{
		case 1 :
			do_sys_reboot();
			break;
		case 2 :
			do_sys_nop();
			break;
		case 3 : 
			do_sys_settime(sp);
			break;
		case 4 :
			do_sys_yieldto(sp);
			break;
		default :
			PANIC();
	}
	
	__asm("ldmfd sp!, {r0-r12, pc}^");
}

void sys_reboot()
{
	__asm("mov r0, #1");
	__asm("SWI #0");
}

void do_sys_reboot()
{
	__asm("mov pc, #0");
}

void sys_nop()
{
	__asm("mov r0, #2");
	__asm("SWI #0");
}

void do_sys_nop()
{
}

void sys_settime(uint64_t date_ms)
{
	__asm("mov r1,%0" : : "r"(date_ms >> 32): "r0");
	__asm("mov r2,%0" : : "r"(date_ms) : "r0", "r1");
	__asm("mov r0, #3");	
	__asm("SWI #0");
}

void do_sys_settime(uint32_t * sp)
{
	/*uint64_t time;
	time = *(sp+4);
	time = time << 32;
	time &= 0xffffffff00000000;
	time += *(sp+8) & 0x00000000ffffffff;

	set_date_ms(time);*/
}

uint64_t sys_gettime(uint64_t date_ms)
{
	__asm("mov r0, #3");	
	__asm("SWI #0");
	uint64_t r0, r1;
	__asm("mov %0, r0":"=r"(r0) : : "r0", "r1");
	__asm("mov %0, r1":"=r"(r1) : : "r0", "r1");
	uint64_t time;
	time = r0;
	time = time << 32;
	time &= 0xffffffff00000000;
	time += r1 & 0x00000000ffffffff;
	return time;
}

void do_sys_gettime(uint32_t * sp)
{
	/*uint64_t time = ;
	
	time = *(sp+4);
	time = time << 32;
	time &= 0xffffffff00000000;
	time += *(sp+8) & 0x00000000ffffffff;*/
}

void sys_yieldto(struct pcb_s* dest)
{
	__asm("mov r2,%0" : : "r"(dest): "r0");
	__asm("mov r3, lr" : : : "r0", "r2");
	__asm("mov r0, #4");	
	__asm("SWI #0");
}

void do_sys_yieldto(uint32_t * sp)
{
	int i = 0;
	for(i = 0; i < 13; i++)
	{
		current_process->reg[i] = (uint32_t*) *(sp+i);
	}
	current_process->lr_svc = (uint32_t*) *(sp+13);
	current_process->lr_user = (uint32_t*) *(sp+3);

	for(i = 0; i < 13; i++)
	{
		*(sp+i) = (uint32_t) ((struct pcb_s*)(current_process->reg[2]))->reg[i];
	}
	*(sp+13) = (uint32_t) ((struct pcb_s*)(current_process->reg[2]))->lr_user;

	current_process = (struct pcb_s *) current_process->reg[2];
}
