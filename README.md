# minimal-x86-disassembler
An x86 disassembler with a limited instruction support, intended for educational purposes.

### Workflow
**mdsm** translates one machine instruction at a time, and operates as a loop of input, decoding, and output.\
I'll add more details on the implementation of these stages later, especially the decoding stage.

### Supported instructions
-add r/m32, imm32\
-sub r/m32, imm32\
-and r/m32, imm32\
-or r/m32, imm32\
-cmp r/m32, imm32\
\
-mov r32, imm32
-inc r32\
-dec r32\
-push r32\
-pop r32\
\
-jmp rel32\
-nop
