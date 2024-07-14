#include "Colors.h"

//Creating the different colors that are used in the game
const Color darkGrey = { 26, 31, 40, 225 };
const Color green = { 47, 230, 23, 225 };
const Color red = { 232, 18, 18, 225 };
const Color orange = { 226, 116, 17, 225 };
const Color yellow = { 237, 234, 4, 225 };
const Color purple = { 166, 0, 247, 225 };
const Color cyan = { 21, 204, 209, 225 };
const Color blue = { 13, 64, 216, 225 };
const Color darkBlue = { 1, 1, 38, 225 };
const Color lightBlue = { 59, 85, 162, 255 };

std::vector<Color> getCellColors() {

	return { darkGrey, green, red, orange, yellow, purple, cyan, blue };
}
