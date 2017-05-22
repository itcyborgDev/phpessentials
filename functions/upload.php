<?php
/**
 * Created by PhpStorm.
 * User: itcyb
 * Date: 5/22/2017
 * Time: 10:29 PM
 */

include "upload.inc";

$upload=new Upload();
//$upload->setName("isaac");
$upload->setFile($_FILES['file']);
$upload->setAll();
echo $upload->getSize();
$upload->up();
echo $upload->getMsg();