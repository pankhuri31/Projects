<html>

<?php
session_start();
require("res/config.php");
echo "choose department: " . "</br>";
$sql1 = mysql_query("select Name from department");
echo "<form action='emp_dept.php' align=center' method='POST'>";
echo "<select name='dept' style=\"text-align:center; \">";
while($row1 = mysql_fetch_array($sql1))
{
//echo $row1['Name'];
echo "<option value=$row1[Name]>" . $row1[Name] . "</option>" ;
}
echo "</select>";
echo "<input type='submit' value='submit' /></form>";
?>
</html>