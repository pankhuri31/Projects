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
$table=$_GET['tablename'];
$_SESSION['table']=$table;
?>
<html>
<head>
<link rel="stylesheet" type="text/css" href="style.css" />
<style>
#h
{
color:white;
font-family:"Comic Sans MS", cursive, sans-serif;
text-transform:capitalize;
}
.heading
{
margin-left:300px;
margin-top:30px;
}
.styl
{
margin-left:400px;
width:200px;
height:30px;
border-radius:20px;
}
</style>
</head>
<body>
<div id="header">
<h1 id="h"><?php echo $_GET['tablename']; ?></h1>
</div>
<?php
if($table == 'employee')
{
echo "<h2 class=\"heading\">Ssn</h2><form action='del_exe.php' method='post' class=\"styl\">";
echo "<select name='Ssn'>";
$sql = mysql_query("select Ssn from employee");
while($row = mysql_fetch_array($sql))
{
echo "<option value='$row[Ssn]'>" . $row[Ssn] . "</option>";
}
}
else if($table == 'customer')
{
echo "<h2 class=\"heading\">Customer_id</h2>";
echo "<form action='del_exe.php' method='post' class=\"styl\">";
echo "<select name='Customer_id'>";
$sql = mysql_query("select Customer_id from customer");
while($row = mysql_fetch_array($sql))
{
echo "<option value='$row[Customer_id]'>" . $row[Customer_id] . "</option>";
}
}
else if($table == 'field')
{
echo "<h2 class=\"heading\">Location</h2>";
echo "<form action='del_exe.php' method='post' class=\"styl\">";
echo "<select name='Location'>";
$sql = mysql_query("select Location from field");
while($row = mysql_fetch_array($sql))
{
echo "<option value='$row[Location]'>" . $row[Location] . "</option>";
}
}
else if($table == 'department')
{
echo "<h2 class=\"heading\">Name</h2>";
echo "<form action='del_exe.php' method='post' class=\"styl\">";
echo "<select name='Name'>";
$sql = mysql_query("select Name from department");
while($row = mysql_fetch_array($sql))
{
echo "<option value='$row[Name]'>" . $row[Name] . "</option>";
}
}


echo "</select><br/><input type='submit' value='submit' id=\"al\" /></form>";



?>
