#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "constants.h"
#include "mesh.h"

#define MAX_LINE 512

int main(void) {
    char filename[MAX_LINE];
    printf("Enter sample output file name: ");
    if (scanf("%511s", filename) != 1) {
        fprintf(stderr, "Error reading filename\n");
        return 1;
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    int NDIM = 0, NX = 0, nblk = 0, npart = 0;
    float lbnd = 0.0f, ubnd = 0.0f;
    int *boundaries = NULL;
    char line[MAX_LINE];

    /* Buffers for printed particle info */
    int *print_blkID = NULL;
    float (*print_coords)[MDIM] = NULL;

    /* Parse header until npart */
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "  NDIM = %d", &NDIM) == 1) continue;
        if (sscanf(line, "  NX = %d", &NX) == 1) continue;
        if (sscanf(line, "  lbnd = %f", &lbnd) == 1) continue;
        if (sscanf(line, "  ubnd = %f", &ubnd) == 1) continue;
        if (sscanf(line, "  nblk = %d", &nblk) == 1) continue;
        if (strncmp(line, "  boundaries:", 12) == 0) {
            boundaries = malloc(NDIM * sizeof(int));
            char *p = strchr(line, ':');
            for (int i = 0; i < NDIM; ++i) {
                if (sscanf(p + 1, " %d", &boundaries[i]) != 1) {
                    fprintf(stderr, "Failed to read boundary %d\n", i);
                    fclose(fp);
                    return 1;
                }
                p = strchr(p + 1, ' ');
            }
            continue;
        }
        if (sscanf(line, "  npart = %d", &npart) == 1) break;
    }

    /* Allocate for parsed particles */
    print_blkID = malloc(npart * sizeof(int));
    print_coords = malloc(npart * sizeof(*print_coords));
    if (!print_blkID || !print_coords) {
        perror("malloc"); fclose(fp); return 1;
    }

    /* Skip to particle listing */
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Particles", 9) == 0) break;
    }

    /* Read printed particles */
    for (int i = 0; i < npart; ++i) {
        if (!fgets(line, sizeof(line), fp)) {
            fprintf(stderr, "Unexpected EOF at particle %d\n", i+1);
            fclose(fp);
            return 1;
        }
        int idx;
        if (sscanf(line, "Particle %d: blkID=%d", &idx, &print_blkID[i]) != 2) {
            fprintf(stderr, "Parse error for particle %d\n", i+1);
            fclose(fp);
            return 1;
        }
        char *p = strstr(line, "coords=");
        if (!p) {
            fprintf(stderr, "Missing coords= on line %d\n", i+1);
            fclose(fp);
            return 1;
        }
        p += 7;
        for (int d = 0; d < NDIM; ++d) {
            if (sscanf(p, " %f", &print_coords[i][d]) != 1) {
                fprintf(stderr, "Failed to read coord %d of particle %d\n", d, i+1);
                fclose(fp);
                return 1;
            }
	    p++;
            p = strchr(p, ' ');
        }
    }
    fclose(fp);

    /* Recreate mesh and particles */
    float domainbnds[MDIM][HIGH];
    int domainbc[MDIM];
    int totalBlocks;
    Block *blocks = createMesh(NDIM, NX, lbnd, ubnd, nblk,
                               boundaries, domainbnds, domainbc,
                               &totalBlocks);
    if (!blocks) { fprintf(stderr, "createMesh failed\n"); return 1; }
    Particle *particles = createLattice(NDIM, npart, totalBlocks,
                                        blocks, domainbnds);
    if (!particles) { fprintf(stderr, "createLattice failed\n"); return 1; }

    /* Verify particles */
    int success = 1;
    for (int i = 0; i < npart; ++i) {
        if (particles[i].blkID != print_blkID[i]) {
            printf("Particle %d blkID mismatch: got %d, expected %d\n",
                   i+1, particles[i].blkID, print_blkID[i]);
            success = 0;
        }
        for (int d = 0; d < NDIM; ++d) {
            if (fabsf(particles[i].coords[d] - print_coords[i][d]) > 1e-6f) {
                printf("Particle %d coord[%d] mismatch: got %.6f, expected %.6f\n",
                       i+1, d,
                       particles[i].coords[d], print_coords[i][d]);
                success = 0;
            }
        }
    }

    printf(success ? "Particle verification PASSED.\n" : "Particle verification FAILED.\n");

    free(boundaries);
    free(blocks);
    free(particles);
    free(print_blkID);
    free(print_coords);
    return success ? 0 : 1;
}

