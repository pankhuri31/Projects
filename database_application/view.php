<?php
session_start();
require("res/config.php");
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
margin-top:15px;
line-height:40pt;
}
</style>
</head>
<body>

	<div id="header">
	<h1 id="h">Select table to view:</h1>
	</div>
<div id="main">
<a href='view_table.php?tablename=employee' > Employee </a></br>
<a href='view_table.php?tablename=department' > Department </a></br>
<a href='view_table.php?tablename=customer' > Customer </a></br>
<a href='view_table.php?tablename=field' > Field </a></br>
<a href='view_table.php?tablename=has' > Has </a></br>
<a href='view_table.php?tablename=resource' > Resource </a></br>
<a href='view_table.php?tablename=transport1' > Transport1 </a></br>
<a href='view_table.php?tablename=transport2' > Transport2 </a></br>
<a href='view_table.php?tablename=manufacturing_company' > Manufacturing Company </a></br>
<a href='view_table.php?tablename=provides' > Provides </a></br>
</div>
</body>
</html>