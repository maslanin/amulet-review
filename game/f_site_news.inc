<?php

if ( ! file_exists("../news/news.htm")) {
    msg("<p>Нет текста, сообщите название рассказа разработчику");
}
$stmp = (file_get_contents("../news/news.htm"));

$stmp = str_replace("|", "<br />------<br />", $stmp);
$stmp = wordwrap($stmp, 500, "|");
$stmp = explode("|", $stmp);

if ( ! $start || $start < 0) {
    $start = 1;
}
if ($start > count($stmp)) {
    $start = count($stmp);
}
$stmp[$start - 1] = "<p>Стр. " . $start . " из " . count($stmp) . " [<a href=\"#page\">изм.</a>]<br/>" .
                    $stmp[$start - 1];
if ($start < count($stmp)) {
    $stmp[$start - 1] .= "<br /><a href=\"?site=news&amp;r=" . rand(97, 122) . "&amp;start=" . ($start + 1) .
                         "\">[след. стр.]</a>";
}
$stmp[$start - 1] .= "<br /><br /><a href=\"?site=news\">[В начало]</a><br /><a href=\"index.php\">[На главную]</a>";
$stmp[$start -
      1] .= "<br/></p></card><card id=\"page\" title=\"Перейти\">\n<p>Введите номер страницы:<br/><input name=\"start\"  format=\"*N\" value=\"1\" maxlength=\"3\"/><br/><a href=\"?site=news&amp;start=$(start)\">Перейти</a>";

$stmp = $stmp[$start - 1] . "<br/><anchor>[Назад]<prev/></anchor>";

msg($stmp);
