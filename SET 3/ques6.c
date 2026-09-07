#include <stdio.h>
#define MAX 5
 
int queue[MAX];
int front = -1, rear = -1;
 
void enqueue(int value)
{
    if ((rear + 1) % MAX == front)
    {
        printf("Queue is Full\n");
        return;
    }
 
    if (front == -1)
        front = 0;
 
    rear = (rear + 1) % MAX;
    queue[rear] = value;
 
    printf("%d inserted into queue\n", value);
}
 
void dequeue()
{
    int value;
 
    if (front == -1)
    {
        printf("Queue is Empty\n");
        return;
    }
 
    value = queue[front];
 
    if (front == rear)
    {
        // Only one element was present
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % MAX;
    }
 
    printf("%d deleted from queue\n", value);
}
 
void display()
{
    int i;
 
    if (front == -1)
    {
        printf("Queue is Empty\n");
        return;
    }
 
    printf("Queue elements: ");
 
    i = front;
    while (1)
    {
        printf("%d ", queue[i]);
 
        if (i == rear)
            break;
 
        i = (i + 1) % MAX;
    }
 
    printf("\n");
}
 
int main()
{
    int choice, value;
 
    while (1)
    {
        printf("\n--- Circular Queue Using Array ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
 
        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                enqueue(value);
                break;
 
            case 2:
                dequeue();
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