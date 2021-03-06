<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global num
 * @global id
 */

use MaxDark\Amulet\OldCode\PageType;

$loc_i[$loc][$login]["macrol"] = "take|$take||";
if ($take) {            //linkПоднять
    // $take=id предмета [$id=id предмета с трупа, $num=кол-во]
    if (substr($take, 0, 9) == "n.a.losh.") {
        include "f_usekon.inc";
    }

    if ($take == "i.flag" && isset($loc_i[$loc]["i.flag"]) && ! $char[8]) {
        addjournal($loc, "all", $char[0] . " поднял флаг!", $login);
        unset($loc_i[$loc]["i.flag"]);
        $game["floc"]  = $loc;
        $game["fid"]   = $login;
        $game["fchar"] = $char[0];
        calcparam($loc, $login);
        $char = explode("|", $loc_i[$loc][$login]["char"]);
    }

    // проверки
    if (substr($take, 0, 8) == 'i.s.note' || substr($take, 0, 8) == 'i.s.book') {
        $look = $take;
    } else {
        if (substr($take, 0, 2) != 'i.') {
            msg("<p>И как вы себе это представляете? :-)");
        }
        if (isset($loc_i[$loc][$take])) {
            if ($take == "i.s.lodka") {
                include "f_uselodka.inc";
            }
            if ($take == "i.s.arena") {
                $b = 0;
                if ($char[8]) {
                    $b = 1;
                }
                if ( ! $b) {
                    $b = 1;
                    foreach (array_keys($loc_i[$loc]) as $i) {
                        if (substr($i, 0, 2) == "u." && $i != $login) {
                            $tc = explode("|", $loc_i[$loc][$i]["char"]);
                            if ( ! $tc[8]) {
                                $b = 0;
                                break;
                            }
                        }
                    }
                }
                if ($b) {
                    manageNPC($login, $loc, "x1086x501");
                    msg("Вы покинули арену");
                } else {
                    msg("Покинуть арену можно либо призраком, либо оставшись единственным в живых.");
                }
            }
            if (substr($take, 0, 4) == 'i.s.' && substr($take, 0, 6) != 'i.s.d.' && substr($take, 0, 7) != 'i.s.res' &&
                substr($take, 0, 11) != 'i.s.portal_'
            ) {
                msg("<p>Этот предмет нельзя взять");
            }
            if ($char[8]) {
                if (substr($take, 0, 7) == 'i.s.res') {
                    ressurect($loc, $login);
                } else {
                    msg("<p>Вы призрак и поэтому не можете ничего передать, поднять или бросить, найдите лекаря или камень воскрешения");
                }
            }
            $def  = get_value($loc_i[$loc][$login], "def");
            $tdef = explode("|", $def ? $def : '|');
            if ($tdef[0] == "p.d.o") {
                msg("В глухой обороне, нельзя брать предметы!");
            }
            //  с трупа
            if (substr($take, 0, 6) == 'i.s.d.') {
                if ($id) {
                    include "f_takediedid.inc";
                }
                if ( ! $id) {
                    include "f_takediednoid.inc";
                }
            }

            // из локации
            if (substr($take, 0, 4) != 'i.s.') {
                $item = explode("|", $loc_i[$loc][$take]);
                // проверим кол-во
                if ($item[1] > 1 && ! $num) {        // запросим кол-во
                    $stmp = "<p>Укажите количество:\n<br/><input name=\"num\" format=\"*N\" maxlength=\"7\" value=\"" .
                            $item[1] . "\"/>\n<br/><a href=\"$PHP_SELF?sid=$sid&take=$take&num=$(num)\">Отправить</a>";
                    msg($stmp, "Взять", 1, PageType::MSG, "num", $item[1]);
                }
                if ( ! $num || $num < 1) {
                    $num = 1;
                }    // если не указано, то 1 предмет
                if ($num > $item[1]) {
                    $num = $item[1];
                }    // и максимум берем все что есть
                manageItems($loc, "loc", $login, $take, $num, "items", "items", 1, -1, 1);
            }

            // портал
            if (substr($take, 0, 11) == 'i.s.portal_') {
                manageNPC($login, $loc, substr($take, 11));
                msg("Вы проходите сквозь портал и оказываетесь в совершенно другом месте");
            }

        }// если есть 
    }//else s.book
}
