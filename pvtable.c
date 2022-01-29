#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "globals.h"
#include "defs.h"
#include "protoypes.h"

//We track the PV using a triangular array. This is an array of principal variations indexed
//by the distance from the root node. The maximal length of the PV decreases as this distance
//increases, hence the triangular structure of the array.

