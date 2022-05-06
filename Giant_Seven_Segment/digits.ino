void digitZero(int offset, uint32_t colour){
    stripClock.fill(colour, (0 + offset), 24);
    stripClock.fill(colour, (32 + offset), 24);
}

void digitOne(int offset, uint32_t colour){
    stripClock.fill(colour, (0 + offset), 8);
    stripClock.fill(colour, (32 + offset), 8);
}

void digitTwo(int offset, uint32_t colour){
    stripClock.fill(colour, (0 + offset), 16);
    stripClock.fill(colour, (24 + offset), 8);
    stripClock.fill(colour, (40 + offset), 16);
}

void digitThree(int offset, uint32_t colour){
    stripClock.fill(colour, (0 + offset), 16);
    stripClock.fill(colour, (24 + offset), 24);
}

void digitFour(int offset, uint32_t colour){
    stripClock.fill(colour, (0 + offset), 8);
    stripClock.fill(colour, (16 + offset), 24);
}

void digitFive(int offset, uint32_t colour){
    stripClock.fill(colour, (8 + offset), 40);
}

void digitSix(int offset, uint32_t colour){
    stripClock.fill(colour, (8 + offset), 48);
}

void digitSeven(int offset, uint32_t colour){
    stripClock.fill(colour, (0 + offset), 16);
    stripClock.fill(colour, (32 + offset), 8);
}

void digitEight(int offset, uint32_t colour){
    stripClock.fill(colour, (0 + offset), 56);
}

void digitNine(int offset, uint32_t colour){
    stripClock.fill(colour, (0 + offset), 40);
}
