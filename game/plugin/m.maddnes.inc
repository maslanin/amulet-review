<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */

if ($loc_i[$loc]) {
    $keys = array_keys($loc_i[$loc]);
    $id   = $keys[rand(0, count($keys) - 1)];
    if ($loc_c[1] == 1 && rand(0, 100) < 80) {
        $id = $login;
        docrim($loc, $login, "провокатор");
    }
    if ((substr($id, 0, 2) == 'u.' || substr($id, 0, 2) == 'n.') && substr($id, 0, 4) != 'n.g.') {
        $idto = $keys[rand(0, count($keys) - 1)];
        if ($id != $idto && (substr($idto, 0, 2) == 'u.' || substr($idto, 0, 2) == 'n.') &&
            substr($idto, 0, 4) != 'n.g.'
        ) {
            $tchar = explode("|", $loc_i[$loc][$id]["char"]);
            addjournal($loc, "all", "Безумие завладело " . $tchar[0] . "!");
            $tchar[7]                 = $idto;
            $loc_i[$loc][$id]["char"] = implode("|", $tchar);
            attack($loc, $id, $idto);
        } else {
            addjournal($loc, "all", "Безумие прошло, никого не тронув");
        }
    } else {
        addjournal($loc, "all", "Безумие никого не тронуло");
    }
}