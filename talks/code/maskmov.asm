global compute

;  void compute(int n, float * tab);
;  tab[i] = (tab[i] > 0) ? (tab[i]+4)*sqrt(tab[i]) : (tab[i]*tab[i])*sqrt(-tab[i]); 

section .text

compute: 

   pxor   xmm0, xmm0
   movups xmm4, [rel four]
   jmp .start
.loop:
   movups xmm1, [rsi]
   
   ;mask
   movaps xmm7, xmm1
   cmpnleps xmm7, xmm0
    
   ; then 
   movaps xmm2, xmm1
   addps  xmm2, xmm4
   movaps xmm6, xmm1
   sqrtps xmm6, xmm6
   mulps  xmm2, xmm6
   movups [rsi], xmm2
   
   ;else 
   movaps xmm3, xmm1
   mulps  xmm3, xmm1
   movaps xmm5, xmm0
   subps  xmm5, xmm1
   sqrtps xmm5, xmm5
   mulps  xmm3, xmm5
   vmaskmovps [rsi], xmm7, xmm3

   add rsi, 16
   sub edi, 3    
   
.start:
   cmp edi,3
   jg .loop
   
   
.end:
   ret
   
section .data
four times 4 dd 4.0

