<?php
session_start();
require("res/config.php");
if(isset($_SESSION['user']))
{
$sql=mysql_query("select insert_permission from members where username='$_SESSION[user]'");
$row=mysql_fetch_array($sql);
if ($row['insert_permission']==0)
header("Location: index.php");
}
if (!isset($_SESSION['user']))
{
header("Location:index.php");
}
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
#al
{
margin-left:650px;
}
.new
{
padding:10px;
	font-size:30px;
	color:white;
	margin-top:-50px;
	font-family:"Comic Sans MS", cursive, sans-serif;
text-align:right;

}
.new>input
{
width:200px;
height:30px;
border-radius:20px;
}
</style>
</head>
<body>
<div id="header">
<h1 id="h">
<?php 
if ($_SESSION['valid']==0)
{
$_SESSION['table']=$_GET['tablename'];
}
echo $_SESSION['table']; 
$tables=$_SESSION['table'];
?>
</h1>
</div>
<a href='insert_table.php'> <h2 style="text-align:right;">Back</h2></a>
<form action='ins_exc.php' method='post'>
<table cellpadding="20" style="margin-left:400px;font-size:20pt;margin-top:5px;">
<?php
//$sql2 = mysql_query("SELECT * FROM $tables WHERE CONSTRAINT_TYPE = 'FOREIGN KEY'");
//$sql2 = mysql_query("SHOW KEYS FROM $tables WHERE Key_name = 'FOREIGN' ");
/*$sql2 = mysql_query("show create table $tables");
if($sql2)
echo ":)";
else echo ":(";
echo mysql_num_rows($sql2);
while($row = mysql_fetch_array($sql2))
{
echo $row[1] . "</br>";
}*/
$sql1 = mysql_query( "show columns from $tables");
$number_of_cols=mysql_num_rows($sql1);
while($row = mysql_fetch_array($sql1))
{
	echo "<tr >";
	echo "<td style=\"text-align:left;text-transform:capitalize;\">" . $row['Field'] . '</td>';
	if($row['Type']=='date'){
	echo "<td class=\"new\"><input type='date' name='$row[Field]' /></td>";
	}
	else if($row['Type'][0]=='c'){
	echo "<td > 
	<input type='radio' name='sex' value='male' checked>" . 'Male' . "</br>
	<input type='radio' name='sex' value='female'>" . 'Female' . "</br></td>";
	}
	else{
	
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
		echo "<td class=\"new\"><input type='text' name='$row[Field]' /></td>";
	}
	echo "</tr>";
}
?>
</table>

<input type='submit' value='submit' id="al"/>
<?php
if ($_SESSION['valid']==-1)
{
$_SESSION['valid']=0;
echo "<h2>Fill in all the fields</h2>";
}
?>
</form>

</body>
</html>
