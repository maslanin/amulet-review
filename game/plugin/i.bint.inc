<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 */
// бинт лечит до 5-5+skill*2 пунктов, но иногда срывается, после использования пропадают (FIX: в будущем пачкаются и можно мыть)

$skills = explode("|", $loc_i[$loc][$login]["skills"]);
if ($skills[22] > 0) {
    $char[6]                     = time() + 5;
    $loc_i[$loc][$login]["char"] = implode("|", $char);
    manageItems($loc, $login, "", "i.bint", 1);

    if (rand(1, 100) < 40 + $skills[22] * 10) {
        $heal = rand(5, 5 + $skills[22] * 2);
        if ($char[1] + $heal > $char[2]) {
            $heal = $char[2] - $char[1];
        }
        $char[1] += $heal;
        $loc_i[$loc][$login]["char"] = implode("|", $char);
        addjournal($loc, $login, "Жизнь +" . $heal);

        addjournal($loc, $login, "Вы забинтовываете раны");
        addjournal($loc, "all", $char[0] . " забинтовывает раны", $login);
    } else {
        addjournal($loc, $login, "Вы не смогли забинтовать раны");
        addjournal($loc, "all", $char[0] . " не смог забинтовать раны", $login);
    }

} else {
    addjournal($loc, $login, "Ваш навык лекаря равен 0, вы не умеете пользоваться бинтами");
}

