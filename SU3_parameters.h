//  Simulation Parameters

#define N_SPC 24  //   Spatial lattice size
#define N_T 16    // Temporal lattice size
#define DIM 4     // Space-time lattice dimension

#define VOLUME N_SPC * N_SPC * N_SPC * N_T  //	Number of points in the lattice


#define Nc 3    //  Number of colors


// Other parameters

#define FIRST_CONFIG 1000

#define LAST_CONFIG 1010

#define CONFIG_STEP 10

#define MAX_CONFIGS (LAST_CONFIG - FIRST_CONFIG) / CONFIG_STEP

#define MAX_LENGTH_NAME 300

#define NUM_THREADS 4

#define NEED_BYTE_SWAP_IN 1

#define NEED_BYTE_SWAP_OUT 0

#define NEED_CONV_FROM_DOUBLE 1

//  #define MPI_CODE

