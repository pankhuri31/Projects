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
$tables=$_GET['tablename'];
$_SESSION['table']=$tables;

$sql1 = mysql_query( "show columns from $tables");
$number_of_cols=mysql_num_rows($sql1);
echo "<form action='update_exe.php' method='post'><table align=center>";

$sql2 = mysql_query("SHOW KEYS FROM $tables WHERE Key_name = 'PRIMARY' ");
$row = mysql_fetch_array($sql2);
echo "<tr><td>";
echo  $row['Column_name'];

$sql = mysql_query("select $row[Column_name] from $tables");
$key1=$row['Column_name'];
$_SESSION['pr']=$key1;
//echo $_SESSION['pr'];
echo "</td>";
echo "<td><select name='key' style=\"text-align:center;\">";
while($row1 = mysql_fetch_array($sql))
{
echo "<option value=$row1[$key1]>" . $row1[$key1] . "</option>" ;
}
echo "</select></td></tr>";
echo "<tr><td><h3 align=center>Fill in all the details: </h3></td></tr>"; 
while($row = mysql_fetch_array($sql1))
{
	echo "<tr>";
	echo "<td>" ." ". $row['Field'] . "</td>";
	if($row['Type']=='date'){
	echo "<td><input type='date' name='$row[Field]' /></td>";
	}
	else if($row['Type'][0]=='c'){
	echo "<td> 
	<input type='radio' name='sex' value='male' checked>" . 'Male' . "</br>
	<input type='radio' name='sex' value='female'>" . 'Female' . "</br></td>";
	}
	else
	{
		if( $tables == 'employee' and $row['Field'] == 'D_name')
		{
			echo "<td><select name='D_name'>";
			$sql = mysql_query("select Name from department");
			while($row = mysql_fetch_array($sql))
			echo "<option value='$row[Name]'>" . $row[Name] . "</option>";
			echo "</select></td>";
		}
		else if( $tables == 'employee' and $row['Field'] == 'Office_name')
		{
			echo "<td><select name='Office_name'>";
			$sql = mysql_query("select Name from Office1");
			while($row = mysql_fetch_array($sql))
			echo "<option value='$row[Name]'>" . $row[Name] . "</option>";
			echo "</select></td>";
		}
		else if($tables == 'field' and $row['Field'] == 'Cust_num')
		{
			echo "<td><select name='Cust_num'>";
			$sql = mysql_query("select Customer_id from customer");
			while($row = mysql_fetch_array($sql))
			echo "<option value='$row[Customer_id]'>" . $row[Customer_id] . "</option>";
			echo "</select></td>";
		}
		else if($tables == 'manufacturing_company' and $row['Field'] == 'Office_name')
		{
			echo "<td><select name='Office_name'>";
			$sql = mysql_query("select Name from Office1");
			while($row = mysql_fetch_array($sql))
			echo "<option value='$row[Name]'>" . $row[Name] . "</option>";
			echo "</select></td>";
		}
		else if( $tables == 'provides' and $row['Field'] == 'Essn')
		{
			echo "<td><select name='Essn'>";
			$sql = mysql_query("select Ssn from employee");
			while($row = mysql_fetch_array($sql))
			echo "<option value='$row[Ssn]'>" . $row[Ssn] . "</option>";
			echo "</select></td>";
		}
		else
		echo "<td><input type='text' name='$row[Field]' /></td>";
	}
	echo "</tr>";
}

echo "<tr><td><input type='submit' value='submit' /></td></tr>";

echo "</table></form>";
?>