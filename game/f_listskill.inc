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
 * @global act
 * @global num
 */
// список всех скиллов

use MaxDark\Amulet\OldCode\ViewOptions;

$arr_skills = [
    "str"          => 0,
    "dex"          => 1,
    "int"          => 2,
    "meditation"   => 5,
    "steal"        => 6,
    "animaltaming" => 7,
    "hand"         => 8,
    "coldweapon"   => 9,
    "ranged"       => 10,
    "parring"      => 11,
    "uklon"        => 12,
    "magic"        => 13,
    "magic_resist" => 14,
    "magic_uklon"  => 15,
    "regeneration" => 16,
    "hiding"       => 17,
    "look"         => 18,
    "steallook"    => 19,
    "animallore"   => 20,
    "spirit"       => 21,
    "healing"      => 22,
    "alchemy"      => 23,
    "mine"         => 24,
    "smith"        => 25,
    "lumb"         => 26,
    "bow"          => 27,
    "stone"        => 28,
    "fish"         => 29,
    "food"         => 30,
    "necro"        => 31,
    "currier"      => 32,
];

$arr_title = [
    "str"          => "Сила",
    "dex"          => "Ловкость",
    "int"          => "Интеллект",
    "meditation"   => "Медитация",
    "steal"        => "Кража",
    "animaltaming" => "Прир.животных",
    "hand"         => "Рукопашная",
    "coldweapon"   => "Холодн.оружие",
    "ranged"       => "Стрельба",
    "parring"      => "Парирование",
    "uklon"        => "Уклон",
    "magic"        => "Магия",
    "magic_resist" => "Сопр.магии",
    "magic_uklon"  => "Уклон от магии",
    "regeneration" => "Регенерация",
    "hiding"       => "Скрытность",
    "look"         => "Осторожность",
    "steallook"    => "Подглядывание",
    "animallore"   => "Изуч.животных",
    "spirit"       => "Спиритизм",
    "healing"      => "Лечение",
    "alchemy"      => "Алхимия",
    "mine"         => "Рудокоп",
    "smith"        => "Кузнец",
    "lumb"         => "Лесоруб",
    "bow"          => "Плотник",
    "stone"        => "Ювелир",
    "fish"         => "Рыболов",
    "food"         => "Повар",
    "currier"      => "Друид",
];

// в $to цель, если есть
$skills = explode("|", $loc_i[$loc][$login]["skills"]);
$war    = explode("|", $loc_i[$loc][$login]["war"]);
if ($macro == 1) {
    $m = "&macros=list&num=$num&name=$name&act=$act#add";
} else {
    $m = '';
}
$stmp = "<p>";
if ( ! $macro) {
    $stmp = "<a href=\"$PHP_SELF?sid=$sid&look=skill.str\">Сила</a>: " . $skills[0] .
            "<br/><a href=\"$PHP_SELF?sid=$sid&look=skill.dex\">Ловкость</a>: " . $skills[1] .
            "<br/><a href=\"$PHP_SELF?sid=$sid&look=skill.int\">Интеллект</a>: " . $skills[2] . "<br/>Опыт: " .
            $skills[3] . "/" . $war[13] * $g_exp . "<br/>Очки опыта: " . $skills[4];
}
unset($arr_skills["str"]);
unset($arr_skills["dex"]);
unset($arr_skills["int"]);

if ( ! $start) {
    $start = 0;
}
$keys = array_keys($arr_skills);
$listEnd = $start + ViewOptions::getInstance()->getMaxListSize();
for ($i = $start; $i < $listEnd && $i < count($keys); $i++) {
    if ($to) {
        if ($keys[$i] == "meditation" || $keys[$i] == "animaltaming" || $keys[$i] == "steal") {
            $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&to=$to&use=skill." . $keys[$i] . $m . "\">" .
                     $arr_title[$keys[$i]] . "</a>";
        }
    } else {    // в след. экране all выберем цель $to для использования
        $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&look=skill." . $keys[$i] . "\">" . $arr_title[$keys[$i]] .
                 "</a>: " . intval($skills[$arr_skills[$keys[$i]]]);
        if ($keys[$i] == "meditation" || $keys[$i] == "animaltaming" || $keys[$i] == "steal" || $keys[$i] == "necro") {
            $stmp .= " <a href=\"$PHP_SELF?sid=$sid&use=skill." . $keys[$i] . "\">[+]</a>";
        }
    }
}
if ($start) {
    $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&list=skill\">^ </a>";
}
if ($listEnd < count($keys)) {
    if ( ! $start) {
        $stmp .= "\n<br/>";
    }
    $stmp .= "<a href=\"$PHP_SELF?sid=$sid&list=skill&start=" . ($listEnd) . "\">+ (" .
             (count($keys) - $listEnd) . ")</a>";
}
msg($stmp, "Навыки", 1);