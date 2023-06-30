#include <string.h>

#include "scr_addr.h"
#include "font.h"
#include "assets.h"

__at (SCREEN_BUFFER_START) char screen_buf[0x1800];
__at (ATTR_SCREEN_BUFFER_START) char screen_attr_buf[0x300];
__at (EMBEDDED_FONT_START) char font0[];

void unpack(char *src, char *dst);
void delay(unsigned int interval);
void print(char *message, unsigned char x, unsigned char y);
  
void main() {
  for (;;) {
    memset(screen_buf + 0x1000, 0x00, 0x800);
    memset(screen_attr_buf, 0x00, 0x200);
    unpack(boy1_img, screen_buf);
    unpack(boy1_atr, screen_attr_buf);
    print("Вот\\ это\\ да\\,\\ какие\\ красивые\\ здания\\!\\ Это\\ же\\ Пермь\\,\\ город\\ с\\ бога\\-той\\ историей\\.", 0, 17);
    delay(200);

    memset(screen_buf + 0x1000, 0x00, 0x800);
    memset(screen_attr_buf, 0x00, 0x200);
    unpack(teller1_img, screen_buf);
    unpack(teller1_atr, screen_attr_buf);
    print("Здравствуй\\,\\ молодой\\ путешественник\\.\\ Вижу\\,\\ что\\ ты\\ ищешь\\ что\\-то\\ особенное\\.", 0, 17);
    delay(200);
  }
}

void print(char *message, unsigned char x, unsigned char y) {
  char *p_scr;
  char const *p_font;

  p_font = font;

  for (; *message!=0; message++) {
    char const *p_char;
    char s;
    
    if (*message == '\n') {
    	y++;
        continue;
    }
    
    if (*message == '\\') {
      message++;
      s = *message - ' ';
    } else {
      s = *message;
    }

    if (x == 0 && s == 0) continue;
    
    p_char = p_font + (s * 8);
    p_scr = ((char *)screen_line_addrs[y * 8]);
    p_scr += (x / 8);
    
    for (unsigned char i = 0; i < 8; i++) {
      char *p;
      unsigned int z;
      z = p_char[i];
      z <<= (8 - (x % 8));
      p = p_scr + (i * 256);
      *p |= z >> 8;
      p++;
      *p |= z;
    }
    if (x >= 31 * 8) {
     y++;
     x = 0; 
    } else {
      x += font_width[s];
    }
  }                                                                                                                                                                                                                
}                                                                                                                                                                                                                  

void unpack(char *src, char *dst) {
(void) src, dst;

  __asm
  ld ix, #4                                                                                                                                                                                                        
  add ix, sp                                                                                                                                                                                                       

  ld l, 0(ix)                                                                                                                                                                                                      
  ld h, 1(ix)
  ld e, 2(ix)
  ld d, 3(ix)
  call dzx0_standard
  __endasm;  
  }

/*; -----------------------------------------------------------------------------
; ZX0 decoder by Einar Saukas & Urusergi
; "Standard" version (68 bytes only)
; https://github.com/einar-saukas/ZX0
; -----------------------------------------------------------------------------
; Parameters:
;   HL: source address (compressed data)
;   DE: destination address (decompressing)
; ----------------------------------------------------------------------------- */
void unpack_naked() __naked{
  __asm
dzx0_standard:
        ld      bc, #0xffff               ; preserve default offset 1
        push    bc
        inc     bc
        ld      a, #0x80
dzx0s_literals:
        call    dzx0s_elias             ; obtain length
        ldir                            ; copy literals
        add     a, a                    ; copy from last offset or new offset?
        jr      c, dzx0s_new_offset
        call    dzx0s_elias             ; obtain length
dzx0s_copy:
        ex      (sp), hl                ; preserve source, restore offset
        push    hl                      ; preserve offset
        add     hl, de                  ; calculate destination - offset
        ldir                            ; copy from offset
        pop     hl                      ; restore offset
        ex      (sp), hl                ; preserve offset, restore source
        add     a, a                    ; copy from literals or new offset?
        jr      nc, dzx0s_literals
dzx0s_new_offset:
        pop     bc                      ; discard last offset
        ld      c, #0xfe                  ; prepare negative offset
        call    dzx0s_elias_loop        ; obtain offset MSB
        inc     c
        ret     z                       ; check end marker
        ld      b, c
        ld      c, (hl)                 ; obtain offset LSB
        inc     hl
        rr      b                       ; last offset bit becomes first length bit
        rr      c
        push    bc                      ; preserve new offset
        ld      bc, #1                   ; obtain length
        call    nc, dzx0s_elias_backtrack
        inc     bc
        jr      dzx0s_copy
dzx0s_elias:
        inc     c                       ; interlaced Elias gamma coding
dzx0s_elias_loop:
        add     a, a
        jr      nz, dzx0s_elias_skip
        ld      a, (hl)                 ; load another group of 8 bits
        inc     hl
        rla
dzx0s_elias_skip:
        ret     c
dzx0s_elias_backtrack:
        add     a, a
        rl      c
        rl      b
        jr      dzx0s_elias_loop
__endasm;
}

void delay(unsigned int interval) {
  for (;--interval > 0;) {
    __asm 
      ei
      halt
    __endasm;	  	
  }
}

