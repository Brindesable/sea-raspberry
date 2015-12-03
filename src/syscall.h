#ifndef SYSCALL_H
#define SYSCALL_H

#include <inttypes.h>
#include "sched.h"

void swi_handler();

void sys_reboot();
void do_sys_reboot();

void sys_nop();
void do_sys_nop();

void sys_settime(uint64_t date_ms);
void do_sys_settime(uint32_t * sp);

uint64_t sys_gettime();
void do_sys_gettime(uint32_t * sp);

void sys_yieldto(struct pcb_s * dest);
void do_sys_yieldto(uint32_t * sp);

#endif
