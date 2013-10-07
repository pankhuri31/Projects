<?php
session_start();
require("res/config.php");
if (!isset($_SESSION['user']))
{
header("Location:index.php");
}
$tables=$_GET['tablename'];
$_SESSION['table']=$tables;
echo "<h3 align=center>" . $tables . '</h3></br>';
$sql = mysql_query( "select * from $tables");

$sql1 = mysql_query("show columns from $tables");
$num = mysql_num_rows($sql1);
echo $num . "<table border=1 align=center><tr>";
while($row1 = mysql_fetch_array($sql1))
{
		echo "<td>" . $row1[0] . " " . '</td>';
}
echo "</tr>";
while($row = mysql_fetch_array($sql))
{
	echo "<tr>";
	for($i=0; $i<$num; $i++)
	{
		echo "<td>" . $row[$i] . " " . "</td>";
	}
	echo "</tr></br>";
}
		echo "</table>";

?>

	