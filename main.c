#include <string.h>

#include "scr_addr.h"
#include "font.h"

#include "boy1_atr.h"
#include "boy1_img.h"

#include "boy2_atr.h"
#include "boy2_img.h"

#include "oldman1_atr.h"
#include "oldman1_img.h"

#include "teller1_atr.h"
#include "teller1_img.h"

#define FIRST_SLIDE 0
#define LAST_SLIDE 15

typedef struct {
  unsigned char *img;
  unsigned char *atr;
  char *text;
  unsigned int delay;
} slide_struct_t;

__at (SCREEN_BUFFER_START) char screen_buf[0x1800];
__at (ATTR_SCREEN_BUFFER_START) char screen_attr_buf[0x300];

static const slide_struct_t story[] = {
// Герой и гадалка
  { // 0
    .img = boy1_img,
    .atr = boy1_atr,
    .text = "Вот\\ это\\ да\\,\\ какие\\ красивые\\ здания\\!\\ Это\\ же\\ "
      "Пермь\\,\\ город\\ с\\ богатой\\ историей\\.",
    .delay = 200
  },
  { // 1
    .img = teller1_img,
    .atr = teller1_atr,
    .text = "Здравствуй\\,\\ молодой\\ путешественник\\.\\ Вижу\\,\\ что\\ ты\\ "
      "ищешь\\ что\\-то\\ особенное\\.",
    .delay = 200
  },
  { // 2
    .img = boy1_img,
    .atr = boy1_atr,
    .text = "Да\\,\\ точно\\!\\ Я\\ хочу\\ открыть\\ для\\ себя\\ все\\ тайны\\ "
      "и\\ легенды\\ Перми\\.\\ Я\\ иду\\ искать\\ приключения\\!",
    .delay = 200
  },
  { // 3
    .img = teller1_img,
    .atr = teller1_atr,
    .text = "Мудрая\\ цель\\,\\ молодой\\ человек\\.\\ Слушай\\,\\ у\\ меня\\ "
      "есть\\ предчувствие\\,\nчто\\ тебя\\ ждет\\ великое\\ свидание\\,\\ "
      "связанное\\ с\\ уральскими\\ мифами\\ и\\ легендами\\.\\ Будь\\ готов\\ "
      "к\\ невероятным\\ приключениям\\!",
    .delay = 200
  },
  { // 4
    .img = boy1_img,
    .atr = boy1_atr,
    .text = "О\\,\\ это\\ звучит\\ увлекательно\\!\\ Я\\ готов\\ "
      "отправиться\\ в\\ этот\\ удивитель\\-ный\\ мир\\ легенд\\ и\\ "
      "мифов\\.\\ Подскажи\\,\\ с\\ чего\\ мне\\ начать\\#",
    .delay = 200
  },
  { // 5
    .img = teller1_img,
    .atr = teller1_atr,
    .text = "Первая\\ легенда\\ рассказывает\\ о\\ Златоусте\\ и\\ "
      "Шайтан\\-Камне\\,\\ маги\\-\nческом\\ мече\\ и\\ волшебном\\ "
      "камне\\,\\ способных\\ исполнить\\ желания\\.\nЛегенда\\ гласит\\,\\ "
      "что\\ они\\ спрятаны\\ в\\ одном\\ из\\ подземных\\ лабирин\\-тов\\.\\ "
      "Найди\\ меч\\ и\\ загадай\\ желание\\ \\-\\ и\\ будущее\\ твое\\ "
      "изменится\\.",
    .delay = 200
  },
  { // 6
    .img = boy1_img,
    .atr = boy1_atr,
    .text = "Звучит\\ увлекательно\\!\\ Я\\ отправлюсь\\ на\\ поиски\\ "
      "Златоуста\\ и\\ Шайтан\\-Камня\\.\\ Как\\ я\\ найду\\ подземный\\ "
      "лабиринт\\#",
    .delay = 200
  },
  { // 7
    .img = teller1_img,
    .atr = teller1_atr,
    .text = "Лучше\\ всего\\ начать\\ с\\ Гороховой\\ горы\\.\\ Ищи\\ "
      "там\\ древнюю\\ пещеру\\,\\ вход\\ в\\ лабиринт\\ должен\\ быть\\ "
      "рядом\\.\\ Будь\\ осторожен\\,\\ уральские\nлегенды\\ полны\\ "
      "опасностей\\,\\ но\\ твое\\ стойкое\\ сердце\\ поможет\\ тебе\n"
      "преодолеть\\ все\\ трудности\\!",
    .delay = 200
  },
  { // 8
    .img = boy1_img,
    .atr = boy1_atr,
    .text = "Спасибо\\ за\\ помощь\\!\\ Я\\ не\\ остановлюсь\\,\\ пока\\ "
      "не\\ найду\\ Златоуст\\ и\nШайтан\\-Камень\\!",
    .delay = 200
  },
  // Герой и старик
  { // 9
    .img = boy2_img,
    .atr = boy2_atr,
    .text = "Привет\\,\\ дедушка\\!\\ Слышал\\ я\\,\\ что\\ ты\\ знаешь\\ "
      "легенду\\ о\\ грибе\\-чуде\\,\nприносящем\\ удачу\\ в\\ любви\\.\\ "
      "Расскажешь\\ ее\\ мне\\#",
    .delay = 200
  },
  { // 10
    .img = oldman1_img,
    .atr = oldman1_atr,
    .text = "Здравствуй\\,\\ молодой\\ искатель\\ легенд\\!\\ Да\\,\\ "
      "моя\\ история\\ расскажет\\ тебе\\ о\\ грибе\\-чуде\\.\\ Итак\\,\\ "
      "давным\\-давно\\.\\.\\.",
    .delay = 200
  },
  { // 11
    .img = oldman1_img,
    .atr = oldman1_atr,
    .text = "Этот\\ гриб\\ находится\\ у\\ пруда\\,\\ который\\ находится\\ "
      "глубоко\\ в\\ лесу\\.\\ Но\\ чтобы\\ найти\\ гриб\\,\\ тебе\\ "
      "придется\\ преодолеть\\ испытания\\ на\\ пути\\.\n\Ты\\ готов\\ "
      "сделать\\ это\\#",
    .delay = 200
  },
  { // 12
    .img = boy2_img,
    .atr = boy2_atr,
    .text = "Конечно\\!\\ Я\\ готов\\ пройти\\ все\\ испытания\\ ради\\ "
      "этого\\ волшебного\nгриба\\!\\ Какие\\ меня\\ ждут\\ испытания\\#",
    .delay = 200
  },
  { // 13
    .img = oldman1_img,
    .atr = oldman1_atr,
    .text = "Первое\\ испытание\\ \\-\\ интеллектуальное\\,\\ тебе\\ представят\\ "
      "ряд\\ зага\\-\nдок\\,\\ которые\\ нужно\\ разгадать\\.\n"
      "Второе\\ испытание\\ \\-\\ физическое\\,\\ тебе\\ предстоит\\ преодолеть\\ "
      "опасные\\ препятствия\\ и\\ показать\\ свою\\ силу\\.\n"
      "И\\,\\ наконец\\,\\ третье\\ испытание\\ \\-\\ духовное\\,\\ придется\\ "
      "открыть\\ свое\\ сердце\\ и\\ понять\\,\\ что\\ значит\\ любовь\\.",
    .delay = 200
  },
  { // 14
    .img = boy2_img,
    .atr = boy2_atr,
    .text = "Я\\ готов\\ к\\ любым\\ испытаниям\\!\\ Расскажи\\,\\ как\\ мне\\ "
      "найти\\ этот\nпруд\\#\\ Куда\\ мне\\ идти\\#",
    .delay = 200
  },
  { // 15
    .img = oldman1_img,
    .atr = oldman1_atr,
    .text = "Добро\\,\\ молодой\\ искатель\\.\\ Иди\\ глубоко\\ в\\ лес\\,\\ "
      "следуй\\ по\\ тропинке\nсправа\\ от\\ старой\\ ивы\\.\\ Она\\ приведет\\ "
      "тебя\\ к\\ прекрасному\\ пруду\\,\\ где\\ можно\\ встретить\\ гриб\\-\\чудо\\.\\ "
      "Удачи\\ тебе\\,\\ смелый\\ путник\\!",
    .delay = 200
  },
};

void unpack(char *src, char *dst);
void delay(unsigned int interval);
void print(char *message, unsigned char x, unsigned char y);
void show_slide(slide_struct_t *slide);

void main() {
  for (;;) {
    for (unsigned char slide = FIRST_SLIDE; slide <= LAST_SLIDE; slide++) {
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
      x = 0;
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
    delay(1);
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

