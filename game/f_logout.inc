<?php

if ($login != $g_admin && $gm != $gm_id && $loc_i[$loc][$login]["srv"] > time() - 120)
    msg("Вы только что вошли в игру, персонаж может покинуть этот сервер не раньше, чем через " .
        round(($loc_i[$loc][$login]["srv"] - time() + 120) / 60 + 1) . " минуты<br/><a href=\"$PHP_SELF?sid=$sid\">В игру</a>");

// если никого рядом нет, то можем удалить персонажа
$b = 0;
foreach (array_keys($loc_i[$loc]) as $j)
    if ($j != $login)
        if ((substr($j, 0, 2) == 'u.') || substr($j, 0, 2) == 'n.') {
            $b = 1;
            break;
        }
if (!$b)
    for ($i = 2; $i < count($loc_c); $i += 2)
        if ($loc_c[$i + 1] != $loc) {
            if (count($loc_i[$loc_c[$i + 1]]) > 0) {
                $keys = array_keys($loc_i[$loc_c[$i + 1]]);
                foreach ($keys as $j)
                    if ((substr($j, 0, 2) == 'u.') || substr($j, 0, 2) == 'n.') {
                        $b = 1;
                        break;
                    }
            }
        };

if (isset($loc_i[$loc][$login])) {
    if ($game["floc"] == $loc && $game["fid"] == $login) {
        addjournal($loc, "all", $char[0] . " бросил флаг!", $login);
        if ($loc == "x1087x543" || $loc == "x1080x539" || $loc == "x1080x532" || $loc ==
            "x1087x528"
        )
            $loc1 = "x1095x532";
        else
            $loc1 = $loc;
        $loc_i[$loc1]["i.flag"] = "флаг лидерства|1|0";
        $game["floc"] = $locl;
        $game["fid"] = "";
        calcparam($loc, $login);
    }
    $auser = $loc_i[$loc][$login];
    $auser["journal"] = "";
    $auser["loc"] = $loc;
    $auser["time"] = time();
    unset($auser["msgt"]);
    unset($auser["macrol"]);
    unset($auser["trade"]);
    $tp = explode("|", $auser["user"]);
    if ($auser["user"] && $auser["char"] && $auser["skills"] && $auser["war"])
        $res = SetData(substr($login, 2), $tp[0], serialize($auser));
    else
        $res = "Неверный формат.";
} else
    $res = "Нет данных";

if ($res)
    msg("<p>Ошибка при сохранении персонажа: " . $res .
        "<br/>Рекомендуем вам оставаться онлайн и регулярно пытаться сохраниться, иначе весь опыт, найденные предметы и т.д. с последнего сохранения, когда покидали игру, будут потеряны.<br/><anchor>Назад<prev/></anchor>",
        "Ошибка", 0);

if (!$b) {
    addnpc($login, $loc, "");
    @unlink("online/" . $login);
    $b = "Так как рядом никого нет, то ваш персонаж только что покинул игру, теперь его не смогут в ваше отсутствие убить или обворовать.
        <br/>Удачного дня, " .
        $char[0] . "!<br/><a href=\"$PHP_SELF\">На главную</a>";
    $login = "";
} else {
    $b = "Если вы сейчас покинете игру, то ваш персонаж останется в игре еще минимум на " .
        round($g_logout / 60) . " минут, так как рядом кто-то есть.";
}

msg("<p>Персонаж сохранен успешно.<br/>" . $b, "Сохранение", 0);