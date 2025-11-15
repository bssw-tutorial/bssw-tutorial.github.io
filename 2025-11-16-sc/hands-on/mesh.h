#ifndef MESH_H
#define MESH_H

#include "constants.h"

/** Block descriptor */
typedef struct {
    int  blkID;              /* unique block identifier */
    float bbnd[MDIM][HIGH];  /* block bounds */
} Block;

/** Particle descriptor */
typedef struct {
    int   blkID;             /* block ID */
    float coords[MDIM];      /* coordinates */
} Particle;

/* Create the mesh */
Block *createMesh(int NDIM,
                  int NX,  /* unused, we’ll silence it in mesh.c */
                  float lbnd,
                  float ubnd,
                  int nblk,
                  const int boundaries[],
                  float domainbnds[][HIGH],
                  int domainbc[],
                  int *out_nBlocks);

/* Find which block contains pos (or -1 if outside) */
int getBlkID(int NDIM,
             const float pos[],
             int totalBlocks,
             const Block blocks[],
             const float domainbnds[][HIGH]);

/* Build a lattice of npart particles */
Particle *createLattice(int NDIM,
                        int npart,
                        int totalBlocks,
                        const Block blocks[],
                        const float domainbnds[][HIGH]);

#endif /* MESH_H */
