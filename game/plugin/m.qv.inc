<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global to
 * @global use
 * @global char
 * @global do
 * @global sid
 * @global PHP_SELF
 * @global translit
 * @global sdesc
 * @global slife
 * @global smana
 * @global shit
 * @global sdmax
 * @global sdmin
 * @global sspeed
 * @global sarm
 * @global sres
 * @global sweap
 * @global tsum
 * @global tsi
 * @global tso
 * @global item
 * @global num
 */

if ( ! $do) {
    $tc = explode("|", $loc_i[$loc][$login]["char"]);
    $tw = explode("|", $loc_i[$loc][$login]["war"]);

    msg(<<<XML
1. <a href="#say">Сказать всем</a><br/>
2. <a href="#pers">Персонаж</a><br/>
3. <a href="#tele">Телепорт</a><br/>
4. <a href="#sum">Призвать</a><br/>
5. <a href="#it">Предмет</a><br/>
6. <a href="$PHP_SELF?sid=$sid&use=$use&do=res">Воскреснуть</a>

</p></card><card id="sum" title="Призвать"><p>
<input name="tsum" emptyok="true" type="text" value="n.c.orc:1:1"/>
<br/><a href="$PHP_SELF?sid=$sid&use=$use&do=sum&tsum=$(tsum)&tsi=$(tsi)&tso=$(tso)&tr=$(tr)&tqn=$(tqn)">Призвать</a>(id_name_weapon:count:follow)
<br/><a href="$PHP_SELF?sid=$sid&use=$use&do=listid">[Список id]</a>
<br/><select name="tr" multiple="true" value="1"><option value="1">Транслит</option></select>
<br/>Предметы (например: i.money:2000|i.w.s.short:1): <input name="tsi" emptyok="true" type="text" value=""/>
<br/>При освежевании: <input name="tso" emptyok="true" type="text" value=""/>
<br/><br/>Сделать NPC мирным (диалог при найме | при отказе | в локации, куда надо отвести | id локации | отдать предметы: i.money:2000|i.w.s.short:1 | не разговаривать, если нет предмета | id предмета) : <input name="tqn" emptyok="true" type="text" value=""/>
<br/>Обязательны только диалоги при найме и отказе (учтите, с обеих сторон от | должны быть пробелы).

</p></card><card id="it" title="Предмет"><p>
<input name="tit" emptyok="true" type="text" value="i.w."/>
<br/><a href="$PHP_SELF?sid=$sid&use=$use&do=filter&inp=$(tit)">Список (id)</a>
<br/><a href="$PHP_SELF?sid=$sid&use=$use&do=geti&inp=$(tit)">Артефакт (id_master_..am..do:count:npc)</a>
<br/><a href="$PHP_SELF?sid=$sid&use=$use&do=getms&inp=$(tit)">Свиток призыва (id_name)</a>
<br/><a href="$PHP_SELF?sid=$sid&use=$use&do=listit">[помощь]</a>

</p></card><card id="pers" title="Персонаж"><p>
Имя: <input name="name" emptyok="true" type="text" value="{$tc[0]}"/>
Описание: <input name="sdesc" emptyok="true" type="text" value="Opisanie otsutstvuet"/>
<br/><select name="translit" multiple="true" value="1"><option value="1">Транслит</option></select>
<br/>Жизнь: <input name="slife" emptyok="true" value="{$tc[1]}"/>
<br/>Мана: <input name="smana" emptyok="true" value="{$tc[3]}"/>
<br/>Меткость: <input name="shit" emptyok="true" value="{$tw[0]}"/>%
<br/>Скорость: <input name="sspeed" emptyok="true" value="{$tw[3]}"/> сек
<br/>Урон min: <input name="sdmin" emptyok="true" value="{$tw[1]}"/>
<br/>Урон max: <input name="sdmax" emptyok="true" value="{$tw[2]}"/>
Чем бьет: <input name="sweap" emptyok="true" type="text" value="{$tw[12]}"/>
<br/>Броня: <input name="sarm" emptyok="true" value="{$tw[5]}"/>
<br/>Сопр.магии: <input name="sres" emptyok="true" value="{$tw[10]}"/>%
<br/><a href="$PHP_SELF?sid=$sid&use=$use&do=set&name=$(name)&translit=$(translit)&slife=$(slife)&shit=$(shit)&sspeed=$(sspeed)&sdmin=$(sdmin)&sdmax=$(sdmax)&sarm=$(sarm)&sres=$(sres)&sweap=$(sweap)&smana=$(smana)&sdesc=$(sdesc)">Отправить</a>

</p></card><card id="say" title="Say all"><p>
<input name="text" emptyok="true" type="text" maxlength="140"/>\n<br/><select name="translit" multiple="true" value="1"><option value="1">Транслит</option></select>
<br/><anchor>Отправить<go href="$PHP_SELF?sid=$sid&use=$use&do=say" method="get">
<postfield name="text" value="$(text)"/>
<postfield name="translit" value="$(translit)"/>
</go></anchor>

</p></card><card id="tele" title="Teleport"><p>
<input name="to" emptyok="true" type="text" maxlength="140"/>
<br/><a href="$PHP_SELF?sid=$sid&use=$use&do=tele&to=$(to)">Teleport(loc или id:loc)</a>
<br/><a href="$PHP_SELF?sid=$sid&use=$use&do=portal&to=$(to)">Портал(loc)</a><br/><br/>
<a href="$PHP_SELF?sid=$sid&use=$use&do=tele&to=qv">База</a><br/>
<a href="$PHP_SELF?sid=$sid&use=$use&do=tele&to=x1011x396">Сев.вор</a><br/>
<a href="$PHP_SELF?sid=$sid&use=$use&do=tele&to=x1259x510">Вост.вор</a><br/>
<a href="$PHP_SELF?sid=$sid&use=$use&do=tele&to=x1173x603">Южн.вор</a><br/>
<a href="$PHP_SELF?sid=$sid&use=$use&do=tele&to=x1284x393">Кладбище</a><br/>
<a href="$PHP_SELF?sid=$sid&use=$use&do=tele&to=x1476x277">Пещера</a><br/>
<a href="$PHP_SELF?sid=$sid&use=$use&do=tele&to=x1884x246">Ансалон</a><br/>
<a href="$PHP_SELF?sid=$sid&use=$use&do=tele&to=x147x1227">Остров центр</a>
XML
, $loc);
}
if ($do == "say") {

    if ( ! $text) {
        msg("Нет текста для отправки");
    }
    if ($translit) {
        include __DIR__ . DIRECTORY_SEPARATOR . "../f_translit.inc";
        $text = trans($text);
    }
    $text = tsrus($text);
    $tl   = [];
    $dh   = opendir("online");
    while (($fname = readdir($dh)) !== false) {
        if ($fname != "." && $fname != ".." && $fname != "1.htaccess" && $fname != ".htaccess") {
            $tmp = file("online/" . $fname);
            $tmp = trim($tmp[0]);
            if ( ! isset($tl[$tmp])) {
                $tl[$tmp] = "1";
                loadloc($tmp);
                addjournal($tmp, "all", "Всем внимание: " . $text);
            }
        }
    }
    closedir($dh);
}

