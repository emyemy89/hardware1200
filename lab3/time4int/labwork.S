  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
.data
    .align 2
mytime:    .word 0x5957
timstr:    .ascii "text more text lots of text\0"



.text
.global enable_interrupt
enable_interrupt:
    ei
    jr $ra
    nop

.global hexasc
hexasc:
     
      andi $a0,$a0,0xf    # only 4 least significant bits are needed, ignore other bits
      li $v0,0x30         # $v0 = 0x30 ('0' in ascii)
      add $v0,$v0,$a0     # add $a0 to $v0
      blt $a0,0xa,end     # if $a0 < 0xa (10 in decimal), jump to end
      nop
      addi $v0,$v0,7      # add 7 to $v0 to get the ascii code for 'A'
end:
      jr $ra
      nop


.global delay
delay:  li $a0, 20         #this is ms

    PUSH $ra
    PUSH $s0
    PUSH $s1

    whileLoop:
    blez $a0, stop
    nop
    sub $a0, $a0, 1

    li $s0, 220000
    move $s1, $0

    forLoop:
    beq $s0, $s1, whileLoop
    nop
    addi $s1, $s1, 1
    j forLoop
    nop

    stop:
    POP $s1
    POP $s0
    POP $ra

    jr $ra
    nop

.global time2string
time2string:
    # Save registers
    PUSH $ra
    PUSH $s0
    PUSH $a0
    # Convert minutes to ASCII
    andi $s0, $a1, 0xf000
    srl $s0, $s0, 12
    move $a0, $s0  # Move the value from $s0 to $a0
    jal hexasc
    nop
    POP $a0
    POP $s0
    #move $s1, $a0       # Save the modified
    sb $v0, 0($a0)
    PUSH $s0
    PUSH $a0
    andi $s0, $a1, 0x0f00
    srl $s0, $s0, 8
    move $a0, $s0  # Move the value from $s0 to $a0
    jal hexasc
    nop
    POP $a0
    POP $s0
    sb $v0, 1($a0)
    # Add colon
    li $s1, 0x3a
    sb $s1, 2($a0)

    PUSH $s0
    PUSH $a0
    # Convert seconds to ASCII
    andi $s0, $a1, 0x00f0
    srl $s0, $s0, 4
    move $a0, $s0         # Move the value from $s0 to $a0
    jal hexasc
    nop
    POP $a0
    POP $s0
    sb $v0, 3($a0)        # Store the byte at the correct address

    PUSH $s0
    PUSH $a0
    andi $s0, $a1, 0x000f
    move $a0, $s0  # Move the value from $s0 to $a0
    jal hexasc
    nop
    POP $a0
    POP $s0
    sb $v0, 4($a0)

    # Add null byte
    li $s2, 0x00
    sb $s2, 5($a0)
    
    # Restore register
    POP $ra
    jr $ra
    nop

#make install TTYDEV=/dev/cu.usbserial-A503WGNJ
