	.text
	.type encode,@function
	.globl encode
	.align 16
encode:
	xor %eax,%eax
	mov 4(%esp),%edx
	movq occupation,%mm0

	.align 16
1:	movzbl (%edx),%ecx
	inc %eax
	shl $2,%ecx
	movd %ecx,%mm2
	movq mask,%mm1
	psllq %mm2,%mm1
	psubb %mm1,%mm0
	movq %mm0,%mm3
	psrlq %mm2,%mm3
	movd %mm3,%ecx
	and $15,%ecx
	mov %cl,(%edx)
	inc %edx
	cmp $16,%eax
	jb 1b

	emms
	ret
	.size encode,.-encode

	.type decode,@function
	.globl decode
	.align 16
decode:
	xor %eax,%eax
	mov 4(%esp),%edx
	mov occupation,%mm0

	.align 16
0:	movzbl (%edx),%ecx
	movq %mm0,%mm3
	shl $2,%ecx
	pcmpeqd %mm5,%mm5
	movd %ecx,%mm2
	neg %ecx
	movq %mm0,%mm4
	psrlq $4,%mm0
	psrlq %mm2,%mm3
	add $64,%ecx
	inc %eax
	movd %ecx,%mm1
	movd %mm3,%ecx
	psrlq %mm1,%mm5
	pand %mm5,%mm4
	pandn %mm0,%mm5
	movq %mm4,%mm0
	and $15,%ecx
	mov %cl,(%edx)
	inc %edx
	por %mm5,%mm0
	cmp $16,%eax
	jb 0b

	emms
	ret
	.size decode,.-decode

	.data
	.type algname,@object
	.globl algname
	.size algname,4
	.align 4
algname:
	.long mmxasm

	.section .rodata
	.type occupation,@object
	.size occupation,8
	.align 8
occupation:
	.long 0x76543210,0xfedcba98

	.type mask,@object
	.size mask,8
mask:	.long 0x11111110,0x11111111

mmxasm:	.string "mmxasm"
