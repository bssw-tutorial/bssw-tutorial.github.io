# Makefile for mesh_app, verify_mesh, verify_particles, and verify_movement

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99
LDFLAGS = -lm

# Executables
TARGETS = mesh_app verify_mesh verify_particles verify_movement 

# Object lists
MAIN_OBJS             = main.o mesh.o
VERIFY_MESH_OBJS      = verify_mesh.o mesh.o
VERIFY_PARTICLES_OBJS = verify_particles.o mesh.o 
VERIFY_MOVEMENT_OBJS  = verify_movement.o mesh.o particles.o move_particles.o

.PHONY: all clean

all: $(TARGETS)

mesh_app: $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJS) $(LDFLAGS)

verify_mesh: $(VERIFY_MESH_OBJS)
	$(CC) $(CFLAGS) -o $@ $(VERIFY_MESH_OBJS) $(LDFLAGS)

verify_particles: $(VERIFY_PARTICLES_OBJS)
	$(CC) $(CFLAGS) -o $@ $(VERIFY_PARTICLES_OBJS) $(LDFLAGS)

verify_movement: $(VERIFY_MOVEMENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $(VERIFY_MOVEMENT_OBJS) $(LDFLAGS)

# Generic rule for building .o files
%.o: %.c constants.h mesh.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGETS)
