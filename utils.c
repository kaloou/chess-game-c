#include "utils.h"
#include "board.h"

bool is_legal_position(int row, int col)
{
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
} 