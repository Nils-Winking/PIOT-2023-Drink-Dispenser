//
// Created by Emilia on 24.12.2023.
//
#ifndef PIOT_2023_DRINK_DISPENSER_PREFERENCE_H
#define PIOT_2023_DRINK_DISPENSER_PREFERENCE_H

#include "Ingredient.h"

class Preference {
public:
    Preference(Ingredient *ingredient, int count);

    Ingredient getIngredient(int index);
    int getIngredientCount();
private:
    Ingredient *ingredients;
    int ingredientCount;
};


#endif //PIOT_2023_DRINK_DISPENSER_PREFERENCE_H
