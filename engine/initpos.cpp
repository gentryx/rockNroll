INT8 currPos[STONES] = { 0, 1, 2, SIZEX + 0, SIZEX + 1, 2 * SIZEX + 0};
UINT32 i = 0;
do {
    for (UINT32 j = 0; j < STONES; j++) {
        Positions[i][j] = currPos[j];
    }
    i++;
} while (std::next_permutation(currPos, currPos+STONES));
