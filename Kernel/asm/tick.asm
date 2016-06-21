GLOBAL setTick

setTick:
    push rax
    cli
    mov al, 0x36
    out 0x43, al
    ;mov rax, 163841
    mov rax,  19886
    out 0x40, al
    mov al,ah
    out 0x40, al
    sti
    pop rax
    ret