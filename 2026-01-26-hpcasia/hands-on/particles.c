#include <stdio.h>
#include "mesh.h"

/**
 * Confirm that a given particle is associated with the correct block.
 *
 * @param NDIM          Number of dimensions in the mesh
 * @param particle      Pointer to the Particle to check
 * @param totalBlocks   Total number of blocks from createMesh
 * @param blocks        Array of Block structs
 * @param domainbnds    Mesh domain bounds from createMesh
 * @return              1 if the particle's blkID matches the computed block, 0 otherwise
 */
int check_particle(int NDIM,
                   const Particle *particle,
                   int totalBlocks,
                   const Block blocks[],
                   const float domainbnds[][HIGH])
{
    /* Compute expected block ID using the particle's coordinates */
    int expected = getBlkID(NDIM,
                            particle->coords,
                            totalBlocks,
                            blocks,
                            domainbnds);
    /* Return whether it matches the stored blkID */
    return (expected == particle->blkID);
}
