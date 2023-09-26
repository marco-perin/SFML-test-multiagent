#pragma once

// UI Settings 

#define NUMCELLS_C 20
#define NUMCELLS_R 20

#define SIZE_C 400
#define SIZE_R 400

#define NUM_AGENTS 0

#define GRID_PADDING 20


// 0: off
// 1: really few things
// 2: more things
// 3: lots of stuff
#define VERBOSE 0

// Utils Macros

#define MIN(A, B) ((A < B) ? (A) : (B))

#define CELLSIZE_C ((float)(SIZE_C - 2*GRID_PADDING) / (float)NUMCELLS_C)
#define CELLSIZE_R ((float)(SIZE_R - 2*GRID_PADDING) / (float)NUMCELLS_R)

#define POS2PXL_C(POS) (POS*CELLSIZE_C + GRID_PADDING)
#define POS2PXL_R(POS) (POS*CELLSIZE_R + GRID_PADDING)
#define POS2PXL_XY(POS) POS2PXL_C(POS.x), POS2PXL_R(POS.y)
#define POS2PXL_XY_SEPARATE(X,Y) POS2PXL_C(X), POS2PXL_R(Y)

#define PXL2PADPXL_C(X) (X - ((float)(X * 2*GRID_PADDING) / (float)SIZE_C)+GRID_PADDING)
#define PXL2PADPXL_R(Y) (Y - ((float)(Y * 2*GRID_PADDING) / (float)SIZE_R)+GRID_PADDING) 


#define INCELLSIZE_X (CELLSIZE_C / 3)
#define INCELLSIZE_Y (CELLSIZE_R / 3)
#define INCELLSIZE_MIN (MIN(INCELLSIZE_X, INCELLSIZE_Y))

#define POS2CELL_X(POS) (POS2PXL_C(POS) - INCELLSIZE_MIN + CELLSIZE_C/2)
#define POS2CELL_Y(POS) (POS2PXL_R(POS) - INCELLSIZE_MIN + CELLSIZE_R/2)
#define POS2CELL_XY(POS) POS2CELL_X(POS.x), POS2CELL_Y(POS.y)

#define PXL2POS_C(PXL) ((float)(PXL-GRID_PADDING)/(CELLSIZE_C))
#define PXL2POS_R(PXL) ((float)(PXL-GRID_PADDING)/(CELLSIZE_R))
#define PXL2POS_XY(PXL) PXL2POS_C(PXL.x), PXL2POS_R(PXL.y)
#define PXL2POS_XY_SEPARATE(X,Y) PXL2POS_C(X), PXL2POS_R(Y)