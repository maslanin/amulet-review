<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global to
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global up
 * @global down
 */
// список инвентори
use MaxDark\Amulet\OldCode\PageType;
use MaxDark\Amulet\OldCode\ViewOptions;

$items = explode("|", $loc_i[$loc][$login]["items"]);
if ($up || $down) {
    include "f_listinvm.inc";
}

// в $to цель, если есть
$stmp = "<p>";
if ( ! $to && ! $start) {
    $stmp .= '<a href="#char">Меню</a>';
    $war = explode("|", $loc_i[$loc][$login]["war"]);
    $stmp .= "<br/>Урон: " . $war[1] . "-" . $war[2] . " [" . $war[0] . "%]<br/>Броня: " . ($war[5] + $war[8]);
} else {
    $stmp .= "Выберите предмет: ";
}
if ($loc_i[$loc][$login]["items"] == "") {
    $stmp .= "<br/>У вас нет ни одного предмета";
} else {

    $items = explode("|", $loc_i[$loc][$login]["items"]);

    if ( ! $start) {
        $start = 0;
    }
    $keys = array_keys($items);

    $listEnd = $start + ViewOptions::getInstance()->getMaxListSize();
    for ($i = $start; $i < $listEnd && $i < count($keys); $i++) {
        if ($items[$keys[$i]]) {
            $k = explode(":", $items[$keys[$i]]);
            $item = findItemByFullId($k[0]);
            $item = $item[0];
            if (strpos($k[0], "..") !== false) {
                $item .= " *";
            }
            if ($k[1] > 1) {
                $item .= " (" . $k[1] . ")";
            }
            $tbp = strpos($loc_i[$loc][$login]["equip"], $k[0]);
            if ($tbp !== false && ($loc_i[$loc][$login]["equip"]{$tbp + strlen($k[0])} == "|" ||
                                   $loc_i[$loc][$login]["equip"]{$tbp + strlen($k[0])} == "")
            ) {
                $item .= " [одето]";
            }
            if ($to) {
                // цель задана - использовать
                $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&to=$to&use=" . $k[0] . "\">" . $item . "</a>";
            } else {
                // возврат в основное меню
                $stmp .= "\n<br/><anchor>" . $item . "<go href=\"#menu\"><setvar name=\"to\" value=\"" . $k[0] .
                         "\"/></go></anchor>";
            }
        }
    }
    if ($start) {
        $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&list=inv\">^ </a>";
    }
    if ($listEnd < count($keys)) {
        if ( ! $start) {
            $stmp .= "\n<br/>";
        }
        $stmp .= "<a href=\"$PHP_SELF?sid=$sid&list=inv&start=" . ($listEnd) . "\">+ (" .
                 (count($keys) - $listEnd) . ")</a>";
    }

    // меню
    $stmp .= "\n</p>\n</card>\n<card id=\"menu\" title=\"Меню\">\n<p>\n";
    $stmp .= "<a href=\"$PHP_SELF?sid=$sid&use=$(to)\">Использовать</a>\n<br/>";
    $stmp .= "<a href=\"$PHP_SELF?sid=$sid&drop=$(to)\">Бросить</a>";
    if (isset($loc_i[$loc][$loc_i[$loc][$login]["trade"]["to"]])) {
        $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&trade=add&id=$(to)\">Добавить в обмен</a>";
    }
    $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&from=$login&look=$(to)\">Инфо</a>\n<br/>";
    $stmp .= "<a href=\"$PHP_SELF?sid=$sid&from=$login&list=inv&up=$(to)\">[Вверх</a> | ";
    $stmp .= "<a href=\"$PHP_SELF?sid=$sid&from=$login&list=inv&down=$(to)\">Вниз</a>]";

}// items!=""

// персонаж
$stmp .= "\n</p>\n</card>\n<card id=\"char\" title=\"Меню\">\n<p>";
$stmp .= "<a href=\"$PHP_SELF?sid=$sid&list=magic\">Магия</a><br/>";
$stmp .= "<a href=\"$PHP_SELF?sid=$sid&list=skill\">Навыки</a><br/>";
$stmp .= "<a href=\"$PHP_SELF?sid=$sid&list=priem\">Приемы</a><br/>";
$stmp .= "<a href=\"$PHP_SELF?sid=$sid&cnick=1\">Настройки</a><br/>";
$stmp .= "<a href=\"$PHP_SELF?sid=$sid&look=$login\">О себе</a>";

if ($char[12]) {
    $stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&use=i.h\">Покинуть седло</a>";
}

msg($stmp, "[" . date("H:i", time()) . "] Предметы ", 1, PageType::INVENTORY);