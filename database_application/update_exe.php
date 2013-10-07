<html>
<?php
session_start();
require("res/config.php");
if(isset($_SESSION['user']))
{
$sql=mysql_query("select update_permission from members where username='$_SESSION[user]'");
$row=mysql_fetch_array($sql);
if ($row['update_permission']==0){
header("Location: index.php");
}
}
if (!isset($_SESSION['user']))
{
header("Location:index.php");
}
echo $_SESSION['table'];
$tab = $_SESSION['table'];
$n=count($_POST);
echo $n;
$i=0;
print_r($_POST);
$var="update" . " ".$tab ." "."set"." ";
foreach($_POST as $k => $v)
{
	if($i==0)
	{
		$smthg=$_SESSION['pr'] ."="."'".$v."'";
	}
	if($i!=0)
	{
		if(!empty($v))
		{
			$var .= $k ."="."'".$v."'".", ";
		}
	}
		$i=$i+1;
}
$var=rtrim($var, " ");
$var=rtrim($var,",");
$var .= "where " .$smthg;
$sql=mysql_query($var);
//header("Location:index.php");
?>
</html>
