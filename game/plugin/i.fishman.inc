<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 * @global loc_water1
 * @global loc_water2
 */
// рыбалка загрузим локации с водой
include __DIR__ . DIRECTORY_SEPARATOR . 'loc_water.inc';
if (strpos($loc_water1, $loc) !== false) {
    $skills = explode("|", $loc_i[$loc][$login]["skills"]);
    if ($skills[29] > 0) {
        $char[6] = time() + 6;

        $loc_i[$loc][$login]["char"] = implode("|", $char);
        addjournal($loc, "all", $char[0] . " ловит рыбу", $login);
        $b   = 0;    // сколько поймали
        $rnd = rand(1, 200);

        if ($rnd < $skills[29] * 0.2) {
            $b = 1;
            $t = "часть амулета";
            manageItems($loc, "", $login, "i.q.ambroken1", 1);
        }
        if ($rnd < $skills[29] * 0.4) {
            $b = 1;
            $t = "чашу из ансалона";
            manageItems($loc, "", $login, "i.q.chasha", 1);
        } else {
            if ($rnd < $skills[29] * 0.6) {
                $b = 1;
                $t = "ключ от потайной комнаты";
                manageItems($loc, "", $login, "i.q.keykrep1", 1);
            } else {
                if ($rnd < $skills[29] * 0.8) {
                    $b = 1;
                    $t = "ящик со склада";
                    manageItems($loc, "", $login, "i.q.yashik", 1);
                } else {
                    if ($rnd < $skills[29] * 1) {
                        $b = 1;
                        $t = "перчатки вора";
                        manageItems($loc, "", $login, "i.q.pervor", 1);
                    } else {
                        if ($rnd < $skills[29] * 1.2) {
                            $b = 1;
                            $t = "зеркального карпа";
                            manageItems($loc, "", $login, "i.q.fish.zerk", 1);
                        } else {
                            if ($rnd < $skills[29] * 1.4) {
                                $b = 1;
                                $t = "тапки";
                                manageItems($loc, "", $login, "i.a.c.tap1", 1);
                            } else {
                                if ($rnd < $skills[29] * 1.6) {
                                    $b = 1;
                                    $t = "туфли";
                                    manageItems($loc, "", $login, "i.a.c.tuf1", 1);
                                } else {
                                    if ($rnd < $skills[29] * 1.8) {
                                        $b = 1;
                                        $t = "треуголку";
                                        manageItems($loc, "", $login, "i.a.k.h1", 1);
                                    } else {
                                        if ($rnd < $skills[29] * 2) {
                                            $b = 1;
                                            $t = "темные очки";
                                            manageItems($loc, "", $login, "i.a.o.t1", 1);
                                        } else {
                                            if ($rnd < $skills[29] * 4) {
                                                $b = 1;
                                                $t = "сома";
                                                manageItems($loc, "", $login, "i.f.som", 1);
                                            } else {
                                                if ($rnd < $skills[29] * 6) {
                                                    $b = 1;
                                                    $t = "щуку";
                                                    manageItems($loc, "", $login, "i.f.wjuka", 1);
                                                } else {
                                                    if ($rnd < $skills[29] * 10) {
                                                        $b = 1;
                                                        $t = "язя";
                                                        manageItems($loc, "", $login, "i.f.jaz", 1);
                                                    } else {
                                                        if ($rnd < $skills[29] * 14) {
                                                            $b = 1;
                                                            $t = "карася";
                                                            manageItems($loc, "", $login, "i.f.karas", 1);
                                                        } else {
                                                            if ($rnd < $skills[29] * 16) {
                                                                $b = 1;
                                                                $t = "сорожку";
                                                                manageItems($loc, "", $login, "i.f.sorozh", 1);
                                                            } else {
                                                                if ($rnd < $skills[29] * 18) {
                                                                    $b = 1;
                                                                    $t = "пескаря";
                                                                    manageItems($loc, "", $login, "i.f.pesk", 1);
                                                                } else {
                                                                    if ($rnd < $skills[29] * 20) {
                                                                        $b = 1;
                                                                        $t = "верхоплавку";
                                                                        manageItems($loc, "", $login, "i.f.verh", 1);
                                                                    } else {
                                                                        if ($b) {
                                                                            addjournal($loc, "all",
                                                                                $char[0] . " поймал " . $t . " ",
                                                                                $login);
                                                                            if (rand(1, 100) < 10) {
                                                                                addexp($loc, $login, 1);
                                                                            }
                                                                        } else {
                                                                            addjournal($loc, $login,
                                                                                "Вам не удалось ничего поймать");
                                                                            addjournal($loc, "all",
                                                                                $char[0] . " ничего не поймал", $login);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // удочка может сломаться, фиксированная вероятность 5%
        $rnd = rand(1, 100);
        if ($rnd <= 4) {
            addjournal($loc, $login, "Ваша удочка сломалась");
            addjournal($loc, "all", $char[0] . " сломал удочку", $login);
            manageItems($loc, $login, "", "i.fishman", 1);
        }

    } else {
        addjournal($loc, $login, "Ваш навык рыболовства равен 0, вы не умеете рыбачить");
    }
} else {
    addjournal($loc, $login, "Здесь нет воды, рыбачить можно только у реки или на берегу моря");
}