if ($do == 'tele') {
    if (strpos($to, ":") !== false) {
        $to = explode(":", $to);
        if ( ! isset($loc_i[$loc][$to[0]])) {
            msg("Рядом с вами нет существ с id " . $to[0] . ", кот. можно телепортировать");
        }
        if ( ! file_exists("loc_i/" . $to[1])) {
            msg("Локации с id " . $to[1] . " не существует");
        }
        if (substr($to[0], 0, 2) != "n.") {
            msg("Телепортировать можно только NPC или игроков");
        } else {
            manageNPC($to[0], $loc, strtolower($to[1]));
        }
        //@mail("romka8@list.ru", "qv teleport " . $to[0] . ":" . $to[1], date("d/m Y H:i", time()));
    } else {
        if ($loc == "qv") {
            foreach ($loc_i[$loc] as $k => $val) {
                if (substr($k, 0, 2) == "n.") {
                    manageNPC($k, $loc, strtolower($to));
                }
            }
        }
        manageNPC($login, $loc, strtolower($to));
        $loc_c = explode("|", $loc_tt[$loc]["d"]);
    }
}

if ($do == 'portal') {
    if ( ! file_exists("loc_i/" . $to)) {
        msg("Локации с id $to не существует");
    }
    if ($to == "x1087x543" || $to == "x1080x539" || $to == "x1087x528" || $to == "x1080x532") {
        msg("В таверну нельзя телепортироваться");
    }
    $loc_i[$loc]["i.s.portal_" . $to] = "портал телепортации|0|" . (time() + 3 * 60);    // 3 минуты
    addjournal($loc, "all", $char[0] . " создал портал телепортации");
}

