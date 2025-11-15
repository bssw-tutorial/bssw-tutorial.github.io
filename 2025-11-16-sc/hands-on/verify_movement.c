#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "mesh.h"

/* Forward declarations (ensure mesh.h declares these too) */
int  check_particle(int NDIM,
                    const Particle *particle,
                    int totalBlocks,
                    const Block blocks[],
                    const float domainbnds[][HIGH]);

void move_particles(int NDIM,
                    int nSteps,
                    int npart,
                    Particle *particles,
                    int totalBlocks,
                    const Block blocks[],
                    const float domainbnds[][HIGH],
                    const int domainbc[]);

int main(void) {
    int NDIM, NX, nblk, npart, nSteps;
    float lbnd, ubnd;

    /* Prompt for mesh parameters */
    printf("Enter NDIM: "); if (scanf("%d", &NDIM)!=1) return 1;
    printf("Enter NX:   "); if (scanf("%d", &NX)!=1) return 1;
    printf("Enter lbnd:"); if (scanf("%f", &lbnd)!=1) return 1;
    printf("Enter ubnd:"); if (scanf("%f", &ubnd)!=1) return 1;
    printf("Enter nblk:"); if (scanf("%d", &nblk)!=1) return 1;

    /* Read boundary conditions */
    int *boundaries = malloc(NDIM*sizeof(int)); if(!boundaries) return 1;
    printf("Enter %d BCs: ", NDIM);
    for(int i=0;i<NDIM;i++) if(scanf("%d",&boundaries[i])!=1) return 1;

    printf("Enter npart:"); if(scanf("%d",&npart)!=1) return 1;
    printf("Enter steps:"); if(scanf("%d",&nSteps)!=1) return 1;

    /* Create mesh and lattice */
    float domainbnds[MDIM][HIGH];
    int   domainbc[MDIM], totalBlocks;
    Block *blocks = createMesh(NDIM,NX,lbnd,ubnd,nblk,
                               boundaries,domainbnds,domainbc,
                               &totalBlocks);
    if(!blocks) { fprintf(stderr,"mesh error\n"); return 1; }

    Particle *particles = createLattice(NDIM,npart,totalBlocks,
                                        blocks,domainbnds);
    if(!particles){ fprintf(stderr,"lattice error\n"); return 1; }

    /* Move and verify */
    move_particles(NDIM,nSteps,npart,
                   particles,totalBlocks,
                   blocks,domainbnds,domainbc);
    int success=1;
    for(int i=0;i<npart;i++){
        if(!check_particle(NDIM,&particles[i],totalBlocks,
                           blocks,domainbnds)){
            printf("Particle %d mismatch: blkID=%d\n",
                   i+1,particles[i].blkID);
            success=0;
        }
    }
    printf(success?"Movement verification PASSED.\n":"Movement verification FAILED.\n");

    free(boundaries);
    free(blocks);
    free(particles);
    return success?0:1;
}
