<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global game
 */
// увеличивает макс. жизнь цели на int*2

if (isset($loc_i[$loc][$to]) && substr($to, 0, 2) == 'u.') {
    $tchar    = explode("|", $loc_i[$loc][$to]["char"]);
    $tskills  = explode("|", $loc_i[$loc][$to]["skills"]);
    $skills   = explode("|", $loc_i[$loc][$login]["skills"]);
    $tchar[2] = 10 + $tskills[0] * 10 + $skills[2] * 2;
    if ($game["fid"] == $to && $game["floc"] == $loc) {
        $tchar[2] += 10;
    }
    if (strpos($loc_i[$loc][$to]["equip"], "..am") !== false) {
        $tchar[2] += 5;
    }
    if (strpos($loc_i[$loc][$to]["equip"], "..ne") !== false) {
        $tchar[2] += 10;
    }
    if (strpos($loc_i[$loc][$to]["equip"], "..on") !== false) {
        $tchar[2] -= 10;
    }
    $tchar[5]                 = time();
    $loc_i[$loc][$to]["char"] = implode("|", $tchar);
    addjournal($loc, $to, "Макс.жизнь +" . ($skills[2] * 2));
    if ($to != $login) {
        addjournal($loc, $login, $tchar[0] . ": макс.жизнь +" . ($skills[2] * 2));
    }
} else {
    addjournal($loc, $login, "Действует только на людей");
}