if ($do == "set") {
    if ( ! $name) {
        msg("Нет имени");
    }
    $tc = explode("|", $loc_i[$loc][$login]["char"]);
    if ($translit) {
        include __DIR__ . DIRECTORY_SEPARATOR . "../f_translit.inc";
        $name  = trans($name);
        $sweap = trans($sweap);
        $sdesc = trans($sdesc);
    }
    if ($sdesc) {
        $loc_i[$loc][$login]["qvi"] = tsrus($sdesc);
    } else {
        unset($loc_i[$loc][$login]["qvi"]);
    }
    $tc[0]                       = tsrus($name);
    $tc[1]                       = $slife;
    $tc[2]                       = $slife;
    $tc[3]                       = $smana;
    $tc[4]                       = $smana;
    $loc_i[$loc][$login]["char"] = implode("|", $tc);

    $tc                         = explode("|", $loc_i[$loc][$login]["war"]);
    $tc[0]                      = $shit;
    $tc[1]                      = $sdmin;
    $tc[2]                      = $sdmax;
    $tc[3]                      = $sspeed;
    $tc[5]                      = $sarm;
    $tc[10]                     = $sres;
    $tc[11]                     = $sres;
    $tc[12]                     = tsrus($sweap);
    $loc_i[$loc][$login]["war"] = implode("|", $tc);
    //@mail("romka8@list.ru", "qv set " . $name . ": " . $loc_i[$loc][$login]["war"], date("d/m Y H:i", time()));
}

if ($do == "sum") {
    if (substr($tsum, 0, 4) != "n.c." && substr($tsum, 0, 4) != "n.a.") {
        msg("Призывать можно только на n.c. и n.a.");
    }
    $npc  = "";
    $tsum = explode(":", $tsum);
    if ( ! $tsum[1]) {
        $tnum = 1;
    } else {
        $tnum = $tsum[1];
    }
    if ($tnum > 10) {
        $tnum = 10;
    }
    $tsn = "";
    $tsq = "";
    if (strpos($tsum[0], "_") !== false) {
        $tsn     = substr($tsum[0], strpos($tsum[0], "_") + 1);
        $tsum[0] = substr($tsum[0], 0, strpos($tsum[0], "_"));
    }
    if (strpos($tsn, "_") !== false) {
        $tsq = substr($tsn, strpos($tsn, "_") + 1);
        $tsn = substr($tsn, 0, strpos($tsn, "_"));
    }
    $tfollow = $tsum[2];
    $tsum    = $tsum[0];
    $npc     = loadNpcById($tsum);
    if ( ! $npc) {
        msg("Существа с id=$tsum не существует");
    }
    if ($tr && ($tsq || $tsn || $tqn)) {
        include __DIR__ . DIRECTORY_SEPARATOR . "../f_translit.inc";
        $tsq = trans($tsq);
    }
    if ($tsq) {
        $tsq = trans($tsq);
        $tsq = tsrus($tsq);
        if ( ! $tsq) {
            msg("Нет названия оружия");
        }
        $twar       = explode("|", $npc["war"]);
        $twar[12]   = $tsq;
        $npc["war"] = implode("|", $twar);
    }
    if ($tsn) {
        $tsn = tsrus($tsn);
        $tsn = trans($tsn);
        $tc  = explode("|", $npc["char"]);
        if ( ! $tsn) {
            msg("Нет имени");
        }
        $tc[0]       = $tsn;
        $npc["char"] = implode("|", $tc);
    }
    if ($tsi) {
        $npc["items"] = $tsi;
    }
    if ($tso) {
        $npc["osvej"] = $tso;
    }
    if ($tqn) {
        $tsn .= " | " . $tqn;
        $tqn = explode(" | ", $tqn);
        if ( ! $tqn[0]) {
            msg("Задайте текст, кот. будет показан при согласии проводить NPC");
        }
        if ( ! $tqn[1]) {
            msg("Задайте текст, кот. будет показан при отказе проводить NPC");
        }
        if ($tqn[3] && ! $tqn[2]) {
            msg("Если указали локацию куда привести, то нужен и текст, кот. будет показан при разговоре в этой локации");
        }
        if ($tqn[3] && ! file_exists("loc_i/" . $tqn[3])) {
            msg("Локации " . $tqn[3] . ", куда надо проводить NPC не существует");
        }

        if ($tr) {
            if ($tqn[0]) {
                $tqn[0] = trans($tqn[0]);
            }
            if ($tqn[1]) {
                $tqn[1] = trans($tqn[1]);
            }
            if ($tqn[2]) {
                $tqn[2] = trans($tqn[2]);
            }
            if ($tqn[5]) {
                $tqn[5] = trans($tqn[5]);
            }
        }
        $tqn[0] = tsrus($tqn[0]);
        $tqn[1] = tsrus($tqn[1]);
        $tqn[2] = tsrus($tqn[2]);
        $tqn[5] = tsrus($tqn[5]);

        $npc["in"]  = $tqn[0];
        $npc["out"] = $tqn[1];
        if ($tqn[2]) {
            $npc["ok"] = $tqn[3] . " | " . $tqn[2] . " | " . $tqn[4];
        }
        if ($tqn[5] && $tqn[6]) {
            $npc["nspeak"] = $tqn[5] . " | " . $tqn[6];
        }
        $loc_i[$loc]["n.q." . rand(99, 9999)] = $npc;
    } else {
        $npc["owner"] = $login . "|";
        if ($tfollow) {
            $npc["owner"] .= $login;
        }
        $npc["owner"] .= "||0";
        for ($i = 0; $i < $tnum; $i++) {
            $loc_i[$loc][$tsum . "." . rand(99, 9999)] = $npc;
        }
    }
    //@mail("romka8@list.ru", "qv summon " . $tsum . ":" . $tnum . ":" . $tfollow . " " . $tsn,
    //    date("d/m Y H:i", time()));
}

