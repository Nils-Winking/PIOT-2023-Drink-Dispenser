//
// Created by Emilia on 24.12.2023.
//

#ifndef PIOT_2023_DRINK_DISPENSER_INGREDIENT_H
#define PIOT_2023_DRINK_DISPENSER_INGREDIENT_H

#include <Arduino.h>

class Ingredient {
public:
    Ingredient();

    Ingredient(int id, int amount);
    int getId();
    int getAmount();

private:
    int id{};
    int amount{};
};


#endif //PIOT_2023_DRINK_DISPENSER_INGREDIENT_H
