<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */
// разведение костра

if (isset($loc_i[$loc]["i.log"])) {
    $skills = explode("|", $loc_i[$loc][$login]["skills"]);
    if ($skills[30] > 0) {
        $char[6]                     = time() + 6;
        $loc_i[$loc][$login]["char"] = implode("|", $char);

        manageItems($loc, $login, "", "i.spichka", 1);    // удаляем одну спичку
        manageItems($loc, "loc", "", "i.log", 1);        // удаляем одну ветку

        if (rand(1, 100) < $skills[30] * 20) {
            addjournal($loc, $login, "Вы разожгли костер");
            addjournal($loc, "all", $char[0] . " разжег костер", $login);
            manageItems($loc, "", "loc", "i.s.fire", 1, "items", "items", 0,
                $skills[30] * 60 * 2);    // горит от 2 до 10 минут
            if (rand(1, 100) < 10) {
                addexp($loc, $login, 1);
            }
        } else {
            addjournal($loc, $login, "Вам не удалось разжечь костер");
            addjournal($loc, "all", $char[0] . " пытался расжечь костер", $login);
        }
    } else {
        addjournal($loc, $login, "Ваш навык приготовления пищи равен 0, вы не умеете разводить костры");
    }
} else {
    addjournal($loc, $login, "Вначале положите на землю хотя бы одну ветку (кот. можно срубить топором с дерева)");
}