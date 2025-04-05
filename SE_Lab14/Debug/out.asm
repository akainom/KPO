.586P
.MODEL FLAT, STDCALL
includelib kernel32.lib
includelib msvcrtd.lib
includelib libucrt.lib
includelib "C:/Users/леха/Desktop/kpolib/stdlib.lib"
ExitProcess PROTO:DWORD 
copystr PROTO :DWORD, :DWORD
concat PROTO :DWORD, :DWORD, :DWORD
.stack 4096

.const
		
		p sdword 5
		x sdword 1
		y sdword 5
		sa byte '1234567890', 0
		sb byte 'aaaaa12345', 0
		L_0 sdword 0
.data
		buffer db 256 dup(0)

		z sdword 0
		c dword ?
		p sdword 0
		x sdword 0
		y sdword 0
		z sdword 0
		sa dword ?
		sb dword ?
		sc dword ?
.code
fi PROC,
	x : sdword, y : sdword  
push ebx
push edx
pop ebx
pop eax
imul eax, ebx
push eaxpop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov z, ebx


pop edx
pop ebx
mov eax, z
ret
fi ENDP

fs PROC,
	a : dword, b : dword  
push ebx
push edx
mov ecx, offset a
mov c, ecx


pop edx
pop ebx
mov eax, c
ret
fs ENDP

main PROC

pop ebx
mov p, ebx


pop ebx
mov x, ebx


pop ebx
mov y, ebx

mov sa, offset sa
mov ecx, offset sa
mov sa, ecx

mov sb, offset sb
mov ecx, offset sb
mov sb, ecx


pop ebx
mov z, ebx


push offset sb
push offset sa
call fs
mov sc, eax


pop edx
pop ebx
mov eax, L_0

push 0
call ExitProcess
main ENDP
end main
