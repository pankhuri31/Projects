<?php
session_start();
require("res/config.php");
if(isset($_SESSION['user']))
{
$sql=mysql_query("select update_permission from members where username='$_SESSION[user]'");
$row=mysql_fetch_array($sql);
if ($row['update_permission']==0)
header("Location: index.php");
}
if (!isset($_SESSION['user']))
{
header("Location:index.php");
}
?>
<html>
<h3> Select table for update: </h3>
<a href='update.php?tablename=employee' > Employee </a></br>
<a href='update.php?tablename=customer' > Customer </a></br>
<a href='update.php?tablename=field' > Field </a></br>
<a href='update.php?tablename=department' > Department </a></br>
<a href='update.php?tablename=resource' > Resource </a></br>
<a href='update.php?tablename=transport1' > Transport1 </a></br>
<a href='update.php?tablename=transport2' > Transport2 </a></br>
<a href='update.php?tablename=manufacturing_company' > Manufacturing Company </a></br>
<a href='update.php?tablename=provides' > Provides </a></br>
</html>