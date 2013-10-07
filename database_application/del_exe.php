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
$tab = $_SESSION['table'];
if($tab == 'employee')
{
if(mysql_query("delete from employee where Ssn=$_POST[Ssn]"))
{
	
	echo '<script type="text/javascript">
	alert("Record deleted successfully!");
	history.back();
	</script>';
}
}
else if($tab == 'customer')
{
if(mysql_query("delete from customer where Customer_id=$_POST[Customer_id]"))
{
	
	echo '<script type="text/javascript">
	alert("Record deleted successfully!");
	history.back();
	</script>';
}
}
else if($tab == 'department')
{

if(mysql_query("delete from department where Name='$_POST[Name]'"))
{
	
	echo '<script type="text/javascript">
	alert("Record deleted successfully!");
	history.back();
	</script>';
}
else 
echo "error";
}
else if($tab == 'field')
{
if(mysql_query("delete from field where Location='$_POST[Location]'"))
{
	
	echo '<script type="text/javascript">
	alert("Record deleted successfully!");
	history.back();
	</script>';
}
}
//header("Location:index.php");
?>