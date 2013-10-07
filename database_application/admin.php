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

$sql = mysql_query("select username from members where type=0");
echo "<form action='admin_exe.php' method='post'><table align=center>";

echo "<tr><td><select name='usr' style=\"text-align:center;\">";
while($row = mysql_fetch_array($sql))
{
echo "<option value='$row[username]'>" . $row['username'] . "</option>" ;
}
echo "</select></td></tr>";
echo "<tr><td><input type='checkbox' name='insert' value='insert' />Grant Insert</td>";
echo "<td><input type='checkbox' name='delete' value='delete' />Grant Delete</td>";
echo "<td><input type='checkbox' name='update' value='update' />Grant Update</td></tr>";
echo "<tr><td><input type='submit' value='submit' /></td></tr></table></form>";

?>
