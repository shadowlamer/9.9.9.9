#include <string.h>

#include "scr_addr.h"
#include "font.h"

#include "boy1_atr.h"
#include "boy1_img.h"

#include "oldman1_atr.h"
#include "oldman1_img.h"

#include "teller1_atr.h"
#include "teller1_img.h"

#define STORY_SIZE 9

typedef struct {
  unsigned char *img;
  unsigned char *atr;
  char *text;
  unsigned int delay;
} slide_struct_t;

__at (SCREEN_BUFFER_START) char screen_buf[0x1800];
__at (ATTR_SCREEN_BUFFER_START) char screen_attr_buf[0x300];

static const slide_struct_t story[] = {
  {
    .img = boy1_img,
    .atr = boy1_atr,
    .text = "Вот\\ это\\ да\\,\\ какие\\ красивые\\ здания\\!\\ Это\\ же\\ Пермь\\,\\ город\\ с\\ богатой\\ историей\\.",
    .delay = 200
  },
  {
    .img = teller1_img,
    .atr = teller1_atr,
    .text = "Здравствуй\\,\\ молодой\\ путешественник\\.\\ Вижу\\,\\ что\\ ты\\ ищешь\\ что\\-то\nособенное\\.",
    .delay = 200
  },
  {
    .img = boy1_img,
    .atr = boy1_atr,
    .text = "Да\\,\\ точно\\!\\ Я\\ хочу\\ открыть\\ для\\ себя\\ все\\ тайны\\ и\\ легенды\\ Перми\\.\\ Я\\ иду\\ искать\\ приключения\\!",
    .delay = 200
  },
  {
    .img = teller1_img,
    .atr = teller1_atr,
    .text = "Мудрая\\ цель\\,\\ молодой\\ человек\\.\\ Слушай\\,\\ у\\ меня\\ есть\\ предчувствие\\,\\ что\\ тебя\\ ждет\\ великое\\ свидание\\,\\ связанное\\ с\\ уральскими\\ мифами\\ и\\ легендами\\.\\ Будь\\ готов\\ к\\ невероятным\\ приключениям\\!",
    .delay = 200
  },
  {
    .img = boy1_img,
    .atr = boy1_atr,
    .text = "О\\,\\ это\\ звучит\\ увлекательно\\!\\ Я\\ готов\\ отправиться\\ в\\ этот\\ удивительный\\ мир\\ легенд\\ и\\ мифов\\.\\ Подскажи\\,\\ с\\ чего\\ мне\\ начать\\?",
    .delay = 200
  },
  {
    .img = teller1_img,
    .atr = teller1_atr,
    .text = "Первая\\ легенда\\ рассказывает\\ о\\ Златоусте\\ и\\ Шайтан\\-Камне\\,\\ магическом\\ мече\\ и\\ волшебном камне\\, способных\\ исполнить\\ желания\\.\\ Легенда\\ гласит\\,\\ что\\ они\\ спрятаны\\ в\\ одном\\ из\\ подземных\\ лабиринтов\\.\\ Найди\\ меч\\ и\\ загадай\\ желание\\ \\-\\ и\\ будущее\\ твое\\ изменится.",
    .delay = 200
  },
  {
    .img = boy1_img,
    .atr = boy1_atr,
    .text = "Звучит\\ увлекательно\\!\\ Я\\ отправлюсь\\ в\\ поиски\\ Златоуста\\ и\\ Шайтан-Камня\\.\\ Как\\ я\\ найду\\ подземный\\ лабиринт\\?",
    .delay = 200
  },
  {
    .img = teller1_img,
    .atr = teller1_atr,
    .text = "Лучше\\ всего\\ начать\\ с\\ Гороховой\\ горы\\.\\ Ищи\\ там\\ древнюю\\ пещеру\\,\\ вход\\ в\\ лабиринт\\ должен\\ быть\\ рядом\\.\\ Будь\\ осторожен\\,\\ уральские\\ легенды\\ полны\\ опасностей\\,\\ но\\ твое\\ стойкое\\ сердце\\ поможет\\ тебе\\ преодолеть\\ все\\ трудности\\!",
    .delay = 200
  },
  {
    .img = boy1_img,
    .atr = boy1_atr,
    .text = "Спасибо\\ за\\ помощь\\!\\ Я\\ не\\ остановлюсь\\,\\ пока\\ не\\ найду\\ Златоуста\\ и\\ Шайтан\\-Камень\\!",
    .delay = 200
  },
};

void unpack(char *src, char *dst);
void delay(unsigned int interval);
void print(char *message, unsigned char x, unsigned char y);
void show_slide(slide_struct_t *slide);

void main() {
  for (;;) {
    for (unsigned char slide = 0; slide < STORY_SIZE; slide++) {
      show_slide(story + slide);
    }
  }
}

void show_slide(slide_struct_t *slide){
    memset(screen_buf + 0x1000, 0x00, 0x800);
    memset(screen_attr_buf, 0x00, 0x200);
    unpack(slide->img, screen_buf);
    unpack(slide->atr, screen_attr_buf);
    print(slide->text, 0, 17);
    delay(slide->delay);
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

