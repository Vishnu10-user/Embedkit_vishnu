#include <stdio.h>
#include <stdint.h>

#define BUFFER_SIZE 8

typedef struct
{
    uint8_t buffer[BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;
} RingBuffer;

/* Initialize buffer */
void RingBuffer_Init(RingBuffer *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

/* Check empty */
uint8_t RingBuffer_IsEmpty(const RingBuffer *rb)
{
    return (rb->count == 0);
}

/* Check full */
uint8_t RingBuffer_IsFull(const RingBuffer *rb)
{
    return (rb->count == BUFFER_SIZE);
}

/* Get count */
uint8_t RingBuffer_Count(const RingBuffer *rb)
{
    return rb->count;
}

/* Write one byte */
int RingBuffer_Write(RingBuffer *rb, uint8_t data)
{
    if (RingBuffer_IsFull(rb))
    {
        return -1;
    }

    rb->buffer[rb->head] = data;

    /* Faster than % BUFFER_SIZE.
       Works only when BUFFER_SIZE is a power of 2 (8 = 2^3). */
    rb->head = (rb->head + 1) & (BUFFER_SIZE - 1);

    rb->count++;

    return 0;
}

/* Read one byte */
int RingBuffer_Read(RingBuffer *rb, uint8_t *data)
{
    if (RingBuffer_IsEmpty(rb))
    {
        return -1;
    }

    *data = rb->buffer[rb->tail];

    /* Faster than % BUFFER_SIZE.
       Works only when BUFFER_SIZE is a power of 2 (8 = 2^3). */
    rb->tail = (rb->tail + 1) & (BUFFER_SIZE - 1);

    rb->count--;

    return 0;
}

int main(void)
{
    RingBuffer rb;
    uint8_t data;

    RingBuffer_Init(&rb);

    /* Step 1 */
    uint8_t initialData[8] =
    {
        0x41, 0x42, 0x43, 0x44,
        0x45, 0x46, 0x47, 0x48
    };

    for (int i = 0; i < 8; i++)
    {
        RingBuffer_Write(&rb, initialData[i]);

        printf("[WRITE] 0x%02X -> OK (count=%u)",
               initialData[i],
               RingBuffer_Count(&rb));

        if (RingBuffer_IsFull(&rb))
        {
            printf(" FULL");
        }

        printf("\n");
    }

    /* Step 2 */
    if (RingBuffer_Write(&rb, 0x99) != 0)
    {
        printf("[WRITE] 0x99 -> FAIL (buffer full)\n");
    }

    /* Step 3 */
    for (int i = 0; i < 3; i++)
    {
        RingBuffer_Read(&rb, &data);

        printf("[READ] -> 0x%02X (count=%u)\n",
               data,
               RingBuffer_Count(&rb));
    }

    /* Step 4 */
    uint8_t newData[3] = {0x49, 0x4A, 0x4B};

    for (int i = 0; i < 3; i++)
    {
        RingBuffer_Write(&rb, newData[i]);

        printf("[WRITE] 0x%02X -> OK (count=%u)\n",
               newData[i],
               RingBuffer_Count(&rb));
    }

    /* Step 5 */
    while (!RingBuffer_IsEmpty(&rb))
    {
        RingBuffer_Read(&rb, &data);

        printf("[READ] -> 0x%02X (count=%u)\n",
               data,
               RingBuffer_Count(&rb));
    }

    /* Step 6 */
    if (RingBuffer_Read(&rb, &data) != 0)
    {
        printf("[READ] (empty) -> FAIL (buffer empty)\n");
    }

    return 0;
}