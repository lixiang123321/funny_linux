func_2():
        push    rbp
        mov     rbp, rsp
        mov     eax, -1
        pop     rbp
        ret
func_1(int, int, int, int):
        push    rbp
        mov     rbp, rsp
        sub     rsp, 32
        mov     DWORD PTR [rbp-20], edi
        mov     DWORD PTR [rbp-24], esi
        mov     DWORD PTR [rbp-28], edx
        mov     DWORD PTR [rbp-32], ecx
        mov     DWORD PTR [rbp-4], 1
        mov     DWORD PTR [rbp-8], 2
        mov     QWORD PTR [rbp-16], 3
        call    func_2()
        mov     edx, DWORD PTR [rbp-20]
        mov     eax, DWORD PTR [rbp-24]
        add     edx, eax
        mov     eax, DWORD PTR [rbp-28]
        add     edx, eax
        mov     eax, DWORD PTR [rbp-32]
        add     eax, edx
        mov     DWORD PTR [rbp-4], eax
        mov     eax, DWORD PTR [rbp-4]
        leave
        ret
.LC0:
        .string "value: %d\n"
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        mov     DWORD PTR [rbp-4], 0
        mov     DWORD PTR [rbp-8], 1
        mov     eax, DWORD PTR [rbp-8]
        add     eax, 4
        mov     ecx, eax
        mov     edx, 3
        mov     esi, 2
        mov     edi, 1
        call    func_1(int, int, int, int)
        mov     DWORD PTR [rbp-4], eax
        mov     eax, DWORD PTR [rbp-4]
        mov     esi, eax
        mov     edi, OFFSET FLAT:.LC0
        mov     eax, 0
        call    printf
        mov     eax, 0
        leave
        ret