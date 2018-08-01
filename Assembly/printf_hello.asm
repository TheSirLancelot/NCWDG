BITS 32
global main                     ;since we're linking with c libraries
extern printf                   ;tells linker that this is elsewhere

section .data
    msg db "Hello world", 10, 0 ;message to printf

section .text

main:
    pushad                      ;push all registers to the stack
    push dword msg              ;push our message
    call printf
    add esp, 4                  ;clear our msg off the stack
    popad                       ;return registers back to normal
    ret
