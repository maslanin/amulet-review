<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 */
// зачаровать до 5 минут животных, сопровождают и охраняют

if (isset($loc_i[$loc][$to]) && substr($to, 0, 4) == 'n.a.') {
    if (isset($loc_i[$loc][$to]["owner"])) {
        msg("Это животное принадлежит другому");
    }
    $timemin = 60;
    $timemax = 5 * 60;
    $follow  = 1;
    $b       = 1;
    if (substr($to, 0, 11) == "n.a.b.jarpt" && rand(0, 100) >= 5) {
        addjournal($loc, $login, "Повышенный иммунитет к приручению");
        $b = 0;
    }
    if ($b) {
        $loc_i[$loc][$to]["owner"] = $login . "|" . $login . "|" . $login . "|" . (time() + rand(60, 5 * 60)) . "|0";
    }
} else {
    addjournal($loc, $login, "Заклинание действует только на животных");
}