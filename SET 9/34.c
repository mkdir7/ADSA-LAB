#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

Point p0;

int orientation(Point a, Point b, Point c) {
    long long value;

    value = (long long)(b.y - a.y) * (c.x - b.x) -
            (long long)(b.x - a.x) * (c.y - b.y);

    if (value == 0)
        return 0;

    if (value > 0)
        return 1;

    return 2;
}

long long distanceSq(Point a, Point b) {
    return (long long)(a.x - b.x) * (a.x - b.x) +
           (long long)(a.y - b.y) * (a.y - b.y);
}

void swap(Point *a, Point *b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

int compare(const void *a, const void *b) {
    Point p1 = *(Point *)a;
    Point p2 = *(Point *)b;
    int o = orientation(p0, p1, p2);

    if (o == 0) {
        if (distanceSq(p0, p1) < distanceSq(p0, p2))
            return -1;
        return 1;
    }

    if (o == 2)
        return -1;

    return 1;
}

void convexHull(Point points[], int n) {
    int lowest = 0;
    int i;
    int top;
    Point *hull;

    if (n < 3) {
        printf("Convex hull cannot be formed\n");
        return;
    }

    for (i = 1; i < n; i++) {
        if (points[i].y < points[lowest].y ||
            (points[i].y == points[lowest].y &&
             points[i].x < points[lowest].x)) {
            lowest = i;
        }
    }

    swap(&points[0], &points[lowest]);
    p0 = points[0];

    qsort(points + 1, n - 1, sizeof(Point), compare);

    hull = (Point *)malloc(n * sizeof(Point));

    hull[0] = points[0];
    hull[1] = points[1];
    hull[2] = points[2];

    top = 2;

    for (i = 3; i < n; i++) {
        while (top >= 1 &&
               orientation(hull[top - 1], hull[top], points[i]) != 2) {
            top--;
        }

        top++;
        hull[top] = points[i];
    }

    printf("Convex Hull:\n");

    for (i = 0; i <= top; i++)
        printf("(%d, %d)\n", hull[i].x, hull[i].y);

    free(hull);
}

int main() {
    int n;
    int i;
    Point *points;

    printf("Enter number of points: ");
    scanf("%d", &n);

    points = (Point *)malloc(n * sizeof(Point));

    printf("Enter coordinates:\n");

    for (i = 0; i < n; i++)
        scanf("%d %d", &points[i].x, &points[i].y);

    convexHull(points, n);

    free(points);

    return 0;
}