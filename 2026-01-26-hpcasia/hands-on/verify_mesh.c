#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "mesh.h"

#define MAX_LINE 256

int main(void) {
    char filename[MAX_LINE];
    printf("Enter sample output file name: ");
    if (scanf("%255s", filename) != 1) {
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

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "  NDIM = %d", &NDIM) == 1) continue;
        if (sscanf(line, "  NX = %d", &NX) == 1) continue;
        if (sscanf(line, "  lbnd = %f", &lbnd) == 1) continue;
        if (sscanf(line, "  ubnd = %f", &ubnd) == 1) continue;
        if (sscanf(line, "  nblk = %d", &nblk) == 1) continue;
        if (strncmp(line, "  boundaries:", 12) == 0) {
            if (NDIM <= 0) {
                fprintf(stderr, "NDIM must be set before boundaries\n");
                fclose(fp);
                return 1;
            }
            boundaries = malloc(NDIM * sizeof(int));
            if (!boundaries) {
                perror("malloc"); fclose(fp); return 1;
            }
            char *p = strchr(line, ':');
            for (int i = 0; i < NDIM; ++i) {
                if (sscanf(p + 1, " %d", &boundaries[i]) != 1) {
                    fprintf(stderr, "Failed to read boundary %d\n", i);
                    free(boundaries);
                    fclose(fp);
                    return 1;
                }
                p = strchr(p + 1, ' ');
                if (!p && i < NDIM - 1) break;
            }
            continue;
        }
        if (sscanf(line, "  npart = %d", &npart) == 1) break;
    }
    fclose(fp);

    if (!boundaries) {
        fprintf(stderr, "No boundary conditions found in file\n");
        return 1;
    }

    /* Create mesh using parsed parameters */
    float domainbnds[MDIM][HIGH];
    int domainbc[MDIM];
    int totalBlocks = 0;
    Block *blocks = createMesh(NDIM, NX, lbnd, ubnd, nblk,
                               boundaries, domainbnds, domainbc,
                               &totalBlocks);
    if (!blocks) {
        fprintf(stderr, "createMesh failed\n");
        free(boundaries);
        return 1;
    }

    /* Verify domain bounds and BCs */
    int success = 1;
    for (int d = 0; d < NDIM; ++d) {
        if (domainbnds[d][LOW-1] != lbnd || domainbnds[d][HIGH-1] != ubnd) {
            fprintf(stderr,
                    "Dimension %d bounds mismatch: got [%.6f, %.6f], expected [%.6f, %.6f]\n",
                    d, domainbnds[d][LOW-1], domainbnds[d][HIGH-1], lbnd, ubnd);
            success = 0;
        }
        if (domainbc[d] != boundaries[d]) {
            fprintf(stderr,
                    "Dimension %d BC mismatch: got %d, expected %d\n",
                    d, domainbc[d], boundaries[d]);
            success = 0;
        }
    }

    if (success) {
        printf("Mesh domain verification PASSED.\n");
    } else {
        printf("Mesh domain verification FAILED.\n");
    }

    free(blocks);
    free(boundaries);
    return success ? 0 : 1;
}
