#include "unit1.h"

struct vect summ(struct vect a, struct vect b)
{
    struct vect c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
};

struct vect summ3(struct vect vector1, struct vect vector2, struct vect vector3)
{
    return summ(vector1 , summ(vector2, vector3));
};
