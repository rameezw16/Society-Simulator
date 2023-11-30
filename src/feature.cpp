#include "../include/features/feature.h"

Feature::Feature(const int pos_x, const int pos_y, const int spritesheet_pos_x, const int spritesheet_pos_y)
	: Entity ( pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};

void Feature::step() {std::cout << "This is called for some reason;";};

Feature::~Feature() = default;
