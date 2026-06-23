# Исключения и ошибки

Небольшие макросы, позволяющие обрабатывать быстро условия при написании кода.

## Макросы
Исключение, которое может использоваться для проверки. 

При ложном условии - выкидывает ошибку и уходит в бесконечный цикл с миганием светодиода микроконтроллера, а также сбрасывает все протоколы и пины на нижний уровень.

```c
#define assert(x);
```


**Пример**
```c
#include "error.h"

int main(void)
{
    unsigned char a = 0b00000000;
    a |= (1 << 0);

    /* Выкинет здесь исключение и будет мигать светодиод */
    assert(a & (1 << 1));
}

```

Быстрый способ проверки условия с возвращаемым значением.

```c
#define check(y, z);
```

**Пример**
```c
#include "error.h"

unsigned char machine = 0b00000000;

error_t init_machine(void)
{
    check(machine & (1 << 0), FAIL); 
    /* Код не пойдет дальше выполняться, если 0 бит имеет 1 */
    machine |= (1 << 0);
    return 0;
}

error_t busy_machine(void)
{
    check(!(machine & (1 << 0)), FAIL);
    machine |= (1 << 1); /* Имитация бурной деятельности */
    return 0;
}

int main(void)
{
    if (!busy_machine())
        (void)printf("The machine is not initialized");
    if (init_machine())
        (void)busy_machine();
}
```