if ($do == "listid") {
    $stmp = "Список id:";
    $dh   = opendir("npc");
    while (($fname = readdir($dh)) !== false) {
        if ($fname != "." && $fname != ".." && $fname != "1.htaccess" && $fname != ".htaccess") {
            if (substr($fname, 0, 4) == "n.c." || substr($fname, 0, 4) == "n.a.") {
                $stmp .= "<br/>" . $fname;
            }
        }
    }
    closedir($dh);
    msg($stmp);
}

if ($do == "res") {
    $char[1]                     = $char[2];
    $char[3]                     = $char[4];
    $char[8]                     = 0;
    $char[9]                     = 0;
    $loc_i[$loc][$login]["char"] = implode("|", $char);
}

if ($do == "calc") {
    unset($loc_i[$loc][$login]["qvi"]);
    calcparam($loc, $login);
}

if ($do == 'filter' && $inp) {
    $stmp = "<p>Кол-во: <input name=\"num\" format=\"*N\" maxlength=\"2\" value=\"1\"/>";
    $dh   = opendir("items/");
    while (($fname = readdir($dh)) !== false) {
        if ($fname != "." && $fname != ".." && substr($fname, 0, strlen($inp)) == $inp) {
            $item = findItemByBaseId($fname);
            $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&use=$use&do=add&item=$fname&num=$(num)\">" . $item[0] .
                     "</a>";
            $count++;
        }
    }
    closedir($dh);
    msg($stmp, "Предметы", 0);
}

if ($do == 'add' && $item) {
    manageItems($loc, "", $login, $item, $num);
    //@mail("romka8@list.ru", "qv add " . $item . ":" . $num, date("d/m Y H:i", time()));
}

if ($do == 'geti' && $inp) {
    $arr = explode(":", $inp);

    $fn = getBaseItemId($arr[0]);
    if ( ! itemExists($fn)) {
        msg("Предмета с id " . $arr[0] . " не существует");
    }

    if (strpos($arr[0], "..") !== false) {
        if (substr($arr[0], 0, 4) != "i.a." && substr($arr[0], 0, 4) != "i.w.") {
            msg("Создавать артефакты можно только на основе одежды i.a. или оружия i.w.");
        }
        if (strpos($arr[0], "_") === false) {
            msg("В артефактах с самоцветами обязательно надо указать имя мастера, любое слово англ. буквами.");
        }
        $xF = preg_match_all("/\\.\\.(\\w\\w)/", $arr[0], $regF);
        for ($j = 0; $j < $xF; $j++) {
            if ( ! itemExists("i.i." . $regF[1][$j])) {
                msg("Самоцвет " . $regF[1][$j] . " не существует");
            }
        }
    }

    if (strpos($arr[0], " ") !== false) {
        msg("В id не должно быть пробелов");
    }
    if ( ! $arr[1]) {
        msg("Надо указать количество count");
    }

    if ($arr[2] &&
        ((substr($arr[2], 0, 2) != "n." && substr($arr[2], 0, 2) != "u.") || ! isset($loc_i[$loc][$arr[2]]))
    ) {
        msg("Третьим параметром должен быть id NPC или игрока рядом с вами, учитывая регистр, которому передать предмет. Если не указано, то себе.");
    }

    if ( ! $arr[2]) {
        manageItems($loc, "", $login, $arr[0], $arr[1]);
    } else {
        manageItems($loc, "", $arr[2], $arr[0], $arr[1]);
        addjournal($loc, $login, "Предмет " . $arr[0] . ":" . $arr[1] . " добавлен к NPC " . $arr[2]);
    }
    //@mail("romka8@list.ru", "qv addi " . $inp, date("d/m Y H:i", time()));
}

