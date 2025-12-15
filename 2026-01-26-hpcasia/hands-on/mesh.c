#include <stdlib.h>
#include <math.h>
#include "constants.h"
#include "mesh.h"


/**
 * Create a Cartesian mesh decomposed into blocks.
 *
 * @param NDIM         Number of dimensions (<= MDIM)
 * @param NX           Number of data points along each dimension (unused in block decomposition)
 * @param lbnd         Lower coordinate bound along each dimension
 * @param ubnd         Upper coordinate bound along each dimension
 * @param nblk         Number of blocks per dimension
 * @param boundaries   Array of size NDIM defining boundary condition at each dimension
 * @param domainbnds   Output array [NDIM][HIGH] for domain bounds
 * @param domainbc     Output array [NDIM] for domain boundary conditions
 * @param out_nBlocks  Output total number of blocks created
 * @return             Pointer to an array of Block structs (caller must free()), or NULL on failure
 */
Block *createMesh(int NDIM,
                   int NX,
                   float lbnd,
                   float ubnd,
                   int nblk,
                   const int boundaries[],
                   float domainbnds[][HIGH],
                   int domainbc[],
                   int *out_nBlocks)
{
    /* 1) Domain bounds and BC */
    for (int d = 0; d < NDIM; ++d) {
        domainbnds[d][LOW-1]  = lbnd;
        domainbnds[d][HIGH-1] = ubnd;
        domainbc[d]           = boundaries[d];
    }

    /* 2) Compute total blocks = nblk^NDIM */
    int totalBlocks = 1;
    for (int d = 0; d < NDIM; ++d) {
        totalBlocks *= nblk;
    }
    *out_nBlocks = totalBlocks;

    /* 3) Allocate block array */
    Block *blocks = (Block *)malloc(totalBlocks * sizeof(Block));
    if (!blocks) return NULL;

    /* 4) Block size in each dimension */
    float blockSize = (ubnd - lbnd) / nblk;

    /* 5) Populate each block in lexicographic order */
    for (int bi = 0; bi < totalBlocks; ++bi) {
        /* compute multi-index for this block */
        int idx[MDIM] = {0};
        int tmp = bi;
        for (int d = NDIM - 1; d >= 0; --d) {
            idx[d] = tmp % nblk;
            tmp /= nblk;
        }

        blocks[bi].blkID = bi + 1;
        for (int d = 0; d < NDIM; ++d) {
            blocks[bi].bbnd[d][LOW-1]  = lbnd + idx[d] * blockSize;
            blocks[bi].bbnd[d][HIGH-1] = blocks[bi].bbnd[d][LOW-1] + blockSize;
        }
    }

    return blocks;
}

/**
 * Determine block ID for a given point position.
 *
 * @param NDIM          Number of dimensions in the mesh
 * @param pos           Array of size NDIM with point coordinates
 * @param totalBlocks   Total number of blocks created by createMesh
 * @param blocks        Array of Block structs
 * @param domainbnds    Mesh domain bounds from createMesh
 * @return              blkID if inside a block, -1 if outside the domain
 */
int getBlkID(int NDIM,
             const float pos[],
             int totalBlocks,
             const Block blocks[],
             const float domainbnds[][HIGH])
{
    /* Check if point is inside the overall domain */
    for (int d = 0; d < NDIM; ++d) {
        if (pos[d] < domainbnds[d][LOW-1] || pos[d] > domainbnds[d][HIGH-1]) {
            return -1;
        }
    }

    /* Search each block */
    for (int i = 0; i < totalBlocks; ++i) {
        int inside = 1;
        for (int d = 0; d < NDIM; ++d) {
            if (pos[d] < blocks[i].bbnd[d][LOW-1] || pos[d] > blocks[i].bbnd[d][HIGH-1]) {
                inside = 0;
                break;
            }
        }
        if (inside) {
            return blocks[i].blkID;
        }
    }
    return -1;
}

/**
 * Create a regular lattice of particles over the mesh domain.
 *
 * @param NDIM          Number of dimensions in the mesh
 * @param npart         Total number of particles to generate
 * @param totalBlocks   Total number of blocks from createMesh
 * @param blocks        Array of Block structs
 * @param domainbnds    Mesh domain bounds from createMesh
 * @return              Pointer to an array of Particle structs (caller must free()), or NULL on failure
 */
Particle *createLattice(int NDIM,
                        int npart,
                        int totalBlocks,
                        const Block blocks[],
                        const float domainbnds[][HIGH])
{
    Particle *particles = (Particle *)malloc(npart * sizeof(Particle));
    if (!particles) return NULL;

    /* Determine number of points per axis for a roughly uniform grid */
    int nPerAxis = (int)roundf(powf((float)npart, 1.0f / NDIM));
    if (nPerAxis < 1) nPerAxis = 1;
    /* Ensure enough points to cover npart */
    while ((int)powf((float)nPerAxis, NDIM) < npart) {
        ++nPerAxis;
    }

    /* Compute spacing along each dimension */
    float spacing[MDIM];
    for (int d = 0; d < NDIM; ++d) {
        if (nPerAxis > 1) {
            spacing[d] =
                (domainbnds[d][HIGH-1] - domainbnds[d][LOW-1]) / (nPerAxis - 1);
        } else {
            spacing[d] = 0.0f;
        }
    }

    /* Populate particles lexicographically */
    for (int p = 0; p < npart; ++p) {
        int idx = p;
        float pos[MDIM] = {0};
        for (int d = 0; d < NDIM; ++d) {
            int coordIndex = idx % nPerAxis;
            idx /= nPerAxis;
            pos[d] = domainbnds[d][LOW-1] + coordIndex * spacing[d];
            particles[p].coords[d] = pos[d];
        }
        particles[p].blkID = getBlkID(NDIM, pos, totalBlocks, blocks, domainbnds);
    }

    return particles;
}
