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
 * @global $look
 */
if (isset($loc_i[$loc][$look])) {
    if ($loc_i[$loc][$look]["qvi"]) {
        msg($loc_i[$loc][$look]["qvi"]);
    }
    $char = explode("|", $loc_i[$loc][$look]["char"]);
    $stmp = "<p>";

    $user = explode("|", $loc_i[$loc][$look]["user"]);
    if ($user[2] == 'f') {
        $stmp .= "Женщ.";
    } else {
        $stmp .= "Мужч.";
    }
    $stmp .= ", " . $user[3] . " лет";
    // холост/женат
    if ($char[13]) {
        $tt = explode(":", $char[13]);
        $tt = $tt[0];
    } else {
        $tt = "";
    }
    if ($tt && $user[2] == "m") {
        $stmp .= ", женат на " . substr($tt, 2);
    }
    if ($tt && $user[2] == "f") {
        $stmp .= ", замужем за " . substr($tt, 2);
    }
    //if(!$user[10] && $user[2]=="m")  $stmp.=", холост";
    //if(!$user[10] && $user[2]=="f")  $stmp.=", не замужем";

    //новичок или опытный игрок
    $stmp .= "<br/>";
    $war = explode("|", $loc_i[$loc][$look]["war"]);
    $sk  = explode("|", $loc_i[$loc][$look]["skills"]);
    $lev = 0;
    for ($i = 0; $i < count($sk); $i++) {
        if ($i != 3 && $i != 4) {
            $lev += $sk[$i];
        }
    }
    $lev = round(($lev - 5) * 100 / ($g_attr + $g_skills));

    if ($lev < 5) {
        $stmp .= "Новичок";
    }
    if ($lev >= 5 && $lev < 10) {
        $stmp .= "Начинающий";
    }
    if ($lev >= 10 && $lev < 20) {
        $stmp .= "Умелый";
    }
    if ($lev >= 20 && $lev < 30) {
        $stmp .= "Опытный";
    }
    if ($lev >= 30 && $lev < 40) {
        $stmp .= "Искусный";
    }
    if ($lev >= 40 && $lev < 50) {
        $stmp .= "Профессионал";
    }
    if ($lev >= 50 && $lev < 60) {
        $stmp .= "Известный";
    }
    if ($lev >= 60 && $lev < 70) {
        $stmp .= "Знаменитый";
    }
    if ($lev >= 70 && $lev < 80) {
        $stmp .= "Мастер";
    }
    if ($lev >= 80 && $lev < 90) {
        $stmp .= "Грандмастер";
    }
    if ($lev >= 90) {
        $stmp .= "Лорд";
    }

    // титул
    $arr_best = [
        8  => "боец",
        9  => "воин",
        10 => "лучник",
        13 => "маг",
        5  => "монах",
        7  => "укротитель",
        17 => "маскировщик",
        21 => "спиритуалист",
        30 => "повар",
        24 => "рудокоп",
        25 => "кузнец",
        26 => "лесоруб",
        27 => "плотник",
        28 => "ювелир",
        29 => "рыболов",
        22 => "лекарь",
        23 => "алхимик",
        31 => "некромант",
        6  => "вор",
        32 => "друид",
    ];

    $maxid  = 8;
    $maxval = 0;
    foreach (array_keys($arr_best) as $i) {
        if ($sk[$i] >= $maxval) {
            $maxid  = $i;
            $maxval = $sk[$i];
        }
    }
    if ($maxval == 0) {
        $stmp .= " боец";
    } else {
        $stmp .= " " . $arr_best[$maxid];
    }

    // сильный и т.д.
    $good = [];
    $bad  = [];
    if ($sk[0] > 3) {
        $good[] = "сильный";
    }
    if ($sk[0] == 1) {
        $bad[] = "слабый";
    }
    if ($sk[1] > 3) {
        $good[] = "ловкий";
    }
    if ($sk[1] == 1) {
        $bad[] = "медлительный";
    }
    if ($sk[2] > 3) {
        $good[] = "умный";
    }
    if ($sk[2] == 1) {
        $bad[] = "не очень умный";
    }
    if (count($bad) > 0 || count($good) > 0) {
        $stmp .= "<br/>";
    }
    if (count($good) == 3) {
        $stmp .= $good[0] . ", " . $good[1] . " и " . $good[2];
    }
    if (count($good) == 2) {
        $stmp .= $good[0] . " и " . $good[1];
    }
    if (count($good) == 1) {
        $stmp .= $good[0];
    }
    if (count($good) > 0 && count($bad) > 0) {
        $stmp .= ", но ";
    }
    if (count($bad) == 3) {
        $stmp .= $bad[0] . ", " . $bad[1] . " и " . $bad[2];
    }
    if (count($bad) == 2) {
        $stmp .= $bad[0] . " и " . $bad[1];
    }
    if (count($bad) == 1) {
        $stmp .= $bad[0];
    }

    if (count($bad) == 0 && count($good) == 0) {
        $stmp .= "<br/>Телосложение среднее";
    }

    if (strpos($char[0], "*") === false) {
        $clan = "";
    } else {
        $clan = substr($char[0], strpos($char[0], "*") + 1, strrpos($char[0], "*") - strpos($char[0], "*") - 1);
    }
    if ($clan) {
        $stmp .= "<br/>Состоит в клане <a href=\"$PHP_SELF?sid=$sid&site=clans&clan=$clan\">" . $clan . "</a>";
    }

    if ($game["floc"] == $loc && $game["fid"] == $look) {
        $stmp .= "<br/>Держит в руках флаг лидерства (нападение не будет преступлением)";
    }

    // что одето
    if ($loc_i[$loc][$look]["equip"]) {
        $str   = "";
        $sto   = "";
        $equip = explode("|", $loc_i[$loc][$look]["equip"]);
        foreach ($equip as $i) {
            if ($i) {
                $item = findItemByFullId($i);
                if (strpos($i, "..") !== false) {
                    $item[0] .= " *";
                }
                if (substr($i, 0, 4) == "i.a.") {
                    if ( ! $sto) {
                        $sto = $item[0];
                    } else {
                        $sto .= ", " . $item[0];
                    }
                } else {
                    if ( ! $str) {
                        $str = $item[0];
                    } else {
                        $str .= ", " . $item[0];
                    }
                }
            }
        }
        if ($str) {
            $stmp .= "<br/>Держит в руках: " . $str;
        }
        if ($sto) {
            $stmp .= "<br/>Одет: " . $sto;
        }
    }

    msg($stmp, $char[0]);
} else {
    addjournal($loc, $login, "Не на кого смотреть");
}