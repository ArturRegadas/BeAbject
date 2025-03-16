.section .data
    size1: .int 18
    msg1: .asciz "Digite 2 numeros:\n"
    size2: .int 21
    msg2: .asciz "A soma entre eles é: "
    buffer1: .space 16
    buffer2: .space 16
    ans: .space 16

.section .text
    .global _start

# _print(msg, size)
# %rsi -> endereço da string
# %rdx -> tamanho da string
_print:
    mov $1, %rax            # syscall write
    mov $1, %rdi            # stdout
    syscall
    ret

# _scan(buffer, size)
# %rsi -> endereço do buffer
# %rdx -> tamanho do buffer
_scan:
    mov $0, %rax            # syscall read
    mov $0, %rdi            # stdin
    syscall
    ret

# _stoi(buffer) -> %rax
# Converte string para inteiro
_stoi:
    xor %rax, %rax          # Zera acumulador
    xor %rcx, %rcx          # Zera contador
stoi_loop:
    mov (%rsi), %dl         # Carrega um caractere
    cmp $10, %dl            # Se for '\n', sai
    je stoi_done
    sub $48, %dl            # Converte ASCII para número
    imul $10, %rax          # Multiplica acumulador por 10
    add %rdx, %rax          # Soma o dígito atual
    inc %rsi                # Avança para o próximo caractere
    jmp stoi_loop
stoi_done:
    ret

# _itoa(value) -> %rdi (endereço da string convertida)
# Converte inteiro para string
_itoa:
    mov $ans + 15, %rdi     # Ponteiro para o final do buffer
    mov $10, %rcx           # Divisor base 10
    movb $0, (%rdi)         # Termina com null byte
itoa_loop:
    dec %rdi                # Move o ponteiro para trás
    xor %rdx, %rdx          # Zera o resto
    div %rcx                # Divide %rax por 10
    add $48, %rdx           # Converte para ASCII
    mov %dl, (%rdi)         # Armazena o caractere
    test %rax, %rax         # Se %rax for 0, encerra
    jnz itoa_loop
    ret

_exit:
    mov $60, %rax
    xor %rdi, %rdi
    syscall

_start:

    movl size1(%rip), %edx
    lea msg1(%rip), %rsi
    call _print

    lea buffer1(%rip), %rsi
    mov $16, %rdx
    call _scan

    lea buffer2(%rip), %rsi
    mov $16, %rdx
    call _scan


    lea buffer1(%rip), %rsi
    call _stoi
    mov %rax, %rbx          

    lea buffer2(%rip), %rsi
    call _stoi
    add %rbx, %rax          

    call _itoa

    movl size2(%rip), %edx
    lea msg2(%rip), %rsi
    call _print

    lea ans(%rip), %rsi
    mov $16, %rdx
    call _print

    call _exit
