<?php
$var =10;
$x = mysql_connect("127.0.0.1","root","");
if(!$x)
{die("ERROR: ".mysql_error());}
mysql_select_db("irrigation enterprise");
session_start();
if (isset($_SESSION['user']))
{
mysql_close($x);
$x = mysql_connect("127.0.0.1","'$_SESSION[user]'","'$_SESSION[pwd]'");
if(!$x)
{die("ERROR: ".mysql_error());}

}
?>
