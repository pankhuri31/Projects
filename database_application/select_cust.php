<html>

<?php
session_start();
require("res/config.php");
echo "choose customer id: " . "</br>";
$sql1 = mysql_query("select distinct Cust_num from field");
echo "<form action='field_cust.php' align=center' method='POST'>";
echo "<select name='id' style=\"text-align:center; \">";
while($row1 = mysql_fetch_array($sql1))
{
//echo $row1['Name'];
echo "<option value=$row1[Cust_num]>" . $row1[Cust_num] . "</option>" ;
}
echo "</select>";
echo "<input type='submit' value='submit' /></form>";
?>
</html>