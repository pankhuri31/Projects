<?php
session_start();
require("res/config.php");


$sql = mysql_query("select * from employee where D_name='$_POST[dept]' ");
$sql1 = mysql_query("show columns from employee");
$num = mysql_num_rows($sql1);
echo "<table border=1 align=center><tr>";
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

