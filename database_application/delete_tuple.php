<?php
session_start();
require("res/config.php");
if(isset($_SESSION['user']))
{
$sql=mysql_query("select delete_permission from members where username='$_SESSION[user]'");
$row=mysql_fetch_array($sql);
if ($row['delete_permission']==0)
header("Location: index.php");
}
if (!isset($_SESSION['user']))
{
header("Location:index.php");
}
?>
<html>
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
	<h1 id="h">Select table for delete:</h1>
	</div>
<div id="main">
<a href='delete.php?tablename=employee' > Employee </a></br>
<a href='delete.php?tablename=customer' > Customer </a></br>
<a href='delete.php?tablename=field' > Field </a></br>
<a href='delete.php?tablename=department' > Department </a></br>
</div>
</body>
</html>