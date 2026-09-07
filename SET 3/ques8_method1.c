#include <stdio.h>
#define MAX 100

struct Queue
{
    int arr[MAX];
    int front, rear;
};

struct Queue q1 = {{0}, 0, -1};
struct Queue q2 = {{0}, 0, -1};

void enqueue(struct Queue *q, int value)
{
    if (q->rear == MAX - 1)
    {
        printf("Queue Overflow\n");
        return;
    }

    q->arr[++q->rear] = value;
}

int dequeue(struct Queue *q)
{
    if (q->front > q->rear)
        return -1;

    return q->arr[q->front++];
}

int isEmpty(struct Queue *q)
{
    return q->front > q->rear;
}

void push(int value)
{
    // Step 1: Insert into q2
    enqueue(&q2, value);

    // Step 2: Move all q1 elements to q2
    while (!isEmpty(&q1))
    {
        enqueue(&q2, dequeue(&q1));
    }

    // Step 3: Swap q1 and q2
    struct Queue temp = q1;
    q1 = q2;
    q2 = temp;

    printf("%d pushed into stack\n", value);
}

void pop()
{
    int value;

    if (isEmpty(&q1))
    {
        printf("Stack Underflow\n");
        return;
    }

    value = dequeue(&q1);
    printf("%d popped from stack\n", value);
}

void display()
{
    int i;

    if (isEmpty(&q1))
    {
        printf("Stack is Empty\n");
        return;
    }

    printf("Stack elements: ");

    for (i = q1.front; i <= q1.rear; i++)
    {
        printf("%d ", q1.arr[i]);
    }

    printf("\n");
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n--- Stack Using Two Queues ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                pop();
                break;

            case 3:
                display();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}
