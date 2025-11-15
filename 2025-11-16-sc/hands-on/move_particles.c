#include <stdio.h>
#include <math.h>
#include "constants.h"
#include "mesh.h"


/**
 * Handle periodic boundary conditions for a single particle.
 * If the particle has moved outside the domain, wrap its position.
 * After wrapping, update its blkID.
 *
 * @param NDIM          Number of dimensions
 * @param p             Pointer to the particle to adjust
 * @param totalBlocks   Total number of blocks in mesh
 * @param blocks        Array of Block structs
 * @param domainbnds    Mesh domain bounds [NDIM][LOW|HIGH]
 * @param domainbc      Boundary conditions per dimension
 */
void handle_boundary(int NDIM,
                     Particle *p,
                     int totalBlocks,
                     const Block blocks[],
                     const float domainbnds[][HIGH],
                     const int domainbc[])
{
    for (int d = 0; d < NDIM; ++d) {
        float pos   = p->coords[d];
        float low   = domainbnds[d][LOW-1];
        float high  = domainbnds[d][HIGH-1];
        float L     = high - low;

        if (pos < low && domainbc[d] == PERIODIC) {
            p->coords[d] = L + pos;
        } else if (pos > high && domainbc[d] == PERIODIC) {
            p->coords[d] = L - pos;
        }
    }
    /* Update block ID after wrapping */
    p->blkID = getBlkID(NDIM, p->coords, totalBlocks, blocks, domainbnds);
}

/**
 * Move particles by -1.5 in each dim for a number of steps,
 * updating block IDs or handling boundaries as needed.
 *
 * @param NDIM          Number of dimensions
 * @param nSteps        Number of movement steps
 * @param npart         Number of particles
 * @param particles     Array of Particle structs
 * @param totalBlocks   Total number of blocks from createMesh
 * @param blocks        Array of Block structs
 * @param domainbnds    Mesh domain bounds
 * @param domainbc      Boundary conditions per dimension
 */
void move_particles(int NDIM,
                    int nSteps,
                    int npart,
                    Particle *particles,
                    int totalBlocks,
                    const Block blocks[],
                    const float domainbnds[][HIGH],
                    const int domainbc[])
{
    for (int step = 0; step < nSteps; ++step) {
        for (int i = 0; i < npart; ++i) {
            Particle *p = &particles[i];
            /* Shift position */
	    for (int d = 0; d < NDIM; ++d) {
	       p->coords[d] -= 1.5f;
	    /* Invoke the pluggable mover */
	   
            }

            /* Determine new block */
            int newBlk = getBlkID(NDIM, p->coords, totalBlocks, blocks, domainbnds);

            if (newBlk == p->blkID) {
                /* Still in same block, nothing to do */
                continue;
            } else if (newBlk > 0) {
                /* Successfully moved to a new block */
                p->blkID = newBlk;
            } else {
                /* Outside domain: apply boundary handling */
                handle_boundary(NDIM, p, totalBlocks, blocks, domainbnds, domainbc);
            }
        }
    }
       /* Print particle info */
    printf("\nParticles (total %d):\n", npart);
    for (int p = 0; p < npart; ++p) {
        printf("Particle %d: blkID=%d, coords=",
               p+1, particles[p].blkID);
        for (int d = 0; d < NDIM; ++d) {
            printf(" %.6f", particles[p].coords[d]);
        }
        printf("\n");
    }

}
