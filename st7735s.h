#ifndef ST7735S_H
#define ST7735S_H

typedef enum st7735s_commands
{
    NOP = (unsigned char)0x00,     /* No Operation */
    SWRESET = (unsigned char)0x01, /* Software Reset */
    SLPIN = (unsigned char)0x10,   /* Sleep In & Booster Off */
    SLPOUT = (unsigned char)0x11,  /* Sleep Out & Booster On */
    PTLON = (unsigned char)0x12,   /* Partial On */
    NORON = (unsigned char)0x13,   /* Partial Off */
    INVOFF = (unsigned char)0x20,  /* Display Inversion Off */
    INVON = (unsigned char)0x21,   /* Display Inversion On */
    GAMSET = (unsigned char)0x26,  /* Gamma Set */
    DISPOFF = (unsigned char)0x28, /* Display Off */
    DISPON = (unsigned char)0x29,  /* Display On */
    CASET = (unsigned char)0x2A,   /* Column Address Set */
    RASET = (unsigned char)0x2B,   /* Row Address Set */
    RAMWR = (unsigned char)0x2C,   /* Memory Write */
    RAMRD = (unsigned char)0x2E,   /* Memory Read  */
    PTLAR = (unsigned char)0x30,   /* Partial Start/End Address Set */
    SCRLAR = (unsigned char)0x33,  /* Scroll Area Set */
    TENOFF = (unsigned char)0x34,  /* Tearing Effect Line Off */
    TENON = (unsigned char)0x35,   /* Tearing Effect Mode Set & On */
    MADCTL = (unsigned char)0x36,  /* Memory Access Control */
    IDMOOFF = (unsigned char)0x38, /* Idle Mode On */
    IDMOON = (unsigned char)0x39,  /* Idle Mode Off */
    COLMOD = (unsigned char)0x3A,  /* Interface Pixel Format */
    RDID1 = (unsigned char)0xDA,   /* Read ID1 */
    RDID2 = (unsigned char)0xDB,   /* Read ID2 */
    RDID3 = (unsigned char)0xDC    /* Read ID3 */
} st7735s_commands_t;

#endif /* ST7735S_H */
