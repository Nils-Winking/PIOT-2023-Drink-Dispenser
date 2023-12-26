//
// Created by Emilia on 24.12.2023.
//

#include "Preference.h"

Ingredient Preference::getIngredient(int index) {
    return ingredients[index];
}

int Preference::getIngredientCount() {
    return ingredientCount;
}

Preference::Preference(Ingredient *ingredient, int count): ingredients(ingredient), ingredientCount(count) {

}
