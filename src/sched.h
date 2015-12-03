#ifndef SCHED_H
#define SCHED_H

#include <inttypes.h>

extern struct pcb_s *current_process;

struct pcb_s
{
	uint32_t * reg[12];
	uint32_t *pc;
	uint32_t *lr_svc;
	uint32_t *lr_user;
	uint32_t * sp;
};

void user_process_1();
void user_process_2();

#endif
