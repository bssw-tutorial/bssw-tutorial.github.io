#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Endpoints */
#define LOW        1  /* lower end */
#define HIGH       2  /* upper end */
#define INTERIOR   3  /* interior */
#define MDIM       3  /* maximum possible dimensionality */

/* Axes */
#define IAXIS      1  /* x axis */
#define JAXIS      2  /* y axis */
#define KAXIS      3  /* z axis */

/* Block identifier */
#define BLOCK      4  /* identity of the block */

/* Boundary conditions */
#define PERIODIC   10 /* periodic boundary condition */
#define REFLECTIVE 11 /* reflective boundary condition */
#define OUTFLOW    12 /* outflow boundary condition */

#endif /* CONSTANTS_H */
