.section .data
    msg: .asciz "Hello, World!\n"

.section .text
    .global _start


#Syscall	O que faz? chama os kernels:
#1	write (escrever no terminal)
#60	exit (sair do programa)
#0	read (ler do teclado)
#2	open (abrir um arquivo)


_start:
    mov $1, %rax            # syscall wirte
    mov $1, %rdi            # stdout

    #carrega o endereco de memora
    #rip ponteiro de instrucao
    #rsi quarda ponteiro
    lea msg(%rip), %rsi     # Ponteiro para a mensagem

    #rdx data register
    mov $15, %rdx        # Tamanho correto da mensagem
    syscall

    mov $60, %rax        # syscall: exit
    xor %rdi, %rdi       # Código de saída 0

    syscall
