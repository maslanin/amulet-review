<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 */

if ($loc_i[$loc]) {
    foreach ($loc_i[$loc] as $i => $val) {
        if (substr($i, 0, 2) == 'n.') {
            $tchar                   = explode("|", $loc_i[$loc][$i]["char"]);
            $tchar[7]                = "";
            $loc_i[$loc][$i]["char"] = implode("|", $tchar);
        }
    }
}