<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global $use
 * @global glava
 * @global info
 * @global clear
 * @global translit
 * @global cadd
 * @global p
 */
// камень гильдии

use MaxDark\Amulet\OldCode\ViewOptions;

$tc = explode("|", $loc_i[$loc][$login]["char"]);
if (strpos($tc[0], "*") === false) {
    $clan = "";
} else {
    $clan = substr($tc[0], strpos($tc[0], "*") + 1, strrpos($tc[0], "*") - strpos($tc[0], "*") - 1);
}
if ($clan && file_exists("data/clans/" . $clan)) {
    $tmp = unserialize((file_get_contents("data/clans/" . $clan)));
} else {
    $tmp = [];
}

if (isset($tmp["g"][$login])) {    // гилдмастер
    if ($to) {
        if (substr($to, 0, 2) != "u." || ! isset($loc_i[$loc][$to])) {
            msg("Приглашать в свой клан можно только игроков");
        }
        if ($to == $login) {
            msg("Нельзя приглашать в клан самого себя");
        }
        $tc1 = explode("|", $loc_i[$loc][$to]["char"]);
        if (strpos($tc1[0], "*") === false) {
            $clan1 = "";
        } else {
            $clan1 = substr($tc1[0], strpos($tc1[0], "*") + 1, strrpos($tc1[0], "*") - strpos($tc1[0], "*") - 1);
        }
        if ($clan1 == $clan && ! $glava) {
            msg($tc1[0] . " и так в вашем клане");
        }
        if ($clan1 && ! $glava || $glava && $clan1 != $clan) {
            msg($tc1[0] . " состоит в клане " . $clan1 .
                ", а приглашать в свой можно только тех, кто не состоит ни в одном клане");
        }
        // приглашаем...
        if ($glava) {
            $tmp["wg"][$to] = "";
            addjournal($loc, $to, $tc[0] . " приглашает вас быть главой его клана");
            addjournal($loc, $login, $tc1[0] .
                                     " приглашен быть главой вашего клана, передайте ему камень гильдии, чтобы он использовал его на вас");
        } else {
            $tmp["w"][$to] = "";
            addjournal($loc, $to, $tc[0] . " приглашает вас в свой клан");
            addjournal($loc, $login,
                $tc1[0] . " приглашен в ваш клан, передайте ему камень гильдии, чтобы он использовал его на вас");
        }
        $file = fopen("data/clans/" . $clan, "w");
        if ($file !== false) {
            fputs($file, serialize($tmp));
            fclose($file);
        }
    } else {
        if ($del) {        // удаление из гильдии
            $b = 0;
            if (isset($tmp["m"][$del])) {
                $b = 1;
                unset($tmp["m"][$del]);
                addjournal($loc, $del,
                    "Вы выгнаны из клана " . $clan . "! При следующем логине надпись о вашем клане исчезнет");
            }
            if (isset($tmp["w"][$del])) {
                $b = 1;
                unset($tmp["w"][$del]);
            }
            if (isset($tmp["wg"][$del])) {
                $b = 1;
                unset($tmp["wg"][$del]);
            }
            if ($b) {
                $file = fopen("data/clans/" . $clan, "w");
                if ($file !== false) {
                    fputs($file, serialize($tmp));
                    fclose($file);
                }
                msg("Вы выгнали из клана/удалили из рекрутов " . substr($del, 2));
            } else {
                msg(substr($del, 2) . " нет в вашем клане");
            }
        }
        if ($info) {    // инфо о клане
            if ($write) {
                if ($clear) {
                    $write = "";
                } else {
                    if ($translit) {
                        include __DIR__ . DIRECTORY_SEPARATOR . "../f_translit.inc";
                        $write = trans($write);
                    }
                    // UTF-8 русские буквы
                    $s = $write;
                    $s = str_replace("\xd0\x81", "Ё", $s);
                    $s = str_replace("\xd1\x91", "ё", $s);
                    $s = preg_replace("/\xd0([\x90-\xbf])/e", "chr(ord('\\1')+48)", $s);
                    $s = preg_replace("/\xd1([\x80-\x8f])/e", "chr(ord('\\1')+112)", $s);

                    $s     = str_replace('\\', "", $s);
                    $s     = preg_replace('/([^ -}А-я#])|\$|"|\'|&/e', "", $s);
                    $s     = str_replace("|", "", $s);
                    $s     = str_replace("<", "", $s);
                    $s     = str_replace(">", "", $s);
                    $write = $s;
                }
                $tmp["i"] = $write;
                $file     = fopen("data/clans/" . $clan, "w");
                if ($file !== false) {
                    fputs($file, serialize($tmp));
                    fclose($file);
                }
                msg("Описание клана сохранено");
            }
            msg("Введите описание своего клана:<br/><input name=\"write\" value=\"" . $tmp["i"] .
                "\"/><br/><select name=\"translit\" multiple=\"true\" value=\"1\"><option value=\"1\">Транслит</option></select><a href=\"$PHP_SELF?sid=$sid&use=$use&info=1&write=$(write)&translit=$(translit)\">Сохранить</a>");
        }
        if ( ! $cadd) {    // меню
            $stmp = "<p>[<a href=\"$PHP_SELF?sid=$sid&use=$use&cadd=1\">Пригласить</a>]";
            $stmp .= " [<a href=\"$PHP_SELF?sid=$sid&use=$use&cadd=1&glava=1\">Сделать главой</a>]";
            $stmp .= " [<a href=\"$PHP_SELF?sid=$sid&use=$use&cadd=1&info=1\">Инфо о клане</a> (<a href=\"$PHP_SELF?sid=$sid&use=$use&info=1&write=1&clear=1\">очистить</a>)]";
            $listEnd = $start + ViewOptions::getInstance()->getMaxListSize();
            if ($tmp["m"]) {
                $stmp .= "<br/>Состав (выберите, чтобы выгнать):";
                if ( ! $start) {
                    $start = 0;
                }
                $keys = array_keys($tmp["m"]);
                for ($i = $start; $i < count($keys) && $i < $listEnd; $i++) {
                    $stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&use=$use&del=" . $keys[$i] . "\">" .
                             substr($keys[$i], 2) . "</a>";
                }
                $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&use=i.guildstone&start=" . $listEnd .
                         "\">+</a>";
            } else {
                $stmp .= "<br/>В вашем клане, кроме вас, никого нет.";
            }
            if ($tmp["wg"]) {
                $stmp .= "<br/><br/>Ожидают, чтобы стать главой вашего клана:";
                if ( ! $start) {
                    $start = 0;
                }
                $keys = array_keys($tmp["wg"]);
                for ($i = $start; $i < count($keys) && $i < $listEnd; $i++) {
                    $stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&use=$use&del=" . $keys[$i] . "\">" .
                             substr($keys[$i], 2) . "</a>";
                }
                $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&use=i.guildstone&start=" . ($listEnd) .
                         "\">+</a>";
            }
            if ($tmp["w"]) {
                $stmp .= "<br/><br/>Рекруты (ожидают вступления):";
                if ( ! $start) {
                    $start = 0;
                }
                $keys = array_keys($tmp["w"]);
                for ($i = $start; $i < count($keys) && $i < $listEnd; $i++) {
                    $stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&use=$use&del=" . $keys[$i] . "\">" .
                             substr($keys[$i], 2) . "</a>";
                }
                $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&use=i.guildstone&start=" . ($listEnd) .
                         "\">+</a>";
            } else {
                $stmp .= "<br/>Список рекрутов пуст.";
            }
            $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&use=i.guildstone\">^</a>";
            msg($stmp);
        } else {
            $list = 'all';
        }    // ниже выведем список
    }
} else {        // if (!$clan) ни в одном клане
    if ($to) {
        if (substr($to, 0, 2) != "u." || ! isset($loc_i[$loc][$to])) {
            msg("Вы должны были выбрать игрока");
        }
        if (substr($to, 0, 2) == $login) {
            msg("Нельзя выбирать самого себя");
        }

        $tc = explode("|", $loc_i[$loc][$to]["char"]);
        if (strpos($tc[0], "*") === false) {
            $clan = "";
        } else {
            $clan = substr($tc[0], strpos($tc[0], "*") + 1, strrpos($tc[0], "*") - strpos($tc[0], "*") - 1);
        }
        if ($clan && file_exists("data/clans/" . $clan)) {
            $tmp = unserialize((file_get_contents("data/clans/" . $clan)));
        } else {
            $tmp = [];
        }
        if ( ! isset($tmp["g"][$to])) {
            msg("Выбирать можно только главу клана");
        }
        if ( ! isset($tmp["w"][$login]) && ! isset($tmp["wg"][$login])) {
            msg("Вы не числитесь в списках рекрутов клана " . $clan . ", обратитесь к главе этого клана");
        }

        // вступаем в клан $clan
        if (isset($tmp["wg"][$login])) {
            $b = 1;
        } else {
            $b = 0;
        }
        if ($b) {
            unset($tmp["wg"][$login]);
            $keys               = array_keys($tmp["g"]);
            $tmp["m"][$keys[0]] = $tmp["g"][$keys[0]];// бывший глава рядовым
            unset($tmp["g"]);    // удаляем старого главу клана
            $tmp["g"][$login] = $p;
        } else {
            unset($tmp["w"][$login]);
            $tmp["m"][$login] = $p;
        }
        $file = fopen("data/clans/" . $clan, "w");
        if ($file !== false) {
            fputs($file, serialize($tmp));
            fclose($file);
        }
        $tc = explode("|", $loc_i[$loc][$login]["char"]);
        if (strpos($tc[0], "*") !== false) {
            $tc[0] = substr($tc[0], 0, strpos($tc[0], "*") - 1);
        }
        $tc[0] .= " *" . $clan . "*";
        $loc_i[$loc][$login]["char"] = implode("|", $tc);
        if ($b) {
            addjournal($loc, $to, $tc[0] . " теперь глава вашего клана!");
        } else {
            addjournal($loc, $to, $tc[0] . " вступил в ваш клан!");
        }
        if ($b) {
            msg("Поздравляем, вы теперь глава клана " . $clan .
                ", рекомендуем <a href=\"$PHP_SELF?sid=$sid&logout=1\">сохранить персонажа</a>.");
        } else {
            msg("Поздравляем, вы зачислены в клан " . $clan .
                ", рекомендуем <a href=\"$PHP_SELF?sid=$sid&logout=1\">сохранить персонажа</a>.");
        }
    } else {
        $list = 'all';
    }
}//else msg("Вы состоите в клане ".$clan.", чтобы использовать камень гильдии надо быть либо главой клана, либо не состоять ни в одном клане");


