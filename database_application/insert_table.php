<?php
session_start();
require("res/config.php");
if(isset($_SESSION['user']))
{
$sql=mysql_query("select insert_permission from members where username='$_SESSION[user]'");
$row=mysql_fetch_array($sql);

if($row['insert_permission'] == 0){
//echo "wtf!";
header("Location: index.php");
}
}
if (!isset($_SESSION['user']))
{
header("Location:index.php");
}
?>
<html>
<head>
<title>Irrigation Enterprise</title>
<LINK REL=StyleSheet HREF="style.css" TYPE="text/css" MEDIA=screen>
<style>
#h
{
color:white;
font-family:"Comic Sans MS", cursive, sans-serif;
}
#main
{
margin-left:30px;
font-size:20pt;
margin-top:20px;
line-height:40pt;
}
</style>
</head>
<body>

	<div id="header">
	<h1 id="h">Select table for insert:</h1>
	</div>
<div id="main">
<a href='insert.php?tablename=employee' > Employee </a></br>
<a href='insert.php?tablename=customer' > Customer </a></br>
<a href='insert.php?tablename=field' > Field </a></br>
<a href='insert.php?tablename=resource' > Resource </a></br>
<a href='insert.php?tablename=transport1' > Transport1 </a></br>
<a href='insert.php?tablename=transport2' > Transport2 </a></br>
<a href='insert.php?tablename=manufacturing_company' > Manufacturing Company </a></br>
<a href='insert.php?tablename=provides' > Provides </a></br>
</div>
</body>
