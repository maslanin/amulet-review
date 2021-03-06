<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */
// ступка смешивает лечебную траву и пустую бутылку, получаем слабое зелье

if (intval(preg_replace('/.*' . "i.f.fileroot" . ':(\d+).*/', "\\1", $loc_i[$loc][$login]["items"])) > 0 &&
    intval(preg_replace('/.*' . "i.f.b.empty" . ':(\d+).*/', "\\1", $loc_i[$loc][$login]["items"])) > 0
) {

    $skills = explode("|", $loc_i[$loc][$login]["skills"]);
    if ($skills[23] > 0) {
        $char[6]                     = time() + 6;
        $loc_i[$loc][$login]["char"] = implode("|", $char);

        // трава пропадает
        manageItems($loc, $login, "", "i.f.fileroot", 1);

        if (rand(1, 100) < $skills[23] * 20 - 5) {
            manageItems($loc, $login, "", "i.f.b.empty", 1);
            manageItems($loc, "", $login, "i.f.b.mana.great", 1);
            addjournal($loc, $login, "Вы сделали элексир маны");
            addjournal($loc, "all", $char[0] . " сделал элексир маны", $login);
        } else {
            addjournal($loc, $login, "Вы не смогли сделать элексир маны");
            addjournal($loc, "all", $char[0] . " пытался сделать элексир маны", $login);
        }

    } else {
        addjournal($loc, $login, "Ваш навык алхимика равен 0, вы не умеете делать зелья");
    }
} else {
    addjournal($loc, $login, "Чтобы сделать элексир маны, нужен огненный корень и пустая бутылка");
}

