<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global id
 * @global locai
 */
if (time() > $game["lastai"] + 240) {
    include "f_online.inc";
}    // обновим список
$g_list = 10;
$stmp   = "";
if ( ! $start) {
    $start = 0;
}
$i  = -1;
$dh = opendir("online/");
while (($fname = readdir($dh)) !== false) {
    if ($fname != "." && $fname != ".." && $fname != "1.htaccess" && $fname != ".htaccess") {
        $i++;
        if ($i >= $start && $i < $start + $g_list) {
            $tmp = file("online/" . $fname);
            if ($tmp[0] == ".") {
                continue;
            }
            for ($it = 0; $it < 2; $it++) {
                $tmp[$it] = str_replace("\n", "", $tmp[$it]);
                $tmp[$it] = str_replace("\r", "", $tmp[$it]);
            }
            if ( ! $tmp[0]) {
                @unlink("online/" . $fname);
                $i--;
                continue;
            }
            loadloc($tmp[0]);
            if (isset($loc_i[$tmp[0]][$fname])) {
                $tmp1 = explode("|", $loc_i[$tmp[0]][$fname]["char"]);
                $stmp .= "\n<br/>" . $tmp1[0];
            } else {
                $i--;
                @unlink("online/" . $fname);
            }
        }
    }
}
closedir($dh);

if ($i > -1) {
    $stmp = "<p>Сейчас в игре " . ($i + 1) . " (на этом сервере разрешено не более $g_max) игроков:" . $stmp;
}
if ($i > -1) {

    if ($start) {
        $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&site=online\">^ </a>";
    }
    if ($start + $g_list < $i + 1) {
        if ( ! $start) {
            $stmp .= "\n<br/>";
        }
        $stmp .= "<a href=\"$PHP_SELF?sid=$sid&site=online&start=" . ($start + $g_list) . "\">+ (" .
                 ($i + 1 + 1 - $start - $g_list) . ")</a>";
    }
} else {
    $stmp = "<p>Сейчас в игре никого нет";
}

$stmp .= "\n<br/><br/><anchor>[Назад]<prev/></anchor>";

msg($stmp, "Онлайн", 0, 'none');