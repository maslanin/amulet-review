<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global tchar
 * @global char
 */
// увеличивает броню цели на int

if (isset($loc_i[$loc][$to]) && substr($to, 0, 2) == 'u.') {
    calcparam($loc, $to);    // чтобы постоянно не увеличивать каждый раз, сбивает эффект заклинания Сила
    $twar   = explode("|", $loc_i[$loc][$to]["war"]);
    $skills = explode("|", $loc_i[$loc][$login]["skills"]);

    $twar[5] += $skills[2];
    $loc_i[$loc][$to]["war"] = implode("|", $twar);
    addjournal($loc, $to, "Броня +" . $skills[2]);
    if ($to != $login) {
        addjournal($loc, $login, $tchar[0] . ": броня +" . $skills[2]);
    }
} else {
    addjournal($loc, $login, "Действует только на людей");
}

