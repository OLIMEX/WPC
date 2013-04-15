section .bss
    result: 		resb   	4096
    result_length:	resd	1
    current_word: 	resb 	4096
    current_index:	resd 	1
  
    buf:		resb    8192
    buf_index:		resd    1
    buf_read:		resd	1	
section .text
    global  _start

checkIfGood:
    mov	    ecx, [current_index]
nextChar:        
    dec     ecx		
    cmp     ecx, 0
    je	    good

    mov     ebx, ecx		; ecx & ebx contain length of word
    mov     al, [current_word+ecx]
check_next:
    dec	    ebx        
    cmp	    al, [current_word+ebx]
    je      bad
    cmp	    ebx, 0 
    jne	    check_next    
    jmp	    nextChar  
bad:
    xor eax, eax
    inc eax
    ret    

good:
    xor eax, eax
    ret

read_stdin_buf:
    mov     eax,    3       ; sys_read
    mov     ebx,    0       ; stdin
    mov     ecx,    buf    ; buffer
    mov     edx,    8192     ; read byte count
    int     80h

    cmp     eax, 0
    jne     read_ok

    call    process_word        ; catch the cornercase where the longes word
                                ; is the last word in the file
    call    print_result
    jmp     _exit

read_ok:
    mov     [buf_read], eax
    xor     eax, eax
    mov     [buf_index], eax
    ret
	
_exit:
    mov     eax,    1       ; exit
    mov     ebx,    0       ; exit status
    int     80h

_start:
    xor     eax, eax
    mov     [buf_read], eax
    mov     [buf_index], eax

start_new_word:
    mov     dword [current_index], 0 

read_next:
    mov     eax, [buf_read]
    cmp	    eax, [buf_index]
    jne     buf_not_empty
    call    read_stdin_buf

buf_not_empty:
    mov     ebx, [buf_index]
    mov	    al, byte [buf+ebx]      ; read single char from buffer
    inc     dword [buf_index]	     ; increase index
    
    xor	    ebx, ebx
    cmp     al, 'Z'
    jg	    .not_uppercase
    cmp     al, 'A'
    jl	    .not_uppercase
    add     al, 0x20 ; convert to lower case
    inc     ebx 
.not_uppercase:
    mov	    ecx, [current_index]	
    mov     byte [current_word+ecx], al
    inc     dword [current_index]

    test    ebx, ebx  ; do not check uppercase letters, twice
    jnz     read_next 
 
    ; treat all characters except letters, as separators
    cmp     al, 'z'
    jg	    .process_word
    cmp     al, 'a'
    jl	    .process_word

    jmp     read_next

.process_word:
    call process_word
   
    jmp    start_new_word
   
print_result:
    mov     eax,    4       ; sys_write
    mov     ebx,    1       ; stdout
    mov     ecx,    result   ; buffer
    mov     edx,    [result_length]       ; write byte count 
    mov     byte [ecx+edx], 0x0a	  ; add linebreak
    inc     edx
    int     80h

    ret

process_word:
     mov    eax, dword [current_index]
     dec    eax
     cmp    dword [result_length], eax
     jge    .exit

     call    checkIfGood
     test    eax, eax
     jnz     start_new_word

    ; copy current word to result
    mov    esi, current_word
    mov    edi, result
    mov    ecx, [current_index]
    cld
    rep    movsb
     
    mov    ecx, [current_index]
    dec    ecx
    mov    [result_length] , ecx

;   debug
;    call   print_result

.exit:
    ret
