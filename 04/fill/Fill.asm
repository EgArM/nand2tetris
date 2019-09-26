// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed.
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

  @8192
  D=A
  @SCREEN
  D=D+A
  @screenEnd
  M=D

(MAIN)
  @KBD
  D=M
  @PAINTWHITE
  D;JEQ
  @PAINTBLACK
  0;JMP

(PAINTWHITE)
  @color
  M=0
  @COLORIZE
  0;JMP

(PAINTBLACK)
  @color
  M=-1
  @COLORIZE
  0;JMP

(COLORIZE)
  @SCREEN
  D=A
  @nextWord
  M=D

(COLORIZELOOP)
  @nextWord
  D=M
  @screenEnd
  D=D-M
  @COLORIZEEND
  D;JEQ

  @color
  D=M
  @nextWord
  A=M
  M=D

  @nextWord
  M=M+1

  @COLORIZELOOP
  0;JMP
(COLORIZEEND)

  @MAIN
  0;JMP
