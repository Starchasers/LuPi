/**/

.section .init
.globl _start
_start:

b main


.section .text
main:

/*
* Set the stack point to 0x8000.
*/
mov sp,#0x8000

bl run

/*LowLevel Utility functions*/

.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.globl GET32
GET32:
    ldr r0,[r0]
    bx lr

.globl dummy
dummy:
    bx lr


