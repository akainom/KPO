.586P
.MODEL FLAT, STDCALL
includelib kernel32.lib
includelib msvcrtd.lib
includelib libucrt.lib
includelib "C:/KPO/alt/SE_Lab14/Debug/StandartLibrary.lib"
ExitProcess PROTO:DWORD 
strcp PROTO :DWORD, :DWORD
stcmp PROTO :DWORD, :DWORD
writestr PROTO :DWORD
writeint PROTO :SDWORD
.stack 4096

.const
		
		L_0 sdword 5
		L_1 sdword 16
		L_2 sdword 0
.data
		buffer db 256 dup(0)
		number dd 64 dup(0)
		res sdword 0
		g sdword 0
		k sdword 0
		res sdword 0
.code
mult PROC,
	a : sdword, b : sdword  
push ebx
push edx
push a
push b
pop ebx
pop eax
imul eax, ebx
push eax
pop ebx
mov res, ebx


pop edx
pop ebx
mov eax, res
ret
mult ENDP

main PROC
push L_0

pop ebx
mov g, ebx

push L_1

pop ebx
mov k, ebx


push g
push g
push g
push g
push g
push g
push g
push k
push k
push k
push k
push k
push k
push g
call mult
push eax

pop ebx
mov res, ebx

push ecx
push res
call writeint
pop ecx


pop edx
pop ebx
mov eax, L_2

push 0
call ExitProcess
main ENDP
end main