if ($do == 'addi' && $inp) {
    $arr = explode(":", $inp);
    $fn = getBaseItemId($arr[0]);
    if ( ! itemExists($fn)) {
        msg("Предмета с id " . $arr[0] . " не существует");
    }
    if ( ! $arr[2] || (substr($arr[2], 0, 2) != "n." && substr($arr[2], 0, 2) != "u.") ||
         ! isset($loc_i[$loc][$arr[2]])
    ) {
        msg("Третьим параметром должен быть id NPC или игрока рядом с вами, учитывая регистр");
    }

    manageItems($loc, "", $arr[2], $arr[0], $arr[1]);
    addjournal($loc, $login, "Предмет " . $arr[0] . ":" . $arr[1] . " добавлен к NPC " . $arr[2]);
    //@mail("romka8@list.ru", "qv addi NPC " . $inp, date("d/m Y H:i", time()));
}

if ($do == 'getms' && $inp) {
    if (substr($inp, 0, 4) != "n.c." && substr($inp, 0, 4) != "n.a.") {
        msg("Свитки призыва можно создавать только на основе id монстров или животных, т.е. n.c.xxx или n.a.xxx");
    }
    $inp = preg_replace('/([^.A-z])/', "", $inp);
    $id = getBaseItemId($inp);
    if ( ! npcExists($id)) {
        msg("id " . $id . " не существует");
    }
    manageItems($loc, "", $login, "i.ms_" . $inp, 1);
    //@mail("romka8@list.ru", "qv addms " . $inp, date("d/m Y H:i", time()));
}

if ($do == 'listit') {
    msg("i.w. - оружие (i.w.s. - мечи, i.w.k. - ножи, i.w.r. - стрелковое и т.д.)
<br/>i.a. - броня (i.a.b. - на тело, i.a.h. - на голову и т.д.)
<br/>i.q. - квестовые предметы
<br/>i.f. - еда (i.f.b. - элексиры)
<br/>i.h. - охотничье трофеи
<br/>i.i. - самоцветы
<br/>i.m. - свитки
<br/>i.r. - руны
<br/>i.s. - стационарные (НЕ ИСПОЛЬЗОВАТЬ!)
<br/><br/>Если создаете артефакт, то обязательно указывать мастера (любое слово англ. буквами), для инкрустации доступны самоцветы: ag, am, az, do, dy, hr, ku, ma, me, ne, ob, on, sa, zm (перед каждым самоцветом обязательно две точки, напр.: ..ag..am..az). Инкрустировать можно любое количество любых самоцветов (или ни одного, а только имя мастера), но не злоупотребляйте нестандартными артефактами, они должны быть редкими, обоснованными и логичными (в том числе по балансу).
<br/>Если указан третий параметр npc, то предмет добавляется NPC или игроку рядом с вами с таким id (регистр учитывается, а имя мастера и самоцветы можно не писать), например: i.money:2000:n.Lukas или i.w.s.p_Natan_:1:n.Lukas
<br/>Свиток призыва можно создать на основе id любого монстра (n.c.xxx) или животного (n.a.xxx) и при желании задать имя name, но только транслитом.
");
}

function tsrus($s)
{
    if ( ! $s) {
        return $s;
    }
    // UTF-8 русские буквы
    $s = str_replace("\xd0\x81", "Ё", $s);
    $s = str_replace("\xd1\x91", "ё", $s);
    $s = preg_replace("/\xd0([\x90-\xbf])/e", "chr(ord('\\1')+48)", $s);
    $s = preg_replace("/\xd1([\x80-\x8f])/e", "chr(ord('\\1')+112)", $s);
    $s = str_replace('\\', "", $s);
    $s = preg_replace('/([^ -}А-я#])|\$|&/e', "", $s);
    $s = str_replace("|", "", $s);
    $s = str_replace("<", "", $s);
    $s = str_replace(">", "", $s);

    return $s;
}