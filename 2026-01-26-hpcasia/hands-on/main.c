#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "mesh.h"

int main(void) {
    int NDIM, NX, nblk, npart;
    float lbnd, ubnd;

    /* Read inputs */
    printf("Enter NDIM and NX: ");
    if (scanf("%d %d", &NDIM, &NX) != 2) return 1;

    printf("Enter lower bound (lbnd): ");
    if (scanf("%f", &lbnd) != 1) return 1;

    printf("Enter upper bound (ubnd): ");
    if (scanf("%f", &ubnd) != 1) return 1;

    printf("Enter number of blocks per dimension (nblk): ");
    if (scanf("%d", &nblk) != 1) return 1;

    /* Allocate and read boundary conditions */
    int *boundaries = malloc(NDIM * sizeof(int));
    if (!boundaries) return 1;
    printf("Enter %d boundary conditions: ", NDIM);
    for (int i = 0; i < NDIM; ++i) {
        if (scanf("%d", &boundaries[i]) != 1) return 1;
    }

    printf("Enter number of particles (npart): ");
    if (scanf("%d", &npart) != 1) return 1;

    /* Print input values */
    printf("\nInputs read:\n");
    printf("  NDIM = %d\n  NX = %d\n  lbnd = %.6f\n  ubnd = %.6f\n  nblk = %d\n", NDIM, NX, lbnd, ubnd, nblk);
    printf("  boundaries:");
    for (int i = 0; i < NDIM; ++i) printf(" %d", boundaries[i]);
    printf("\n  npart = %d\n", npart);

    /* Create mesh */
    float domainbnds[MDIM][HIGH];
    int domainbc[MDIM];
    int totalBlocks = 0;
    Block *blocks = createMesh(NDIM, NX, lbnd, ubnd, nblk,
                               boundaries, domainbnds, domainbc,
                               &totalBlocks);
    if (!blocks) {
        fprintf(stderr, "Error: mesh creation failed\n");
        free(boundaries);
        return 1;
    }

    /* Print block info */
    printf("\nMesh blocks (total %d):\n", totalBlocks);
    for (int i = 0; i < totalBlocks; ++i) {
        printf("Block %d:", blocks[i].blkID);
        for (int d = 0; d < NDIM; ++d) {
            printf(" [%.6f, %.6f]",
                   blocks[i].bbnd[d][LOW-1],
                   blocks[i].bbnd[d][HIGH-1]);
        }
        printf("\n");
    }

    /* Create lattice of particles */
    Particle *particles = createLattice(NDIM, npart, totalBlocks,
                                        blocks, domainbnds);
    if (!particles) {
        fprintf(stderr, "Error: lattice creation failed\n");
        free(blocks);
        free(boundaries);
        return 1;
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

    /* Cleanup */
    free(particles);
    free(blocks);
    free(boundaries);
    return 0;
}
