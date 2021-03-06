<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global item
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global id
 * @global msg
 */
// перемещение в контактах
$items = explode("|", $loc_i[$loc][$login]["msg"]);
if ($msg == "up") {
    for ($i = 0; $i < count($items); $i++) {
        if ($items[$i] == $id) {
            break;
        }
    }
    if ($i == count($items)) {
        msg("Нет такого");
    }
    if ($i == 0) {
        array_push($items, $items[$i]);
        array_shift($items);
    } else {
        $tc            = $items[$i - 1];
        $items[$i - 1] = $items[$i];
        $items[$i]     = $tc;
    }
    $loc_i[$loc][$login]["msg"] = implode("|", $items);
    msg("Пользователь передвинут вверх.");
}
if ($msg == "down") {
    for ($i = 0; $i < count($items); $i++) {
        if ($items[$i] == $id) {
            break;
        }
    }
    if ($i == count($items)) {
        msg("Нет такого");
    }
    if ($i == count($items) - 1) {
        array_unshift($items, $items[$i]);
        array_pop($items);
    } else {
        $tc            = $items[$i + 1];
        $items[$i + 1] = $items[$i];
        $items[$i]     = $tc;
    }

    $loc_i[$loc][$login]["msg"] = implode("|", $items);
    msg("Пользователь передвинут вниз.");
}