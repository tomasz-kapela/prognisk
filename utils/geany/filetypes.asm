# For complete documentation of this file, please see Geany's main documentation
[styling]
# foreground;background;bold;italic
default=0x000000;0xffffff;false;false
comment=0x808080;0xffffff;false;false
number=0x007f00;0xffffff;false;false
string=0xff901e;0xffffff;false;false
operator=0x000000;0xffffff;false;false
identifier=0x880000;0xffffff;false;false
cpuinstruction=0x111199;0xffffff;true;false
mathinstruction=0x7f0000;0xffffff;true;false
register=0x000000;0xffffff;true;false
directive=0x3d670f;0xffffff;true;false
directiveoperand=0xff901e;0xffffff;false;false
commentblock=0x808080;0xffffff;false;false
character=0xff901e;0xffffff;false;false
stringeol=0x000000;0xe0c0e0;false;false
extinstruction=0x007f7f;0xffffff;false;false

[keywords]
# all items must be in one line
instructions=adc add addpd addps addsd addss addsubpd addsubps and andnpd andnps andpd andps blendpd blendps bsf bsr bswap bt btc btr bts call callf cbw cdq cdqe clc cld clflush cli clts cmc cmova cmovae cmovb cmovbe cmovc cmove cmovg cmovge cmovl cmovle cmovna cmovnae cmovnb cmovnbe cmovnc cmovne cmovng cmovnge cmovnl cmovnle cmovno cmovnp cmovns cmovnz cmovo cmovp cmovpe cmovpo cmovs cmovz cmp cmppd cmpps cmps cmpsb cmpsd cmpsq cmpss cmpsw cmpxchg cmpxchg16b cmpxchg8b comisd comiss cpuid cqo crc32 cvtdq2pd cvtdq2ps cvtpd2dq cvtpd2pi cvtpd2ps cvtpi2pd cvtpi2ps cvtps2dq cvtps2pd cvtps2pi cvtsd2si cvtsd2ss cvtsi2sd cvtsi2ss cvtss2sd cvtss2si cvttpd2dq cvttpd2pi cvttps2dq cvttps2pi cvttsd2si cvttss2si cwd cwde dec div divpd divps divsd divss dppd dpps emms enter extractps f2xm1 fabs fadd faddp fbld fbstp fchs fclex fcmovb fcmovbe fcmove fcmovnb fcmovnbe fcmovne fcmovnu fcmovu fcom fcom2 alias fcomi fcomip fcomp fcomp3 alias fcomp5 alias fcompp fcos fdecstp fdiv fdivp fdivr fdivrp ffree ffreep fiadd ficom ficomp fidiv fidivr fild fimul fincstp finit fist fistp fisttp fisub fisubr fld fld1 fldcw fldenv fldl2e fldl2t fldlg2 fldln2 fldpi fldz fmul fmulp fnclex fndisi nop fneni nop fninit fnop fnsave fnsetpm nop fnstcw fnstenv fnstsw fpatan fprem fprem1 fptan frndint frstor fs fsave fscale fsin fsincos fsqrt fst fstcw fstenv fstp fstp1 part alias4  fstp8 alias fstp9 alias fstsw fsub fsubp fsubr fsubrp ftst fucom fucomi fucomip fucomp fucompp fwait fxam fxch fxch4 alias fxch7 alias fxrstor fxsave fxtract fyl2x fyl2xp1 getsec gs haddpd haddps hint_nop hlt hsubpd hsubps icebp part alias9  idiv imul in inc ins insb insd insertps insw int int1 part alias9  into int alias invd invept invlpg invvpid iret iretd iretq ja jae jb jbe jc je jecxz jg jge jl jle jmp jmpe jmpf jna jnae jnb jnbe jnc jne jng jnge jnl jnle jno jnp jns jnz jo jp jpe jpo jrcxz js jz lahf lar lddqu ldmxcsr lea leave lfence lfs lgdt lgs lidt lldt lmsw lock lods lodsb lodsd lodsq lodsw loop loope loopne loopnz loopz lsl lss ltr maskmovdqu maskmovq maxpd maxps maxsd maxss mfence minpd minps minsd minss monitor mov movapd movaps movbe movd movddup movdq2q movdqa movdqu movhlps movhpd movhps movlhps movlpd movlps movmskpd movmskps movntdq movnti movntpd movntps movntq movq movq2dq movs movsb movsd movshdup movsldup movsq movss movsw movsx movsxd movupd movups movzx mpsadbw mul mulpd mulps mulsd mulss mwait neg nop not or orpd orps out outs outsb outsd outsw packssdw packsswb packuswb paddb paddd paddq paddsb paddsw paddusb paddusw paddw palignr pand pandn pause pavgb pavgw pblendw pcmpeqb pcmpeqd pcmpeqw pcmpestri pcmpestrm pcmpgtb pcmpgtd pcmpgtw pcmpistri pcmpistrm pextrb pextrd pextrq pextrw pinsrb pinsrd pinsrq pinsrw pmaddwd pmaxsw pmaxub pminsw pminub pmovmskb pmulhuw pmulhw pmullw pmuludq pop popcnt popf popfq por prefetchnta prefetcht0 prefetcht1 prefetcht2 psadbw pshufd pshufhw pshuflw pshufw pslld pslldq psllq psllw psrad psraw psrld psrldq psrlq psrlw psubb psubd psubq psubsb psubsw psubusb psubusw psubw punpckhbw punpckhdq punpckhqdq punpckhwd punpcklbw punpckldq punpcklqdq punpcklwd push pushf pushfq pxor rcl rcpps rcpss rcr rdmsr rdpmc rdtsc rdtscp rep repe repne repnz repz retf ret retn rex rex.b rex.r rex.rb rex.rx rex.rxb rex.w rex.wb rex.wr rex.wrb rex.wrx rex.wrxb rex.wx rex.wxb rex.x rex.xb rol ror roundpd roundps roundsd roundss rsm rsqrtps rsqrtss sahf sal sal alias sar sbb scas scasb scasd scasq scasw seta setae setb setbe setc sete setg setge setl setle setna setnae setnb setnbe setnc setne setng setnge setnl setnle setno setnp setns setnz seto setp setpe setpo sets setz sfence sgdt shl shld shl alias shr shrd shufpd shufps sidt sldt smsw sqrtpd sqrtps sqrtsd sqrtss stc std sti stmxcsr stos stosb stosd stosq stosw str sub subpd subps subsd subss swapgs syscall sysenter sysexit sysret test test alias ucomisd ucomiss ud ud2 unpckhpd unpckhps unpcklpd unpcklps verr verw vmcall vmclear vmlaunch vmptrld vmptrst vmread vmresume vmwrite vmxoff vmxon wait wbinvd wrmsr xadd xchg xgetbv xlat xlatb xor xorpd xorps xrstor xsave xsetbv 
registers=rax eax ax al ah rbx ebx bx bl bh rcx ecx cx cl ch rdx edx dx dl dh rdi edi di dil dih rsi esi si sil sih rbp ebp bp rsp esp sp r8 r8d r8w r9b r9 r9d r9w r9b r10 r10d r10w r10b r11 r11d r11w r11b r12 r12d r12w r12b r13 r13d r13w r13b r14 r14d r14w r14b r15 r15d r15w r15b st0 st1 st2 st3 st4 st5 st6 st7 xmm0 xmm1 xmm2 xmm3 xmm4 xmm5 xmm6 xmm7 xmm8 xmm9 xmm10 xmm11 xmm12 xmm13 xmm14 xmm15  ymm0 ymm1 ymm2 ymm3 ymm4 ymm5 ymm6 ymm7 ymm8 ymm9 ymm10 ymm11 ymm12 ymm13 ymm14 ymm15.data .text .bss _start
directives=org list nolist page equivalent word dword qword tword byte text equ section segment global extern %define %idefine %macro %endmacro db dw dd dq dt times resb byte %1 %2 %3 %4 %5 %6 %7 %8 %9 %10


[settings]
# default extension used when saving files
extension=asm

# the following characters are these which a "word" can contains, see documentation
#wordchars=_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789

# single comments, like # in this file
comment_single=;
# multiline comments
#comment_open=
#comment_close=

# set to false if a comment character/string should start at column 0 of a line, true uses any
# indentation of the line, e.g. setting to true causes the following on pressing CTRL+d
    #command_example();
# setting to false would generate this
#   command_example();
# This setting works only for single line comments
comment_use_indent=true

# context action command (please see Geany's main documentation for details)
context_action_cmd=

[indentation]
#width=4
# 0 is spaces, 1 is tabs, 2 is tab & spaces
#type=0

[build_settings]
# %f will be replaced by the complete filename
# %e will be replaced by the filename without extension
# (use only one of it at one time)
#compiler=nasm "%f"

[build-menu]
FT_00_LB=_Skompiluj
FT_00_CM=(nasm "%f" -felf64 -o "%e".o) && (ld -m elf_x86_64 "%e".o -o"%e")
FT_00_WD=
FT_01_LB=Zbuduj z asm io
FT_01_CM=(nasm "%f" -felf64 -o "%e".o) && (gcc "%e".o asm64_io.o -o"%e")
FT_01_WD=
