<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 */
// букет цветов
$arr = "roftphlgvadibjeknmxs";
manageItems($loc, "", $login, "i.bc." . $arr{rand(0, strlen($arr) - 1)}, 1);