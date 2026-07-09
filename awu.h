#ifndef AWU_H
#define AWU_H

#define AWU ((volatile awu_t *)0x0050F0)

typedef struct
{
    volatile unsigned char CSR1; /* control/status  */
    volatile unsigned char APR;  /* asynchronous prescaler buffer */
    volatile unsigned char TBR;  /* timebase selection */
} awu_t;

#endif /* AWU_H */
