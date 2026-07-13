BITS 32

section .text
global _strequal

_strequal:
   
    push ebp
    mov ebp, esp
    
    push esi
    push edi

    cld

    mov edi, [ebp + 8]
    xor al, al
    mov ecx, -1

    repne scasb

    not ecx

    mov esi, [ebp + 12]
    sub edi, ecx
    
    repe cmpsb
    je .e
    jne .ne        

    .e:
        mov eax, 1
        jmp .done    

    .ne:
        mov eax, 0

    .done:
        pop edi
        pop esi
        
        mov esp, ebp
        pop ebp
        ret
