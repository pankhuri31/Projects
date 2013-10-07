<?php
session_start();
require("res/config.php");
if(isset($_SESSION['user'])){
$sql=mysql_query("select type from members where username='$_SESSION[user]'");
$row=mysql_fetch_array($sql);
}
if (!isset($_SESSION['user']) or $row['type']==0){
header("Location: index.php");
}

if(isset($_POST['insert']))
mysql_query("update members set insert_permission=1 where username='$_POST[usr]'");

if(isset($_POST['delete']))
mysql_query("update members set delete_permission=1 where username='$_POST[usr]'");

if(isset($_POST['update']))
mysql_query("update members set update_permission=1 where username='$_POST[usr]'");

mysql_query("update members set type=1 where insert_permission=1 and delete_permission=1 and update_permission=1");

?>


